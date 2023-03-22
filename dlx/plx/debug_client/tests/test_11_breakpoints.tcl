#
# Tcl script to test PLX on chip debugging TUI.
#
# Verify stepping and breakpoints
#
# Execute as follows:
#  1) start server (echo_server, HDL simulator or jtalk)
#  2) start client ISS:
#         ../plx_client -t test_4a_breakpoints.tcl -u <host>:<tile>

source "ocd_test.tcl"
set testname [ file rootname [ file tail [info script] ] ]
initiate b


proc test_stepping { iss } {
    log "Test stepping"
    load_program $iss

    expect_pc $iss 0
    command $iss "step 1"
    expect_pc $iss 4
    command $iss "step 1"
    expect_pc $iss 8
    command $iss "step 1"
    expect_pc $iss 12
    command $iss "step 2"
    expect_pc $iss 20

    expect_r $iss  R1  1 dec
    expect_r $iss  R2  2 dec
    expect_r $iss  R3  3 dec
    expect_r $iss  R4  4 dec
    expect_r $iss  R5  5 dec
    expect_r $iss  R6  0 dec
}

proc test_stepping_with_bp { iss bp_type } {
    log "Test stepping with breakpoint"
    load_program $iss

    expect_a $iss PM 16 54050005 hex

    command $iss "breakpoint mic set 16 $bp_type"
    if { $bp_type == "-software 1" } {
        expect_a $iss PM 16 b8000000 hex
    }
    command $iss "breakpoint mic set 20 $bp_type"

    command $iss "step 20"
    expect_break_context $iss 0 $bp_type
    expect_pc $iss 16

    command $iss "step 20"
    expect_break_context $iss 0 $bp_type
    expect_pc $iss 20

    expect_r $iss  R1  1 dec
    expect_r $iss  R2  2 dec
    expect_r $iss  R3  3 dec
    expect_r $iss  R4  4 dec
    expect_r $iss  R5  5 dec
    expect_r $iss  R6  0 dec
}

proc test_resume_with_bp { iss bp_type} {
    log "Test resume with breakpoint"
    load_program $iss

    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 20 $bp_type"

    command $iss "step -1"
    expect_break_context $iss 0 $bp_type
    expect_pc $iss 16

    command $iss "step -1"
    expect_break_context $iss 0 $bp_type
    expect_pc $iss 20

    expect_r $iss  R5  5 dec
    expect_r $iss  R6  0 dec
}

proc test_clear_bp { iss bp_type } {
    log "Test breakpoint clear"
    load_program $iss

    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 20 $bp_type"
    command $iss "breakpoint mic clear 16"

    command $iss "step -1"
    expect_pc $iss 20

    expect_r $iss  R5  5 dec
    expect_r $iss  R6  0 dec
}

proc test_stepping_consecutive_bp { iss bp_type } {
    log "Test consecutive breakpoints with stepping"
    load_program $iss

    command $iss "breakpoint mic set 8 $bp_type"
    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 20 $bp_type"

    command $iss "step 10"
    expect_pc $iss 8

    command $iss "step 10"
    expect_pc $iss 16

    command $iss "step 10"
    expect_pc $iss 20

    expect_r $iss  R5  5 dec
    expect_r $iss  R6  0 dec
}

proc test_resume_consecutive_bp { iss bp_type } {
    log "Test consecutive breakpoints with resume"
    load_program $iss

    command $iss "breakpoint mic set 8 $bp_type"
    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "breakpoint mic set 20 $bp_type"

    command $iss "step -1"
    expect_pc $iss 8

    command $iss "step -1"
    expect_pc $iss 16

    command $iss "step -1"
    expect_pc $iss 20

    expect_r $iss  R5  5 dec
    expect_r $iss  R6  0 dec
}

proc test_resume_in_other_thread { iss bp_type } {
    log "Test resume in other thread"
    load_program $iss
    command $iss "breakpoint mic set 8 $bp_type"
    command $iss "breakpoint mic set 16 $bp_type"
    command $iss "step -1"
    expect_break_context $iss 0 $bp_type
    expect_pc $iss 8
    command $iss "set_context 1"
    command $iss "step -1"
    expect_break_context $iss 0 $bp_type
    expect_pc $iss 0
    command $iss "set_context 0"
    expect_pc $iss 8
}

proc test_all { iss bp_type } {
    test_stepping $iss
    test_stepping_with_bp $iss $bp_type
    test_resume_with_bp $iss $bp_type
    test_clear_bp $iss $bp_type
    test_stepping_consecutive_bp $iss $bp_type
    test_resume_consecutive_bp $iss $bp_type
    test_resume_in_other_thread $iss $bp_type
}

test_all b "-hardware 1"
test_all b "-software 1"

finalise b

