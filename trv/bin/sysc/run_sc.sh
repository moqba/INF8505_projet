#!/bin/bash
#
# Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

mydir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
myname="$(basename ${BASH_SOURCE[0]})"
projdir=$(readlink -f $mydir/../..)

# argument parsing
while (( "$#" )); do
  case "$1" in
    -asip2gdb)
      USE_ASIP2GDB=1
      shift
      ;;
    -iss)
      SCISS=$2
      shift 2
      ;;
    --) # end argument parsing
      shift
      break
      ;;
    *) # preserve unknown arguments
      PARAMS="${PARAMS:-}${PARAMS:+ }$1"
      shift
      ;;
  esac
done

# set arguments in their proper place
eval set -- "${PARAMS:-} $*"

echo "$myname : start"

export SCISS=${SCISS:-trv32p3_sc_dbg}

# default simulator
COMMAND=${projdir}/iss/${SCISS}
PROC_NAME=::trv32p3_top.TRV32P3

PROG=$1

[[ -e "$COMMAND" ]] || exit 1
[[ -e "$PROG" ]] || exit 1

rm -f ISS_RPC_SERVER_PORT
export ISS_RPC_SERVER_PORT=0

export trv32p3_DIR=${projdir}/lib
trap '( kill -0 "$PID_SYSTEMC" && kill -9 "$PID_SYSTEMC" &&  wait "$PID_SYSTEMC" ) 2> /dev/null' EXIT
# start systemC simulator (in background)
${COMMAND}  &
PID_SYSTEMC=$!


sleep 1s
count=0
while [ ! -f ISS_RPC_SERVER_PORT ] ; do
    if [ $count -ge 200 ] ; then
        echo "ERROR: Did not find ISS_RPC_SERVER_PORT after 200s"
        kill -9 $PID_SYSTEMC
        exit 1
    fi
    sleep 1s
    ((count++))
done

sleep 1s

if [[ x${USE_ASIP2GDB:-0} == x1 ]] ; then
  cat <<EOF | asip2gdb -l localhost,$(cat ISS_RPC_SERVER_PORT) -e $PROG -iss-name $PROC_NAME
iss eval {$PROC_NAME fileoutput chess_report set -file "$PROG.[dict get [tclutils::list2dict [$PROC_NAME info keys iss_option] [$PROC_NAME info issoptions]] iss_name].gdb.mem"}
continue
quit
EOF

else
  tct_tclsh ${mydir}/run_sc_dbg.tcl $PROG ${projdir}/lib $PROC_NAME
fi