#
# Tcl script for regression simulation runs.
#
# Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

source [file join [file dirname [file normalize [info script]]] isscaps.tcl]

# defaults
set disable_rcd 0
set no_reports 0

# parse script args
if {[llength $::iss::tcl_script_args] > 0} {
  # positional arguments
  set vargs {
    # arg or {arg set}
  }

  # options
  set vopts {
    {"-disable-rcd" b disable_rcd}
    {"-no-reports" b no_reports}
    # {"-pat*" b/v/l name set}
  }
  # b: boolean
  # v: variable
  # l: list

  if { [catch {::tclutils::parse_args $vargs $vopts $::iss::tcl_script_args [info script]} msg] } {
    puts "ERROR: $msg"
    exit 1
  }
}


# Create ISS
set processor [lindex [::iss::processors] 0]
::iss::create $processor iss

set procdir [iss info processor_dir {} 0]

set program $::iss::cmdln_program_name

proc readoptions {fname} {
  if {![file exists $fname]} { return "" }
  set fh [open $fname r]
  set content [read $fh]
  close $fh
  return [string trim $content]
}

# use hw_init of PC and SP regs
#  -do_not_set_entry_pc 1
#  -do_not_load_sp 1
# for profiling & reports
#  -dwarf
#  -disassemble

set program_load_args [list \
  -do_not_set_entry_pc 1 \
  -do_not_load_sp 1 \
]

if {!$no_reports} {
  lappend program_load_args [list \
    -dwarf \
    -disassemble \
    -disassembleoptions "[readoptions $program.cmico]" \
  ]
}

# Load program
iss program load $program {*}$program_load_args


set issname [dict get [tclutils::list2dict [iss info keys iss_option] [iss info issoptions]] iss_name]

set mem_file "$program.$issname.mem"
set rcd_file "$program.$issname.rcd"
set prf_file "$program.$issname.prf"
set ipr_file "$program.$issname.ipr"

if {!$disable_rcd && [has_file_output iss X]} {
  puts {INFO: Register change dump enabled}
  catch { iss fileoutput go -file $rcd_file -skip_internal_memories true }
} else {
  puts {INFO: Register change dump disabled}
}

iss fileoutput chess_report set -file $mem_file

# Simulate until chess_exit
set rtval [catch { iss step -1 } msg]
puts $msg

if { [dict get [iss errors pdg] assert] != 0 } {
  puts "ERROR: PDG assertion failure"
  iss close
  exit 1
}

if {!$no_reports} {
  # Save instruction profile in human readable form
  iss profile save $prf_file

  # Generate instruction profile in form usable for coverage analysis
  iss profile save -type profile-Risk $ipr_file

  # Print maximum stack size
  set stack_info [lindex [iss stack query] 0]
  puts "Stack info: $stack_info"
  if {[expr {[lindex stack_info 5] eq 1}]} {
    # growing up
    set stack_size [expr [lindex $stack_info 4] - [lindex $stack_info 2]]
  } else {
    # growing down
    set stack_size [expr [lindex $stack_info 3] - [lindex $stack_info 4]]
  }
  puts "Stack size: $stack_size"
}

# Print cycle count
set cycle_count [ lindex [iss info count -cycle] 0 ]
puts "Cycle count : $cycle_count"

set cf [open "$program.$issname.cycle_count" w]
puts $cf $cycle_count

if {!$disable_rcd} {
  set cf [open "$program.cycle_count" w]
  puts $cf $cycle_count
}

iss close

exit $rtval

