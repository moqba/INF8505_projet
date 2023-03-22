#
# Tcl script to test TLX on chip debugging TUI.
#
# Verify put/get on registers
#

source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]
initiate b


proc test_regs {iss start step} {
    log "test_regs $start $step"
    set value $start
    foreach r { R1 R2 R8 R14 R15 } {
        put_r $iss $r $value dec
        set value [expr $value + $step]
    }

    set value $start
    foreach r { R1 R2 R8 R14 R15 } {
        expect_r $iss $r $value dec
        set value [expr $value + $step]
    }
}

test_regs b 0 10
test_regs b 1000 10
test_regs b 0 0
test_regs b 100000 50000

finalise b

