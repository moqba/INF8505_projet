#!/bin/bash -e

mydir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
myname="$(basename ${BASH_SOURCE[0]})"
projdir=$(readlink -f $mydir/../..)

# argument parsing
while (( "$#" )); do
  case "$1" in
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

PID_VCS=$(cat .PID_VCS)

# all normal - gracefully shutdown VCS
touch .OCD_VCS_STOP
sleep 1s
kill -9 $PID_VCS 2> /dev/null
rm -f ucli.key JTS_POR_NUMBER rcdname.cfg .OCD_VCS_STOP .PID_VCS
