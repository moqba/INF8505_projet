
P = plx

HDL=vlog

# Run/debug configuation: Direct or OCD_VCS
RDC=Direct

L = ../../lib
HDLDIR = ../../hdl/$(P)_$(HDL)
DEBUG_CLIENT = ../$(P)_client
STOP_SIM_SCRIPT=../../bin/stop_simv.tcl
FAIL_ACTION=cat $*.ll

TCL_SCRIPT_ARG=
J=
ifeq ($(RDC),OCD_VCS)
export LD_LIBRARY_PATH:=../../$(HDLDIR):$(LD_LIBRARY_PATH)
TCL_SCRIPT_ARG=$(HDLDIR)/simv
FAIL_ACTION=cat $*.ll; tct_tclsh $(STOP_SIM_SCRIPT) $*
else
JTS_PORT_NUMBER=41001 # default
J=-u port=$(JTS_PORT_NUMBER)
endif

S = localhost
C = 1
V = -u verbose -u jts_verbose
V =

help:
	@ echo ""
	@ echo "    Run 'make clean' to remove results and intermediate files"
	@ echo "        'make tests' to execute all tests"
	@ echo "        'make <nr> ' to execute tests number <nr>"
	@ echo "                        <nr> is a two digit number, e.g. 01"
	@ echo ""

%.log : %.tcl %.s
ifneq ($(filter $(RDC), Direct OCD_VCS),)
	chesscc +a -P $L -p $P $*.s -o $*.x +Wdarts,+Whazards
	chesscc +d -P $L -p $P $*.x
	$(DEBUG_CLIENT) -u server=$S -u core=$C $J $V -t "$< $(TCL_SCRIPT_ARG)" >& $*.ll || { $(FAIL_ACTION); }
	@ egrep "PASSED|FAILED" $*.log
else
	@echo "   Unknown Run-Debug-Configuration (RDC=$(RDC))"
	exit 1
endif

01: test_01_mem.log
02: test_02_reg.log
03: test_03_memincr.log
04: test_04_ready.log
10: test_10_breakpoints.log
11: test_11_breakpoints.log
14: test_14_dm.log
15: test_15_watchpoint.log
08: test_08_break.log
09: test_09_detach.log

testlist: 01 02 03 04 10 11 14 15 08 09

tests: testlist
	@if [ "`grep FAILED *.log | wc -l`" != 0 ]; then \
            echo "************************ "; \
            echo "*** Some tests fail. *** "; \
            echo "************************ "; \
            grep -l FAILED *.log; \
            echo "************************ "; \
            exit 1; \
        fi
	@echo "All tests OK."

clean:
	@ -rm -rf *.log DVEfiles inter.vpd ucli.key
	@ -rm -rf *.ll
	@ -rm -rf *.x
	@ -rm -rf *.x.lst
	@ -rm -rf work

