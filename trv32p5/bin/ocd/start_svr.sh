#!/usr/bin/env bash
set -e

# Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
prjdir="$(cd -- "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"

PARAMS=()
opt_hdl="trv32p5_vlog"
opt_simv="$prjdir/hdl/$opt_hdl/simv"
opt_vcs_script="$prjdir/bin/ocd_vcs_stop.tcl"
opt_cov=0

# argument parsing
while (( "$#" )); do
  case "$1" in
    -simv)
      opt_simv="$2"
      shift
      ;;
    -vcsscr)
      opt_vcs_script="$2"
      shift
      ;;
    -hdl)
      opt_hdl="$2"
      opt_simv="$prjdir/hdl/$opt_hdl/simv"
      shift
      ;;
    -cov)
      opt_cov=1
      ;;
    --) # end argument parsing
      shift
      break
      ;;
    *) # preserve unknown arguments
      PARAMS+=("$1")
      ;;
  esac
  shift
done

# set arguments in their proper place
set -- "${PARAMS[@]}" "$@"

echo "${BASH_SOURCE[0]}: start, args left:" "$@"

if [[ $opt_cov == 1 ]] ; then
  set -- "$@" -cm_name $opt_hdl.Direct -cm line+cond+branch
fi

echo "SIMV: $opt_simv"
echo "VCS script: $opt_vcs_script"

export LD_LIBRARY_PATH="$(cd -- $(dirname $opt_simv) && pwd -P):$LD_LIBRARY_PATH"

rm -f JTS_PORT_NUMBER
export JTS_PORT_NUMBER=0

echo "/dev/null" > ./rcdname.cfg

if (( $# > 0 )) ; then
  args="$(printf '%q ' "$@")"
fi
cmd="$opt_simv -ucli -do $opt_vcs_script $args &> hdlsim.log"
echo $cmd

# launch VCS
( $cmd ) &
PID_VCS=$!
if [[ "$PID_VCS" == 0 ]] ; then
  exit 127
fi

echo $PID_VCS > .PID_VCS

# wait for JTAG emulator
sleep 1s
count=0
while [[ ! ( -f JTS_PORT_NUMBER && -s JTS_PORT_NUMBER ) ]] ; do
    if [[ $count -ge 30 ]] ; then
        echo "ERROR: Did not find JTS_PORT_NUMBER after 30s"
        kill -9 $PID_VCS
        exit 1
    fi
    sleep 1s
    ((count++)) || true
done

echo "VCS running, JTS port is $(cat JTS_PORT_NUMBER)"