#
# Tcl procedures used in tests for on chip debugging.
#

set bindir "../../bin"
source "$bindir/async_hdl.tcl"

# give up after 5 minutes
after 300000 {
    global async
    puts "Timeout: giving up after 5 minutes."
    iss close
    if { $async == 1 } { ocd_stop }
    exit 2
}

set error_count 0

proc initiate {iss} {
    global async testname lf bindir $iss pname

    set procname [lindex [::iss::processors] 0]

    set pname ../../$testname.x
    set lfname $testname.log
    set lf [open $lfname w]

    # separate dir for concurrency
    set wdir work/$testname
    file mkdir $wdir
    cd $wdir

    set async [expr [llength $::iss::tcl_script_args] >= 1];
    if { $async == 1 } {
        # default use simv (vcs)
        set simulator_executable ../../hdl/${procname}_vlog/simv
        if { [lindex  $::iss::tcl_script_args 0] != "async" } {
            set simulator_executable [lindex  $::iss::tcl_script_args 0]
        }
        puts "using sim: $simulator_executable"
        set simulator_executable ../../$simulator_executable
        set bindir "../../$bindir"
        ocd_start $simulator_executable
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
proc command {iss cmd} {
    global async lf error_count
    puts $lf "cmd : $iss $cmd"
    flush $lf
    if { [catch { eval $iss $cmd } msg ] } {
      puts stderr $msg
      incr error_count
      report_errors
      $iss close
      if { $async == 1 } { ocd_stop }
      exit
    }
}

# Write a value into the specified storage.
# The radix parameter specifies the radix of the value.
proc put_r {iss storage value {radix hex}} {
    global lf error_count
    puts $lf "put_r: $iss $storage: $value, $radix "
    flush $lf
    $iss put -radix $radix $value $storage
    flush $lf
}

# Write a value into the specified storage at the specified address.
# The radix parameter specifies the radix of the value.
proc put_a {iss storage address value {radix hex}} {
    global lf error_count
    puts $lf "put_a: $iss $storage\[$address\]: $value, $radix"
    flush $lf
    $iss put -radix $radix $value $storage $address
    flush $lf
}


# Test if the specified storage contains the expected value.
# The radix parameter specifies the radix of the expected value.
proc expect_r {iss storage expected {radix hex} {format string}} {
    global lf error_count
    set val [$iss get $storage -radix $radix -format $format]
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
    set val [$iss get $storage $address -radix $radix -format $format]
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
    set val [$iss get PC]
    if { $val == $expected } {
        puts $lf "expect_pc: same: $val, expected $expected"
    } else {
        puts $lf "expect_pc: diff: $val, expected $expected  !!!"
        incr error_count
    }
    flush $lf
}

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

