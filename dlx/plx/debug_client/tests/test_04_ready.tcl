#
# Tcl script to test PLX on chip debugging TUI.
#
# Verify ocd_rdy flow control
#

source "ocd_test.tcl"
set testname [ file rootname [ file tail [info script] ] ]
initiate b

proc test_fc {iss} {
    log "test_fc"
    # 8 pages have cache miss on write and on read
    set L {0 1 2 3 4 5 6 7}
    foreach x $L {
        set adr [expr 16*$x]
        set val [expr  1+$x]
        put_a $iss DMb $adr $val dec
    }
    foreach x $L {
        set adr [expr 16*$x]
        set val [expr  1+$x]
        expect_a $iss DMb $adr $val dec
    }
}

test_fc b

finalise b




