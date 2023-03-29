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

  namespace export test_regs

  namespace import ::testing::*

  proc test_regs {start step} {
      log "test_regs $start $step"
      set value $start
      foreach r { x1 x2 x8 x16 x31 } {
          put_r $r $value dec
          set value [expr $value + $step]
      }

      set value $start
      foreach r { x1 x2 x8 x16 x31 } {
          expect_r $r $value dec
          set value [expr $value + $step]
      }
  }

}

testing::run_tests {

  namespace import tests::*

  test_regs 0 10
  test_regs 1000 10
  test_regs 0 0
  test_regs 100000 50000

}
