#
# Tcl script to test tlx on chip debugging TUI.
#
# Test debug break request during delay slots
#
# Execute as follows:
#  1) start server (echo_server, HDL simulator or jtalk)
#  2) start client ISS:
#         ../tlx_client -t test_7a_jrd.tcl -u <host>:<tile>

source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]


set addr_end 27
set addr_jump 17
set addr_retaddr 20
set addr_trgt 116
set expected_values {{1024 11} {1028 11111} {1032 1111111}}

proc test_resume { iss VCS_bp exp_stopaddr } {
    global addr_end expected_values
    log "Execute program using resume"
    command $iss "breakpoint mic set $addr_end -hardware 1"

    setup_VCS_bp $VCS_bp

    command $iss "step -1"

    expect_pc $iss $exp_stopaddr
    # due to VCS breakpoint

    if { $addr_end != [command $iss "get PC"] } {
        # guard against failed VCS breakpoint
        command $iss "step -1"
    }

    expect_m  $iss DMw $expected_values
}


initiate b "[file dirname [file normalize [info script]]]/vcs_extdbgbrk.tcl"

# harmless breakpoint
load_program b
test_resume b 6 7

# break on jump
load_program b
test_resume b $addr_jump $addr_trgt

# break on first delay slot
load_program b
test_resume b [expr 1 + $addr_jump] $addr_trgt

# break on second delay slot
load_program b
test_resume b [expr 2 + $addr_jump] $addr_trgt

finalise b
