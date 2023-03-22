#
# Tcl script for OCD based regression simulation runs.
#
# Copyright (c) 2018-2021 Synopsys, Inc. This processor model and the associated
# documentation are proprietary to Synopsys, Inc.  This model may only be
# used in accordance with the terms and conditions of a written license
# agreement with Synopsys, Inc.  All other use, reproduction, or distribution
# of this model are strictly prohibited.
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
set bindir [file normalize $procdir/../bin]
puts "bindir: $bindir"


# defaults
set simv [file normalize $procdir/../hdl/${processor}_vlog/simv]
set step -1
set tmo  20
set rcd false

# parse script args
if {[llength $::iss::tcl_script_args] > 0} {
  puts "tcl script args: $::iss::tcl_script_args"

  # positional arguments
  set vargs {
    # arg or {arg set}
  }

  # options
  set vopts {
      {"-simv" v simv}
      {"-step" v step}
      {"-tmo"  v tmo}
      {"-rcd"  b rcd}
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
puts "simulator_executable: $simv"
puts "step: $step"
puts "timeout (minutes): $tmo"

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

set program $::iss::cmdln_program_name

if { $simv != "NONE" } {
    if { $rcd != false } {
    ocd_start $simv $program.ilx_vlog.rcd
  } else {
    ocd_start $simv
  }
} else {
  set t1 [clock seconds]
}

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
} else {
  set t2 [clock seconds]
  puts "program load successful, time (s): [expr $t2 - $t1]"
}

set mem_file $program.mem

iss fileoutput chess_report set -file $mem_file

# Simulate until end of main
if { $step == -1 } {
  # resume
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

if { [file exists $mem_file] } { file rename -force $mem_file ./ }

iss close
if { $simv != "NONE" } { ocd_stop }
exit $rtval

