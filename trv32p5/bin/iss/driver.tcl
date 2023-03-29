#
# Tcl script for regression simulation runs.
#
# Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

proc usage {} {
  puts "

ISS driver script
=================

Options:

   -NOrcd       Do not generate register change dump
   -nmlcov      Generate *.ipr reports for nML coverage collection
   -ia          Generate IA compatible RCD file
   -max N       Maximum number of simulation cycles (default: -1)
   -NOchecks    Disable runtime checks

   -help        This help

"
}

proc log {args} {
  puts "[file tail [info script]]: [join $args]"
}

# defaults
set rcd 1
set nmlcov 0
set rcd_ia 0
set max_cycles -1
set checks 1

# ------------------------------------------------------------------------------
# Process script arguments

if {[llength $::iss::tcl_script_args] > 0} {
  # positional arguments
  set vargs {}

  # options
  set vopts {
    { -NOrcd    b NOrcd }
    { -nmlcov   b nml_coverage }
    { -ia       b rcd_ia }
    { -max      v max_cycles }
    { -NOchecks b NOchecks }
    { -help     b help }
  }
  # {-pat* b/v/l var [var_set]} b: boolean, v: variable, l: list

  if {[catch {
    ::tclutils::parse_args $vargs $vopts $::iss::tcl_script_args [info script]
  } msg]} {
    log "ERROR: $msg"
    exit 1
  }

  if {[info exists help] && $help} {
    usage
    exit
  }

  if {[info exists NOrcd] && $NOrcd} {
    set rcd 0
  }
  if {[info exists NOchecks] && $NOchecks} {
    set checks 0
  }
}

# ------------------------------------------------------------------------------

# Create ISS
set processor [lindex [::iss::processors] 0]
::iss::create $processor iss

set program $::iss::cmdln_program_name

proc readfile {fname} {
  if {[file exists $fname]} {
    set fh [open $fname r]
    set content [read $fh]
    close $fh
    return [string trim $content]
  }
}

# use hw_init of PC and SP regs
set program_load_args [list \
  -do_not_set_entry_pc 1 \
  -do_not_load_sp 1 \
]

if {$nmlcov} {
  # for profiling
  lappend program_load_args \
    -dwarf \
    -disassemble \
    -disassembleoptions [readfile $program.cmico]
}

# Load program
iss program load $program {*}$program_load_args

# Get name of ISS
set iss_opts [tclutils::list2dict [iss info keys iss_option] [iss info issoptions]]
set iss_name [dict get $iss_opts iss_name]
#set ia [dict get $iss_opts instr_accurate_mode]

# ------------------------------------------------------------------------------
# Configure RCD trace

if {$rcd} {
  set args [list]
  if {$rcd_ia} {
    # CA vs IA ISS: skip storages that are not used in the IA ISS
    lappend args ia -skip {PC_ID PC_EX eDM}
  } else {
    # ISS vs HDL: skip internal memories
    lappend args go -skip_internal_memories true
  }
  lappend args -file $program.$iss_name.rcd
  if {[catch {
    iss fileoutput {*}$args
  } msg]} {
    log "ERROR: RCD setup failed: $msg"
    set rcd 0
  }
}
if {$rcd} {
  log "INFO: Register change dump (RCD) enabled"
} else {
  log "INFO: Register change dump (RCD) disabled"
}

# ------------------------------------------------------------------------------
# Set chess report filename

iss fileoutput chess_report set -file $program.$iss_name.mem

# ------------------------------------------------------------------------------
# SAIF: record profile begin/end cycle intervals

set ivals [list]

proc user_cycle_count {} {
  dict get [::tclutils::list2dict {user system delta} [iss info count -cycle]] user
}

# breakpoint callback
proc mycb {begin_or_end} {
  # log "mycb: $begin_or_end [iss program query pc -virtual] [user_cycle_count]"
  lappend ::ivals [user_cycle_count]
  return CONTINUE
}

# add new breakpoints at profile_begin/end
foreach bp [iss breakpoint mic get] {
  set bd [::tclutils::list2dict [iss info keys mic_breakpoint] $bp]
  if {[dict get $bd profile_begin]} {
    iss breakpoint mic add [dict get $bd pc] -command "mycb profile_begin"
  }
  if {[dict get $bd profile_end]} {
    iss breakpoint mic add [dict get $bd pc] -command "mycb profile_end"
  }
}

# ------------------------------------------------------------------------------

# Disable all profiling capabilities (faster sim)
iss profile functions set -control off
iss profile hazards set -control off
iss profile instruction_tracing set -control off
iss profile branch_coverage set -control off
iss profile set -control off
iss profile storages_set_active 0

# Setup checks
iss check_unbalanced_return set_active $checks
iss check_uninitialized_memory_reads set_active $checks
iss enable_address_checking \
        -check_stores [expr {$checks ? "error" : "off"}] \
        -check_loads [expr {$checks ? "error" : "off"}]
# Note: allow redundant loads -> set check_loads to off or warning

if {$nmlcov} {
  # need instruction profiling data for nML coverage
  iss profile set -control on
  iss profile set_active 1
}

# ------------------------------------------------------------------------------

# Simulate until chess_exit
if {[catch {
  iss step $max_cycles
} msg]} {
  # step failed - error encountered
  if {$msg ne ""} {
    log "ERROR: $msg"
  }
  if {[dict get [iss errors pdg] assert] != 0} {
    log "ERROR: PDG assertion failure"
  }
  iss close
  exit 1
}

# ------------------------------------------------------------------------------
# Check if we stopped at an exit breakpoint

# PC of breakpoint focus stage
set bkpt_pc [iss program query pc -virtual]

# breakpoints at that PC
set bl [iss breakpoint mic get -pc $bkpt_pc -nocomplain]

# stopped at exit?
set exitbp 0
if {[llength $bl]} {
  foreach bp $bl {
    set bd [::tclutils::list2dict [iss info keys mic_breakpoint] $bp]
    if {[dict get $bd exit] || [dict get $bd end_of_main]} {
      set exitbp 1
      break
    }
  }
}

if {$exitbp} {
  # exit code of simulated application
  set rc [iss program query exit_code]
  log "INFO: Simulated program exited with code $rc"
} else {
  log "WARNING: Stopped at non-exit address $bkpt_pc"
  if {[user_cycle_count] == $max_cycles && !$exitbp} {
    log "INFO: ... and hit cycles limit of $max_cycles"
  }
}

# ------------------------------------------------------------------------------

if {$nmlcov} {
  # Generate instruction profile in form usable for coverage analysis
  iss profile save -type profile-Risk $program.$iss_name.ipr
}

# ------------------------------------------------------------------------------
# Print stack info

set stacks [iss stack query]
for {set idx 0} {$idx < [llength $stacks]} {incr idx} {
  set stack [lindex $stacks $idx]
  set stack_info [::tclutils::list2dict [iss info keys stack_info] $stack]
  log "INFO: Stack $idx info: $stack_info"
  if {[dict get $stack_info growing_up]} {
    set stack_size [expr [dict get $stack_info max_addr] - [dict get $stack_info low_addr]]
  } else {
    set stack_size [expr [dict get $stack_info hi_addr]  - [dict get $stack_info max_addr]]
  }
  log "INFO: Stack $idx size: $stack_size"
}

# ------------------------------------------------------------------------------
# Print cycle count

set cycle_count_info [::tclutils::list2dict {user system delta} [iss info count -cycle]]
set cycle_count [dict get $cycle_count_info user]
log "INFO: Cycle count info: $cycle_count_info"
log "INFO: Cycle count: $cycle_count"

set cf [open $program.$iss_name.cycle_count w]
puts $cf $cycle_count
close $cf

if {$rcd} {
  # Generate cycle_count file for HDL simulations
  set cf [open $program.cycle_count w]
  puts $cf $cycle_count
  close $cf
}

# ------------------------------------------------------------------------------
# Cycle count intervals profile_begin/end

if {[llength $ivals]} {
  set f [open $program.profile_intervals w]
  puts $f [join $ivals \n]
  close $f
}

# ------------------------------------------------------------------------------

iss close
exit
