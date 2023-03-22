#
# Tcl script to test dlx on chip debugging TUI.
#
# Test debug break request during delay slots
#


source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]


set addr_end 92
set addr_jump 56
set addr_retaddr 64
set addr_trgt 100
set expected_values {{1024 11} {1028 1111} {1032 111111}}

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
test_resume b 24 28

# break on jump
load_program b
test_resume b $addr_jump $addr_trgt

# break on first delay slot
load_program b
test_resume b [expr 4 + $addr_jump] $addr_trgt

finalise b
