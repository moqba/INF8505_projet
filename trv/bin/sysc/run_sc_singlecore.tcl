#
# Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#
proc encode {s} {
    return [string map {\n %NEWLINE% \r %CARRIGERETURN% \{ %LBRACE% \} %RBRACE%} $s]
}

proc decode {s} {
    set rt [string index $s 0]
    set s [string map { %NEWLINE% \n %CARRIGERETURN% \r %LBRACE% \{ %RBRACE% \} } [string range $s 1 end]]
    return [list $rt $s]
}

proc execute {args} {
    global skt_iss
    # Write command on the socket
    set cmd [encode [join $args]]
    #puts "ISS cmd: $cmd"
    puts $skt_iss $cmd
    # Read return value
    lassign [decode [gets $skt_iss]] err value
    #puts "ISS rsp: err='$err' value='$value'"
    if {$err eq ""} {
        return ""
    }
    if {!$err} {
        error $value
    }
    return $value
}

proc disconnect {} {
    global skt_iss
    close $skt_iss
}

proc usage { } {
    puts ""
    puts "Usage: tct_tclsh run_sc_singlecore.tcl <program> <proc_lib> <proc>"
    puts ""
}

if { [llength $argv] < 3 } {
    usage
    exit -1
}

set program   [lindex  $argv 0]
set procdir   [lindex  $argv 1]
set proc      [lindex  $argv 2]

set cf [open "ISS_RPC_SERVER_PORT" r]
gets $cf sc_server_port

puts "connect to port $sc_server_port"

global skt_iss
set skt_iss [socket localhost $sc_server_port]
fconfigure $skt_iss -buffering line

# get list of iss'es
set isslst [execute iss::isss]
puts "isslist = $isslst"

execute $proc program load $program \
    -do_not_set_entry_pc 1 \
    -do_not_load_sp 1 \
    -nmlpath $procdir \
    -dwarf2 \
    -disassemble \
    -sourcepath {.}

package require TctTclUtils

set iss_name [dict get [tclutils::list2dict [execute $proc info keys iss_option] [execute $proc info issoptions]] iss_name]
set mem_file "$program.$iss_name.mem"
execute $proc fileoutput chess_report set -file $mem_file

# start executing
execute ::iss::iss_rpc_clock_start -1


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
set cf [open "$program.cycle_count" w]
puts $cf $cycle_count
close $cf

execute $proc profile save "$program.$iss_name.prf" -type function_details -user_cycle_count Off -xml 0 -source_refs Off -hide_instruction_bits On

#execute exit
#disconnect
