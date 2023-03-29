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
# Verify put/get on registers
#


source [file join [file dirname [info script]] .. scr ocd_test.tcl]

namespace eval tests {

  namespace export do_reg_test

  namespace import ::testing::*

  variable regs
  for {set i 1} {$i < 32} {incr i} {
    lappend regs x$i
  }

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

  proc test_regs {start incr {dbgstep 0}} {
    log "test_regs $start $incr"

    if {$dbgstep != 0} {
      load_program
    }

    set value $start
    foreach r { x1 x2 x8 x16 x31 } {
      put_r $r $value dec
      lappend vals $value
      set value [expr $value + $incr]
    }

    if {$dbgstep != 0} {
      iss step $dbgstep
    }

    foreach r { x1 x2 x8 x16 x31 } value $vals {
      expect_r $r $value dec
    }
  }

  proc test_rand {regs nbytes {dbgstep 0}} {
    log "test_range $regs $nbytes"

    if {$dbgstep != 0} {
      load_program
    }

    foreach r $regs {
      set val [gen $nbytes]
      put_r $r $val hex
      lappend vals $val
    }

    if {$dbgstep != 0} {
      iss step 1
    }

    foreach r $regs val $vals {
      expect_r $r $val hex
    }
  }

  proc test_x0 {{dbgstep 0}} {
    log "test_x0"

    if {$dbgstep != 0} {
      load_program
    }

    put_r x0 10 hex

    if {$dbgstep != 0} {
      iss step $dbgstep
    }

    expect_r x0 0 hex
  }

  variable nbytes

  proc setup {} {
    variable nbytes
    # determine width of X[]
    set stor_info [tclutils::list2dict [iss info keys stor_info] [lindex [iss info storage X] 0]]
    set dt [dict get $stor_info data_type]
    set type_info [tclutils::list2dict [iss info keys type_info] [lindex [iss info type $dt] 0]]
    set nbits [dict get $type_info width]
    set nbytes [expr {$nbits / 8}]
  }

  proc do_reg_test {{dbgstep 0}} {

    variable nbytes
    variable regs

    setup

    test_regs 0 10 $dbgstep
    test_regs 1000 10 $dbgstep
    test_regs 0 0 $dbgstep
    test_regs 100000 50000 $dbgstep

    test_x0 $dbgstep

    test_rand $regs $nbytes $dbgstep

    test_rand [lreverse $regs] $nbytes $dbgstep

  }

  proc test_all {} {
  }
}


testing::run_tests {

  namespace import tests::*

  # regular run - write then read
  do_reg_test

  # now with 1 step in-between - flush caches: write - step - read
  do_reg_test 1

}

