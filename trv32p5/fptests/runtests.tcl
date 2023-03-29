#!/usr/bin/env tct_tclsh

proc usage {} {
  puts "

Floating-Point Tests Driver
===========================

Optional Arguments:

  --iss <iss>           Select ISS (default: trv32p5_ca)
  --cfg <cfg>           Select comile config (default: Release)
  --rnd <rnd>           Select rounding mode (default: near_even/minMag)
  --build               Build test application
  --keep-going          Continue on error
  --gen <arg>+          Extra argument for testfloat_gen
  --ver <arg>+          Extra argument for testfloat_ver
  --genver <arg>+       Extra argument for both testfloat_gen and testfloat_ver
  --help                This help
  --                    Stop parsing optional arguments

Extra arguments <arg>+ consume the next argument (optional or positional), then
all positional arguments that follow:

        --genver -seed 10

Abbreviated Forms:

  +D<iss>|+D <iss>      for --iss
  -C<cfg>|-C <cfg>      for --cfg
  -r<rnd>|-r <rnd>      for --rnd
  -h                    for --help
  -b                    for --build
  -k                    for --keep-going

Positional Arguments:

   fn[ fn]*     Select functions for testing (default: all functions)

Available Test Functions:

  f32_add
  f32_sub
  f32_mul
  f32_div
  f32_to_i32
  f32_to_ui32
  i32_to_f32
  ui32_to_f32
  f32_to_i64
  f32_to_ui64
  i64_to_f32
  ui64_to_f32
  f32_eq
  f32_le
  f32_lt
  f64_add
  f64_sub
  f64_mul
  f64_div
  f64_to_i32
  f64_to_ui32
  i32_to_f64
  ui32_to_f64
  f64_to_i64
  f64_to_ui64
  i64_to_f64
  ui64_to_f64
  f64_eq
  f64_le
  f64_lt
  f32_to_f64
  f64_to_f32

Available Rounding Modes:

  near_even
  minMag
  min
  max
  near_maxMag

Note: For Models without FPU, do not specify a rounding mode. The floating-point
  emulation uses near_even for most operations, and minMag for functions that
  convert between floating point numbers and integers, as per C standard.

Example for passing an argument to testfloat_gen and testfloat_ver:

  [file tail [info script]] --genver -seed 10

"
}

package require TctTclUtilsParseArgs

set scrdir [file dirname [info script]]
source [file join $scrdir .. bin utils.tcl]


# defaults
set iss trv32p5_ca
set cfg Release
set rndmode_set 0
set tests [list]
set build 0
set keep_going 0

set testapp [file join $scrdir driver test]
set testfloat_gen [file join $scrdir testfloat_gen]
set testfloat_ver [file join $scrdir testfloat_ver]

set testfloat_gen_args [list -tininessafter -exact]
set testfloat_ver_args [list -tininessafter -exact -errors -1]

# parse script args
if {[llength $::argv] > 0} {
  for {set i 0} {$i < [llength $::argv]} {incr i} {
    switch -glob -- [lindex $::argv $i] {
      --iss -
      +D {
        set iss [lindex $::argv [incr i]]
      }
      +D* {
        set iss [string range [lindex $::argv $i] 2 end]
      }
      --cfg -
      -C {
        set cfg [lindex $::argv [incr i]]
      }
      -C* {
        set cfg [string range [lindex $::argv $i] 2 end]
      }
      --rnd {
        set rndmode [lindex $::argv [incr i]]
        set rndmode_set 1
      }
      -r* {
        set rndmode [string range [lindex $::argv $i] 2 end]
        set rndmode_set 1
      }
      --help -
      -h {
        usage
        exit
      }
      --build -
      -b {
        set build 1
      }
      --keep-going -
      -k {
        set keep_going 1
      }
      --gen {
        lappend testfloat_gen_args [lindex $::argv [incr i]]
        while {($i + 1) < [llength $::argv] && ![string match -* [lindex $::argv [expr {$i + 1}]]]} {
          lappend testfloat_gen_args [lindex $::argv [incr i]]
        }
      }
      --ver {
        lappend testfloat_ver_args [lindex $::argv [incr i]]
        while {($i + 1) < [llength $::argv] && ![string match -* [lindex $::argv [expr {$i + 1}]]]} {
          lappend testfloat_ver_args [lindex $::argv [incr i]]
        }
      }
      --genver {
        lappend testfloat_gen_args [lindex $::argv [incr i]]
        lappend testfloat_ver_args [lindex $::argv $i]
        while {($i + 1) < [llength $::argv] && ![string match -* [lindex $::argv [expr {$i + 1}]]]} {
          lappend testfloat_gen_args [lindex $::argv [incr i]]
          lappend testfloat_ver_args [lindex $::argv $i]
        }
      }
      -- {
        incr i
        break
      }
      -* {
        log "ERROR: Unknonw argument [lindex $::argv $i]"
        exit 1
      }
      default {
        lappend tests [lindex $::argv $i]
      }
    }
  }
  if {$i < [llength $::argv]} {
    lappend tests {*}[lrange $::argv $i end]
  }
}

set fns [list {*}{
  f32_add
  f32_sub
  f32_mul
  f32_div
  f32_to_i32
  f32_to_ui32
  i32_to_f32
  ui32_to_f32
  f32_to_i64
  f32_to_ui64
  i64_to_f32
  ui64_to_f32
  f32_eq
  f32_le
  f32_lt
  f64_add
  f64_sub
  f64_mul
  f64_div
  f64_to_i32
  f64_to_ui32
  i32_to_f64
  ui32_to_f64
  f64_to_i64
  f64_to_ui64
  i64_to_f64
  ui64_to_f64
  f64_eq
  f64_le
  f64_lt
  f32_to_f64
  f64_to_f32
}]

if {[llength $tests] == 0} {
  set tests $fns
}

log "INFO: Testing functions [join $tests {, }]"

set def_rnd_mode {
  default     near_even

  f32_to_i32  minMag
  f32_to_ui32 minMag
  f32_to_i64  minMag
  f32_to_ui64 minMag
  f64_to_i32  minMag
  f64_to_ui32 minMag
  f64_to_i64  minMag
  f64_to_ui64 minMag
}

proc get_default_rounding_mode fn {
  if {![dict exists $::def_rnd_mode $fn]} {
    set fn default
  }
  return [dict get $::def_rnd_mode $fn]
}

proc run-one {fn iss cfg rndmode} {
  lappend cmd $::testfloat_gen -r$rndmode {*}$::testfloat_gen_args $fn
  lappend cmd | chessmk $::testapp +D $iss -C $cfg -S -s +X $rndmode,$fn
  lappend cmd | $::testfloat_ver -r$rndmode {*}$::testfloat_ver_args $fn
  log_exec {*}$cmd
}

if {$build} {
  if {[chessmk $testapp -C $cfg >& build.log]} {
    log "ERROR: failed building test application\n[cat_file build.log]"
    exit 1
  }
}

if {![file exists $testfloat_gen] || ![file exists $testfloat_ver]} {
  log "ERROR: Could not find testfloat_gen or testfloat_ver. Please build testfloat first"
  exit 1
}

set err 0
set cnt 0
foreach fn $tests {
  if {!$rndmode_set} {
    set rndmode [get_default_rounding_mode $fn]
  }
  set rc [run-one $fn $iss $cfg $rndmode]
  incr cnt
  if {$rc != 0} {
    incr err
    if {$keep_going} {
      log "ERROR: verification for $fn failed, but continuing on error"
    } else {
      log "ERROR: verification for $fn failed, stopping on first error"
      break
    }
  }
}

log "------------------------------------------------------"
log "   --- Total number of tests: $cnt ran of [llength $tests]"
log "   --- Failures: $err"
if {$err > 0} {
  log "   --- Status: FAILED"
  exit 1
} else {
  log "   --- Status: PASSED"
}
