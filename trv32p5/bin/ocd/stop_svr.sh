#!/usr/bin/env bash
set -e

# Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
echo "${BASH_SOURCE[0]}: start, args left:" "$@"

if [[ ! -e .PID_VCS ]] ; then
  echo "WARNING: Did you start VCS in this working dir?"
fi

PID_VCS=$(cat .PID_VCS)

# all normal - gracefully shutdown VCS
touch .OCD_VCS_stop

count=0
while kill -s 0 -- $PID_VCS 2> /dev/null ; do
  if (( $count > 10 )) ; then
    kill -9 $PID_VCS 2> /dev/null
    break
  fi
  sleep 1s
  ((count++)) || true
done

rm -f ucli.key JTS_POR_NUMBER rcdname.cfg .OCD_VCS_stop .PID_VCS
