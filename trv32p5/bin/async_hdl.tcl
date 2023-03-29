#
# Tcl script for regression simulation runs.
#
# Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#


proc ocd_start { simulator_executable {rcd_file /dev/null} {vcs_script ""} } {
  if {![file exists [lindex $simulator_executable 0]]} {
    puts "ERROR: could not find HDL simulator executable, expecting [lindex $simulator_executable 0] - did you build the HDL simulator?"
    exit 1
  }

  global pid t1 OCD_VCS bindir
  set t1 [clock milliseconds]

  if {$vcs_script eq ""} {
    set vcs_script $bindir/ocd_vcs_stop.tcl
  }
  puts "Using VCS script: $vcs_script"

  # set the JTS-PORT to ZERO such that the simulator chooses a free port
  set ::env(JTS_PORT_NUMBER) 0

  file delete ./JTS_PORT_NUMBER
  exec echo $rcd_file > ./rcdname.cfg

  file delete ./appname.cfg
  file delete {*}[ glob -nocomplain data.* ]
  file delete ./.OCD_VCS_stop

  set cmd [list {*}$simulator_executable -ucli -do $vcs_script >& hdlsim.log]
  puts "INFO: background launch '$cmd'"
  set pid [exec -- {*}$cmd &]

  puts "HDL ASYNC RUN: PID: $pid"
  while { [file exists ./JTS_PORT_NUMBER] == 0 || [file size ./JTS_PORT_NUMBER] == 0 } { after 1000 }
  set pdc_port [read [open ./JTS_PORT_NUMBER r]]
  set pdc_server localhost

  iss::iss_debug_client_set pdc_port   $pdc_port
  iss::iss_debug_client_set pdc_server $pdc_server

  puts "INFO: set PDC server to $pdc_server @ $pdc_port"
}

proc ocd_stop { } {
  global pid t1 OCD_VCS
  set t2 [clock milliseconds]
  puts "HDL ASYNC RUN: Elapsed time: [expr double($t2 - $t1)/1000] s"

  close [open ./.OCD_VCS_stop w]
  while { ![catch {exec kill -0 $pid}] } { exec usleep 1000 }

  file delete ucli.key
  file delete ./.OCD_VCS_stop
  file delete ./JTS_PORT_NUMBER
  file delete ./rcdname.cfg
}

