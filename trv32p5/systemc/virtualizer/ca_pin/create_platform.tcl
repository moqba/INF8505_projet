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

proc createPlatform { xml } {
  set HW /HARDWARE

  ::pct::new_project

  ::pct::open_library ${xml}
  ::pct::copy_block_to_system_library trv32p5_sc:trv32p5_sc
  ::pct::close_library trv32p5_sc

  ::pct::open_library GenericIPlib

  # Clock/Reset
  ::pct::create_instance GenericIPlib:ClockGenerator $HW i_ClockGenerator GIPL_CLK "GIPL_CLK(period, period_unit, duty_cycle, start_time, start_time_unit, posedge_first)"
  ::pct::set_param_value i_ClockGenerator "Constructor Arguments" period 10

  ::pct::create_instance GenericIPlib:ResetGenerator $HW i_ResetGenerator GIPL_RST "GIPL_RST(active_level, start_time, start_time_unit, duration, duration_unit)"
  ::pct::set_param_value i_ResetGenerator "Constructor Arguments" start_time 0
  ::pct::set_param_value i_ResetGenerator "Constructor Arguments" duration 100

  # Cores
  ::pct::create_instance SYSTEM_LIBRARY:trv32p5_sc $HW i_trv32p5
  ::pct::set_param_value i_trv32p5 {Extra properties} /modellib $::nmldir
  ::pct::global_connect i_ClockGenerator/CLK i_trv32p5/clock
  ::pct::global_connect i_ResetGenerator/RST i_trv32p5/reset

  # Memories
  ::pct::add_to_systemc_include_path $::env(CHESSDIR)/
  ::pct::add_to_systemc_include_path $::env(CHESSDIR)/checkersdir/include/
  ::pct::load_all_modules --set-category pin_memories.h
  ::pct::set_block_port_protocol --set-category SYSTEM_LIBRARY:DataMemory/clock SYSTEM_LIBRARY:CLOCK
  ::pct::create_instance SYSTEM_LIBRARY:DataMemory $HW i_eDM DataMemory DataMemory()
  ::pct::set_param_value i_eDM {Template Arguments} lanes 4
  ::pct::set_param_value i_eDM {Template Arguments} lane_nbits 8

  # connect all the instances created in the system

  ::pct::global_connect i_ClockGenerator/CLK i_eDM/clock
  ::pct::global_connect i_trv32p5/edm_rd i_eDM/q
  ::pct::global_connect i_trv32p5/edm_addr i_eDM/a
  ::pct::global_connect i_trv32p5/ld_edm i_eDM/ld
  ::pct::global_connect i_trv32p5/edm_wr i_eDM/d
  ::pct::global_connect i_trv32p5/st_edm i_eDM/st

  ::pct::set_main_configuration default {
  {
  #include "trv32p5_converter_sc_impl.h"
  #include "ChkrsDebugAdapter.h"
  } {}
  {
    trv32p5_converter_sc_impl<DataMemory<4,8>> sctb(&(HARDWARE->i_eDM));
    (HARDWARE->i_trv32p5).set_sc_converter((trv32p5_converter_sc*)&sctb);
  }
  {} {}}

  # Export
  ::pct::create_simulation_build_project export
  ::pct::set_simulation_build_project_setting Debug "Main Configuration" default
  ::pct::set_simulation_build_project_setting Debug "Optimize Level" "Optimize most (-O3)"
  ::pct::set_simulation_build_project_setting Debug "Backdoor Mode" true
  ::pct::set_simulation_build_project_setting Debug "Fast Linking" false
  ::pct::export_simulation
}

createPlatform trv32p5_sc_systemc.xml
