set ::scriptdir [file dirname [file normalize [info script]]]
proc createPlatform { xml } {
  ::pct::new_project

  ::pct::open_library ${xml}
  ::pct::copy_block_to_system_library trv32p3_sc:trv32p3_sc
  ::pct::close_library trv32p3_sc

  ::pct::open_library $::env(COWAREHOME)/../../IP/GenericIPlib/ConvergenSC/GenericIPlib.xml
  ::pct::copy_block_to_system_library GenericIPlib:ClockGenerator
  ::pct::copy_block_to_system_library GenericIPlib:ResetGenerator
  ::pct::close_library GenericIPlib

  ::pct::load_all_modules --set-category PinMemories.h
  ::pct::set_block_port_protocol --set-category SYSTEM_LIBRARY:PMType/clock SYSTEM_LIBRARY:CLOCK
  ::pct::set_block_port_protocol --set-category SYSTEM_LIBRARY:DMBankType/clock SYSTEM_LIBRARY:CLOCK
  ::pct::create_instance SYSTEM_LIBRARY:PMType /HARDWARE i_PMb PMType PMType()
  ::pct::create_instance SYSTEM_LIBRARY:DMBankType /HARDWARE i_DMb DMBankType DMBankType()

  # Clock/Reset
  ::pct::create_instance SYSTEM_LIBRARY:ClockGenerator /HARDWARE i_ClockGenerator GIPL_CLK "GIPL_CLK(period, period_unit, duty_cycle, start_time, start_time_unit, posedge_first)"
  ::pct::set_param_value i_ClockGenerator "Constructor Arguments" period 100

  ::pct::create_instance SYSTEM_LIBRARY:ResetGenerator /HARDWARE i_ResetGenerator GIPL_RST "GIPL_RST(active_level, start_time, start_time_unit, duration, duration_unit)"
  ::pct::set_param_value i_ResetGenerator "Constructor Arguments" start_time 0
  ::pct::set_param_value i_ResetGenerator "Constructor Arguments" duration 10

  # Cores
  ::pct::create_instance SYSTEM_LIBRARY:trv32p3_sc /HARDWARE i_trv32p3
  ::pct::set_param_value i_trv32p3 {Extra properties} /modellib [file normalize [file join $::scriptdir ../../lib]]
  ::pct::global_connect i_ClockGenerator/CLK i_trv32p3/clock
  ::pct::global_connect i_ResetGenerator/RST i_trv32p3/reset

  # connect all the instances created in the system

  ::pct::global_connect i_ClockGenerator/CLK i_DMb/clock
  ::pct::global_connect i_trv32p3/edm_rd i_DMb/q
  ::pct::global_connect i_trv32p3/edm_addr i_DMb/a
  ::pct::global_connect i_trv32p3/ld_edm i_DMb/ld
  ::pct::global_connect i_trv32p3/edm_wr i_DMb/d
  ::pct::global_connect i_trv32p3/st_edm i_DMb/st

  ::pct::global_connect i_ClockGenerator/CLK i_PMb/clock
  ::pct::global_connect i_trv32p3/epm_addr i_PMb/a
  ::pct::global_connect i_trv32p3/epm_rd i_PMb/q
  ::pct::global_connect i_trv32p3/ld_epm i_PMb/ld

  ::pct::set_main_configuration default {
  {
  #include "trv32p3_sc_testbench_impl.h"
  #include "ChkrsDebugAdapter.h"
  } {}
  {
    trv32p3_testbench_sc_impl sctb(&(HARDWARE->i_DMb), &(HARDWARE->i_PMb));
    (HARDWARE->i_trv32p3).set_sc_testbench((trv32p3_testbench_sc*)&sctb);
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

createPlatform trv32p3_sc_systemc.xml
