#!/usr/bin/env tct_tclsh

package require TctTclUtilsParseArgs

source [file join [file dirname [info script]] .. .. .. bin utils.tcl]

proc usage {} {
  puts "

OCD Compare Script
==================

Options:

   -ref         Reference dump file (default: reg.ref.dmp)
   -iss         ISS dump file (default: reg.iss.dmp)
   -ocd         OCD dump file (default: reg.ocd.dmp)

   -help        This help

"
}

# defaults
set fnm_ocd reg.ocd.dmp
set fnm_iss reg.iss.dmp
set fnm_ref reg.ref.dmp

# parse script args
if {[llength $::argv] > 0} {
  # positional arguments
  set vargs {
  }
  # arg or {arg set}

  # options
  set vopts {
    { -ref      v fnm_ref }
    { -iss      v fnm_iss }
    { -ocd      v fnm_ocd }
    { -help     b help }
  }
  # {-pat* b/v/l var [var_set]} b: boolean, v: variable, l: list

  if {[catch {
    ::tclutils::parse_args $vargs $vopts $::argv [info script]
  } msg]} {
    puts "ERROR: $msg"
    exit 1
  }

  if {[info exists help] && $help} {
    usage
    exit
  }
}

if {![file exists $fnm_ref]} {
  puts "ERROR: Could not find reference dump $fnm_ref"
  exit 1
}

if {![file exists $fnm_iss]} {
  puts "ERROR: Could not find ISS dump $fnm_iss"
  exit 1
}

if {![file exists $fnm_ocd]} {
  puts "ERROR: Could not find OCD dump $fnm_ocd"
  exit 1
}

set OCD [open $fnm_ocd r]
set ISS [open $fnm_iss r]
set REF [open $fnm_ref r]

# get next non-blank non-comment line from file handle $fh
proc get_next_line {fh line} {
  upvar $line l
  while {[gets $fh l] >= 0} {
    # skip blank lines and comments
    if {[regexp {^\s*(//.*)?$} $l]} continue
    return 1
  }
  return 0
}

set pat_cyc_hdr {^\s*Cycle:\s*(\d+),\s*PC:\s*(\d+),\s*Instruction:\s*(.+?)\s*$}

# get next per-cycle dump
proc get_next_cycle_dump fh {
  set pos [tell $fh]
  set first 1
  set vals [list]
  while {[get_next_line $fh line]} {
    if {[regexp $::pat_cyc_hdr $line]} {
      if {!$first} {
        seek $fh $pos
        return [list 1 $cyc $pc $ins $vals]
      }
      regexp $::pat_cyc_hdr $line -> cyc pc ins
      set first 0
    } else {
      if {$first} {
        error "Expected cycle header"
      }
      lappend vals $line
    }
    set pos [tell $fh]
  }
  # EOF
  if {$first} {
    return 0 ; # invalid
  }
  return [list 1 $cyc $pc $ins $vals]
}


set diffs 0
set errors 0
set steps 0

set fmt "%20s %20s %20s %5s"

puts [format $fmt REF ISS OCD ""]
puts [format $fmt --- --- --- ""]
puts [format $fmt $fnm_ref $fnm_iss $fnm_ocd ""]
puts [format $fmt --- --- --- ""]

proc report_compare {v_ref v_iss v_ocd} {
  if {$v_ref eq $v_ocd} {
    set d ok
  } else {
    set d diff
    incr ::diffs
  }
  if {$v_ref ne $v_iss} {
    append d *
  }
  puts [format $::fmt $v_ref $v_iss $v_ocd $d]
}

while 1 {
  lassign [get_next_cycle_dump $REF] r_vld r_cyc r_pc r_ins r_vals
  lassign [get_next_cycle_dump $ISS] i_vld i_cyc i_pc i_ins i_vals
  lassign [get_next_cycle_dump $OCD] o_vld o_cyc o_pc o_ins o_vals


  if {!( $r_vld && $i_vld && $o_vld )} {
    if {!($r_vld || $i_vld || $o_vld)} {
      break
    }
    if {!$r_vld} {
      puts "ERROR: early end of reference dump"
      incr errors
    }
    if {!$i_vld} {
      puts "ERROR: early end of ISS dump"
      incr errors
    }
    if {!$o_vld} {
      puts "ERROR: early end of OCD dump"
      incr errors
    }
    break
  }

  incr steps

  puts "// -------------------------------------------------------------"
  puts "// PC=$r_pc, REF cycle $r_cyc, instr $r_ins"
  puts "// -------------------------------------------------------------"

  report_compare "pc=$r_pc" "pc=$i_pc" "pc=$o_pc"
  foreach rv $r_vals iv $i_vals ov $o_vals {
    report_compare $rv $iv $ov
  }
}

close $OCD
close $ISS
close $REF

puts ""
puts "   --- Total number of differences: $diffs"
puts "   --- Total number of steps: $steps"
if {$errors > 0} {
  puts "   --- Encountered $errors errors"
}

if {$errors != 0 || $diffs != 0} {
  puts "   --- Status: FAILED"
  exit 1
} else {
  puts "   --- Status: PASSED"
  exit 0
}
