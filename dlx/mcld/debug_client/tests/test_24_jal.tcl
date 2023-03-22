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

set addr_end 92
set addr_jump 56
set addr_retaddr 64
set addr_trgt 100
set expected_values {{1024 11} {1028 1111} {1032 111111}}


proc test_resume { iss } {
    global addr_end expected_values
    log "Execute program using resume"
    command $iss "breakpoint mic set $addr_end -hardware 1"
    command $iss "step -1"
    expect_m  $iss DMw $expected_values
}

proc test_stepping { iss } {
    global addr_end expected_values
    log "Test program using single stepping"
    command $iss "breakpoint mic set $addr_end -hardware 1"
    command $iss "step 200"
    expect_m  $iss DMw $expected_values
}

proc test_bp_on_call { iss bp_type } {
    global addr_end addr_jump expected_values
    log "Execute program with bp on call ($bp_type)"
    command $iss "breakpoint mic set $addr_end  -hardware 1"
    command $iss "breakpoint mic set $addr_jump $bp_type"
    command $iss "step -1"
    expect_pc $iss $addr_jump
    command $iss "step -1"
    expect_pc $iss $addr_end
    expect_m  $iss DMw $expected_values
}

proc test_bp_on_trgt { iss bp_type } {
    global addr_end addr_trgt expected_values
    log "Execute program with bp on target ($bp_type)"
    command $iss "breakpoint mic set $addr_end  -hardware 1"
    command $iss "breakpoint mic set $addr_trgt $bp_type"
    command $iss "step -1"
    expect_pc $iss $addr_trgt
    command $iss "step -1"
    expect_pc $iss $addr_end
    expect_m  $iss DMw $expected_values
}

proc test_bp_on_return_addr { iss bp_type } {
    global addr_end addr_retaddr expected_values
    log "Execute program with bp on return address ($bp_type)"
    command $iss "breakpoint mic set $addr_end  -hardware 1"
    command $iss "breakpoint mic set $addr_retaddr $bp_type"
    command $iss "step -1"
    expect_pc $iss $addr_retaddr
    command $iss "step -1"
    expect_pc $iss $addr_end
    expect_m  $iss DMw $expected_values
}

load_program b
test_resume b

load_program b
test_stepping b

load_program b
test_bp_on_call b "-hardware 1"
load_program b
test_bp_on_call b "-software 1"

load_program b
test_bp_on_trgt b "-hardware 1"
load_program b
test_bp_on_trgt b "-software 1"

load_program b
test_bp_on_return_addr b "-hardware 1"
load_program b
test_bp_on_return_addr b "-software 1"

finalise b
