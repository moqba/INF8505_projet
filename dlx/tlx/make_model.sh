#!/bin/sh

export PROC=tlx

if [[ "$1" == "help" ]]
then
    echo "usage: ./`basename $0` [full|noreset|virgin|help]*"
    echo "       full:      including RTL regression"
    echo "       norst:     incremental build of model"
    echo "       virgin:    clean all known intermediate files and exit"
    echo "       help:      this help"
    exit 0
fi


MAKE_VGN=0 # virgin model
MAKE_RST=1 # reset the model
MAKE_ISS=0 # make all ISSs not just the cycle accurate
MAKE_RTL=0

# parse arguments
for var in "$@"
do
    if [[ $var == "full" ]]
    then
        echo "make full"
        MAKE_ISS=1
        MAKE_RTL=1
    fi
    if [[ $var == "norst_mdl" || $var == "norst" ]]
    then
        echo "make noreset"
        MAKE_RST=0
    fi
    if [[ $var == "virgin" ]]
    then
        echo "make virgin"
        MAKE_VGN=1
    fi
done


export CHESSMK_OPTIONS="+P $NCORES_HOST"


if [ $MAKE_VGN -ne 0 ]
then
    echo "virgin model"
    #chessmk ${CHESSMK_OPTIONS} -r model.prx
    rm -rf lib/isg lib/oneliners
    rm -rf lib/Native lib/Release lib/Debug
    rm -rf lib/runtime/lib/Release lib/runtime/lib/Debug
    rm -rf iss/work
    rm -rf hdl/${PROC}_vlog hdl/${PROC}_vhdl
    rm  -f hdl/${PROC}_go_unused_instrs.rpt           \
           hdl/jtag_emulator_vhdl/jtag_socket.o       \
           hdl/jtag_emulator_vhdl/jtag_emulator.o     \
           hdl/jtag_emulator_vhdl/jtag_emulator.so    \
           hdl/jtag_emulator_vlog/jtag_socket.o       \
           hdl/jtag_emulator_vlog/jtag_emulator.o     \
           hdl/jtag_emulator_vlog/jtag_emulator.so
    rm -rf logs
    find * | egrep "\.prxui" | xargs rm -f

    echo "virgin regression"
    ( cd regression; ./domake virgin > /dev/null)

    # echo "virgin applications"
    # nothing here

    exit 0
fi

###########################################################
# reset
mkdir -p logs
if [ $MAKE_RST -ne 0 ]
then
    echo "reset model"
    chessmk ${CHESSMK_OPTIONS} -r model.prx -m
fi

###########################################################
# basis model
echo "chessmk ${CHESSMK_OPTIONS} model.prx -m"
chessmk ${CHESSMK_OPTIONS} model.prx -m > logs/chessmk.model.log 2>&1
if [ $? -ne 0 ]
then
    echo "error building model (see logs/chessmk.model.log)"
    exit 1
fi

###########################################################
# make all ISSs
if [ $MAKE_ISS -ne 0 ]
then
    cd iss
    for i in *.prx
    do
        echo "chessmk ${CHESSMK_OPTIONS} $i"
        chessmk ${CHESSMK_OPTIONS} $i > ../logs/chessmk.$i.log 2>&1
        if [ $? -ne 0 ]
        then
            echo "error building iss $i (see logs/chessmk.$i.log)"
            exit 1
        fi
    done
    cd ..
fi

###########################################################
# make all RTL
if [ $MAKE_RTL -ne 0 ]
then
    echo "chessmk hdl/${PROC}_vlog.prx"
    chessmk hdl/${PROC}_vlog.prx > logs/rtl.vlog.gen.output 2>&1
    if [ $? -ne 0 ]
    then
        echo "error generating vlog (see logs/rtl.vlog.gen.output)"
        exit 1
    fi

    echo "make elab (in dir hdl/${PROC}_vlog"
    (cd hdl/${PROC}_vlog; make elab ) > logs/rtl.vlog.elab.log 2>&1
    if [ $? -ne 0 ]
    then
        echo "Error during RTL elaboration (see logs/rtl.vlog.elab.log)"
        exit -1;
    fi
fi
