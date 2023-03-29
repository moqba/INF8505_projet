#
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#
# Tcl procedures used in tests for on chip debugging.
#

set processor [lindex [::iss::processors] 0]

set prjdir [file join [file dirname [info script]] .. .. ..]
set bindir [file join $prjdir bin]


set lf [open test.log w]
proc log line {
  puts $::lf "### $line"
  puts "### $line"
  flush $::lf
}

# defaults
set sim_mode vcs ; # vcs ext iss
set simv [file join $prjdir hdl ${processor}_vlog simv]

# parse script args
if {[llength $::iss::tcl_script_args] > 0} {
  puts "tcl script args: $::iss::tcl_script_args"

  # positional arguments
  set vargs {
  }
  # arg or {arg set}

  set sim_mode_set 0
  # options
  set vopts {
      { -mode v sim_mode sim_mode_set}
      { -simv v simv }
  }
  # {"-pat*" b/v/l name set}
  # b: boolean
  # v: variable
  # l: list

  if { [catch {::tclutils::parse_args $vargs $vopts $::iss::tcl_script_args [info script]} msg] } {
    log "ERROR: $msg"
    exit 1
  }

  if {$sim_mode_set && $sim_mode ni "vcs ext iss"} {
    log "ERROR: unknown sim mode '$sim_mode'"
    exit 1
  }
}

set program $::iss::cmdln_program_name

log "mode: $sim_mode"
log "program: $program"

if {$sim_mode eq "vcs"} {
  set hdl [lindex [file split $simv] end-1]
  log "simulator_executable: $simv"
  log "hdl: $hdl"

  source [file join $bindir async_hdl.tcl]
}

# ------------------------------------------------------------------------------

namespace eval testing {
  namespace export run_tests iss err load_program put_r put_a expect_r expect_a \
    expect_m expect_pc _iss init_X find_symbol find_all_syms get_pc \
    get_all_delay_slots find_all_symadr setup_VCS_bp setup_dump dump

  variable error_count 0
  variable first 1

  variable fwords
  variable syms

  variable bkpt_stage
#  variable stages

  proc run_tests body {
    initialize
    try {
      uplevel 1 $body
    } trap {} {msg opts} {
      err "Script execution failed: $msg"
      log [dict get $opts -errorinfo]
    } finally {
      finalize
    }
  }

  proc err msg {
    log "ERROR: $msg"
    puts stderr "ERROR: $msg"
    variable error_count
    incr error_count
  }

  proc initialize {} {
    log "Setup timeout handler"
    # give up after 5 minutes
    after 300000 {
      log "Timeout: giving up after 5 minutes."
      iss close
      if { $::sim_mode eq "vcs" } { ocd_stop }
      exit 1
    }

    if {$::sim_mode eq "vcs"} {
      log "Launching VCS $::simv in background"
      set args [list]
      if {[info exists ::ocd_vcs_script]} {
        lappend args /dev/null $::ocd_vcs_script
      }
      ocd_start $::simv {*}$args
    }

    try {
      ::iss::create $::processor _iss
    } trap {} {msg opts} {
      err "Could not create processor instance: $msg"
      if { $::sim_mode eq "vcs" } { ocd_stop }
      exit 1
    }

    log "In debug client: [_iss info is_debug_client], sim mode is $::sim_mode"

    # disable 'Cycle count, ... elapsed' messags after every ISS step
    set ::iss::print_messages 0
    set ::iss::time_simulation 0

    set d [iss info issoptions]
    set d [tclutils::list2dict $::iss::iss_option_keys $d]
    variable bkpt_stage [dict get $d breakpoint_stage]
#    variable stages [dict get $d pipeline_stage_name_list]
  }

  proc finalize {} {
    variable error_count
    report_errors
    iss close
    if { $::sim_mode eq "vcs" } { ocd_stop }
    exit [expr {$error_count > 0 ? 1 : 0}]
  }

  proc iss args {
    log [join [list iss {*}$args]]
    if {[catch {set val [_iss {*}$args]} msg]} {
      err $msg
      finalize
    }
    if {$::sim_mode eq "iss"} {
      lassign $args method
      if {$method eq "step"} {
        # mimicking HW based stepping
        variable bkpt_stage
        while 1 {
          set d [lindex [_iss info pipeline] $bkpt_stage]
          set d [tclutils::list2dict $::iss::instruction_info_keys $d]
          # would the db client stop here?
          # delay_slots -> not stopping
          # ZOL end-of-loop -> not stopping
          # cycles(3|1) not-taken branch -> would stop
          if {[dict get $d is_delay_slot] || ([dict get $d hw_breakpoint_forbidden] && [dict get $d sw_breakpoint_forbidden])} {
            if {[catch {set val [_iss step 1]} msg]} {
              err $msg
              finalize
            }
            continue
          }
          # step over bubbles in breakpoint stage
          lassign [_iss info pchistory] - pipe_valid - pipe_removed
          if {![lindex $pipe_valid $bkpt_stage] || [lindex $pipe_removed $bkpt_stage]} {
            if {[catch {set val [_iss step 1]} msg]} {
              err $msg
              finalize
            }
            continue
          }
          break
        }
      }
    }
    return $val
  }

  proc get_pc {} {
    if {$::sim_mode eq "iss"} {
      # retrieve PC of breakpoint focus stage
      return [iss program query pc -virtual]
    } else {
      return [iss program query pc]
    }
  }

  proc put_r {storage value {radix hex}} {
    log "put_r: $storage: $value, $radix"
    iss put -radix $radix $value $storage
  }

  proc put_a {storage address value {radix hex}} {
    log "put_a: $storage\[$address\]: $value, $radix"
    iss put -radix $radix $value $storage $address
  }

  # Test if the specified storage contains the expected value.
  proc expect_r {storage expected {radix hex} {format string}} {
    set val [iss get $storage -radix $radix -format $format]
    if { $val == $expected } {
      log "expect_r: same, ${storage}: $val, expected $expected"
    } else {
      log "expect_r: diff, ${storage}: $val, expected $expected  !!!"
      variable error_count
      incr error_count
    }
  }

  # Test if the specified storage location contains the expected value at
  # the specified address.
  proc expect_a {storage address expected {radix hex} {format string}} {
    set val [iss get $storage $address -radix $radix -format $format]
    if { $val == $expected } {
      log "expect_a: same, $storage\[$address\]: $val, expected $expected"
    } else {
      log "expect_a: diff, $storage\[$address\]: $val, expected $expected  !!!"
      variable error_count
      incr error_count
    }
  }

  # Test if the program counter contains the expected value.
  proc expect_pc {expected} {
    set val [get_pc]
    if { $val == $expected } {
      log "expect_pc: same, pc:$val, expected $expected"
    } else {
      log "expect_pc: diff, pc:$val, expected $expected  !!!"
      variable error_count
      incr error_count
    }
  }

  # Test if the memory range contains the expected values.
  proc expect_m { mem values } {
    foreach { v } $values {
      set a [lindex $v 0]
      set v [lindex $v 1]
      expect_a $mem $a $v dec
    }
  }

  proc report_errors {} {
    log ""
    variable error_count
    if { $error_count != 0 } {
      log "FAILED ($error_count errors) ************"
    } else {
      log "PASSED"
    }
    log ""
  }

  proc load_program {} {
    variable first
    log "Load program"
    iss reset
    iss program load $::program -dwarf -disassemble
    if {$first == 1} {
      set first 0
      variable fwords [_iss program query first_words]
      variable syms [elf_symbols]
      check_syms $syms
    }
    if {$::sim_mode eq "iss"} {
      # mimic db client behavior - run until first instruction is in breakpoint
      # focus stage
      iss src_step step 1
    }
  }

  # use only after instruction is decoded (simulated at least once)
  proc instr_at {pc args} {
    tclutils::list2dict $::iss::instruction_info_keys [lindex [_iss info instruction $pc {*}$args] 0]
  }

  proc elf_symbols args {
    lmap sym [_iss info elf32_symbols {*}$args] {
      tclutils::list2dict $::iss::elf32_symbol_keys $sym
    }
  }

  proc check_syms syms {
    log "Checking [llength $syms] symbols for alignment requirements"
    foreach sym $syms {
      set lbl [dict get $sym name]
      if {[regexp {chk_(\d+)m(\d+)} $sym -> off mod]} {
        set adr [dict get $sym value]
        log "Check $lbl at $adr for ($adr % $mod) == $off"
        if {![expr {($adr % $mod) == $off}]} {
          err "ERROR: Alignment of symbol $lbl mismatches expectations"
        }
      }
    }
  }

  proc setup_VCS_bp {addr} {
    set cndfile [open .OCD_VCS_extdbgcnd w]
    puts $cndfile "{inst_trv32p5/inst_reg_PC/pcr_out = $addr}"
    close $cndfile

    # request VCS breakpoint
    close [open .OCD_VCS_extdbgreq w]
    # wait for ack
    while {![file exists .OCD_VCS_setupdone]} { after 100 }
    # delete request
    file delete -force .OCD_VCS_extdbgreq
    # wait for ack
    while {[file exists .OCD_VCS_setupdone]} { after 100 }
  }

  proc init_X {{val 0}} {
    for {set i 1} {$i < 32} {incr i} {
      put_r x$i $val
    }
  }

  proc find_symbol lbl {
    variable syms
    foreach sym $syms {
      set name [dict get $sym name]
      if {$name eq $lbl} {
        set adr [dict get $sym value]
        break
      }
    }
    if {![info exist adr]} {
      err "Could not find $lbl"
      error "Test aborted"
    }
    variable fwords
    return [list $adr [lsearch $fwords $adr]]
  }

  proc find_all_syms pat {
    variable syms
    lmap sym $syms {expr {
      [string match $pat [dict get $sym name]] ? \
        [list [dict get $sym name] [dict get $sym value]] : [continue]
    }}
  }

  proc find_all_symadr pat {
    variable syms
    lmap sym $syms {expr {
      [string match $pat [dict get $sym name]] ? [dict get $sym value] : [continue]
    }}
  }

  proc get_all_delay_slots {} {
    variable fwords
    set ds {}
    foreach adr $fwords {
      set d [tclutils::list2dict $::iss::instruction_info_keys [lindex [_iss info instruction $adr] 0]]
      if {[dict get $d is_delay_slot] == 1} {
        lappend ds $adr
      }
    }
    return $ds
  }

  variable dmp
  proc setup_dump {} {
    variable dmp
    regexp {\D*(\d+)} [lindex [find_all_syms c_reg_min_x*] 0 0] -> r_min
    regexp {\D*(\d+)} [lindex [find_all_syms c_reg_max_x*] 0 0] -> r_max
    log "Test changes x$r_min .. x$r_max subranges"

    if {$::sim_mode eq "iss"} {
      set fnm "reg.iss.dmp"
    } else {
      set fnm "reg.ocd.dmp"
    }
    log "Dumping register state to $fnm"
    set dmp [_iss fileoutput_range add X $r_min $r_max -file $fnm -format unsigned]
  }

  proc dump {} {
    variable dmp
    _iss fileoutput_range print_header $dmp
    _iss fileoutput_range print $dmp
  }

}
