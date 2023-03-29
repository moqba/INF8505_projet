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

  namespace export test_stepping

  namespace import ::testing::*

  proc test_stepping {  } {
    log "Test stepping"

    load_program
    expect_pc 0

    iss step 1
    expect_pc 4
    expect_r x10 0 dec

    iss step 1
    expect_pc 8
    expect_r x10 0 dec

    iss step 1
    expect_pc 12
    expect_r x10 0 dec

    iss step 1
    expect_pc 16
    expect_r x10 0 dec

    iss step 1
    expect_pc 20
    expect_r x10 1 dec

    iss step 1
    expect_pc 24
    expect_r x10 3 dec

    iss step 1
    expect_pc 28
    expect_r x10 7 dec

    iss step 1
    expect_pc 32
    expect_r x10 15 dec

    iss step 1
    expect_pc 36
    expect_r x10 31 dec

    iss step 1
    expect_pc 40
    expect_r x10 63 dec

    iss step 1
    expect_pc 44
    expect_r x10 127 dec

    iss step 1
    expect_pc 48
    expect_r x10 127 dec
  }

}

testing::run_tests {

  namespace import tests::*


  test_stepping

}
