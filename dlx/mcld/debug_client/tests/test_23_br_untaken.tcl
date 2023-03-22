#
# Tcl script to test mcld on chip debugging TUI.
#
# Verify control flow instructions
#
# Execute as follows:
#  1) start server (echo_server, HDL simulator or jtalk)
#  2) start client ISS:
#         ../mcld_client -t test_7a_jrd.tcl -u <host>:<tile>

source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]
initiate b


proc test_resume { iss } {
    log "Execute program using resume"
    set bpa 48
    command $iss "breakpoint mic set $bpa"
    command $iss "step -1"
    expect_pc $iss $bpa
    expect_r $iss R6 21 dec
}

proc test_stepping { iss } {
    log "Test program using single stepping"
    set bpa 48
    command $iss "breakpoint mic set $bpa"
    command $iss "step 200"
    expect_pc $iss $bpa
    expect_r $iss R6 21 dec
}

load_program b
test_resume b

load_program b
test_stepping b

finalise b

