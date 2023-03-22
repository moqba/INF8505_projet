#
# Tcl procedures used in tests for on chip debugging.
#

set bindir [file join [file dirname [file normalize [info script]]] .. .. bin]
source [file join $bindir async_hdl.tcl]

# give up after 5 minutes
after 300000 {
    global async
    puts "Timeout: giving up after 5 minutes."
    iss close
    if { $async == 1 } { ocd_stop }
    exit 2
}

set error_count 0

proc initiate {iss {vcs_script ""}} {
    global async testname lf bindir $iss pname

    set procname [lindex [::iss::processors] 0]

    set pname  $testname.x
    set lfname $testname.err
    set lf [open $lfname w]

    set async [expr [llength $::iss::tcl_script_args] >= 1];
    if { $async == 1 } {

        # default use simv (vcs)
        set simulator_executable ../../hdl/${procname}_vlog/simv
        if { [lindex  $::iss::tcl_script_args 0] != "async" } {
            set simulator_executable [lindex  $::iss::tcl_script_args 0]
        }

        set simulator_executable [file normalize $simulator_executable]
        set bindir               [file normalize $bindir]
        set pname                [file normalize $pname]

        puts "using sim: $simulator_executable"

        # separate dir for concurrency
        set wdir work/$testname
        file mkdir $wdir
        cd $wdir
        ocd_start $simulator_executable /dev/null $vcs_script
    } else {
        puts "please make sure the simulator is started and listening"
    }

    ::iss::create $procname $iss
}

proc finalise {iss} {
    global async
    report_errors
    $iss close
    if { $async == 1 } { ocd_stop }
    exit
}

# add comment to log file
proc log {line} {
    global lf
    puts $lf "### $line"
    puts "### $line"
    flush $lf
}

# execute ISS command
proc command_ {iss cmd} {
    global error_count
    if { [catch { set val [eval $iss $cmd] } msg ] } {
      puts stderr $msg
      incr error_count
      finalise $iss
    }
    return $val
}

proc command {iss cmd} {
    global lf
    puts $lf "cmd : $iss $cmd"
    flush $lf
    return [command_ $iss $cmd]
}

# Write a value into the specified storage.
# The radix parameter specifies the radix of the value.
proc put_r {iss storage value {radix hex}} {
    global lf
    puts $lf "put_r: $iss $storage: $value, $radix "
    flush $lf
    command_ $iss "put -radix $radix $value $storage"
}

# Write a value into the specified storage at the specified address.
# The radix parameter specifies the radix of the value.
proc put_a {iss storage address value {radix hex}} {
    global lf
    puts $lf "put_a: $iss $storage\[$address\]: $value, $radix"
    flush $lf
    command_ $iss "put -radix $radix $value $storage $address"
    flush $lf
}


# Test if the specified storage contains the expected value.
# The radix parameter specifies the radix of the expected value.
proc expect_r {iss storage expected {radix hex} {format string}} {
    global lf error_count
    set val [command_ $iss "get $storage -radix $radix -format $format"]
    if { $val == $expected } {
        puts $lf "expect_r: same $storage: $val, expected $expected"
    } else {
        puts $lf "expect_r: diff $storage: $val, expected $expected  !!!"
        incr error_count
    }
    flush $lf
}

# Test if the specified storage location contains the expected value at
# the specified address.
# The radix parameter specifies the radix of the expected value.
proc expect_a {iss storage address expected {radix hex} {format string}} {
    global lf error_count
    set val [command_ $iss "get $storage $address -radix $radix -format $format"]
    if { $val == $expected } {
        puts $lf "expect_a: same $storage\[$address\]: $val, expected $expected"
    } else {
        puts $lf "expect_a: diff $storage\[$address\]: $val, expected $expected  !!!"
        incr error_count
    }
    flush $lf
}

# Test if the program counter contains the expected value.
proc expect_pc {iss expected} {
    global lf error_count
    set val [command_ $iss "get PC"]
    if { $val == $expected } {
        puts $lf "expect_pc: same: $val, expected $expected"
    } else {
        puts $lf "expect_pc: diff: $val, expected $expected  !!!"
        incr error_count
    }
    flush $lf
}

# for ILX
proc expect_break { iss expected { bp_type "-software 1" } } {
    global lf error_count

    set vals [$iss debug_client core_status]
    ::tclutils::list2array $iss::core_status_keys $vals sa

    if { $bp_type == "-hardware 1" } {
        set val1 $sa(hw_break)
    } else {
        set val1 $sa(sw_break)
    }

    if { $val1 != $expected } {
        puts $lf "expect_break: diff: $val1, expected $expected  !!!"
        incr error_count
    } else {
        puts $lf "expect_break: same: $val1, expected $expected"
    }
    flush $lf
}

# for ILX
proc expect_break_context { iss expected { bp_type "-software 1" } } {
    global lf error_count

    set vals [$iss debug_client core_status]
    ::tclutils::list2array $iss::core_status_keys $vals sa
    #puts $lf $iss::core_status_keys
    #puts $lf $vals

    if { $bp_type == "-hardware 1" } {
        set val1 $sa(hw_break)
    } else {
        set val1 $sa(sw_break)
    }
    set val2 $sa(break_context)
    if { $val1 != 1 } {
        puts $lf "break: diff: $val1, expected 1  !!!"
        incr error_count
    } elseif { $val2 != $expected } {
        puts $lf "expect_break_context: diff: $val2, expected $expected  !!!"
        incr error_count
    } else {
        puts $lf "expect_break_context: same: $val2, expected $expected"
    }
    flush $lf
}

# Test if the memory range contains the expected values.
proc expect_m { iss mem values } {
    foreach { v } $values {
        set a [lindex $v 0]
        set v [lindex $v 1]
        expect_a $iss $mem $a $v dec
    }
}

proc report_errors {} {
    global lf error_count
    puts $lf ""
    puts ""
    if { $error_count != 0 } {
        puts $lf "FAILED ($error_count errors) ************"
        puts     "FAILED ($error_count errors) ************"
    } else {
        puts $lf "PASSED"
        puts     "PASSED"
    }
    puts $lf ""
    puts ""
    flush $lf
}

proc load_program { iss } {
    global pname
    log "Load program $pname"
    command $iss reset
    command $iss "program load $pname"
}

proc setup_VCS_bp {addr} {
  set cndfile [open .OCD_VCS_extdbgcnd w]
  puts $cndfile "{inst_mcld/inst_reg_PC/pcr_out = $addr}"
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
