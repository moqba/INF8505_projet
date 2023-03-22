#
# Tcl script to test dlx on chip debugging TUI.
#
# Verify load/store instructions
#
# Execute as follows:
#  1) start server (echo_server, HDL simulator or jtalk)
#  2) start client ISS:
#         ../dlx_client -t test_6_dm.tcl -u <host>:<tile>

source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]
initiate b


proc test_resume { iss } {
    log "Execute using resume"
    set bpa 44
    command $iss "breakpoint mic set $bpa"
    command $iss "step -1"
    expect_a $iss DMw 1000 256 dec
    expect_a $iss DMw 256 1000 dec
    expect_a $iss DMw 1024 500 dec
}

proc test_stepping { iss } {
    log "Execute using stepping"
    set bpa 44
    command $iss "breakpoint mic set $bpa"
    command $iss "step 100"
    expect_a $iss DMw 1000 256 dec
    expect_a $iss DMw 256 1000 dec
    expect_a $iss DMw 1024 500 dec
}

proc test_bp_resume { iss } {
    log "Execute with breakpoint using resume"
    set bpa 44
    command $iss "breakpoint mic set 28"
    command $iss "breakpoint mic set $bpa"
    command $iss "step -1"
    command $iss "step -1"
    expect_a $iss DMw 1000 256 dec
    expect_a $iss DMw 256 1000 dec
    expect_a $iss DMw 1024 500 dec
}

proc test_bp_stepping { iss } {
    log "Execute with breakpoint using stepping"
    set bpa 44
    command $iss "breakpoint mic set 28"
    command $iss "breakpoint mic set $bpa"
    command $iss "step 100"
    command $iss "step 100"
    expect_a $iss DMw 1000 256 dec
    expect_a $iss DMw 256 1000 dec
    expect_a $iss DMw 1024 500 dec
}


load_program b
test_resume b

load_program b
test_stepping b

load_program b
test_bp_resume b

load_program b
test_bp_stepping b

finalise b

