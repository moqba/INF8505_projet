#
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#
# for run.tcl

package require TctTclUtilsParseArgs

source [file join [file dirname [info script]] .. .. .. bin utils.tcl]

# defaults
set vp_set 0
set exe_set 0
set vpname ""
set vpworkdir ""

# parse script args
if {[llength $::argv] > 0} {
  # positional arguments
  set vargs {
    { vp   vp_set }
    { exe  exe_set }
  }
  # arg or {arg set}

  # options
  set vopts {
    { --vp    v  vp      vp_set }
    { --exe   v  exe     exe_set }
    { --name  v  vpname  }
    { --vpwd  v  vpworkdir }
  }
  # {"-pat*" b/v/l name}
  # {"-pat*" b/v/l name set}
  # b: boolean, v: variable, l: list

  if {[catch {::tclutils::parse_args $vargs $vopts $::argv [info script]} msg] } {
    puts "ERROR: $msg"
    exit 1
  }
}

if {!$vp_set || !$exe_set} {
  puts "Usage: $::argv0 <vp> <exe>"
  exit 1
}

set orig_vp $vp

if {[file isfile $vp] && [file extension $vp] eq ".prx"} {
  set vp [file dirname $vp]
}

if {[file isfile $vp] && [file tail $vp] ne "sim"} {
  set vp [file dirname $vp]
}

set prjdir [simplify_relpath [file join [file dirname [info script]] .. .. ..]]
set candidates [list \
  $vp \
  [file join $vp sim] \
  [file join $vp export Debug sim] \
  [file join $prjdir $vp export Debug sim] \
  [file join $prjdir systemc virtualizer $vp export Debug sim] \
]

set ok 0
foreach vp $candidates {
  if {[file isfile $vp]} {
    set ok 1
    break
  }
}

if {!$ok} {
  log "ERROR: invalid VP $orig_vp, tried\n[join $candidates \n]"
  exit 1
}
