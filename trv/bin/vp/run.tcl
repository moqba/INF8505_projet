proc setEndOfMainBreakpoints { core exitFile } {
  if { [catch { set fp [open $exitFile r] } msg ]} {
    puts stderr "could not open file: $msg"
  }
  set endOfMainAddresses [split [read -nonewline $fp] "\n"]
  if { [llength $endOfMainAddresses] == 0 } {
    error "No exit points found for main"
  }
  foreach address $endOfMainAddresses {
    $core create_breakpoint $address
  }
}

proc run_sim {} {

  vpx::start_simulation $::env(VIRTUALIZER_MODEL_PATH)/sim . --cwr_wait 120 test.log test.err

  i_trv32p3 load_image $::env(APPLICATION)
  puts "image loaded"
  setEndOfMainBreakpoints i_trv32p3 $::env(APPLICATION).exit
  puts "breakpoints set at the end of main"

  vpx::continue_simulation
  vpx::wait_interrupted 180

  vpx::stop_simulation
}

if { [catch { run_sim } msg ]} {
  puts $msg
  vpx::set_exit_code 1
}
