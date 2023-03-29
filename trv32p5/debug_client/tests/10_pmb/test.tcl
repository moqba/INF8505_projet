#
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#
# Tcl script to test TRV32P5 on chip debugging TUI.
#
# Purpose: Verify read/write on memories.
#


source [file join [file dirname [info script]] .. scr ocd_test.tcl]

namespace eval tests {

  namespace export test1 test2

  namespace import ::testing::*

  variable mem PMb
  variable step 1

  variable cur 1
  proc genbyte {} {
    variable cur
    set cur [expr {($cur * 1664525 + 1013904223) % (2**32)}]
    expr {$cur % 256}
  }
  proc gen {nbytes} {
    set r ""
    for {set i 0} {$i < $nbytes} {incr i} {
      append r [format %02x [genbyte]]
    }
    return $r
  }

  variable mem_value {
      0   00
      1   01
      2   02
      3   03
      4   04
      5   05
      6   06
      7   07
      8   80
      9   81
     10   82
     11   83
     12   84
     13   85
     14   86
     15   87
  }

  proc test1 { } {
    variable mem
    variable mem_value

    log "test1 $mem"

    foreach {x val} $mem_value {
      put_a $mem [expr 128+$x] $val
    }

    foreach {x val} $mem_value {
      expect_a $mem [expr 128+$x] $val
    }

  }

  proc test2 { {off 0} } {
    variable mem
    variable step

    log "test2 $mem $off"

    for {set a 0} {$a < 64} {incr a} {
      set val [gen $step]
      set adr [expr {$step * $a + $off}]
      put_a $mem $adr $val hex
      lappend vals $val
    }

    for {set a 0} {$a < 64} {incr a} {
      set val [lindex $vals $a]
      set adr [expr {$step * $a + $off}]
      expect_a $mem $adr $val hex
    }
  }
}


testing::run_tests {

  namespace import tests::*

  test1

  test2

  test2 42

}

