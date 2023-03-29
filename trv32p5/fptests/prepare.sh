#!/usr/bin/env bash
set -ex

# compute paths
scrdir="$(cd -- "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
prjdir="$(cd -- "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

cd $scrdir

[[ -e SoftFloat-3e.zip ]] || wget http://www.jhauser.us/arithmetic/SoftFloat-3e.zip
[[ -e TestFloat-3e.zip ]] || wget http://www.jhauser.us/arithmetic/TestFloat-3e.zip

[[ -d SoftFloat-3e/ ]] || unzip SoftFloat-3e.zip
[[ -d TestFloat-3e/ ]] || unzip TestFloat-3e.zip

if [[ ! -d SoftFloat-3e/source/riscv ]] ; then
  cp -r $prjdir/lib/softfloat/SoftFloat-3e/source/riscv SoftFloat-3e/source/riscv
fi

pushd SoftFloat-3e/build/Linux-x86_64-GCC/
make all SPECIALIZE_TYPE=riscv
popd

pushd TestFloat-3e/build/Linux-x86_64-GCC/
make all
popd

ln -sf TestFloat-3e/build/Linux-x86_64-GCC/testfloat_gen testfloat_gen
ln -sf TestFloat-3e/build/Linux-x86_64-GCC/testfloat_ver testfloat_ver
