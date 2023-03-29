#
# Copyright (c) 2020-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

set ::nmldir [file normalize [file join [file dirname [file normalize [info script]]] .. .. .. lib]]

proc get_mem_sizes {define_h} {
  set db [dict create ePM 23 eDM 23]
  if {[catch {set fp [open $define_h r]} msg]} {
    puts stderr "ERROR: Could not open file $define_h: $msg"
  } else {

    set filedata [read $fp]
    close $fp

    set pat {^\#define \s+ MEM_(\w+)_SZ_NBIT \s+ (.+) (?: // .*)? $}
    foreach {- mem sz} [regexp -line -all -inline -expanded $pat $filedata] {
      dict set db $mem [expr $sz]
    }
  }

  return [list [dict get $db ePM] [dict get $db eDM]]
}

proc createPlatform { xml } {
  set HW /HARDWARE

  ::pct::new_project

  ::pct::open_library ${xml}
  ::pct::copy_block_to_system_library trv32p5_sc:trv32p5_sc
  ::pct::close_library trv32p5_sc

  ::pct::open_library GenericIPlib
  ::pct::open_library SBLTLM2FT_BL

  # Clock/Reset
  ::pct::create_instance GenericIPlib:ClockGenerator $HW i_ClockGenerator GIPL_CLK "GIPL_CLK(period, period_unit, duty_cycle, start_time, start_time_unit, posedge_first)"
  ::pct::set_param_value i_ClockGenerator "Constructor Arguments" period 10

  ::pct::create_instance GenericIPlib:ResetGenerator $HW i_ResetGenerator GIPL_RST "GIPL_RST(active_level, start_time, start_time_unit, duration, duration_unit)"
  ::pct::set_param_value i_ResetGenerator "Constructor Arguments" start_time 0
  ::pct::set_param_value i_ResetGenerator "Constructor Arguments" duration 100

  # Cores
  ::pct::create_instance SYSTEM_LIBRARY:trv32p5_sc $HW i_trv32p5
  ::pct::set_param_value i_trv32p5 {Extra properties} /modellib $::nmldir
  ::pct::add_initiator i_trv32p5/p_eDM
  ::pct::global_connect i_ClockGenerator/CLK i_trv32p5/clock
  ::pct::global_connect i_ResetGenerator/RST i_trv32p5/reset

  # get memsizes from lib/trv32p5_define.h
  lassign [get_mem_sizes [file join $::nmldir trv32p5_define.h]] ePM_sz_nbit eDM_sz_nbit

  # DM
  ::pct::create_instance GenericIPlib:Memory_Generic $HW i_eDM
  ::pct::set_param_value i_eDM/MEM:protocol "Protocol Common Parameters" address_width 32
  ::pct::set_param_value i_eDM {Template Arguments} BUSWIDTH 32
  ::pct::set_target_location_size i_eDM/MEM:m_memory [expr (2**($eDM_sz_nbit))]
  ::pct::set_param_value i_eDM {Scml Properties} /timing/read/cmd_accept_cycles 2
  ::pct::set_param_value i_eDM {Scml Properties} /timing/write/cmd_accept_cycles 3
  ::pct::add_target i_eDM/MEM
  ::pct::global_connect i_ClockGenerator/CLK i_eDM/CLK

  #bus
  ::pct::instantiate_bl_framework $HW BUS
  ::pct::global_connect i_ClockGenerator/CLK $HW/BUS/Clk
  ::pct::global_connect i_ResetGenerator/RST $HW/BUS/Rst

  ::pct::create_connection C_DM_BUS $HW/i_trv32p5/p_eDM $HW/BUS/i_trv32p5_p_eDM
  ::pct::create_connection C_BUS_EDM $HW/BUS/i_eDM_MEM $HW/i_eDM/MEM

  # Memory map
  foreach initiator [::pct::list_initiators] {
    foreach target [::pct::list_targets] {
      ::pct::remove_links ${initiator}:${target}
      ::pct::set_address ${initiator}:${target} unreachable
    }
  }

  ::pct::set_address i_trv32p5/p_eDM:i_eDM/MEM 0x0

  # Bus Generation parameters
  set coreclk Clk
  set memclk Clk
  set busWidth 32
  set arbitration_delay 0
  set paramSetInfo ""

  # Create the list of arguments for '::BLWizard::generateFramework' command
  lappend paramSetInfo "common_configuration:BackBone:/basic/protocol:TLM2_GP"
  lappend paramSetInfo "common_configuration:BackBone:/basic/BUSWIDTH:$busWidth"
  lappend paramSetInfo "common_configuration:BackBone:/timing_parameters/arbitration_delay:${arbitration_delay}"
  lappend paramSetInfo "master_ports:BB_i_eDM_MEM:/Domains/clock:$memclk"
  lappend paramSetInfo "slave_ports:BB_i_trv32p5_p_eDM:/Domains/clock:$coreclk"
  lappend paramSetInfo "slave_ports:BB_i_trv32p5_p_eDM:priority:1"


  # Generate Bus Framework
  ::BLWizard::generateFramework $HW/BUS SBLTLM2FT  * { } $paramSetInfo

  # Export
  ::pct::create_simulation_build_project export
  ::pct::set_simulation_build_project_setting Debug "Optimize Level" "Optimize most (-O3)"
  ::pct::set_simulation_build_project_setting Debug "Backdoor Mode" true
  ::pct::set_simulation_build_project_setting Debug "Fast Linking" false
  ::pct::export_simulation
}
createPlatform trv32p5_sc_systemc.xml
