#!/usr/bin/env tct_tclsh
#
# Tcl script to stop regression simulation runs.
#
# Copyright (c) 2020-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
set testname [lindex $argv 0]
set testdir work/${testname}

if {[file isdirectory ${testdir}]} {
  close [open ${testdir}/.OCD_VCS_stop w]
} else {
  puts "** stop_simv.tcl: Error, directory '${testdir}' does not exist.."
}

