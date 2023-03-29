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
# Purpose: Verify stepping and breakpoints.
#

source [file join [file dirname [info script]] .. scr ocd_test.tcl]

namespace eval tests {

  namespace export test1

  namespace import ::testing::*

  namespace upvar ::testing fwords fwords

  proc test1 {} {
    variable fwords

    log "test1"

    load_program
    init_X

    expect_pc 0

    # first step
    iss step 1
    expect_pc [lindex $fwords 1]
    check 1

    # second step
    iss step 1
    expect_pc  [lindex $fwords 2]
    check 2

    # 3 more steps
    iss step 3
    expect_pc  [lindex $fwords 5]
    check 5

    # 10 more steps
    iss step 10
    expect_pc  [lindex $fwords 15]
    check 15
  }

  proc init_X {} {
    for {set i 1} {$i < 32} {incr i} {
      put_r x$i 0
    }
  }

  # X[1..31] = { 1, 1, ..., 1, 0, ... }
  # after N steps, there N ones and the rest i zero
  # ... see test.s: instr N is "addi xN, xN, 1"
  proc check {n} {
    for {set i 1} {$i < 32} {incr i} {
      expect_r x$i [expr {$i <= $n ? 1 : 0}]
    }
  }

}

testing::run_tests {

  namespace import tests::*

  test1

}
