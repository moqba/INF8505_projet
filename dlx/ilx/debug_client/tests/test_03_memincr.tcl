#
# Tcl script to test ILX on chip debugging TUI.
#
# Verify put/get on range of memory locations
#

source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]
initiate b


proc test_dm { iss start amount } {
    log "test_dm $start $amount "
    set mem DMw
    set last [expr $start + $amount]
    set a $start
    while {$a<$last} {
        set v [expr $a + 100]
        put_a $iss $mem $a $v dec
        incr a  4
    }

    set last [expr $start + $amount]
    set a $start
    while {$a<$last} {
        set v [expr $a + 100]
        expect_a $iss $mem $a $v dec
        incr a  4
    }
}

test_dm b 0 128
test_dm b 512 44
test_dm b 1024 12

finalise b

