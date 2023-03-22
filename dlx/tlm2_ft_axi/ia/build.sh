#!/bin/sh

set -e

#generate systemc wrapper
chessmk -m +P12 dlx_ia_tlm2_ft.prx

#import wrapper
pcsh import_pct.tcl

#export platform
cd platform
pcsh simple_platform.tcl

#build platform
cd export
pcsh sim_build.tcl

