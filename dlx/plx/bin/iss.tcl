#
#
# Copyright (c) 2014 Synopsys, Inc. This processor model and the associated
# documentation are proprietary to Synopsys, Inc.  This model may only be
# used in accordance with the terms and conditions of a written license
# agreement with Synopsys, Inc.  All other use, reproduction, or distribution
# of this model are strictly prohibited.
#
# Tcl srcipt for regression simulation runs.
#

# Create ISS
set procname [lindex [::iss::processors] 0]
::iss::create $procname iss

after 600000 {
 puts "Timeout: giving up after 10 minutes."
 iss close
 exit 2
}

set program $::iss::cmdln_program_name

# Load program
iss program load $program \
    -dwarf2\
    -disassemble\
    -sourcepath {.}

set rcd_file $program.iss.rcd
set prf_file $program.prf
set ipr_file $program.ipr


# File outputs for ISS versus RTL tests
iss fileoutput go -file $rcd_file \
                  -format go_verilog  \
                  -skip_internal_memories true


# Simulate until end of main
catch { iss step -1 } msg
puts $msg

# Save instruction profile in human readable form
iss profile save $prf_file

# Generate instruction profile in form usable for coverage analysis
iss profile save -type profile-Risk $ipr_file

# Print maximum stack size
set stack_info [iss stack query]
set stack_size [lindex $stack_info 0 4]
puts "Stack size: $stack_size"

# Print cycle count
set cycle_count [ lindex [iss info count -cycle] 0 ]
puts "Cycle count : $cycle_count"
set cf [open "$program.cycle_count" w]
puts $cf $cycle_count

iss close
exit

