#
# Tcl script to test DLX on chip debugging TUI.
#
# Verify put/get on memories
#

source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]
initiate b


array set dmb_value {
  0   00
  1   01
  2   02
  3   03
  4   80
  5   ff
  6   fe
  7   be
}

array set dmw_value {
  0   00000001
  1   80000000
  2   0000cafe
  3   cafebabe
}


proc test_dm { iss } {
    log "test_dm"
    global dmb_value dmw_value

    set mem DMb
    set L { 0 1 2 3 4 5 6 7 }
    foreach x $L {
	set addr [expr 100+$x]
        put_a $iss $mem $addr $dmb_value($x) 
    }

    foreach x $L {
	set addr [expr 100+$x]
        expect_a $iss $mem $addr $dmb_value($x) 
    }

    set mem DMw
    set L { 0 1 2 3 }
    foreach x $L {
	set addr [expr 40+4*$x]
        put_a $iss $mem $addr $dmw_value($x) 
    }

    foreach x $L {
	set addr [expr 40+4*$x]
        expect_a $iss $mem $addr $dmw_value($x) 
    }
}

array set pm_value {
  0   00000000
  1   00000001
  2   0000f000
  3   000a0003
  4   000000fe
  5   89000000
  6   0000cafe
  7   cafebabe
}

array set pmb_value {
  0   00
  1   01
  2   80
  3   75
  4   fe
  5   6a
  6   fe
  7   be
}

proc test_pm { iss } {
    log "test_pm"
    global pm_value pmb_value

    set mem PM
    set L { 0 1 2 3 4 5 6 7 }
    foreach x $L {
	set addr [expr 40+4*$x]
        put_a $iss $mem $addr $pm_value($x) 
    }

    foreach x $L {
	set addr [expr 40+4*$x]
        expect_a $iss $mem $addr $pm_value($x) 
    }

    set mem PMb
    set L { 0 1 2 3 4 5 6 7 }
    foreach x $L {
	set addr [expr 100+$x]
        put_a $iss $mem $addr $pmb_value($x) 
    }

    foreach x $L {
	set addr [expr 100+$x]
        expect_a $iss $mem $addr $pmb_value($x) 
    }
}

proc test_loop_16 { iss mem } {
    log "test_loop_16 $mem"
    set a 0
    set N 64
    while {$a<$N} {
        set v [expr $a + 100]
        put_a $iss $mem $a $v dec
        incr a
    }
    set a 0
    while {$a<$N} {
        set v [expr $a + 100]
        expect_a $iss $mem $a $v dec
        incr a
    }
}


test_dm b
test_pm b

# test_loop_16 b PM
# test_loop_16 b DM

finalise b

