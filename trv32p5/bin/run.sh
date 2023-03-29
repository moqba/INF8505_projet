#!/usr/bin/env bash
#
# Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

debug () {
  echo "`date` ($$,$BASHPID) $0:" "$@"
}

PARAMS=()
opt_timeout=""
opt_msg="ERROR: Timeout"

# argument parsing
while (( "$#" )); do
  case "$1" in
    -t|-tmo|--timeout)
      opt_timeout="$2"
      shift
      ;;
    -m|-msg|--message)
      opt_msg="$2"
      shift
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

################################################################################

# cleanup in EXIT trap - stop $1 and its descendants
cleanup () {
  local rc=$?
  local pid="$1"
  if [[ "$pid" ]] && kill -0 -- "$pid" 2> /dev/null ; then
    local p=($(list_descendant_processes "$pid" true))
    kill -- "${p[@]}" 2> /dev/null
    wait "$pid" 2> /dev/null
  fi
  exit $rc
}

################################################################################

# Interruptible sleep
sleep_ () {
  ( # subshell - new scope for traps

    trap 'cleanup $sleep_pid' EXIT

    # launch sleep in background
    sleep "$1" &
    sleep_pid=$!

    # wait for sleep
    wait $sleep_pid 2> /dev/null

    # rely on EXIT trap to cleanup sleep
  )
}

################################################################################

# list_descendant_processes pid [and_self:-true]
list_descendant_processes() {
  local pid="$1"
  local and_self="${2:-true}"
  # ignore $(..) subshell with pid $BASHPID
  if children="$(BP=${BASHPID} ; pgrep -P "$pid" | grep -v ^${BP}$)"; then
    for child in $children; do
      list_descendant_processes "$child" true
    done
  fi
  if [[ "${and_self}" == true ]] ; then
    echo "$pid"
  fi
}

################################################################################

# wait_on pid1 [pid2 ...]
# also works for processes that are no children of us
wait_on() {
  for p in "$@" ; do
    tail --pid="$p" -f /dev/null 2> /dev/null
  done
}

################################################################################

# stop_processes pid1 [pid2 ...]
# stop_processes -t 5[s] pid1 [pid2 ...]
# 2 steps: 1) terminate 2) force-kill after timeout
stop_processes() {
  local timeout="2s"
  if (( $# > 2 )) && [[ "$1" == "-t" ]] ; then
    timeout="$2"
    shift 2
  fi
  local pids=("$@")

  # after timeout, force-kill $@
  timeout_killer() {
    # interruptible sleep (uses EXIT trap)
    sleep_ $timeout

    # force kill if timed out or sleep was interrupted
    kill -s SIGKILL -- "$@" &> /dev/null

    # Note: new descendants that are started after list_descendant_processes,
    # for example in a SIGTERM trap, will not be terminated/killed.
  }

  # request termination
  kill -s SIGTERM -- "${pids[@]}" 2> /dev/null

  ( # subshell - new scope for traps

    # prepare cleanup trap
    trap 'cleanup $KILLER' EXIT

    # escalate to SIGKILL after timeout
    ( timeout_killer "${pids[@]}" ) &
    KILLER=$!

    # wait for processes to terminate, or for timeout
    wait_on "${pids[@]}"

    # rely on EXIT trap to cleanup KILLER
  )
}

################################################################################

# cleanup: stop all descendants of $$ (myself)
exit_script() {
  local rc=$?
  local exitsig="$1"

  # remove traps - make cleanup interruptible
  trap - SIGINT SIGTERM EXIT

  # stop all descendants, but not myself
  pids=($(list_descendant_processes $$ not_myself))

  # remove subshell from list, if applicable
  if (( $$ != $BASHPID )) ; then
    for i in "${!pids[@]}" ; do
      if [[ "${pids[i]}" == $BASHPID ]] ; then
        unset 'pids[i]'
      fi
    done
  fi

  # remove already dead processes
  for i in "${!pids[@]}" ; do
    if ! kill -s 0 -- "${pids[i]}" 2> /dev/null ; then
      unset 'pids[i]'
    fi
  done

  if (( ${#pids[@]} > 0 )) ; then
    stop_processes "${pids[@]}"
  fi

  # proper SIGINT behavior - kill myself with SIGINT
  if [[ "$exitsig" == "SIGINT" || "$exitsig" == "INT" ]] ; then
    trap - SIGINT
    kill -s SIGINT -- $$ $BASHPID 2> /dev/null
  fi

  # in EXIT trap, forward exit code
  if [[ "$exitsig" == "EXIT" ]] ; then
    trap - EXIT
    exit $rc
  fi
}

################################################################################

# install signal traps
setup_cleanup_traps () {
  trap "exit_script SIGINT" SIGINT
  trap "exit_script SIGTERM" SIGTERM
  trap "exit_script EXIT" EXIT
}

################################################################################

# cleanup_on_interrupt <command>
# executes <command> in a subshell
# on SIGINT SIGTERM or EXIT, stop <command> and all its descendants
cleanup_on_interrupt () {
  setup_cleanup_traps

  # we want to handle signals, hence launch in background
  ( "$@" ) &
  PID=$!

  wait $PID 2> /dev/null
  rc=$?

  return $rc
}

################################################################################

# run_with_timeout <command>
# executes <command> in a subshell
# on timeout, stop <command> and all its descendants
run_with_timeout () {
  # timeout handler
  timeout_killer ()
  {
    local pid="$1"

    # interruptible sleep (uses EXIT trap)
    sleep_ $opt_timeout

    # print user message
    echo $opt_msg

    TIMEOUT_OCCURED=1

    # stop downstream process
    stop_processes $(list_descendant_processes "$pid" true)
  }

  (
    # subshell - new scope for traps

    # we want to handle signals, hence launch in background
    ( "$@" ) &
    PID=$!

    # prepare cleanup trap
    trap 'cleanup $KILLER' EXIT

    # start timeout killer
    ( timeout_killer $PID ) &
    KILLER=$!

    wait $PID 2> /dev/null
    rc=$?

    if [[ $TIMEOUT_OCCURED ]] ; then
      wait $KILLER 2> /dev/null
    fi

    # rely on EXIT trap to cleanup timeout_killer
    exit $rc
  )
  rc=$?
  return $rc
}

################################################################################

# need bash's job-control to trap SIGINT
set -m

if [[ -z "$opt_timeout" ]] ; then
  echo "INFO: Running without timeout"
  cleanup_on_interrupt "$@"
  rc=$?
else
  echo "INFO: Running with timeout $opt_timeout"
  cleanup_on_interrupt run_with_timeout "$@"
  rc=$?
fi

exit $rc