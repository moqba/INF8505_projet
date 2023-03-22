#
# Tcl script to test PLX on chip debugging TUI.
#
# Verify stepping and watchpoints
#
# Execute as follows:
#  1) start server (echo_server, HDL simulator or jtalk)
#  2) start client ISS:
#         ../plx_client -t test_15_watchpoint.tc -u <host>:<tile>

source "ocd_test.tcl"
set testname [ file rootname [ file tail [info script] ] ]
initiate b

proc step_persist {iss count} {
  command $iss "step $count"
  while { [$iss get ACK] == 0} {
    log "retry"
    command $iss "step 1"
  }
}
proc test_sb { iss } {
    log "Test byte store"
    command $iss "watchpoint set DMb 16 -write true"
    command $iss "watchpoint set DMb 17 -write true"
    #command $iss "step 20"
    step_persist $iss 20
    expect_pc $iss 24
    expect_a $iss DMb 16 120 dec
    expect_a $iss DMb 17 0 dec
    expect_a $iss DMb 18 0 dec
    #command $iss "step 20"
    step_persist $iss 20
    expect_pc $iss 28
    expect_a $iss DMb 16 120 dec
    expect_a $iss DMb 17 120 dec
    expect_a $iss DMb 18 0 dec
    command $iss "watchpoint clear -all"
}

proc test_sh { iss } {
    log "Test short store"
    command $iss "watchpoint set DMb 20 -write true"
    command $iss "watchpoint set DMh 22 -write true"
    #command $iss "step 20"
    step_persist $iss 20
    expect_pc $iss 44
    expect_a $iss DMh 20 22136 dec
    expect_a $iss DMh 22 0 dec
    expect_a $iss DMh 24 0 dec
    #command $iss "step 20"
    step_persist $iss 20
    expect_pc $iss 48
    expect_a $iss DMh 20 22136 dec
    expect_a $iss DMh 22 22136 dec
    expect_a $iss DMh 24 0 dec
    command $iss "watchpoint clear -all"
}

proc test_sw { iss } {
    log "Test word store"
    command $iss "watchpoint set DMb 32 -write true"
    command $iss "watchpoint set DMw 36 -write true"
    #command $iss "step 20"
    step_persist $iss 20
    expect_pc $iss 64
    expect_a $iss DMw 32 305419896 dec
    expect_a $iss DMw 36 0 dec
    expect_a $iss DMw 40 0 dec
    #command $iss "step 20"
    step_persist $iss 20
    expect_pc $iss 68
    expect_a $iss DMw 32 305419896 dec
    expect_a $iss DMw 36 305419896 dec
    expect_a $iss DMw 40 0 dec
    command $iss "watchpoint clear -all"
}

load_program b
test_sb b
test_sh b
test_sw b

finalise b

