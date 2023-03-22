#
# Tcl script to test PLX on chip debugging TUI.
#
# Verify load/store instructions
#
# Execute as follows:
#  1) start server (echo_server, HDL simulator or jtalk)
#  2) start client ISS:
#         ../plx_client -t test_6_dm.tcl -u <host>:<tile>

source "ocd_test.tcl"
set testname [ file rootname [ file tail [info script] ] ]
initiate b


proc load_program { iss } {
    global value radix pname
    log "Load program $pname"
    command $iss reset
    command $iss "program load $pname"
}

proc test_resume { iss } {
    log "Execute using resume"
    set bpa 44
    command $iss "breakpoint mic set $bpa"
    command $iss "step -1"
    expect_a $iss DMw 1000 16 dec
    expect_a $iss DMw 16 1000 dec
    expect_a $iss DMw 1024 500 dec
}

proc test_stepping { iss } {
    log "Execute using stepping"
    set bpa 44
    command $iss "breakpoint mic set $bpa"
    command $iss "step 100"
    expect_a $iss DMw 1000 16 dec
    expect_a $iss DMw 16 1000 dec
    expect_a $iss DMw 1024 500 dec
}

proc test_bp_resume { iss } {
    log "Execute with breakpoint using resume"
    set bpa 44
    command $iss "breakpoint mic set 28"
    command $iss "breakpoint mic set $bpa"
    command $iss "step -1"
    command $iss "step -1"
    expect_a $iss DMw 1000 16 dec
    expect_a $iss DMw 16 1000 dec
    expect_a $iss DMw 1024 500 dec
}

proc test_bp_stepping { iss } {
    log "Execute with breakpoint using stepping"
    set bpa 44
    command $iss "breakpoint mic set 28"
    command $iss "breakpoint mic set $bpa"
    command $iss "step 100"
    command $iss "step 100"
    expect_a $iss DMw 1000 16 dec
    expect_a $iss DMw 16 1000 dec
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

