#
# Utility procedures
#
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

proc log {args} {
  puts "[clock format [clock seconds]] ([pid]) $::argv0: [join $args]"
}

proc on_windows {} {
  expr {$::tcl_platform(platform) eq "windows"}
}

proc try_exec {args} {
  try {
    set result [exec -ignorestderr -- {*}[auto_execok [lindex $args 0]] {*}[lrange $args 1 end]]
    if {[lindex $args end] eq "&"} {
      return $result ; # pid
    } else {
      return 0 ; # exit code
    }
  } trap CHILDKILLED {- opts} {
    lassign [dict get $opts -errorcode] -> pid sigName msg
    log "process $pid was killed by signal $sigName; message is $msg"
  } trap CHILDSTATUS {- opts} {
    lassign [dict get $opts -errorcode] -> pid code
#    log "process $pid exited with non-zero exit code $code"
    return $code
  } trap CHILDSUSP {- opts} {
    lassign [dict get $opts -errorcode] -> pid sigName msg
    log "process $pid was suspended by signal $sigName; message is $msg"
  } trap POSIX {- opts} {
    lassign [dict get $opts -errorcode] -> errName msg
    log "Some kind of kernel failure; details in $errName and $msg"
  }
  return -code error "FAILED: $args"
}

proc log_exec {args} {
  log "Exec: $args"
  try_exec {*}$args
}

proc chessmk {args} {
  set cmd [list chessmk {*}$args]
  if {[info exists ::env(NCORES)]} {
    lappend cmd "+P$::env(NCORES)"
  }
  log_exec {*}$cmd
}

proc simplify_relpath {p} {
  set path [list]
  foreach elem [file split $p] {
    if {$elem eq ".."} {
      if {![llength $path] || [lindex $path end] eq ".."} {
        lappend path $elem
      } else {
        set path [lreplace $path end end]
      }
    } elseif {$elem eq ""} {
    } elseif {$elem ne "."} {
      lappend path $elem
    }
  }
  if {[llength $path]} {
    return [file join {*}$path]
  } else {
    return ""
  }
}

proc read_port_file {file} {
  set fh [open $file r]
  set buf [string trim [read $fh]]
  close $fh
  return $buf
}

proc cat_file file {
  set fh [open $file r]
  set t [read $fh]
  close $fh
  return $t
}