#!/bin/sh

set -e

#generate systemc wrapper
cd ../common/dlx_tlm2_lt
chessmk -m +P12 dlx_ia_tlm2_lt.prx

#build software
cd ../software/
chessmk cons.prx
cd ../../ARC/software
./build.sh

#build platform
cd ../platform
pcsh arc_dlx_platform.tcl
cd export
pcsh sim_build.tcl
cd ..

