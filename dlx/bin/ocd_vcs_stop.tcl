while 1 {
  run 10us
  if { [file exists ./.OCD_VCS_stop] } {
    quit
    break
  }
}
