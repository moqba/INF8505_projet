#############################################################################
# Copyright 1996-2021 Synopsys, Inc.                                        #
#                                                                           #
# This Synopsys software and all associated documentation are proprietary   #
# to Synopsys, Inc. and may only be used pursuant to the terms and          #
# conditions of a written license agreement with Synopsys, Inc.             #
# All other use, reproduction, modification, or distribution of the         #
# Synopsys software or the associated documentation is strictly prohibited. #
#############################################################################

namespace eval ::example_arm_dlx {

proc initialize { } {

    ::pct::new_project

    ::pct::open_library SBLTLM2FT_BL
    ::pct::open_library AMBA_TLM2_BL
    ::pct::open_library AMBA_TLM2_GENERIC_LIBRARY
    ::pct::open_library ARM_CORTEX_A5_TLM2_LT_PSP
    ::pct::open_library GenericIPlib
    ::pct::open_library ../../common/dlx_tlm2_lt/dlx_ia_tlm2_systemc.xml
}

proc create_system { } {

    ::pct::create_instance AMBA_TLM2_GENERIC_LIBRARY:basic_clock /HARDWARE CLOCK
    ::pct::set_bounds /HARDWARE/CLOCK 50 50 100 100

    ::pct::create_instance AMBA_TLM2_GENERIC_LIBRARY:basic_reset /HARDWARE RESET
    ::pct::set_bounds /HARDWARE/RESET 50 200 100 100

    ::pct::create_instance ARM_CORTEX_A5_TLM2_LT_PSP:ARM_FM_CORTEX_A5UP /HARDWARE ARM0
    ::pct::set_bounds /HARDWARE/ARM0 350 50 100 400

    ::pct::create_instance dlx_sc:dlx_sc /HARDWARE DLX
    ::pct::set_param_value DLX {Extra properties} /modellib ../../../../../lib

    ::pct::instantiate_bl_framework /HARDWARE AXI
    ::pct::set_bounds /HARDWARE/AXI 600 50 26 400

    ::pct::instantiate_block GenericIPlib:Memory_Generic         /HARDWARE RAM
    ::pct::set_bounds /HARDWARE/RAM 800 0 100 100
    ::pct::set_param_value /HARDWARE/RAM/MEM:protocol "Protocol Common Parameters" address_width 29
    ::pct::set_param_value /HARDWARE/RAM "Template Arguments" BUSWIDTH "64"

    ::pct::global_connect /HARDWARE/CLOCK/p_clock /HARDWARE/ARM0/CLKIN
    ::pct::global_connect /HARDWARE/CLOCK/p_clock /HARDWARE/AXI/Clk
    ::pct::global_connect /HARDWARE/CLOCK/p_clock /HARDWARE/RAM/CLK
    ::pct::global_connect /HARDWARE/CLOCK/p_clock /HARDWARE/DLX/clock

    ::pct::global_connect /HARDWARE/RESET/p_reset /HARDWARE/ARM0/nCPURESET
    ::pct::global_connect /HARDWARE/RESET/p_reset /HARDWARE/AXI/Rst
    ::pct::global_connect /HARDWARE/RESET/p_reset /HARDWARE/DLX/reset

    ::pct::set_param_value /HARDWARE/RESET {Constructor Arguments} start_time -1
    ::pct::set_param_value /HARDWARE/RESET {Constructor Arguments} duration 100
    ::pct::set_param_value /HARDWARE/RESET {Constructor Arguments} duration_unit SC_US

    ::pct::create_connection C1 /HARDWARE/ARM0/AXIM0 /HARDWARE/AXI
    ::pct::create_connection C2 /HARDWARE /HARDWARE/AXI /HARDWARE/RAM/MEM
    ::pct::create_connection C3 /HARDWARE/DLX/p_DMb     /HARDWARE/AXI


    ::pct::set_address /HARDWARE/ARM0/AXIM0:/HARDWARE/RAM/MEM   0x00000000
    ::pct::set_address /HARDWARE/DLX/p_DMb:/HARDWARE/RAM/MEM    0x00000000
    ::BLWizard::generateFramework /HARDWARE/AXI SBLTLM2FT  * { \
								{C1_s AMBA_TLM2_BL:amba_pv_to_ft_bridge} \
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
    ::pct::set_param_value /HARDWARE/ARM0 {Extra properties} /config/cpu0/semihosting/enable "true"
    ::pct::set_param_value /HARDWARE/ARM0 {Extra properties} /ImageInfo/initial_image "../../software/prod.axf"
    ::pct::set_param_value DLX {Extra properties} /ImageInfo/initial_image "../../../common/software/Release/cons"

}

proc configure_build_project { export_dir { export_type "DYNAMIC NETLIST" } { backdoor true } } {

    ::pct::create_simulation_build_project $export_dir
    ::pct::set_simulation_build_project_setting Debug {Export Type} $export_type
    ::pct::set_simulation_build_project_setting Debug {Backdoor Mode} $backdoor
    ::pct::set_simulation_build_project_setting Debug {sc_main Arguments} --cwr_wait

}

}

set script_root_dir [file normalize [file dirname [info script]]]
::example_arm_dlx::initialize
::example_arm_dlx::create_system
::example_arm_dlx::configure_software
::example_arm_dlx::configure_build_project [pwd]/export
::pct::export_simulation

