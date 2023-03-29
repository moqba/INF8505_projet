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

source [file join [file dirname [info script]] scr cliargs-build.tcl]

cd [file dirname $issprx]

log "Building '[file tail [file dirname $issprx]]'"

# build ISS; creates import_pct.tcl
if {[chessmk [file tail $issprx] >& build_issprx.log]} {
  log "ERROR: ISS build failed"
  exit 1
}

# choose a unique file for reporting the ISS server port
set ::env(ISS_RPC_SERVER_PORT_FILE) "[pwd]/ISS_RPC_SERVER_PORT_FILE.[pid]"
file delete -force $::env(ISS_RPC_SERVER_PORT_FILE)

# build will launch ISS - use free port
set ::env(ISS_RPC_SERVER_PORT) 0

if {[log_exec pcsh import_pct.tcl >& pcsh_import.log]} {
  log "ERROR: import pct failed"
  exit 1
}

if {[log_exec pcsh create_platform.tcl >& pcsh_create_platform.log]} {
  log "ERROR: create platform failed"
  exit 1
}

cd export
if {[log_exec pcsh sim_build.tcl >& ../sim_build.log]} {
  log "ERROR: sim build failed"
  exit 1
}
cd ..

file delete -force $::env(ISS_RPC_SERVER_PORT_FILE)

log "Done"