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

  variable mem PM
  variable step 4

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
    0   03020100
    4   07060504
    8   0000cafe
    12  cafebabe
  }

  proc test1 { } {
    variable mem
    variable mem_value

    log "test1 $mem"

    foreach {x val} [array get mem_value] {
      put_a $mem [expr 128+$x] $val
    }

    foreach {x val} [array get mem_value] {
      expect_a $mem [expr 128+$x] $val
    }

  }

  proc test2 { step {off 0} } {
    variable mem

    log "test2 $mem $step $off"

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

  namespace import ::testing::iss

  set pm_opts [tclutils::list2dict [iss info keys stor_info] [lindex [iss info storage PM] 0]]
  set nstep [dict get $pm_opts native_step]
  set astep [dict get $pm_opts address_step]

  if {$nstep == 4} {
    test1
  }

  test2 $nstep

  test2 $nstep [expr {42 * $nstep}]

  if {$nstep != $astep} {
    for {set off $astep} {$off < $nstep} {incr off $astep} {
      test2 $nstep $off
    }
  }

}

