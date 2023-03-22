#
# Tcl script to test PLX on chip debugging TUI.
#
# Verify break (async stop)
#

source "ocd_test.tcl"
set testname [ file rootname [ file tail [info script] ] ]
initiate b

proc test { iss } {
    global lf error_count
    load_program $iss

    set val [$iss get R2]
    puts $lf $val
    if { $val != 0 } {
        puts $lf "expected core reset !!!"
        incr error_count
     }

    for {set x 0} {$x<3} {incr x} {
        after 1000 $iss debug_client request
        $iss step -1

        set val [$iss get R2]
        puts $lf $val
        if { $val == 0 } {
            puts $lf "not expected core reset !!!"
            incr error_count
         }
    }

    flush $lf
}

test b

finalise b

