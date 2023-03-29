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

  namespace export test_all

  namespace import ::testing::*

  proc test_step {} {
    log "test_step"

    load_program

    iss step 1
    expect_pc 4
    expect_r x1 1 dec

    iss step 1
    expect_pc 8
    expect_r x2 2 dec

    iss step 3
    expect_pc 20
    expect_r x5 5 dec
  }

  proc test_go {} {
    log "test_go"

    load_program

    set bpa 24
    iss breakpoint mic set $bpa -hardware 1
    iss step -1
    expect_pc $bpa
    expect_r x1 1 dec
    expect_r x2 2 dec
    expect_r x6 6 dec
  }

  proc test_go2 {} {
    log "test_go"

    load_program

    set bpa 24
    iss breakpoint mic set $bpa
    iss step -1
    expect_pc $bpa
    expect_r x1 1 dec
    expect_r x2 2 dec
    expect_r x6 6 dec
  }

  proc test_step_n {} {
    log "test_step_n"

    load_program

    set bpa 24
    iss breakpoint mic set $bpa -hardware 1
    iss step 100
    expect_pc $bpa
    expect_r x1 1 dec
    expect_r x2 2 dec
    expect_r x6 6 dec
  }

  proc test_step_bp {} {
    log "test_step_bp"

    load_program

    iss breakpoint mic set 8
    iss breakpoint mic set 12
    iss breakpoint mic set 16
    iss breakpoint mic set 20

    iss step 100
    expect_pc 8
    iss step 100
    expect_pc 12
    iss step 100
    expect_pc 16
    iss step 100
    expect_pc 20
  }

  proc test_all {} {
    test_step
    test_go
    test_go2
    test_step_n
    test_step_bp
  }

}

testing::run_tests {

  namespace import tests::*

  test_all

}
