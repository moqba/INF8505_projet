#
# Copyright (c) 2020-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

set scriptDir [file dirname [info script]]
source [file join $scriptDir .. .. .. bin iss rpc.tcl]

proc get_exit_breakpoints {fnm} {
  if {[catch {set fp [open $fnm r]} msg]} {
    error "could not open file '$fnm': '$msg'"
  }
  set bps [split [read -nonewline $fp] "\n"]
  close $fp
  if {[llength $bps] == 0} {
    error "No exit points found"
  }
  return $bps
}

proc set_breakpoints {core bps} {
  foreach bp $bps {
    $core create_breakpoint $bp
  }
}

proc list2dict { kl vl } {
  set d [dict create]
  foreach k $kl v $vl { dict set d $k $v }
  return $d
}

proc enable_debug_adapters {core} {
  # enable debug in adapters
  ::issrpc::execute $core set_global_member debug_initiator_sockets true
}

proc get_chess_report_filename {core program} {
  set isslst [::issrpc::execute iss::isss]

  set iss_name [dict get [list2dict \
    [::issrpc::execute $core info keys iss_option] \
    [::issrpc::execute $core info issoptions]] iss_name]

  if {[info exists ::env(CHESS_REPORT_FILENAME)] && [string length $::env(CHESS_REPORT_FILENAME)]} {
    set crpt_file [string map [list %PROGRAM% $program %ISS% $iss_name] $::env(CHESS_REPORT_FILENAME)]
  } else {
    set crpt_file "$program.$iss_name.vzer.mem"
  }
  return $crpt_file
}

proc set_chess_report_filename {core crpt_file} {
  ::issrpc::execute $core fileoutput chess_report set -file $crpt_file
}

proc is_absolute {path} {
  expr {[string range $path 0 0] eq {/}}
}

proc add_prefix {path prefix} {
  expr {[is_absolute $path] ? $path : [file join $prefix $path]}
}

proc log {args} {
  puts "[clock format [clock seconds]] ([pid]) $::argv0: [join $args]"
}

proc run_sim {} {

  if {[info exists ::env(VPWORKDIR)] && [string length $::env(VPWORKDIR)]} {
    set vpworkdir $::env(VPWORKDIR)
  } else {
    set vpworkdir .
  }
  log "VP workdir: $vpworkdir"

  set vpmodel $::env(VIRTUALIZER_MODEL_PATH)

  set application $::env(APPLICATION)
  log "application: $application"

  if {$vpworkdir ne "." && ![is_absolute $vpworkdir]} {
    log "Make paths relative to workdir $vpworkdir"
    # make paths relative to vpworkdir
    set vpwd [file normalize [file join [pwd] $vpworkdir]]
    set rel ""
    while {[file normalize [file join $vpwd $rel]] ne [pwd] && [file split $rel] <= [file split $vpwd]} {
      set rel [file join $rel ..]
    }
    log "INFO: VP workdir is '$vpworkdir', relative path prefix is '$rel'"

    set application [add_prefix $application $rel]
    if {$::env(APPLICATION) ne $application} {
      log "INFO: Changed application path from $::env(APPLICATION) to $application"
    }

    set vpmodel [add_prefix $vpmodel $rel]
    if {$::env(VIRTUALIZER_MODEL_PATH) ne $vpmodel} {
      log "INFO: Changed model path from $::env(VIRTUALIZER_MODEL_PATH) to $vpmodel"
    }
  }

  set exit_bps [get_exit_breakpoints "$::env(APPLICATION).exit"]
  log "Exit breakpoints: $exit_bps"

  set issargs {--cwr_wait}
  set timeout 120
  set outfile "test.$::env(VP_ISS).log"
  set errfile "test.$::env(VP_ISS).err"

  log "outfile: $outfile"
  log "errfile: $errfile"
  log "VP model path: $vpmodel"

  log "vpx::start_simulation"

  vpx::start_simulation \
        $vpmodel \
        $vpworkdir \
        $issargs \
        $timeout \
        $outfile \
        $errfile

  log "...started"

  i_trv32p5 load_image $application
  log "INFO: image loaded"

  set_breakpoints i_trv32p5 $exit_bps
  log "INFO: breakpoints set at chess_exit(s) '$exit_bps'"

  ::issrpc::connect

  set core ::HARDWARE.i_trv32p5
  set crpt_file [get_chess_report_filename $core $application]
  set_chess_report_filename $core $crpt_file
  log "INFO: Set chess report filename to '$crpt_file'"

  # enable_debug_adapters $core

  # run
  vpx::continue_simulation
  vpx::wait_interrupted 180

  set app_rc [::issrpc::execute $core program query exit_code]
  log "INFO: chess exit code of app is $app_rc"

  ::issrpc::disconnect

  vpx::stop_simulation

  log "Done"
}

if { [catch { run_sim } msg ]} {
  log $msg
  vpx::set_exit_code 1
}