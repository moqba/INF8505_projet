#
# Tcl script to test PLX on chip debugging TUI.
#
# Verify put/get on registers
#

source "ocd_test.tcl"
set testname [ file rootname [ file tail [info script] ] ]
initiate b


proc test_regs {iss start step} {
    log "test_regs $start $step"
    global r_list
    set value $start
    foreach r $r_list {
        put_r $iss $r $value dec
        set value [expr $value + $step]
    }
    set value $start
    foreach r $r_list {
        expect_r $iss $r $value dec
        set value [expr $value + $step]
    }
}

set r_list { R1 R2 R8 R11 R15 }
test_regs b 0 10
test_regs b 1000 10
test_regs b 0 0
test_regs b 100000 50000

set r_list { TK ACK }
test_regs b 1 0
test_regs b 0 0

set r_list { EN }
test_regs b 12 0
test_regs b  1 0

set r_list { AP }
test_regs b 0 0
test_regs b 3 0
test_regs b 1 0
test_regs b 4 0
test_regs b 2 0
test_regs b 0 0

proc test_mc {iss} {
    log "test_mc"
    command $iss "set_context 0"
    put_r $iss MC 1
    command $iss "set_context 3"
    put_r $iss MC 0

    command $iss "set_context 0"
    expect_r $iss MC 1
    command $iss "set_context 3"
    expect_r $iss MC 0
}

test_mc b

proc test_r {iss} {
    log "test_r"
    command $iss "set_context 0"
    put_r $iss R1    2 dec
    put_r $iss R12 -72 dec
    command $iss "set_context 3"
    put_r $iss R1   42 dec
    put_r $iss R12  72 dec

    command $iss "set_context 0"
    expect_r $iss R1    2 dec
    expect_r $iss R12 -72 dec integer
    command $iss "set_context 3"
    expect_r $iss R1   42 dec
    expect_r $iss R12  72 dec

}

test_r b

finalise b

