#
# Tcl script to test BLX on chip debugging TUI.
#
# Verify stepping and breakpoints
#
# Execute as follows:
#  1) start server (echo_server, HDL simulator or jtalk)
#  2) start client ISS:
#         ../blx_client -t test_4a_breakpoints.tcl -u <host>:<tile>

source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]
initiate b

proc step1_csync { iss } {
  set msg [command $iss "prepare_sync_command"]
  switch -exact -- $msg {
    "ready" {
      # do one synchronous step
      command $iss "step 1 -csync 1"
      return true
    }
    "ready_after_step" {
      # already stepped
      return true
    }
    "at_break_after_step" {
      # already stepped, hit breakpoint
      return false
    }
    default {
      error "Unknown state after prepare_sync_command"
    }
  }
  return false
}

proc step_csync { iss n } {
  log "cmd: step_csync $n"
  for {set i 0} {$i < $n} {incr i} {
    if { ! [step1_csync $iss] } {
      # did one step, hit breakpoint
      break
    }
    if {[expr $n - $i > 1]} {
      # check for breakpoint
      set cs [::tclutils::list2dict $::iss::core_status_keys [command $iss "debug_client core_status"]]
      if {[dict get $cs sw_break] || [dict get $cs hw_break] || [dict get $cs external_break]} {
        break
      }
    }
  }
}

proc resume_csync { iss } {
  log "cmd: resume_csync"
  set msg [command $iss "prepare_sync_command"]
  switch -exact -- $msg {
    "ready" {
      # ready for resume
      command $iss "step -1 -csync 1"
    }
    "ready_after_step" {
      # stepped once, now resume stepped
      command $iss "step -1 -csync 1"
    }
    "at_break_after_step" {
      # stepped once, hit breakpoint - end of resume
    }
    default {
      error "Unknown state after prepare_sync_command"
    }
  }
}

proc test_stepping { iss } {
    log "Test stepping"

    expect_pc $iss 0

    step_csync $iss 1
    expect_pc $iss 4

    step_csync $iss 1
    expect_pc $iss 8

    step_csync $iss 1
    expect_pc $iss 12

    step_csync $iss 3
    expect_pc $iss 24

    expect_r $iss  R1  1 dec
    expect_r $iss  R2  2 dec
    expect_r $iss  R3  3 dec
    expect_r $iss  R4  4 dec
    expect_r $iss  R5  5 dec
    expect_r $iss  R6  6 dec
}

proc test_stepping_with_bp { iss bp_type } {
    log "Test stepping with breakpoint, $bp_type"
    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 24 $bp_type"
    step_csync $iss 20
    expect_pc $iss 16
    step_csync $iss 20
    expect_pc $iss 24
    expect_r $iss  R1  1 dec
    expect_r $iss  R2  2 dec
    expect_r $iss  R3  3 dec
    expect_r $iss  R4  4 dec
    expect_r $iss  R5  5 dec
    expect_r $iss  R6  6 dec
}

proc test_resume_bp { iss bp_type } {
    log "Test resume with breakpoint, $bp_type"
    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 24 $bp_type"
    resume_csync $iss
    expect_pc $iss 16
    resume_csync $iss
    expect_pc $iss 24
    expect_r $iss  R1  1 dec
    expect_r $iss  R6  6 dec
}

proc test_clear_bp { iss bp_type } {
    log "Test breakpoint clear, $bp_type"
    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 24 $bp_type"
    command $iss "breakpoint mic clear 16"
    resume_csync $iss
    expect_pc $iss 24
    expect_r $iss  R1  1 dec
    expect_r $iss  R6  6 dec
}

proc test_stepping_consecutive_bp { iss bp_type } {
    log "Test consecutive breakpoints with stepping, $bp_type"
    command $iss "breakpoint mic set 8 $bp_type"
    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 24 $bp_type"
    step_csync $iss 10
    expect_pc $iss 8
    step_csync $iss 10
    expect_pc $iss 16
    step_csync $iss 10
    expect_pc $iss 24
    expect_r $iss  R1  1 dec
    expect_r $iss  R6  6 dec
}

proc test_resume_consecutive_bp { iss bp_type } {
    log "Test consecutive breakpoints with resume, $bp_type"
    command $iss "breakpoint mic set 8 $bp_type"
    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 24 $bp_type"
    resume_csync $iss
    expect_pc $iss 8
    resume_csync $iss
    expect_pc $iss 16
    resume_csync $iss
    expect_pc $iss 24
    expect_r $iss  R1  1 dec
    expect_r $iss  R6  6 dec
}

proc test_all { iss bp_type } {
    load_program $iss
    test_stepping $iss
    load_program $iss
    test_stepping_with_bp $iss $bp_type
    load_program $iss
    test_resume_bp $iss $bp_type
    load_program $iss
    test_clear_bp $iss $bp_type
    load_program $iss
    test_stepping_consecutive_bp $iss $bp_type
    load_program $iss
    test_resume_consecutive_bp $iss $bp_type
}

test_all b "-hardware 1"
test_all b "-software 1"

finalise b

