#
# Tcl script to test PLX on chip debugging TUI.
#
# Verify detach
#

source "ocd_test.tcl"
set testname [ file rootname [ file tail [info script] ] ]
initiate b

iss::iss_debug_client_set pdc_attach 1
# default '::iss::create' also includes 'reset' and 'request'
# 'iss::create' only connects with option 'attach'

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
        $iss debug_client detach
        ::iss::create plx $iss
        $iss debug_client request

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

