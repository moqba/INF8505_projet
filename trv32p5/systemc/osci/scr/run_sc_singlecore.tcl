#
# Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

source [file join [file dirname [info script]] .. .. .. bin iss rpc.tcl]
namespace import ::issrpc::*;

package require TctTclUtils
package require TctTclUtilsParseArgs


proc usage { } {
  puts ""
  puts "Usage: tct_tclsh run_sc_singlecore.tcl <program> <proc>"
  puts ""
}

# defaults
set no_reports 0

# parse script args
if {[llength $argv] < 2} {

  usage
  exit -1

} else {

  # positional arguments
  set vargs {
    program
    proc
  }
  # arg or {arg set}

  # options
  set vopts {
    {"-no-reports" b no_reports}
  }
  # {"-pat*" b/v/l name set}

  if { [catch {::tclutils::parse_args $vargs $vopts $argv [info script]} msg] } {
    puts "ERROR: $msg"
    exit 1
  }

}

# ISS RPC connect
connect

# get list of iss'es
set isslst [execute iss::isss]
puts "isslist = $isslst"

execute ::iss::iss_rpc_server_connection_established $proc
execute ::iss::iss_rpc_clock_stop

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
execute $proc program load $program {*}$program_load_args

set isscfg [tclutils::list2dict \
 [execute $proc info keys iss_option] \
 [execute $proc info issoptions]]

set iss_name [dict get $isscfg iss_name]

if {[info exists ::env(CHESS_REPORT_FILENAME)] && [string length $::env(CHESS_REPORT_FILENAME)]} {
  set mem_file [string map [list %PROGRAM% $program %ISS% $iss_name] $::env(CHESS_REPORT_FILENAME)]
} else {
  set mem_file "$program.$iss_name.osci.mem"
}

execute $proc fileoutput chess_report set -file $mem_file

execute ::iss::iss_rpc_clock_start_source chessde

# start executing
execute ::iss::iss_rpc_clock_start_from_iss -1 [list $proc] 0 "mic"

set done 0

# poll loop
while {!$done} {
  # is running?
  set tmp [execute ::iss::iss_rpc_clock_running]
  lassign $tmp running clock_step_id
  if {$running eq ""} {
    puts "Error: SystemC simulation stopped unexpectedly. Aborting."
    exit -1
  }
  if {!$running} {
    # not running anymore, print possible errors and exit poll loop
    foreach iss $isslst {
      puts [execute $iss errors get]
    }
    break
  }
  # poll every 0.1s
  after 100
}

# stop running (in case we exit the above loop because of $done==1)
execute ::iss::iss_rpc_clock_stop

# Print cycle count
set cycle_count [ lindex [execute $proc info count -cycle] 0 ]
puts "Cycle count : $cycle_count"

if { [info script] eq $::argv0 } {
  execute exit
  disconnect
}
