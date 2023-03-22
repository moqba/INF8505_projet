#!/bin/sh

if [[ "$1" == "help" ]]
then
    echo "usage: ./`basename $0` [full|norst_mdl|norst_rgr|virgin|help]*"
    echo "       full:      including RTL regression"
    echo "       norst:     incremental build of model+regression"
    echo "       norst_mdl: incremental build of model"
    echo "       norst_rgr: incremental build of regression"
    echo "       virgin:    clean all known intermediate files and exit"
    echo "       help:      this help"
    exit 0
fi

# make model
./make_model.sh $@
if [ $? -ne 0 ]
then
    echo "error in building model"
    exit 1
fi

TEST_VGN=0 # virgin model
TEST_RST=1 # reset the model
TEST_ISS=0 # make all ISSs not just the cycle accurate
TEST_RTL=0

# parse arguments
for var in "$@"
do
    if [[ $var == "full" ]]
    then
        echo "test full"
        TEST_ISS=1
        TEST_RTL=1
    fi
    if [[ $var == "norst_rgr" || $var == "norst" ]]
    then
        echo "test noreset"
        TEST_RST=0
    fi
    if [[ $var == "virgin" ]]
    then
        echo "test virgin"
        TEST_VGN=1
    fi
done

mkdir -p logs

# normal order:
#REGR_DIRS="C[0-9][0-9]_*"
# faster order: The C5x_ tests are started first because they take longer to complete
REGR_DIRS="C5[0-9]_* C[0-4][0-9]_* C[6-9][0-9]_*"


cd regression
if [ $TEST_RST -ne 0 ]
then
    ./domake clean ${REGR_DIRS}
fi

if [ $TEST_VGN -ne 0 ]
then
    ./domake virgin ${REGR_DIRS}
    exit 0
fi

./domake diff ${REGR_DIRS}
if [ $? -ne 0 ]
then
    echo "error in regression (diff)"
    exit 1
fi
cd ..

if [ $TEST_RTL -ne 0 ]
then
    cd regression
    ./domake rtldiff ${REGR_DIRS}
    if [ $? -ne 0 ]
    then
        echo "error in regression (rtldiff)"
        exit 1
    fi
fi

echo "OK ($0)"
