#
# Tcl script to test flx on chip debugging TUI.
#
# Test debug break request during delay slots
#


source [file join [file dirname [file normalize [info script]]] ocd_test.tcl]
set testname [ file rootname [ file tail [info script] ] ]


set addr_end 112
set addr_doi 64
set addr_bol 76
set addr_eol 80
set addr_retaddr 84
set expected_values {{1024 11} {1028 11111} {1032 21111} {1036 31111} {1040 131111}}

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

proc test_resume2 { iss VCS_bp exp_stopaddr } {
    global addr_end expected_values
    log "Execute program using resume"
    command $iss "breakpoint mic set $addr_end -hardware 1"

    foreach bp $VCS_bp exp $exp_stopaddr {
      setup_VCS_bp $bp
      command $iss "step -1"
      expect_pc $iss $exp

      if { $addr_end == [command $iss "get PC"] } {
          # guard against failed VCS breakpoint
          break
      }
    }

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

# break on doi
load_program b
test_resume b $addr_doi $addr_bol

# break on first delay slot
load_program b
test_resume b [expr 4 + $addr_doi] $addr_bol

# break on second delay slot
load_program b
test_resume b [expr 8 + $addr_doi] $addr_bol

# break on first instruction of loop, first iteration
load_program b
test_resume b $addr_bol [expr 4 + $addr_bol]

# break on first instruction of loop, fall iteration
load_program b
test_resume2 b [list $addr_bol $addr_bol $addr_bol] [list [expr 4 + $addr_bol] [expr 4 + $addr_bol] [expr 4 + $addr_bol]]

# break on end of loop, first iteration
load_program b
test_resume b $addr_eol $addr_bol

# break on end of loop, each iteration
load_program b
test_resume2 b [list $addr_eol $addr_eol $addr_eol] [list $addr_bol $addr_bol $addr_retaddr]

# break on first instruction after loop
load_program b
test_resume b $addr_retaddr [expr 4 + $addr_retaddr]

finalise b
