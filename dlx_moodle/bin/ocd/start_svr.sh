#!/bin/bash -e

mydir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
myname="$(basename ${BASH_SOURCE[0]})"
projdir=$(readlink -f $mydir/../..)

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

rm -f JTS_PORT_NUMBER
export JTS_PORT_NUMBER=0

# launch VCS
( ${SIMV:-${projdir}/hdl/dlx_vlog_noreglog/simv} -ucli \
  -do ${VCS_SCRIPT:-${mydir}/../ocd_vcs_stop.tcl} &> sim_run.log ) &
PID_VCS=$!
if [[ "$PID_VCS" == 0 ]] ; then
  exit 127
fi

echo $PID_VCS > .PID_VCS

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
    ((count++)) || true
done
