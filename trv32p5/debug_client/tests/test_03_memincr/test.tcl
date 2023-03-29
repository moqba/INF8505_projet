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

  namespace export test_dm

  namespace import ::testing::*

  proc test_dm { start amount } {
      log "test_dm $start $amount "
      set mem DMw
      set last [expr $start + $amount]
      set a $start
      while {$a<$last} {
          set v [expr $a + 100]
          put_a $mem $a $v dec
          incr a  4
      }

      set last [expr $start + $amount]
      set a $start
      while {$a<$last} {
          set v [expr $a + 100]
          expect_a $mem $a $v dec
          incr a  4
      }
  }

}

testing::run_tests {

  namespace import tests::*

  test_dm 0 128
  test_dm 512 44
  test_dm 1024 12

}
