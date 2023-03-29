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

  proc test_stepping { } {
      log "Test stepping"

      expect_pc 0

      iss step 1
      expect_pc 4

      iss step 1
      expect_pc 8

      iss step 1
      expect_pc 12

      iss step 3
      expect_pc 24

      expect_r  x1  1 dec
      expect_r  x2  2 dec
      expect_r  x3  3 dec
      expect_r  x4  4 dec
      expect_r  x5  5 dec
      expect_r  x6  6 dec
  }

  proc test_stepping_with_bp { bp_type } {
      log "Test stepping with breakpoint"
      iss breakpoint mic set 16 {*}$bp_type
      iss breakpoint mic set 24 {*}$bp_type
      iss step 20
      expect_pc 16
      iss step 20
      expect_pc 24
      expect_r  x1  1 dec
      expect_r  x2  2 dec
      expect_r  x3  3 dec
      expect_r  x4  4 dec
      expect_r  x5  5 dec
      expect_r  x6  6 dec
  }

  proc test_resume_bp { bp_type } {
      log "Test resume with breakpoint"
      iss breakpoint mic set 16 {*}$bp_type
      iss breakpoint mic set 24 {*}$bp_type
      iss step -1
      expect_pc 16
      iss step -1
      expect_pc 24
      expect_r  x1  1 dec
      expect_r  x6  6 dec
  }

  proc test_clear_bp { bp_type } {
      log "Test breakpoint clear"
      iss breakpoint mic set 16 {*}$bp_type
      iss breakpoint mic set 24 {*}$bp_type
      iss breakpoint mic clear 16
      iss step -1
      expect_pc 24
      expect_r  x1  1 dec
      expect_r  x6  6 dec
  }

  proc test_stepping_consecutive_bp { bp_type } {
      log "Test consecutive breakpoints with stepping"
      iss breakpoint mic set 8 {*}$bp_type
      iss breakpoint mic set 16 {*}$bp_type
      iss breakpoint mic set 24 {*}$bp_type
      iss step 10
      expect_pc 8
      iss step 10
      expect_pc 16
      iss step 10
      expect_pc 24
      expect_r  x1  1 dec
      expect_r  x6  6 dec
  }

  proc test_resume_consecutive_bp { bp_type } {
      log "Test consecutive breakpoints with resume"
      iss breakpoint mic set 8 {*}$bp_type
      iss breakpoint mic set 16 {*}$bp_type
      iss breakpoint mic set 24 {*}$bp_type
      iss step -1
      expect_pc 8
      iss step -1
      expect_pc 16
      iss step -1
      expect_pc 24
      expect_r  x1  1 dec
      expect_r  x6  6 dec
  }

  proc test_all { bp_type } {
      load_program
      test_stepping
      load_program
      test_stepping_with_bp $bp_type
      load_program
      test_resume_bp $bp_type
      load_program
      test_clear_bp $bp_type
      load_program
      test_stepping_consecutive_bp $bp_type
      load_program
      test_resume_consecutive_bp $bp_type
  }

}

testing::run_tests {

  namespace import tests::*

  test_all "-hardware 1"
  test_all "-software 1"

}
