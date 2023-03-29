#
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

set setup_done false

while 1 {
  run 10us
  if { [file exists ./.OCD_VCS_stop] } {
    quit
    break
  }
  if {$setup_done == false && [file exists ./.OCD_VCS_extdbgreq]} {
    set setup_done true

    set cndfile [open .OCD_VCS_extdbgcnd]
    set cnd [read $cndfile]
    close $cndfile

    stop -once -posedge clock -condition $cnd \
         -command {
            puts "Trigger external debug request"
            force dbg_ext_break 1
            stop -once -posedge clock -command { force dbg_ext_break 0 } -continue
         } \
         -continue
    close [open .OCD_VCS_setupdone w]

    puts "Setup VCS bp: $cnd"
  }
  if {$setup_done == true && ![file exists ./.OCD_VCS_extdbgreq]} {
    set setup_done false
    file delete -force .OCD_VCS_setupdone
  }
}
