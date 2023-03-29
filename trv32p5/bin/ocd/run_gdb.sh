#!/usr/bin/env bash

# Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.

mydir="$(cd -- "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
myname="$(basename ${BASH_SOURCE[0]})"
projdir="$(cd -- "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"

# argument parsing
while (( "$#" )); do
  case "$1" in
    -simv)
      temp="${2%\"}"
      SIMV="${temp#\"}"
      echo "SIMV=$SIMV"
      shift 2
      ;;
    -vcsscr)
      temp="${2%\"}"
      VCS_SCRIPT="${temp#\"}"
      echo "VCS_SCRIPT=$VCS_SCRIPT"
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

echo "$myname : start, args left: $*"


PROG=$1

rm -f JTS_PORT_NUMBER
export JTS_PORT_NUMBER=0

# launch VCS
( ${SIMV:=${projdir}/hdl/trv32p5_vlog_noreglog/simv} -ucli \
  -do ${VCS_SCRIPT:-${mydir}/../ocd_vcs_stop.tcl} &> hdlsim.log ) &
PID_VCS=$!
if [[ "$PID_VCS" == 0 ]] ; then
  exit 127
fi

# wait for JTAG emulator
sleep 1s
count=0
while [ ! -f JTS_PORT_NUMBER ] ; do
    if [ $count -ge 200 ] ; then
        echo "ERROR: Did not find JTS_PORT_NUMBER after 200s"
        kill -9 $PID_VCS
        exit 1
    fi
    sleep 1s
    ((count++))
done

hdl=$(basename $(dirname $SIMV))

# launch asip2gdb

cat <<EOF | asip2gdb -l ${projdir}/debug_client/trv32p5_client -connect-hw server=localhost,port=$(cat JTS_PORT_NUMBER),core=1 -e $PROG
iss eval {::p fileoutput chess_report set -file "[dict get [tclutils::list2dict [::p info keys program] {*}[::p program query name]] program].$hdl.gdb.ocd.mem"}
continue
quit
EOF
exitcode=$?

# all normal - gracefully shutdown VCS
touch .OCD_VCS_STOP
sleep 1s
kill -9 $PID_VCS 2> /dev/null
rm -f ucli.key JTS_POR_NUMBER rcdname.cfg .OCD_VCS_STOP

# exit with code of asip2gdb
exit $exitcode
