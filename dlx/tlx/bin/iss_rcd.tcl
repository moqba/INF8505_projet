#
# Tcl script for regression simulation runs.
#
# Copyright (c) 2014-2021 Synopsys, Inc. This processor model and the associated
# documentation are proprietary to Synopsys, Inc.  This model may only be
# used in accordance with the terms and conditions of a written license
# agreement with Synopsys, Inc.  All other use, reproduction, or distribution
# of this model are strictly prohibited.
#

source [file join [file dirname [file normalize [info script]]] isscaps.tcl]

# defaults
set disable_rcd 0

# parse script args
if {[llength $::iss::tcl_script_args] > 0} {
  # positional arguments
  set vargs {
    # arg or {arg set}
  }

  # options
  set vopts {
    {"-disable-r*" b disable_rcd}
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


# Load program
iss program load $program \
    -do_not_set_entry_pc 1\
    -do_not_load_sp 1\
    -nmlpath $procdir \
    -dwarf2 \
    -disassemble \
    -sourcepath {.}


set mem_file $program.mem
set rcd_file $program.iss.rcd
set prf_file $program.prf
set ipr_file $program.ipr

if {!$disable_rcd && [has_file_output iss R]} {
  puts {INFO: Register change dump enabled}
  catch { iss fileoutput go -file $rcd_file -skip_internal_memories true }
} else {
  puts {INFO: Register change dump disabled}
}

iss fileoutput chess_report set -file $mem_file

# Simulate until end of main
set rtval [catch { iss step -1 } msg]
puts $msg

if { [dict get [iss errors pdg] assert] != 0 } {
  puts "PDG assertion failure"
  iss close
  exit 1
}

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

# Print cycle count
set cycle_count [ lindex [iss info count -cycle] 0 ]
puts "Cycle count : $cycle_count"
set cf [open "$program.cycle_count" w]
puts $cf $cycle_count

iss close

if { [file exists $mem_file] } {
  file rename -force $mem_file ./
}

exit $rtval

