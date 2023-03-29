#!/usr/bin/env tct_tclsh
#
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

source [file join [file dirname [info script]] scr cliargs-run.tcl]

if {!$crpt_set} {
  if {$gdb} {
    set sfx "gdb.osci"
  } else {
    set sfx "osci"
  }

  set crpt "%PROGRAM%.[file tail $iss].$sfx.mem"

  # guess
  set pc [file split [file normalize $iss]]
  set idx [lsearch -exact $pc [file tail [file dirname [file normalize [info script]]]]]
  if {$idx >= 0 && [expr {($idx+1) < [llength $pc]}]} {
    set acc [lindex $pc [expr {1 + $idx}]]
    set crpt "%PROGRAM%.$acc.%ISS%.$sfx.mem"
  }
}
set ::env(CHESS_REPORT_FILENAME) $crpt

# choose a unique file for reporting the ISS server port
set ::env(ISS_RPC_SERVER_PORT_FILE) [file normalize "ISS_RPC_SERVER_PORT.[pid]"]
file delete -force $::env(ISS_RPC_SERVER_PORT_FILE)

# use free port
set ::env(ISS_RPC_SERVER_PORT) 0

# some info
log "setenv CHESS_REPORT_FILENAME $::env(CHESS_REPORT_FILENAME)"
log "setenv ISS_RPC_SERVER_PORT_FILE $::env(ISS_RPC_SERVER_PORT_FILE)"

try {
  # launch in background
  set pid [log_exec $iss >& oscisim.log &]
  log "Launched OSCI SystemC ISS with PID $pid"

  # record pid
  set fh [open .PID w]
  puts $fh $pid
  close $fh

  # wait for RPC server port
  set seconds 0
  while {![file exists $::env(ISS_RPC_SERVER_PORT_FILE)] || ![file size $::env(ISS_RPC_SERVER_PORT_FILE)]} {
    after 1000
    incr seconds
    if {$seconds > 30} {
      log "ERROR: No $::env(ISS_RPC_SERVER_PORT_FILE) after 30s"
      kill 1 $pid
      exit 1
    }
  }

  if {$gdb} {
    # collect asip2gdb args
    set proc ::iss
    set port [read_port_file $::env(ISS_RPC_SERVER_PORT_FILE)]

    # assemble cmd
    set cmd [list asip2gdb -l localhost,$port -e $exe -iss-name $proc]

    # prep gdb commands
    set gdbcmd [format {
      iss eval {%s fileoutput chess_report set -file "%s.%s.[dict get [tclutils::list2dict [%s info keys iss_option] [%s info issoptions]] iss_name].gdb.osci.mem"}
      continue
      quit
    } $proc $exe $acc $proc $proc]

    set lines [lmap line [split [string trim $gdbcmd] "\n"] {string trim $line}]
    set gdbcmd [join $lines "\n"]

    set fh [open gdbcmds.txt w]
    puts $fh $gdbcmd
    close $fh

    lappend cmd --command=gdbcmds.txt

    # execute asip2gdb
    set rc [log_exec {*}$cmd >& simrun.log]

  } else {
    # collect script args
    set scr [file join [file dirname [info script]] scr run_sc_dbg.tcl]
    set proc ::iss

    # assemble script command
    set cmd [list $scr $exe $proc]
    if {$args_set} {
      lappend cmd {*}$args
    }

    # execute driver script
    set rc [log_exec {*}$cmd >& simrun.log]
  }

  # cleanup
  file delete -force $::env(ISS_RPC_SERVER_PORT_FILE)

} on error {msg opts} {

  log "Fail: $msg"
  kill 1 $pid
  set rc 1

} finally {

  kill 1 $pid

}

log "Done"
exit $rc
