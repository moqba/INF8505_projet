#
# Tcl script to test dlx on chip debugging TUI.
#
# Verify control flow instructions
#
# Execute as follows:
#  1) start server (echo_server, HDL simulator or jtalk)
#  2) start client ISS:
#         ../dlx_client -t test_7a_jrd.tcl -u <host>:<tile>

source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]
initiate b


set addr_end 112
set addr_doi 64
set addr_bol 76
set addr_retaddr 84
set expected_values {{1024 11} {1028 11111} {1032 21111} {1036 31111} {1040 131111}}


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

proc test_bp_on_doi { iss bp_type } {
    global addr_end addr_doi expected_values
    log "Execute program with bp on doi ($bp_type)"
    command $iss "breakpoint mic set $addr_end  -hardware 1"
    command $iss "breakpoint mic set $addr_doi $bp_type"
    command $iss "step -1"
    expect_pc $iss $addr_doi
    command $iss "step -1"
    expect_pc $iss $addr_end
    expect_m  $iss DMw $expected_values
}

proc test_bp_on_bol { iss bp_type } {
    global addr_end addr_bol expected_values
    log "Execute program with bp on BOL ($bp_type)"
    command $iss "breakpoint mic set $addr_end  -hardware 1"
    command $iss "breakpoint mic set $addr_bol $bp_type"
    command $iss "step -1"
    expect_pc $iss $addr_bol
    command $iss "step -1"
    expect_pc $iss $addr_bol
    command $iss "step -1"
    expect_pc $iss $addr_bol
    command $iss "step -1"
    expect_pc $iss $addr_end
    expect_m  $iss DMw $expected_values
}

proc test_bp_on_eolP1 { iss bp_type } {
    global addr_end addr_retaddr expected_values
    log "Execute program with bp on EOL + 1 ($bp_type)"
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
test_bp_on_doi b "-hardware 1"
load_program b
test_bp_on_doi b "-software 1"

load_program b
test_bp_on_bol b "-hardware 1"
load_program b
test_bp_on_bol b "-software 1"

load_program b
test_bp_on_eolP1 b "-hardware 1"
load_program b
test_bp_on_eolP1 b "-software 1"

finalise b
