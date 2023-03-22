#
# Tcl script to test DLX on chip debugging TUI.
#
# Verify stepping and breakpoints
#
# Execute as follows:
#  1) start server (echo_server, HDL simulator or jtalk)
#  2) start client ISS:
#         ../dlx_client -t test_4a_breakpoints.tcl -u <host>:<tile>

source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]
initiate b


proc test_stepping { iss step_args } {
    log "Test stepping, $step_args"

    expect_pc $iss 0

    command $iss "step 1 $step_args"
    expect_pc $iss 4

    command $iss "step 1 $step_args"
    expect_pc $iss 8

    command $iss "step 1 $step_args"
    expect_pc $iss 12

    command $iss "step 3 $step_args"
    expect_pc $iss 24

    expect_r $iss  R1  1 dec
    expect_r $iss  R2  2 dec
    expect_r $iss  R3  3 dec
    expect_r $iss  R4  4 dec
    expect_r $iss  R5  5 dec
    expect_r $iss  R6  6 dec
}

proc test_stepping_with_bp { iss bp_type step_args } {
    log "Test stepping with breakpoint, $bp_type $step_args"
    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 24 $bp_type"
    command $iss "step 20 $step_args"
    expect_pc $iss 16
    command $iss "step 20 $step_args"
    expect_pc $iss 24
    expect_r $iss  R1  1 dec
    expect_r $iss  R2  2 dec
    expect_r $iss  R3  3 dec
    expect_r $iss  R4  4 dec
    expect_r $iss  R5  5 dec
    expect_r $iss  R6  6 dec
}

proc test_resume_bp { iss bp_type step_args } {
    log "Test resume with breakpoint, $bp_type $step_args"
    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 24 $bp_type"
    command $iss "step -1 $step_args"
    expect_pc $iss 16
    command $iss "step -1 $step_args"
    expect_pc $iss 24
    expect_r $iss  R1  1 dec
    expect_r $iss  R6  6 dec
}

proc test_clear_bp { iss bp_type step_args } {
    log "Test breakpoint clear, $bp_type $step_args"
    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 24 $bp_type"
    command $iss "breakpoint mic clear 16"
    command $iss "step -1 $step_args"
    expect_pc $iss 24
    expect_r $iss  R1  1 dec
    expect_r $iss  R6  6 dec
}

proc test_stepping_consecutive_bp { iss bp_type step_args } {
    log "Test consecutive breakpoints with stepping, $bp_type $step_args"
    command $iss "breakpoint mic set 8 $bp_type"
    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 24 $bp_type"
    command $iss "step 10 $step_args"
    expect_pc $iss 8
    command $iss "step 10 $step_args"
    expect_pc $iss 16
    command $iss "step 10 $step_args"
    expect_pc $iss 24
    expect_r $iss  R1  1 dec
    expect_r $iss  R6  6 dec
}

proc test_resume_consecutive_bp { iss bp_type step_args } {
    log "Test consecutive breakpoints with resume, $bp_type $step_args"
    command $iss "breakpoint mic set 8 $bp_type"
    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 24 $bp_type"
    command $iss "step -1 $step_args"
    expect_pc $iss 8
    command $iss "step -1 $step_args"
    expect_pc $iss 16
    command $iss "step -1 $step_args"
    expect_pc $iss 24
    expect_r $iss  R1  1 dec
    expect_r $iss  R6  6 dec
}

proc test_all { iss bp_type step_args } {
    load_program $iss
    test_stepping $iss $step_args
    load_program $iss
    test_stepping_with_bp $iss $bp_type $step_args
    load_program $iss
    test_resume_bp $iss $bp_type $step_args
    load_program $iss
    test_clear_bp $iss $bp_type $step_args
    load_program $iss
    test_stepping_consecutive_bp $iss $bp_type $step_args
    load_program $iss
    test_resume_consecutive_bp $iss $bp_type $step_args
}

test_all b "-hardware 1" ""
test_all b "-software 1" ""

test_all b "-hardware 1" "-sync 1"
test_all b "-software 1" "-sync 1"

finalise b

