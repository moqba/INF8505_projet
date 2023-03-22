#
# Tcl script to test tlx on chip debugging TUI.
#
# Verify control flow instructions
#
# Execute as follows:
#  1) start server (echo_server, HDL simulator or jtalk)
#  2) start client ISS:
#         ../tlx_client -t test_7a_jrd.tcl -u <host>:<tile>

source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]
initiate b

set addr_end 10
set addr_jump 2
set addr_trgt 6

proc test_resume { iss } {
    global addr_end
    log "Execute program using resume"
    command $iss "breakpoint mic set $addr_end -hardware 1"
    command $iss "step -1"
    expect_pc $iss $addr_end
    expect_r $iss R1 19 dec
}

proc test_stepping { iss } {
    global addr_end
    log "Test program using single stepping"
    command $iss "breakpoint mic set $addr_end -hardware 1"
    command $iss "step 200"
    expect_pc $iss $addr_end
    expect_r $iss R1 19 dec
}

proc test_bp_on_jump { iss bp_type } {
    global addr_end addr_jump
    log "Execute program with bp $bp_type on jump"
    command $iss "breakpoint mic set $addr_end  -hardware 1"
    command $iss "breakpoint mic set $addr_jump $bp_type"
    command $iss "step -1"
    expect_pc $iss $addr_jump
    expect_r $iss R1 3 dec
    command $iss "step -1"
    expect_pc $iss $addr_end
    expect_r $iss R1 19 dec
}

proc test_bp_on_trgt { iss bp_type } {
    global addr_end addr_trgt
    log "Execute program with bp $bp_type on target"
    command $iss "breakpoint mic set $addr_end  -hardware 1"
    command $iss "breakpoint mic set $addr_trgt $bp_type"
    command $iss "step -1"
    expect_pc $iss $addr_trgt
    command $iss "step -1"
    expect_pc $iss $addr_end
    expect_r $iss R1 19 dec
}


load_program b
test_resume b

load_program b
test_stepping b

load_program b
test_bp_on_jump b "-hardware 1"
load_program b
test_bp_on_jump b "-software 1"

load_program b
test_bp_on_trgt b "-hardware 1"
load_program b
test_bp_on_trgt b "-software 1"

finalise b

