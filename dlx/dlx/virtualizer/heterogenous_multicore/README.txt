Heterogenous Multi-core Virtualizer Examples
============================================

These examples demonstrates simultaneous debugging of an ASIP and a non-ASIP
core in a Virtualizer platform. DLX is being used as the ASIP core, while
ARM and ARC cores are the non-ASIP cores each in a separate example.

The ARM directory has a simple platform with an ARM Cortex A5 core and a DLX
core sitting on common FT bus (TLM2-GP) and accessing a shared memory.

Similarly, the ARC directory has a simple platform with an ARC core and a DLX
core sitting on common FT bus (TLM2-GP) and accessing a shared memory.

Both the examples run a simple producer-consumer application, where the ARM/ARC
cores play the producer, while DLX plays the consumer.

The common directory has the DLX project for generating its SystemC wrapper,
fast-build DLL etc., which is used by both the ARM and ARC examples.

How to set-up?
==============
- Both the ARM and ARC directories have a setup.csh script that sets up the
  required environment. You will need to adapt the script according to the
  installation paths at your end
- For the ARM example, you will need an ARM compiler tool-chain and licenses
  for the ARM fast models
- For the ARC example, you will the Metware compiler tool-chain and ARC NSIM
  installation and licenses
- Additionally, you will need the ASIP Designer environment and GCC for building
  the simulation

How to build?
============
- There are build.sh scripts in both the ARM and ARC directories that you can
  invoke to build both the simulation and the software

How to run?
===========
- There are run.sh scripts in both the ARM and ARC directories that you can
  invoke to run the simulation in batch mode

How to do simultaneous debugging?
=================================

For the ARC example
-------------------
- Go to platform/export; Invoke VPExplorer: vpexplorer -c <Default vpconfig> and
  start the simulation
- Run, ../invoke_mdb.sh to invoke the Metware debugger connected to the simulation
- To start debugging, first you need to give a run in the MW debugger and then in
  VPExplorer
- Go to common/software; Invoke ChessDE: chessde cons.prx and invoke the debugger
  in Client mode to connect to the DLX core in the simulation
- Now all the debuggers should be connected to the simulation, and simultaneous
  debugging can be done

For the ARM example
-------------------
- Go to platform/export; Invoke VPExplorer: vpexplorer -c <Default vpconfig> and
  start the simulation
- To start Trace32 debugger, Go to Custom -> Launch Debugger -> TRACE32 ->
  Debug HARDWARE.ARM0 in VPExplorer GUI
- Go the common/software; Invoke ChessDE: chessde cons.prx and invoke the debugger
  in Client mode to connect to the DLX core in the simulation
- Now all the debuggers should be connected to the simulation, and simultaneous
  debugging can be done

Note, all the three debuggers should give a run, in order for the simulation
to proceed

Sample output of the application
================================

Core: HARDWARE.DLX, waiting for initial reset..
Initial reset for core: HARDWARE.DLX done.
Producer: produced 0 at array[0]
Producer: produced 0 at array[1]
Producer: produced 0 at array[2]
Producer: produced 0 at array[3]
Producer: produced 0 at array[4]
Producer: produced 0 at array[5]
Producer: produced 0 at array[6]
Producer: produced 0 at array[7]
Producer: produced 0 at array[8]
Consumer: consumed 0 at array[8]
Consumer: consumed 0 at array[7]
Consumer: consumed 0 at array[6]
Consumer: consumed 0 at array[5]
Consumer: consumed 0 at array[4]
Consumer: consumed 0 at array[3]
Consumer: consumed 0 at array[2]
Consumer: consumed 0 at array[1]
Consumer: consumed 0 at array[0]
Producer: produced 1 at array[0]
Producer: produced 1 at array[1]
Producer: produced 1 at array[2]
...
