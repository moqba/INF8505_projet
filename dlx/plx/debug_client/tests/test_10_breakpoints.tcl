#
# Tcl script to test PLX on chip debugging TUI.
#
# Verify stepping and breakpoints
#

source "ocd_test.tcl"
set testname [ file rootname [ file tail [info script] ] ]
initiate b


proc test_step { iss } {
    log "test_step"
    load_program $iss

    command $iss "step 1 "
    expect_pc $iss 4
    expect_r $iss R1 1 dec

    command $iss "step 1 "
    expect_pc $iss 8
    expect_r $iss R2 2 dec

    command $iss "step 3 "
    expect_pc $iss 20
    expect_r $iss R5 5 dec
}

proc test_go { iss } {
    log "test_go"
    load_program $iss

    set bpa 20
    command $iss "breakpoint mic set $bpa"
    command $iss "step -1 "
    expect_break $iss 1
    expect_break_context $iss 0
    expect_pc $iss $bpa
    expect_r $iss R1 1 dec
    expect_r $iss R2 2 dec
    expect_r $iss R6 0 dec
}

proc test_step_n { iss } {
    log "test_step_n"
    load_program $iss

    set bpa 20
    command $iss "breakpoint mic set $bpa"
    command $iss "step 100 "
    expect_break $iss 1
    expect_break_context $iss 0
    expect_pc $iss $bpa
    expect_r $iss R1 1 dec
    expect_r $iss R2 2 dec
    expect_r $iss R6 0 dec
}

proc test_step_bp { iss } {
    log "test_step_bp"
    load_program $iss

    command $iss "breakpoint mic set 8"
    command $iss "breakpoint mic set 12"
    command $iss "breakpoint mic set 16"
    command $iss "breakpoint mic set 20"

    command $iss "step 100 "
    expect_pc $iss 8
    command $iss "step 100 "
    expect_pc $iss 12
    command $iss "step 100 "
    expect_pc $iss 16
    command $iss "step 100 "
    expect_pc $iss 20
}

test_step b
test_go b
test_step_n b
test_step_bp b

finalise b

