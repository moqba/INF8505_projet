#!/bin/bash -ex

[[ -e SoftFloat-3e.zip ]] || wget http://www.jhauser.us/arithmetic/SoftFloat-3e.zip
[[ -e TestFloat-3e.zip ]] || wget http://www.jhauser.us/arithmetic/TestFloat-3e.zip

[[ -d SoftFloat-3e/ ]] || unzip SoftFloat-3e.zip
[[ -d TestFloat-3e/ ]] || unzip TestFloat-3e.zip

pushd SoftFloat-3e/build/Linux-386-SSE2-GCC
make clean all
popd

pushd TestFloat-3e/build/Linux-386-SSE2-GCC
make clean all
popd

ln -sf TestFloat-3e/build/Linux-386-SSE2-GCC/testfloat_gen testfloat_gen
ln -sf TestFloat-3e/build/Linux-386-SSE2-GCC/testfloat_ver testfloat_ver
