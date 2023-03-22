#!/bin/sh
source $SNPS_VP_HOME/../any/external_debuggers/setup.sh
export LD_LIBRARY_PATH=$SNPS_EXTERNAL_DEBUGGERS_HOME/plugins/MCD/gcc-6.2.0:$LD_LIBRARY_PATH
mdb -virtualizer -on=sim_unhalt_arc -off=hostlink -OK ../../software/prod.elf
