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

  namespace export test_bptype

  namespace import ::testing::*

  variable bp_end 48

  proc testcase {  bptype step {bkpt ""} } {
    variable bp_end
    load_program
    log "Execute program using step $step"
    iss breakpoint mic set $bp_end -$bptype 1
    if {$bkpt ne ""} {
      iss breakpoint mic set [lindex $bkpt 0] -$bptype 1
      if {[llength $bkpt] > 1} {
        iss step $step
        expect_pc [lindex $bkpt 1]
      }
    }
    iss step $step
    expect_pc $bp_end
    expect_r x3 63 dec
  }

  proc testcase_ext {  bptype step {bkpt ""} } {
    variable bp_end
    load_program
    log "Execute program using step $step, using external debug request"
    iss breakpoint mic set $bp_end -$bptype 1

    setup_VCS_bp [lindex $bkpt 0]
    if {[llength $bkpt] > 1} {
      iss step $step
      expect_pc [lindex $bkpt 1]
      if {$bp_end != [iss get PC]} {
        iss step $step
      }
    } else {
      iss step $step
    }
    expect_pc $bp_end
    expect_r x3 63 dec
  }

  proc test_bkpt {  bptype step } {
    # no intermediate breakpoint
    testcase $bptype $step
    # simple intermediate one
    testcase $bptype $step {8 8}
    # on branch
    testcase $bptype $step {16 16}
    # breakpoints on delay slots are illegal - undefined behavior
    if {$bptype eq "hardware"} {
      # stops at branch target, if the breakpoint address is fetched
      # on 1st delay slot
  #    testcase $bptype $step {20 28}
      # on 2nd delay slot
  #    testcase $bptype $step {24 28}
    } else {
      # since these instructions won't execute, there should be no break
      # on 1st delay slot
      testcase $bptype $step 20
      # on 2nd delay slot
      testcase $bptype $step 24
    }
    # on target
    testcase $bptype $step {28 28}

    ## external requests
    if {$step == -1} {
      # simple one
      testcase_ext $bptype $step {8 12}

      # before branch
      testcase_ext $bptype $step {12 16}

      # on branch
      testcase_ext $bptype $step {16 28}
    }
  }


  proc test_step {  bptype  } {
    # resume
    test_bkpt $bptype -1
    # single stepping
    test_bkpt $bptype 200
  }

  proc test_bptype {  } {
    # hardware breakpoints
    test_step hardware
    # software breakpoints
    test_step software
  }

}

set ::ocd_vcs_script [file dirname [info script]]/../scr/vcs_extdbgbrk.tcl

testing::run_tests {

  namespace import tests::*

  test_bptype

}

#.text_segment PMb      0
#.entry_point
#           0    0x00 0x10 0x01 0x93  addi    x3,  x0,  1
#           4    0x00 0x21 0x81 0x93  addi    x3,  x3,  2
#           8    0x00 0x41 0x81 0x93  addi    x3,  x3,  4
#          12    0x00 0x81 0x81 0x93  addi    x3,  x3,  8
#          16    0x00 0x00 0x06 0x63  beq     x0,  x0,  12
#          20    0x04 0x01 0x81 0x93  addi    x3,  x3,  64
#          24    0x08 0x01 0x81 0x93  addi    x3,  x3,  128
#.label La
#          28    0x01 0x01 0x81 0x93  addi    x3,  x3,  16
#          32    0x02 0x01 0x81 0x93  addi    x3,  x3,  32
#          36    0x00 0x00 0x00 0x13  addi    x0,  x0,  0
#          40    0x00 0x00 0x00 0x13  addi    x0,  x0,  0
#          44    0x00 0x00 0x00 0x13  addi    x0,  x0,  0
#          48    0x00 0x00 0x00 0x13  addi    x0,  x0,  0


