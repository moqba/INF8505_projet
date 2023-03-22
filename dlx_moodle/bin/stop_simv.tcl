#
# Tcl script to stop regression simulation runs.
#
# Copyright (c) 2020-2021 Synopsys, Inc. This processor model and the associated
# documentation are proprietary to Synopsys, Inc.  This model may only be
# used in accordance with the terms and conditions of a written license
# agreement with Synopsys, Inc.  All other use, reproduction, or distribution
# of this model are strictly prohibited.
#


set testname [lindex $argv 0]
set testdir work/${testname}

if {[file isdirectory ${testdir}]} {
    close [open ${testdir}/.OCD_VCS_stop w]
} else {
    puts "** stop_simv.tcl: Error, directory '${testdir}' does not exist.."
}

