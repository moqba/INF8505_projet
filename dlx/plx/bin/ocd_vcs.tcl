#
# Tcl script for regression simulation runs.
#
# Copyright (c) 2017 Synopsys, Inc. This processor model and the associated
# documentation are proprietary to Synopsys, Inc.  This model may only be
# used in accordance with the terms and conditions of a written license
# agreement with Synopsys, Inc.  All other use, reproduction, or distribution
# of this model are strictly prohibited.
#

set processor [lindex [::iss::processors] 0]

# Parse command-line arguments
set x 0
while { $x < [llength $argv] } {
    if { [lindex $argv $x] == "-P" } {
        incr x
        set procdir [lindex $argv $x]
    }
    incr x
}
puts "procdir: $procdir"
set bindir "$procdir/../bin"
puts "bindir: $bindir"


#

set simv ../../hdl/${processor}_vlog/simv
set step -1
set tmo  20
set gap  0

# Parse Tcl script arguments
set x 0
while { $x < [llength $::iss::tcl_script_args] } {
    if       { [lindex $::iss::tcl_script_args $x] == "-simv" } {
        incr x
        set simv [lindex $::iss::tcl_script_args $x]
    } elseif { [lindex $::iss::tcl_script_args $x] == "-step" } {
        incr x
        set step [lindex $::iss::tcl_script_args $x]
    } elseif { [lindex $::iss::tcl_script_args $x] == "-tmo" } {
        incr x
        set tmo [lindex $::iss::tcl_script_args $x]
    } elseif { [lindex $::iss::tcl_script_args $x] == "-gap" } {
        incr x
        set gap [lindex $::iss::tcl_script_args $x]
    }
    incr x
}
puts "simulator_executable: $simv"
puts "step: $step"
puts "timeout (minutes): $tmo"
puts "schedule same thread with (AP+1) cycles difference: $gap"

#

source "$bindir/async_hdl.tcl"

if { $tmo > 0 } {
  after [expr $tmo * 60000 ] {
    puts "Timeout: giving up after $tmo minutes."
    iss close
    if { $simv != "NONE" } { ocd_stop }
    exit 2
  }
}

if { $simv != "NONE" } {
  ocd_start $simv
} else {
  set t1 [clock seconds]
}

set jss [ ::iss::create $processor iss ]

set program $::iss::cmdln_program_name

# Load program
set rtval [ catch { iss program load $program\
    -do_not_set_entry_pc 1\
    -do_not_load_sp 1\
    -dwarf2 \
    -disassemble \
    -end_of_main_breakpoints \
    -sourcepath {.} \
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

proc count_trailing_zeros { state offset } {
  set n [ expr ($offset-1)%16 ]
  set seek 1
  for {set i 0} {$i<15} {incr i} {
    set idx [ expr ($offset+$i)%16 ]
    if { [ expr ($state>>$idx)&$seek ] } {
      set seek 0
      set n $idx
    }
  }
  return $n
}

# stress variations for thread scheduler
iss put $gap AP

# Simulate until end of main
if { $step == -1 } {
  # resume
  set rtval [catch { iss step -1 } msg]
  puts $msg
} else {
  # step by step
  set steps 0
  set cntxt 0
  set ::iss::iss_options($jss,time_simulation) 0
  while { 1 } {
    update ;# allow to timeout
    set en [iss get EN]
    set cntxt [ count_trailing_zeros $en [ expr ($cntxt+1)%16 ] ]
    iss set_context $cntxt
    set pc0 [iss get PC]
    set rtval [catch { iss step 1 } msg]
    set pc1 [iss get PC]
    set st [ expr $pc1 - $pc0 ]
    puts "EN=$en PC<$cntxt>=$pc1=$pc0+$st"
    incr steps
    set br 0
    foreach b [iss breakpoint mic get] {
      set d [::tclutils::list2dict $::iss::mic_breakpoint_keys $b]
      if {[dict get $d hit_last_cycle]} { set br 1 }
    }
    if { $br } { break }
  }
  puts "Steps count : $steps"
}

if { [file exists $mem_file] } { file rename -force $mem_file ./ }

iss close
if { $simv != "NONE" } { ocd_stop }
exit $rtval

