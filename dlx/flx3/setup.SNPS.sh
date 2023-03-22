#!/usr/bin/env bash

if ! (return 0 2>/dev/null)
then  # not sourced
  echo "Script needs to be sourced"
else
  export VERILATOR_ROOT=/u/sgasip/ipd/verilator/verilator-4.010
fi
