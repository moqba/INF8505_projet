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

if {$vpname eq ""} {
  set vpname "UNKNOWN"
  # guess name
  set pc [file split [file normalize $vp]]
  set idx [lsearch -exact $pc [file tail [file dirname [file normalize [info script]]]]]
  if {$idx >= 0 && [expr {($idx+1) < [llength $pc]}]} {
    set vpname [lindex $pc [expr {1 + $idx}]]
  }
}

# pass arguments to run.vpxsh.tcl
set ::env(VIRTUALIZER_MODEL_PATH) $vp
set ::env(APPLICATION) $exe
set ::env(VP_ISS) $vpname
set ::env(CHESS_REPORT_FILENAME) "%PROGRAM%.$vpname.vzer.mem"

# choose a unique file for reporting the ISS server port
set ::env(ISS_RPC_SERVER_PORT_FILE) [file normalize "ISS_RPC_SERVER_PORT.[pid]"]
file delete -force $::env(ISS_RPC_SERVER_PORT_FILE)

# use free port
set ::env(ISS_RPC_SERVER_PORT) 0

# prep work dir
if {$vpworkdir eq ""} {
  set vpworkdir "work.$vpname"
  log "Recreating dir $vpworkdir"
  file delete -force $vpworkdir
  file mkdir $vpworkdir
}
set ::env(VPWORKDIR) $vpworkdir

# chess_exit locations
if {![file exists "$exe.exit"]} {
  log_exec read_elf -e +x -G $exe >& readelf.log
}

# some info
log "setenv VIRTUALIZER_MODEL_PATH $::env(VIRTUALIZER_MODEL_PATH)"
log "setenv APPLICATION $::env(APPLICATION)"
log "setenv VP_ISS $::env(VP_ISS)"
log "setenv CHESS_REPORT_FILENAME $::env(CHESS_REPORT_FILENAME)"
if {[info exists ::env(VPWORKDIR)]} {
  log "setenv VPWORKDIR $::env(VPWORKDIR)"
}
log "setenv ISS_RPC_SERVER_PORT_FILE $::env(ISS_RPC_SERVER_PORT_FILE)"

# run
try {
  # note: without << "", vpxsh hangs
  log_exec vpxsh -s [file join [file dirname [info script]] scr run.vpxsh.tcl] >& vpxsh.log << ""
} finally {
  file delete -force $::env(ISS_RPC_SERVER_PORT_FILE)
}

log "Done"