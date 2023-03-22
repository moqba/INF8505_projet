#!/bin/bash

# exit on the first error
set -e

cd $(dirname "${BASH_SOURCE[0]}")
ISS=$1

cd $1

# create the ISS
chessmk -m +P12 trv32p3_sc.prx

rm -f ISS_RPC_SERVER_PORT
export ISS_RPC_SERVER_PORT=0

# create the Virtualizer model
pcsh import_pct.tcl
pcsh create_platform.tcl

cd export
pcsh sim_build.tcl
