#!/usr/bin/env tct_tclsh
#
# Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

source [file join [file dirname [info script]] .. .. .. bin utils.tcl]

log "start"

# source run_sc_common.tcl
set scriptDir [file dirname [info script]]
puts   [file join $scriptDir  "run_sc_singlecore.tcl"]
source [file join $scriptDir  "run_sc_singlecore.tcl"]


if {!$no_reports} {
  execute $proc profile save $program.fprf -type function_statistics \
        -entry_pc 0 -function_details 0 -call_details 0 -xml 0

  execute $proc profile save $program.iprf -type function_details \
        -user_cycle_count Off -xml 0 -source_refs Off -hide_instruction_bits On

  execute $proc profile save $program.etrc -type execution_trace -xml 0
}

execute exit
disconnect

log "end"