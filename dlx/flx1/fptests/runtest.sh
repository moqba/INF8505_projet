#!/bin/bash

{
# Default:
# TESTFLOAT_OPTS="-level 1 -seed 1"
# More tests + random seed
# TESTFLOAT_OPTS="-level 2 -seed $RANDOM"

renice 10 $$

set -e
set -o pipefail

[[ -e ./testfloat_gen ]] || ( echo "Could not find testfloat_gen" ; exit 1 )
[[ -e ./testfloat_ver ]] || ( echo "Could not find testfloat_ver" ; exit 1 )

# argument parsing
while (( "$#" )); do
  case "$1" in
    --iss)
      TESTISS="${TESTISS:-} $2"
      shift 2
      ;;
    +P)
      NCORES_HOST=$2
      shift 2
      ;;
    --) # end argument parsing
      shift
      break
      ;;
    *) # preserve unknown arguments
      PARAMS="${PARAMS:-} $1"
      shift
      ;;
  esac
done
# set arguments in their proper place
eval set -- "${PARAMS:-} $*"

# pass remaining args to testfloat_gen
TESTFLOAT_OPTS="$*"

# build
for CFG in Release Release_LLVM Debug Debug_LLVM Native
do
  chessmk ${NCORES_HOST++P${NCORES_HOST}} -m driver/test -C $CFG
done

for ISS in ${TESTISS:=flx_ia flx_ia_fast flx_ca}
do
  {
    echo " + ISS: $ISS"

    for CFG in Release Release_LLVM Debug Debug_LLVM Native
    do
     echo " ++ CFG: $CFG"

      # round to nearest even
      for FN in \
        f32_add \
        f32_sub \
        f32_mul \
        f32_div \
        f32_sqrt \
        f32_roundToInt \
        i32_to_f32 \
        ui32_to_f32 \
        f32_eq \
        f32_lt \
        f32_le \
        f64_add \
        f64_sub \
        f64_mul \
        f64_div \
        f64_sqrt \
        f64_roundToInt \
        i32_to_f64 \
        ui32_to_f64 \
        f64_eq \
        f64_lt \
        f64_le \
        f32_to_f64 \
        f64_to_f32
      do
        echo " +++ Testing $FN on $ISS in $CFG"
        set +e
        ./testfloat_gen ${TESTFLOAT_OPTS} -tininessbefore $FN |& \
        chessmk driver/test +D $ISS -C $CFG -S -s +X $FN |& \
        ./testfloat_ver -errors -1 -tininessbefore $FN
        exitcodes=("${PIPESTATUS[@]}")
        set -e
        echo " +++ Exit codes ${exitcodes[@]}"
        [[ ${exitcodes[0]} != 0 || ${exitcodes[1]} != 0 ]] && exit 1
      done

      # to int: round to zero
      for FN in \
        f32_to_i32 \
        f32_to_ui32 \
        f64_to_i32 \
        f64_to_ui32
      do
        echo " +++ Testing $FN on $ISS in $CFG"
        set +e
        ./testfloat_gen ${TESTFLOAT_OPTS} -rminMag $FN |& \
        chessmk driver/test +D $ISS -C $CFG -S -s +X $FN |& \
        ./testfloat_ver -errors -1 -rminMag $FN
        exitcodes=("${PIPESTATUS[@]}")
        set -e
        echo " +++ Exit codes ${exitcodes[@]}"
        [[ ${exitcodes[0]} != 0 || ${exitcodes[1]} != 0 ]] && exit 1
      done


     echo " ++ end: $CFG"
    done

   echo " + end: $ISS"
 } |& tee fptest-${ISS}.log

done

echo "-- Done"

echo " ############################################################## "
echo " Diff between ISSs"

for ISS1 in ${TESTISS} ; do
  for ISS2 in ${TESTISS} ; do
    if [[ "$ISS1" != "$ISS2" ]] ; then
      echo "$ISS1 vs $ISS2"
      diff -uEbBw <(grep -vE ".*$ISS1.*" fptest-$ISS1.log)  <(grep -vE "^.*$ISS2.*" fptest-$ISS2.log) |& tee diff-$ISS1-$ISS2
    fi
  done
done


} |& tee $(basename ${BASH_SOURCE[0]} .sh ).log-$(date +%Y%m%d-%H%M%S)
