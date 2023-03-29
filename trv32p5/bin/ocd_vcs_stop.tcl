#
# Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

if {[info exists ::env(OCD_VCS_TRACE)] && $::env(OCD_VCS_TRACE) == 1} {
  puts {[INFO] Dumping all signals to inter.fsb}
  puts {[INFO] To look at debug traces after the simulation:}
  puts {[INFO] verdi -dbdir <path>/hdl/trv32p5_vlog/simv.daidir -ssf inter.fsdb}

  dump -add / -depth 0
}

onbreak {
  puts {[INFO] Encountered stop-point, $stop task or CTRL-C, stopping VCS ...}
  quit
}

while 1 {
  run 10us
  if { [file exists ./.OCD_VCS_stop] } {
    quit
    break
  }
}
