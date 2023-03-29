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

  namespace export test_resume test_stepping test_bp_resume test_bp_stepping

  namespace import ::testing::*

  proc test_resume {  } {
    log "Execute using resume"
    load_program
    set bpa 36
    iss breakpoint mic set $bpa
    iss step -1
    expect_a DMw 1000 256 dec
    expect_a DMw 256 1000 dec
    expect_a DMw 1024 500 dec
  }

  proc test_stepping {  } {
    log "Execute using stepping"
    load_program
    set bpa 36
    iss breakpoint mic set $bpa
    iss step 100
    expect_a DMw 1000 256 dec
    expect_a DMw 256 1000 dec
    expect_a DMw 1024 500 dec
  }

  proc test_bp_resume {  } {
    log "Execute with breakpoint using resume"
    load_program
    set bpa 36
    iss breakpoint mic set 28
    iss breakpoint mic set $bpa
    iss step -1
    iss step -1
    expect_a DMw 1000 256 dec
    expect_a DMw 256 1000 dec
    expect_a DMw 1024 500 dec
  }

  proc test_bp_stepping {  } {
    log "Execute with breakpoint using stepping"
    load_program
    set bpa 36
    iss breakpoint mic set 28
    iss breakpoint mic set $bpa
    iss step 100
    iss step 100
    expect_a DMw 1000 256 dec
    expect_a DMw 256 1000 dec
    expect_a DMw 1024 500 dec
  }

}

testing::run_tests {

  namespace import tests::*

  test_resume

  test_stepping

  test_bp_resume

  test_bp_stepping
}

