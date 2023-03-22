#############################################################################
# Copyright 1996-2018 Synopsys, Inc.                                        #
#                                                                           #
# This Synopsys software and all assoccated documentation are proprietary   #
# to Synopsys, Inc. and may only be used pursuant to the terms and          #
# conditions of a written license agreement with Synopsys, Inc.             #
# All other use, reproduction, modification, or distribution of the         #
# Synopsys software or the assoccated documentation is strictly prohibited. #
#############################################################################
set ::scriptdir [file dirname [file normalize [info script]]]
#create a new PCT procject
::pct::new_project 

#open the required libraries for the platform. one or more component from the libraries are used in project
::pct::open_library "GenericIPlib"
::pct::open_library "SBLTLM2FT_BL"
::pct::open_library ../dlx_ia_tlm2_systemc.xml
::pct::copy_block_to_system_library dlx_sc:dlx_sc
::pct::close_library dlx_sc

#create a new dlx_sc instance
::pct::create_instance SYSTEM_LIBRARY:dlx_sc /HARDWARE i_dlx
::pct::set_param_value i_dlx {Extra properties} /modellib $::scriptdir/../../../lib  

#instantiating the memory
::pct::create_instance GenericIPlib:Memory_Generic /HARDWARE i_DM
::pct::set_param_value i_DM/MEM:protocol "Protocol Common Parameters" address_width 32
::pct::set_param_value i_DM {Template Arguments} BUSWIDTH 8
::pct::set_target_location_size i_DM/MEM:m_memory 0x100000


#create new clock and reset generator instances
::pct::create_instance GenericIPlib:ClockGenerator /HARDWARE i_ClockGenerator GIPL_CLK {GIPL_CLK(period, period_unit, duty_cycle, start_time, start_time_unit, posedge_first)}
::pct::create_instance GenericIPlib:ResetGenerator /HARDWARE i_ResetGenerator GIPL_RST {GIPL_RST(active_level, start_time, start_time_unit, duration, duration_unit)}
::pct::set_param_value i_ResetGenerator {Scml Properties} active_at_start true

#create a new BLFramework instance to generate SBLTLM2FT_BL bus
::pct::instantiate_bl_framework /HARDWARE i_BLFramework

#connect all the instances created in the system
::pct::create_connection C /HARDWARE/i_dlx/p_DMb_ft /HARDWARE/i_BLFramework/i_DM_socket
::pct::create_connection C_1 /HARDWARE/i_BLFramework/i_DM_mem /HARDWARE/i_DM/MEM
::pct::create_connection C_2 /HARDWARE /HARDWARE/i_ClockGenerator/CLK /HARDWARE/i_BLFramework/Clk /HARDWARE/i_DM/CLK /HARDWARE/i_dlx/clock
::pct::create_connection C_3 /HARDWARE /HARDWARE/i_ResetGenerator/RST /HARDWARE/i_BLFramework/Rst /HARDWARE/i_dlx/reset

#set memory map of the system
# Memory map
foreach initiator [::pct::list_initiators] {
  foreach target [::pct::list_targets] {
    ::pct::remove_links ${initiator}:${target}
    ::pct::set_address ${initiator}:${target} unreachable
  }
}


::pct::set_address /HARDWARE/i_dlx/p_DMb_ft:/HARDWARE/i_DM/MEM 0

#update ft_protocol_tag to AXI for Initiator block and Target block
::pct::set_param_value /HARDWARE/i_DM/MEM:protocol {Protocol Common Parameters} ft_protocol_tag AXI
::pct::set_param_value /HARDWARE/i_dlx/p_DMb_ft:protocol {Protocol Common Parameters} ft_protocol_tag AXI

#generate the BLFramework for SBLTLM2FT_BL instance.
::BLWizard::generateFramework /HARDWARE/i_BLFramework SBLTLM2FT  * { \
								} \
								{ \
								common_configuration:BackBone:/basic/protocol:AXI \
								common_configuration:BackBone:/advanced/num_resources_per_target:2 \
								master_ports:BB_i_DM_mem:/Domains/clock:Clk \
                                                                master_ports:BB_i_DM_mem:read_access_latency:1 \
                                                                master_ports:BB_i_DM_mem:outstanding_reads:2 \
                                                                master_ports:BB_i_DM_mem:outstanding_trans:4 \
								slave_ports:BB_i_DM_socket:priority:0 \
								slave_ports:BB_i_DM_socket:outstanding_reads:2 \
								slave_ports:BB_i_DM_socket:outstanding_writes:2 \
								slave_ports:BB_i_DM_socket:outstanding_trans:4 \
								slave_ports:BB_i_DM_socket:/Domains/clock:Clk \
								}

 # Export
::pct::create_simulation_build_project export
::pct::set_simulation_build_project_setting Debug "Optimize Level" "None (-O0)"
::pct::set_simulation_build_project_setting Debug "Backdoor Mode" true
::pct::set_simulation_build_project_setting Debug "Fast Linking" false
::pct::export_simulation

