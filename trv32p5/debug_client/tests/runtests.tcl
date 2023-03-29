#!/usr/bin/env tct_tclsh

source [file join [file dirname [info script]] .. .. bin utils.tcl]

# Run test
#  -> Self-checking test, or compare.tcl based?
proc run_test test_prx {
  set dir [file dirname $test_prx]
  set ref [file join $dir reg.ref.dmp]
  if {[file exists $ref]} {
    run_cmp_test $test_prx
  } else {
    run_selfchk_test $test_prx
  }
}

# Run self-checking test
proc run_selfchk_test test_prx {
  set dir [file dirname $test_prx]
  set log_bld [file join $dir build.log]
  set log_ocd [file join $dir ocd.log]

  if {[chessmk $test_prx >& $log_bld]} {
    log "ERROR: building $test_prx failed"
    return 0
  }

  if {[chessmk $test_prx +C vcs -S >& $log_ocd]} {
    log "ERROR: OCD simulation failed"
    return 0
  }

  return 1
}

# Run compare.tcl based test
proc run_cmp_test test_prx {
  set dir [file dirname $test_prx]
  set ref [file join $dir reg.ref.dmp]
  set iss [file join $dir reg.iss.dmp]
  set ocd [file join $dir reg.ocd.dmp]
  set dif [file rootname $test_prx].diff

  set log_bld [file join $dir build.log]
  set log_iss [file join $dir iss.log]
  set log_ocd [file join $dir ocd.log]

  if {[chessmk $test_prx >& $log_bld]} {
    log "ERROR: building $test_prx failed"
    return 0
  }

  if {[chessmk $test_prx +C vcs -S >& $log_ocd]} {
    log "ERROR: OCD simulation failed"
    return 0
  }

  if {[chessmk $test_prx +C iss -S >& $log_iss]} {
    log "ERROR: ISS simulation failed"
    return 0
  }

  if {[compare -ref $ref -iss $iss -ocd $ocd >& $dif]} {
    log "ERROR: compare failed"
    return 0
  }

  return 1
}

# Wrapper for compare.tcl
proc compare args {
  set scr [file join [file dirname [info script]] scr compare.tcl]
  log_exec $scr {*}$args
}

proc main tests {
  set err 0

  foreach test_prx $tests {
    if {[run_test $test_prx]} {
      log "PASSED: [file dirname $test_prx]"
    } else {
      log "FAILED: [file dirname $test_prx]"
      incr err
    }
  }

  log "------------------------------------------------------"
  log "   --- Total number of tests: [llength $tests]"
  log "   --- Failures: $err"
  if {$err > 0} {
    log "   --- Status: FAILED"
    exit 1
  } else {
    log "   --- Status: PASSED"
  }
}

if {[llength $argv] > 0} {
  foreach arg $argv {
    set prx $arg
    if {[file isdir $prx]} {
      set prx [file join $prx test.prx]
    }
    if {[file exists $prx]} {
      lappend tests $prx
    } else {
      log "ERROR: unknown positional argument '$arg', expected path to prx file, or directory containing test.prx"
      exit 1
    }
  }
} else {
  if {[file exists test.prx]} {
    lappend tests test.prx
  } else {
    set scrdir [file dirname [info script]]
    set tests [glob [file join $scrdir * test.prx]]
  }
}

main $tests
