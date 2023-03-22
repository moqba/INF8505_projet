namespace eval ::example_arc_dlx {

proc initialize { } {

    ::pct::new_project

    ::pct::open_library SBLTLM2FT_BL
    ::pct::open_library GenericIPlib
    ::pct::open_library TLM2_PL
    ::pct::open_library ../../common/dlx_tlm2_lt/dlx_ia_tlm2_systemc.xml
    # location where ARC PSP was installed. See setup.csh for more info
    set ARC_PSP_INSTALL "../../../../../"
    ::pct::open_library "$ARC_PSP_INSTALL/IP/ARC/ARC_NSIM_TLM2_LT_Model/Tool/PCT/ARC_NSIM_TLM2_LT_Model.xml"
    ::pct::open_library "$ARC_PSP_INSTALL/lib/arc_protocols.xml"
}

proc create_system { } {

    ::pct::create_instance GenericIPlib:ClockGenerator /HARDWARE i_ClockGenerator GIPL_CLK {GIPL_CLK(period, period_unit, duty_cycle, start_time, start_time_unit, posedge_first)}
    ::pct::create_instance GenericIPlib:ResetGenerator /HARDWARE i_ResetGenerator GIPL_RST {GIPL_RST(active_level, start_time, start_time_unit, duration, duration_unit)}
    ::pct::set_param_value i_ResetGenerator {Scml Properties} active_at_start true
    ::pct::set_param_value i_ResetGenerator {Constructor Arguments} active_level true
    ::pct::set_param_value i_ResetGenerator {Constructor Arguments} start_time 0
    ::pct::set_param_value i_ResetGenerator {Constructor Arguments} duration 1

    ::pct::create_instance ARC_NSIM_TLM2_LT_Model:ARC_NSIM_TLM2_LT_Model /HARDWARE ARC
    ::pct::set_param_value ARC {Extra properties} /ARC/core_configuration custom
    ::pct::set_param_value ARC {Extra properties} /ARC/tools_configuration_file $::env(METAWARE_ROOT)/arc/tcf/hs48_full.tcf
    ::pct::set_param_value ARC {Scml Properties} /model_config/nsim_properties_file ../../nsim0.prop
    ::pct::set_param_value ARC {Scml Properties} /model_config/halt_on_reset true
    ::pct::set_param_value ARC {Scml Properties} /model_config/irq_polarity active_high

    ::pct::create_instance dlx_sc:dlx_sc /HARDWARE DLX
    ::pct::set_param_value DLX {Extra properties} /modellib ../../../../../lib

    ::pct::instantiate_bl_framework /HARDWARE AXI

    ::pct::instantiate_block GenericIPlib:Memory_Generic         /HARDWARE RAM
    ::pct::set_param_value /HARDWARE/RAM/MEM:protocol "Protocol Common Parameters" address_width 32
    ::pct::set_param_value /HARDWARE/RAM "Template Arguments" BUSWIDTH 32
    ::pct::set_target_location_size RAM/MEM:m_memory 0x100000000

    ::pct::set_param_value  GenericIPlib:Inverter/IN  {Port Properties} Category Reset
    ::pct::set_param_value  GenericIPlib:Inverter/OUT  {Port Properties} Category Reset
    ::pct::instantiate_block GenericIPlib:Inverter         /HARDWARE INV

    #connect all the instances created in the system
    ::pct::create_connection C1 /HARDWARE/ARC/initiator_socket /HARDWARE/AXI
    ::pct::create_connection C2 /HARDWARE /HARDWARE/AXI /HARDWARE/RAM/MEM
    ::pct::create_connection C3 /HARDWARE/DLX/p_DMb     /HARDWARE/AXI
    ::pct::create_connection C4 /HARDWARE /HARDWARE/i_ClockGenerator/CLK RAM/CLK /HARDWARE/DLX/clock /HARDWARE/AXI/Clk
    ::pct::create_connection C5 /HARDWARE /HARDWARE/i_ResetGenerator/RST /HARDWARE/ARC/rst_a /HARDWARE/AXI/Rst /HARDWARE/INV/IN
    ::pct::create_connection C6 /HARDWARE /HARDWARE/INV/OUT /HARDWARE/DLX/reset
    ::pct::set_stub_block /HARDWARE/ARC/target_socket TLM2TargetSocketStub

    ::pct::set_address /HARDWARE/ARC/initiator_socket:/HARDWARE/RAM/MEM   0x00000000
    ::pct::set_address /HARDWARE/DLX/p_DMb:/HARDWARE/RAM/MEM    0x00000000
    ::BLWizard::generateFramework /HARDWARE/AXI SBLTLM2FT  * { \
								{C1_s __EMPTY__} \
								{C2_m __EMPTY__} \
								{C3_s __EMPTY__} \
								} \
								{ \
								common_configuration:BackBone:/advanced/num_resources_per_target:1 \
								master_ports:BB_C2_m:/Domains/clock:Clk \
								slave_ports:BB_C1_s:/Domains/clock:Clk \
								slave_ports:BB_C1_s:priority:0 \
								slave_ports:BB_C3_s:/Domains/clock:Clk \
								slave_ports:BB_C3_s:priority:1 \
								}
}

proc configure_software { } {

    ::pct::set_parameter_configuration Default
    ::pct::set_param_value DLX {Extra properties} /ImageInfo/initial_image "../../../common/software/Release/cons"
    ::pct::set_param_value ARC {Extra properties} /ImageInfo/ImageLoaderIPT "../../software/prod.elf"

}

proc configure_build_project { export_dir { export_type "DYNAMIC NETLIST" } { backdoor true } } {

    ::pct::create_simulation_build_project $export_dir
    ::pct::set_simulation_build_project_setting Debug {Export Type} $export_type
    ::pct::set_simulation_build_project_setting Debug {Backdoor Mode} $backdoor
    ::pct::set_simulation_build_project_setting Debug {sc_main Arguments} --cwr_wait

}

}

set script_root_dir [file normalize [file dirname [info script]]]
::example_arc_dlx::initialize
::example_arc_dlx::create_system
::example_arc_dlx::configure_software
::example_arc_dlx::configure_build_project [pwd]/export
::pct::export_simulation

