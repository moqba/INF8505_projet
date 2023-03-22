#!/bin/sh

set -e

iss=$1
test=$2

mydir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
myname="$(basename ${BASH_SOURCE[0]})"
projdir=$(readlink -f $mydir/../..)

VIRTUALIZER_MODEL_PATH=${projdir}/virtualizer/$iss/export/Debug
APPLICATION=${test}

rm -f ISS_RPC_SERVER_PORT
export ISS_RPC_SERVER_PORT=0

export VIRTUALIZER_MODEL_PATH
export APPLICATION

# generate exit file
read_elf -e +x -G ${test}
vpxsh -s ${mydir}/run.tcl 
