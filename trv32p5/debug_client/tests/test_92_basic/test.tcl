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

  namespace export test1

  namespace import ::testing::*

  proc test1 {} {
    iss put  5 PMb  0
    iss put  6 PMb  1
    iss put  7 PMb  2
    iss put  8 PMb  3
    iss put  9 PMb  4
    iss put 10 PMb  5
    iss put 11 PMb  6
    iss put 12 PMb  7
    iss put 13 PMb  8
    iss put 14 PMb  9
    iss put 15 PMb 10
    iss put 16 PMb 11
    iss put 17 PMb 12
    iss put 18 PMb 13
    iss put 19 PMb 14
    iss put 20 PMb 15
    iss put 21 PMb 16
    iss put 22 PMb 17
    iss put 23 PMb 18
    iss put 24 PMb 19
    iss put 25 PMb 20
    iss put 26 PMb 21
    iss put 27 PMb 22
    iss put 28 PMb 23
    iss put 29 PMb 24
    iss put 30 PMb 25
    iss put 31 PMb 26
    iss put 32 PMb 27
    iss put 33 PMb 28
    iss put 34 PMb 29
    iss put 35 PMb 30
    iss put 36 PMb 31

    iss update

    iss get PMb 0
    iss get PMb 1
    iss get PMb 2
    iss get PMb 31
  }

}

testing::run_tests {

  namespace import tests::*

  test1

}
