#
# Tcl script for regression simulation runs.
#
# Copyright (c) 2017-2021 Synopsys, Inc. This processor model and the associated
# documentation are proprietary to Synopsys, Inc.  This model may only be
# used in accordance with the terms and conditions of a written license
# agreement with Synopsys, Inc.  All other use, reproduction, or distribution
# of this model are strictly prohibited.
#

set OCD_VCS 1

proc ocd_start { simulator_executable {rcd_file /dev/null} {vcs_script ""} } {
    global pid t1 OCD_VCS bindir
    set t1 [clock seconds]

    if {$vcs_script eq ""} {
      set vcs_script $bindir/ocd_vcs_stop.tcl
    }
    puts "Using VCS script: $vcs_script"

    # set the JTS-PORT to ZERO such that the simulator chooses a free port
    set ::env(JTS_PORT_NUMBER) 0

    file delete ./JTS_PORT_NUMBER
    exec echo $rcd_file > ./rcdname.cfg

    if { ! $OCD_VCS } {
      set pid [exec $simulator_executable > sim_run.log &]
    } else {
      file delete ./appname.cfg
      file delete {*}[ glob -nocomplain data.* ]
      file delete ./.OCD_VCS_stop
      set pid [exec {*}$simulator_executable -ucli -do $vcs_script > sim_run.log &]
    }
    puts "HDL ASYNC RUN: PID: $pid"
    while { [file exists ./JTS_PORT_NUMBER] == 0 || [file size ./JTS_PORT_NUMBER] == 0 } { after 1000 }
    set pdc_port [read [open ./JTS_PORT_NUMBER r]]
    set pdc_server localhost

    iss::iss_debug_client_set pdc_port   $pdc_port
    iss::iss_debug_client_set pdc_server $pdc_server
}

proc ocd_stop { } {
    global pid t1 OCD_VCS
    set t2 [clock seconds]
    puts "HDL ASYNC RUN: Elapsed time (s): [expr $t2 - $t1]"

    if { ! $OCD_VCS } {
      exec kill -9 $pid
    } else {
      close [open ./.OCD_VCS_stop w]
      while { ![catch {exec kill -0 $pid}] } { exec usleep 1000 }
      file delete ucli.key
      file delete ./.OCD_VCS_stop
    }
    file delete ./JTS_PORT_NUMBER
    file delete ./rcdname.cfg
}

