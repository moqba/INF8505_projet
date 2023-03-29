#
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#
# for build.tcl and clean.tcl

package require TctTclUtilsParseArgs

source [file join [file dirname [info script]] .. .. .. bin utils.tcl]

# defaults
set issprx ""
set issprx_set 0

# parse script args
if {[llength $::argv] > 0} {
  # positional arguments
  set vargs {
    { issprx issprx_set }
  }
  # arg or {arg set}

  # options
  set vopts {
  }
  # {"-pat*" b/v/l name}
  # {"-pat*" b/v/l name set}
  # b: boolean, v: variable, l: list

  if {[catch {::tclutils::parse_args $vargs $vopts $::argv [info script]} msg] } {
    puts "ERROR: $msg"
    exit 1
  }
}

if {!$issprx_set} {
  puts "Usage: $::argv0 <issprx>"
  exit 1
}

set orig_issprx $issprx

set prjdir [simplify_relpath [file join [file dirname [info script]] .. .. ..]]
set candidates [list \
  $issprx \
  [file join $prjdir $issprx] \
  [file join $prjdir systemc $issprx] \
  [file join $prjdir systemc virtualizer $issprx] \
  [file join $issprx trv32p5_sc.prx] \
  [file join $prjdir $issprx trv32p5_sc.prx] \
  [file join $prjdir systemc $issprx trv32p5_sc.prx] \
  [file join $prjdir systemc virtualizer $issprx trv32p5_sc.prx] \
]

set ok 0
foreach issprx $candidates {
  if {[file isfile $issprx] && [file extension $issprx] eq ".prx"} {
    set ok 1
    break
  }
}

# no file? end of luck
if {!$ok} {
  puts "Invalid: $orig_issprx, tried\n[join $candidates \n]"
  exit 1
}
