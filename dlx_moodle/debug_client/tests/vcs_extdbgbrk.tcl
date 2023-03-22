
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
