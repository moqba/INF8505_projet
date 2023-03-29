#
# Tcl script for OCD based regression simulation runs.
#
# Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

set processor [lindex [::iss::processors] 0]

# Parse debug_client command-line arguments
set x 0
while { $x < [llength $argv] } {
  if { [lindex $argv $x] == "-P" } {
    incr x
    set procdir [lindex $argv $x]
  }
  incr x
}
puts "procdir: $procdir"
set bindir [file join $procdir .. bin]
puts "bindir: $bindir"


# defaults
set simv [file join $procdir .. hdl ${processor}_vlog simv]
set step -1
set tmo  20
set rcd false

# ------------------------------------------------------------------------------
# Process script arguments


if {[llength $::iss::tcl_script_args] > 0} {
  puts "tcl script args: $::iss::tcl_script_args"

  # positional arguments
  set vargs {
    # arg or {arg set}
  }

  # options
  set vopts {
      { -simv  v simv}
      { -step  v step}
      { -tmo   v tmo}
      { -rcd   b rcd}
  }
  # {-pat* b/v/l var [var_set]} b: boolean, v: variable, l: list

  if { [catch {::tclutils::parse_args $vargs $vopts $::iss::tcl_script_args [info script]} msg] } {
    puts "ERROR: $msg"
    exit 1
  }
}
set hdl [lindex [file split $simv] end-1]
set program $::iss::cmdln_program_name

puts "simulator_executable: $simv"
puts "step: $step"
puts "timeout (minutes): $tmo"
puts "hdl: $hdl"
puts "program: $program"

#

source "$bindir/async_hdl.tcl"

if { $tmo > 0 } {
  after [expr $tmo * 60000 ] {
    puts "OCD_VCS: Timeout: giving up after $tmo minutes."
    iss close
    if { $simv != "NONE" } { ocd_stop }
    exit 2
  }
}


if { $simv != "NONE" } {
  if { $rcd == true } {
    ocd_start $simv $program.trv32p5_vlog.rcd
  } else {
    ocd_start $simv
  }
}

set t1a [clock milliseconds]

set jss [ ::iss::create $processor iss ]

# Load program
set rtval [ catch { iss program load $program \
    -do_not_set_entry_pc 1 \
    -do_not_load_sp 1 \
    -dwarf2 \
    -disassemble \
    -sourcepath {.} \
    -hardware_breakpoints_allowed 0 \
    -software_breakpoints_allowed 1 \
  } msg ]

if { $rtval } {
  iss close
  if { $simv != "NONE" } { ocd_stop }
  exit $rtval
}

set t2a [clock milliseconds]
puts "program load successful, time: [expr double($t2a - $t1a)/1000] s"

set mem_file "$program.$hdl.ocd.mem"
iss fileoutput chess_report set -file $mem_file

# Simulate until end of main
if { $step == -1 } {
  # resume
  puts "INFO: Run till chess_exit"
  set steps 1
  set rtval [catch { iss step -1 } msg]
  puts $msg
} else {
  # step by step
  set steps 0
  set ::iss::iss_options($jss,time_simulation) 0
  set pc1 [iss get PC]
  while { 1 } {
    update ;# allow to timeout
    set rtval [catch { iss step $step } msg]
    if { $rtval } { puts $msg ; break }
    set pc0 $pc1
    set pc1 [iss get PC]
    set st [ expr $pc1 - $pc0 ]
    set steps [ expr $steps + $step ]
    puts "PC=$pc1=$pc0+$st steps=$steps"
    set br 0
    foreach b [iss breakpoint mic get] {
      set d [::tclutils::list2dict $::iss::mic_breakpoint_keys $b]
      if {[dict get $d exit] && [dict get $d hit_last_cycle]} {
        set br 1
        break
      }
    }
    if { $br } { break }
  }
}

puts "Steps count : $steps"
set cf [open "$program.steps_count" w]
puts $cf $steps

iss close
if { $simv != "NONE" } { ocd_stop }
exit $rtval

