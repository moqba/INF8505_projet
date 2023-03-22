#
# Copyright (c) 2019 Synopsys, Inc. This processor model and the associated
# documentation are proprietary to Synopsys, Inc.  This model may only be
# used in accordance with the terms and conditions of a written license
# agreement with Synopsys, Inc.  All other use, reproduction, or distribution
# of this model are strictly prohibited.
#

# source run_sc_common.tcl
set scriptDir [ file dirname $argv0 ]
puts   [file join $scriptDir  "run_sc_singlecore.tcl"]
source [file join $scriptDir  "run_sc_singlecore.tcl"]


execute $proc profile save $program.fprf -type function_statistics -entry_pc 0 -function_details 0 -call_details 0 -xml 0

execute $proc profile save $program.iprf -type function_details -user_cycle_count Off -xml 0 -source_refs Off -hide_instruction_bits On

execute $proc profile save $program.etrc -type execution_trace -xml 0

execute exit
disconnect

