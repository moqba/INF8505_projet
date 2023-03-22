#!/bin/bash

list_descendant_processes() {
    local pid="$1"
    local and_self="${2:-true}"
    if children="$(pgrep -P "$pid")"; then
        for child in $children; do
            list_descendant_processes "$child" true
        done
    fi
    if [[ "${and_self}" == true ]] ; then
      echo "$pid"
    fi
}

# SIGINT SIGTERM handler
exit_script()
{
  echo "SIGINT - aborting $$"
  # remove handler
  trap - SIGINT SIGTERM
  # kill this process and all children
  procs=$(list_descendant_processes "$$")
  echo "Killing $procs"
  kill -s 9 -- $procs
}

export -f list_descendant_processes exit_script

# (return 0 2>/dev/null) && sourced=1 || sourced=0

if ! (return 0 2>/dev/null)
then  # not sourced
  trap exit_script SIGINT SIGTERM
  exec "$@"
fi