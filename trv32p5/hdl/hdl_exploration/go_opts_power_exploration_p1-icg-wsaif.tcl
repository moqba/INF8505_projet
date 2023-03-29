#############################################################################
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#############################################################################
# ASIP DESIGNER - RTL EXPLORER
# File: go_opts_power_exploration_p1-icg.tcl
# Usage:
#   cd trv32p5/hdl/
#   asip_rtl_explorer -i hdl_exploration/go_opts_power_exploration_p1-icg-wsaif.tcl
#
# This examples is an extension to the basic example:
#     hdl_exploration/go_opts_power_exploration_p1-icg.tcl
# It shows how additional procedures can be created using commands like
# 'chessmk' and 'execute'. In this case for the generation of a SAIF file
# for a given RTL version and a given application project .

set ::rtl_simulator "vcs" ;# For check

# The following procedure builds the variant, and runs a give application in
# an RTL simulator for the generation of a SAIF file to be used as input for
# the RTL-A's Exploration Flow.
proc build_variant_&_gen_saif {rtl_id path_to_app_dir app_name} {

    # Build and elaborate the variant
    build_variant $rtl_id -chessmk_options {-m +e}

    # Generation of SAIF files:
    # Example application is compiled, simulated to get cycle count (with -S), and the
    # memory content files are generated (with +H).
    # Same logfile ending for easy cleaning: 'rm -f *.chessmk.log *.execute.log'
    chessmk $path_to_app_dir/$app_name > $rtl_id.app_compilation.chessmk.log
    chessmk -S $path_to_app_dir/$app_name +C rcd  > $rtl_id.app_simulation.chessmk.log
    chessmk +H $path_to_app_dir/$app_name > $rtl_id.app_gen_mem_content.chessmk.log

    # Execute RTL Simulator using target 'saif' of the simulation Makefile.
    execute make -f [current_project]_$rtl_id/Makefile saif APP=$path_to_app_dir/Release/$app_name > $rtl_id.saif_gen.execute.log

    # It is required that the generated SAIF file is stored in the
    # asip_scripts directory of the corresponding variant. And all
    # SAIF files should have the same name to be able to pass it
    # during the make call (see output at the end of execution)
    file rename -force  $::processor_name.saif [current_project]_$rtl_id/syn_rtla/asip_scripts/$::processor_name.saif

}

proc check_for_rtl_simulator {} {
  try {
      execute which $::rtl_simulator
    } on error {msg opts} {
      puts stderr "Check failed: Make sure that '$::rtl_simulator' is available on PATH"
      exit
    }
}

current_project trv32p5_vlog

# Part1: Evaluating the effect of Go Options that could enable
# Insertion of Clock Gating (ICG) by the synthesis tool.
# Analyzing Go Options:
#   - register_write_enable | register_vector_write_enable
#   - pipe_write_enable
#   - instruction_pipe_write_enable

# Create baseline: reset options of interest and any dependant
# option (in trv32p5_vlog, i.e., register_write_per_field).
create_variant r0 \
  -go_options { register_vector_write_enable:0
                register_write_per_field:0
                pipe_write_enable:0
                instruction_pipe_write_enable:0
                fixed_file_header }

# Variants to analyze the option's effect on the ICG
# enabling options one-by-one:
create_variant rvwe \
  -go_options { register_vector_write_enable:1
                register_write_per_field:0
                pipe_write_enable:0
                instruction_pipe_write_enable:0
                fixed_file_header }

create_variant rvwe_rwpf \
  -go_options { register_vector_write_enable:1
                register_write_per_field:1
                pipe_write_enable:0
                instruction_pipe_write_enable:0
                fixed_file_header }

create_variant rvwe_rwpf_pwe \
  -go_options { register_vector_write_enable:1
                register_write_per_field:1
                pipe_write_enable:1
                instruction_pipe_write_enable:0
                fixed_file_header }

create_variant rvwe_rwpf_pwe_ipwe1 \
  -go_options { register_vector_write_enable:1
                register_write_per_field:1
                pipe_write_enable:1
                instruction_pipe_write_enable:1
                fixed_file_header }

create_variant rvwe_rwpf_pwe_ipwe2 \
  -go_options { register_vector_write_enable:1
                register_write_per_field:1
                pipe_write_enable:1
                instruction_pipe_write_enable:2
                fixed_file_header }

set ::processor_name [file tail [get_processor_model [current_project]]]
# Make sure the complete model is up-to-date: Processor, libraries
# and ISS should be built. Also checking for the RTL Simulator
# required for SAIF file generation.
chessmk -m ../model > build.model.log
check_for_rtl_simulator

foreach rtl_id [list_variants] {
  # Using sort example
  build_variant_&_gen_saif $rtl_id ../examples/sort sort
}

puts "\nRTL Versions Ready! For starting exploration, check RTLA and PrimeTime are in 'PATH' and execute:\n"
puts "cd [current_project]_r0/syn_rtla;"
puts "make explore RTL_ID_LIST=\"[list_variants]\" ASIP_SAIF_FILE=$::processor_name.saif ASIP_SAIF_INSTANCE=test_bench/inst_$::processor_name ASIP_LIB_SETUP=..."
puts "\nTo inspect results:"
puts "make view_qor"
puts "\nTo clean:"
puts "asip_rtl_explorer -c [current_project] -r all"
puts "rm -f *.chessmk.log *.execute.log"