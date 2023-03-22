#
# Tcl script to test vlx on chip debugging TUI.
#
# Verify control flow instructions
#
# Execute as follows:
#  1) start server (echo_server, HDL simulator or jtalk)
#  2) start client ISS:
#         ../vlx_client -t test_7a_jrd.tcl -u <host>:<tile>

source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]


set addr_end 120
set addr_jump 80
set addr_retaddr 92
set addr_trgt 140
set expected_values {{1024 110} {1028 11111} {1032 1111111}}

proc test_resume { iss VCS_bp } {
    global addr_end expected_values
    log "Execute program using resume"
    command $iss "breakpoint mic set $addr_end -hardware 1"

    setup_VCS_bp $VCS_bp

    command $iss "step -1"

    # TODO correct expected stop address for jumps
    expect_pc $iss [expr $VCS_bp + 4]
    # due to VCS breakpoint

    command $iss "step -1"

    expect_m  $iss DMw $expected_values
}


initiate b "[file dirname [file normalize [info script]]]/vcs_extdbgbrk.tcl"

# harmless breakpoint
load_program b
test_resume b 36

# break on delayed jump
load_program b
test_resume b $addr_jump

finalise b
