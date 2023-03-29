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
#   asip_rtl_explorer -i hdl_exploration/go_opts_power_exploration_p1-icg.tcl

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

foreach rtl_id [list_variants] {
  build_variant $rtl_id
}

puts "\nRTL Versions Ready! For starting exploration, execute:\n"
puts "cd [current_project]_r0/syn_rtla;"
puts "make explore RTL_ID_LIST=\"[list_variants]\" ASIP_LIB_SETUP=..."
puts "\nTo inspect results:"
puts "make view_qor"
puts "\nTo clean:"
puts "asip_rtl_explorer -c [current_project] -r all"

