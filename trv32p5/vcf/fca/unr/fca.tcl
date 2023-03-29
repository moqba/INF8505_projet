#
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#


set_fml_appmode COV
set_fml_var fml_cov_enable_branch_cov true
set_app_var fml_cov_tgl_input_port true
set_fml_var fml_reset_property_check true
set_fml_var fml_cov_gen_trace on
set_fml_var fml_cov_enable_unconst_analysis true
read_file -cov all -top trv32p5 -vcs "+v2k -sverilog -f main.f"
create_clock clock -period 100
create_reset reset_ext
create_reset dbg_reset
create_reset reset
sim_run -stable
sim_save_reset
check_fv_setup -verbose