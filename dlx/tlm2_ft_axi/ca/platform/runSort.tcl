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

vpx::start_simulation ./Debug/sim . --cwr_wait 120 test.log test.err

i_dlx load_image ../../../../sort/Release/sort
puts "image loaded"
setEndOfMainBreakpoints i_dlx ../../../../sort/Release/sort.exit
puts "breakpoints set at the end of main"

vpx::continue_simulation
vpx::wait_interrupted 180

