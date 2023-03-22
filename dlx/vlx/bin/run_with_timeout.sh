#!/bin/bash
#
# Copyright (c) 2019-2021 Synopsys, Inc. This processor model and the associated
# documentation are proprietary to Synopsys, Inc.  This model may only be
# used in accordance with the terms and conditions of a written license
# agreement with Synopsys, Inc.  All other use, reproduction, or distribution
# of this model are strictly prohibited.
#
mydir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
projdir=$(readlink -f $mydir/..)

# argument parsing
while (( "$#" )); do
  case "$1" in
    -tmo)
      temp="${2%\"}"
      TIMEOUT="${temp#\"}m"
      echo "TIMEOUT=$TIMEOUT"
      shift 2
      ;;
    -msg)
      temp="${2%\"}"
      MSG="${temp#\"}"
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

# import list_descendant_processes
source $projdir/bin/clean_on_interrupt.sh

remove_from_list()
{
  local arr=("$1")
  arr=( ${arr[@]/$2/} )
  echo "${arr[@]}"
}

# timeout
(
  _KILLER=$BASHPID
  trap '[[ $sleep_pid ]] && kill "$sleep_pid"' EXIT
  sleep "${TIMEOUT:-20m}" & sleep_pid=$!
  wait $sleep_pid
  sleep_pid=
  echo "${MSG:-ERROR: Timeout}"
  # descendants of our parent, don't include parent
  procs=$(list_descendant_processes "$$" false)
  # remove this timeout subshell
  procs=$(remove_from_list "$procs" "$_KILLER")
  kill -s 9 -- $procs
  wait $procs
) & 2> /dev/null
KILLER=$!
# NOTE: on timeout, $KILLER should not kill itself before finishing

cleanup() {
  rc=$?
  kill -0 "$KILLER" && kill -HUP "$KILLER" && wait "$KILLER" 2> /dev/null
  exit $rc
}
trap cleanup EXIT

# launch in background, such that timeout works
( "$@" ) &
PID=$!
wait $PID 2> /dev/null
exit $?