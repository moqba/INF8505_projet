#
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#
# Tcl script to test trv32p5 on chip debugging TUI.
#

source [file join [file dirname [info script]] .. scr ocd_test.tcl]

namespace eval tests {

  namespace export test_resume

  namespace import ::testing::*

  proc test_resume {  } {
    log "Execute program using resume"
    load_program
    set bpa 40
    iss breakpoint mic set $bpa -hardware 1
    iss step -1
    expect_pc $bpa
  }

}

testing::run_tests {

  namespace import tests::*


  test_resume

}
