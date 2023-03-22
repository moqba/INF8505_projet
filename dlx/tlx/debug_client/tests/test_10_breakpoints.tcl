#
# Tcl script to test TLX on chip debugging TUI.
#
# Verify stepping and breakpoints
#

source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]
initiate b


proc test_step { iss } {
    log "test_step"
    global value radix pname

    command $iss reset
    command $iss "program load $pname"

    command $iss "step 1 "
    expect_pc $iss 1
    expect_r $iss R1 1 dec

    command $iss "step 1 "
    expect_pc $iss 2
    expect_r $iss R2 2 dec

    command $iss "step 3 "
    expect_pc $iss 5
    expect_r $iss R5 5 dec
}

proc test_go { iss } {
    log "test_go"
    global value radix pname

    command $iss reset
    command $iss "program load $pname"

    set bpa 6
    command $iss "breakpoint mic set $bpa"
    command $iss "step -1 "
    expect_pc $iss $bpa
    expect_r $iss R1 1 dec
    expect_r $iss R2 2 dec
    expect_r $iss R6 6 dec
}

proc test_step_n { iss } {
    log "test_step_n"
    global value radix pname

    command $iss reset
    command $iss "program load $pname"

    set bpa 6
    command $iss "breakpoint mic set $bpa"
    command $iss "step 100 "
    expect_pc $iss $bpa
    expect_r $iss R1 1 dec
    expect_r $iss R2 2 dec
    expect_r $iss R6 6 dec
}

proc test_step_bp { iss } {
    log "test_step_bp"
    global value radix pname

    command $iss reset
    command $iss "program load $pname"

    command $iss "breakpoint mic set 2"
    command $iss "breakpoint mic set 3"
    command $iss "breakpoint mic set 4"
    command $iss "breakpoint mic set 5"

    command $iss "step 100 "
    expect_pc $iss 2
    command $iss "step 100 "
    expect_pc $iss 3
    command $iss "step 100 "
    expect_pc $iss 4
    command $iss "step 100 "
    expect_pc $iss 5
}

test_step b
test_go b
test_step_n b
test_step_bp b

finalise b

