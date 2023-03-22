set ::scriptdir [file dirname [file normalize [info script]]]
proc createPlatform { xml } {
  ::pct::new_project

  ::pct::open_library ${xml}
  ::pct::copy_block_to_system_library trv32p3_sc:trv32p3_sc
  ::pct::close_library trv32p3_sc

  ::pct::open_library $::env(COWAREHOME)/../../IP/GenericIPlib/ConvergenSC/GenericIPlib.xml
  ::pct::copy_block_to_system_library GenericIPlib:ClockGenerator
  ::pct::copy_block_to_system_library GenericIPlib:ResetGenerator
  ::pct::copy_block_to_system_library GenericIPlib:Memory_Generic
  ::pct::close_library GenericIPlib

  # Clock/Reset
  ::pct::create_instance SYSTEM_LIBRARY:ClockGenerator /HARDWARE i_ClockGenerator GIPL_CLK "GIPL_CLK(period, period_unit, duty_cycle, start_time, start_time_unit, posedge_first)"
  ::pct::set_param_value i_ClockGenerator "Constructor Arguments" period 100

  ::pct::create_instance SYSTEM_LIBRARY:ResetGenerator /HARDWARE i_ResetGenerator GIPL_RST "GIPL_RST(active_level, start_time, start_time_unit, duration, duration_unit)"
  ::pct::set_param_value i_ResetGenerator "Constructor Arguments" start_time 0
  ::pct::set_param_value i_ResetGenerator "Constructor Arguments" duration 10

  # Cores
  ::pct::create_instance SYSTEM_LIBRARY:trv32p3_sc /HARDWARE i_trv32p3
  ::pct::set_param_value i_trv32p3 {Extra properties} /modellib [file normalize [file join $::scriptdir ../../lib]]
  ::pct::add_initiator i_trv32p3/p_ePM
  ::pct::add_initiator i_trv32p3/p_eDM
  ::pct::global_connect i_ClockGenerator/CLK i_trv32p3/clock
  ::pct::global_connect i_ResetGenerator/RST i_trv32p3/reset

  # Memories
  ::pct::create_instance SYSTEM_LIBRARY:Memory_Generic /HARDWARE i_PMb
  ::pct::set_param_value i_PMb/MEM:protocol "Protocol Common Parameters" address_width 32
  ::pct::set_param_value i_PMb {Template Arguments} BUSWIDTH 32
  ::pct::set_target_location_size i_PMb/MEM:m_memory 262144
  ::pct::add_target i_PMb/MEM

  ::pct::create_instance SYSTEM_LIBRARY:Memory_Generic /HARDWARE i_DMb
  ::pct::set_param_value i_DMb/MEM:protocol "Protocol Common Parameters" address_width 32
  ::pct::set_param_value i_DMb {Template Arguments} BUSWIDTH 32
  ::pct::set_target_location_size i_DMb/MEM:m_memory 8388608
  ::pct::add_target i_DMb/MEM

  ::pct::create_connection C_PM i_trv32p3/p_ePM i_PMb/MEM
  ::pct::global_connect i_ClockGenerator/CLK i_PMb/CLK
  ::pct::create_connection C_DM i_trv32p3/p_eDM i_DMb/MEM
  ::pct::global_connect i_ClockGenerator/CLK i_DMb/CLK


  # Memory map
  foreach initiator [::pct::list_initiators] {
    foreach target [::pct::list_targets] {
      ::pct::remove_links ${initiator}:${target}
      ::pct::set_address ${initiator}:${target} unreachable
    }
  }

  ::pct::set_address i_trv32p3/p_ePM:i_PMb/MEM 0x0
  ::pct::set_address i_trv32p3/p_eDM:i_DMb/MEM 0x0

  # Export
  ::pct::create_simulation_build_project export
  ::pct::set_simulation_build_project_setting Debug "Optimize Level" "Optimize most (-O3)"
  ::pct::set_simulation_build_project_setting Debug "Backdoor Mode" true
  ::pct::set_simulation_build_project_setting Debug "Fast Linking" false
  ::pct::export_simulation
}
createPlatform trv32p3_sc_systemc.xml
