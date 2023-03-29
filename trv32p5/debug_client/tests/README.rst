
These tests support 3 simulation modes

 * vcs - the test launches a VCS simulation in the background, then uses the
   debug client to connect to it via Jtalk

 * ext - the test connects to an HDL simulation or prototype hardware via
   Jtalk, using the debug client

 * iss - the test executes in an ISS

VCS is started with the script <project-dir>/bin/ocd_vcs_stop.tcl. This script
dumps all signals to a waveform file (inter.fsdb).

You can look at waveforms after the HDL simulation finished with Verid:

    verdi -dbdir <prjdir>/hdl/trv32p5_vlog/simv.daidir -ssf inter.fsdb

These projects have 3 run-debug configurations

 * vcs (default)
 * iss
 * ext


Build

    chessmk test


Run

    chessmk test -S


Run on ISS

    chessmk test -S +C iss


Run on external (simulated/emulated/real) hardware

    chessmk test -S +C ext

