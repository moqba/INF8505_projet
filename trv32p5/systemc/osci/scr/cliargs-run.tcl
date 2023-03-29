#
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

package require TctTclUtilsParseArgs

source [file join [file dirname [info script]] .. .. .. bin utils.tcl]

# defaults
set iss_set 0
set exe_set 0
set crpt_set 0
set gdb 0
set args_set 0

# parse script args
if {[llength $::argv] > 0} {
  # positional arguments
  set vargs {
    { iss  iss_set }
    { exe  exe_set }
  }
  # arg or {arg set}

  # options
  set vopts {
    { --iss   v  iss      iss_set }
    { --exe   v  exe      exe_set }
    { --crpt  v  crpt     crpt_set }
    { --gdb   b  gdb }
    { --args  v  args     args_set }
  }
  # {"-pat*" b/v/l name}
  # {"-pat*" b/v/l name set}
  # b: boolean, v: variable, l: list

  if {[catch {::tclutils::parse_args $vargs $vopts $::argv [info script]} msg] } {
    puts "ERROR: $msg"
    exit 1
  }
}

if {!$iss_set || !$exe_set} {
  puts "Usage: $::argv0 <iss> <exe>"
  exit 1
}

set orig_iss $iss

if {[file isfile $iss] && [file extension $iss] eq ".prx"} {
  set iss [file dirname $iss]
}

set prjdir [simplify_relpath [file join [file dirname [info script]] .. .. ..]]
set candidates [list \
  $iss \
  [file join $prjdir $iss] \
  [file join $prjdir systemc $iss] \
  [file join $prjdir systemc osci $iss] \
  [file join $prjdir $iss trv32p5_sc] \
  [file join $prjdir systemc $iss trv32p5_sc] \
  [file join $prjdir systemc osci $iss trv32p5_sc] \
]

set ok 0
foreach iss $candidates {
  if {[file isfile $iss]} {
    set ok 1
    break
  }
}

if {!$ok} {
  log "ERROR: invalid ISS $orig_iss, tried\n[join $candidates \n]"
  exit 1
}

if {![file isfile $exe]} {
  log "ERROR: no program $exe"
  exit 1
}
