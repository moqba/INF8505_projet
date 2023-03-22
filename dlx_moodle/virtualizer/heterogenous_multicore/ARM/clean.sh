#!/bin/sh

cd ../common/dlx_tlm2_lt
./clean.sh

cd ../software
rm -rf Release

cd ../../ARM/software
./clean.sh

cd ../platform
rm -rf cwr export
