
P = tlx

HDL=vlog

# Run/debug configuation: Direct or OCD_VCS
RDC=Direct

# Path to root
THISDIR:=$(abspath $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))
L=$(abspath $(THISDIR)/../../lib)
PROJDIR=$(abspath $(L)/..)
HDLDIR=$(abspath $(PROJDIR)/hdl)/$(P)_$(HDL)

vpath %.tcl $(THISDIR)
vpath %.s $(THISDIR)

DEBUG_CLIENT=$(THISDIR)/../$(P)_client
STOP_SIM_SCRIPT=../../bin/stop_simv.tcl
FAIL_ACTION=cat $*.ll

TCL_SCRIPT_ARG=
J=
ifeq ($(RDC),OCD_VCS)
export LD_LIBRARY_PATH:=$(HDLDIR):$(LD_LIBRARY_PATH)
SIMV=$(HDLDIR)/simv
TCL_SCRIPT_ARG=\"$(SIMV)\"
FAIL_ACTION=cat $*.ll; tct_tclsh $(STOP_SIM_SCRIPT) $*
else
#JTS_PORT_NUMBER=41001 # default
J=-u port=$(JTS_PORT_NUMBER)
endif

ifdef CODE_COV_SIMV
SIMV+= $(CODE_COV_SIMV) -cm_name $*.$(HDL)
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
	@ echo "    Hint: * Use 'make -B <nr>' to force a test"
	@ echo "          * Use 'make <tgt> RDC=OCD_VCS' to auto-start VCS for each test"
	@ echo ""
	@ echo "    Known targets are $(shell $(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$' | xargs)"
	@ echo ""

%.x : %.s
	chesscc +a -P $L -p $P $< -o $@ +Wdarts,+Whazards
	chesscc +d -P $L -p $P $@

%.log : %.x %.tcl
ifneq ($(filter $(RDC), Direct OCD_VCS),)
	$(DEBUG_CLIENT) -u server=$S -u core=$C $J $V -t "$(word 2,$^) $(TCL_SCRIPT_ARG)" >& $(@:.log=.ll) || { $(FAIL_ACTION); }
	mv $(@:.log=.err) $@ # only if prev. cmd did not fail
	@ egrep "PASSED|FAILED" $@
else
	@echo "   Unknown Run-Debug-Configuration (RDC=$(RDC))"
	exit 1
endif

# If the above recipe fails, check the test_%_*.err file. 

getlogfiles = $(patsubst $(THISDIR)/%.tcl,%.log,$(wildcard $(patsubst %,$(THISDIR)/test_%_*.tcl,$(1)))) 


doloop_tests = 26 36

extbrk_tests = \
       30 31 32 33 34 35 36
       
testlist = \
       01 02 03 \
       10 11 12 14 15 \
       20 21 22 23 24 25 26

# TODO test 27

# We need control over VCS to run the external-break tests
ifeq ($(RDC),OCD_VCS)
testlist += $(extbrk_tests)
endif


tests: $(call getlogfiles,$(testlist))
	@if [ "`grep FAILED $^ | wc -l`" != 0 ]; then \
            echo "************************ "; \
            echo "*** Some tests fail. *** "; \
            echo "************************ "; \
            grep -l FAILED $^; \
            echo "************************ "; \
            exit 1; \
        fi
	@echo "All tests OK."

tests_no_doloop: $(call getlogfiles,$(filter-out $(doloop_tests),$(testlist)))
	@if [ "`grep FAILED $^ | wc -l`" != 0 ]; then \
            echo "************************ "; \
            echo "*** Some tests fail. *** "; \
            echo "************************ "; \
            grep -l FAILED $^; \
            echo "************************ "; \
            exit 1; \
        fi
	@echo "All tests OK."

# Discover tests from tcl filenames, add a rule for each of them, to allow e.g. make 11
discovered_tests = $(patsubst test_%,%,$(shell echo $(wildcard $(THISDIR)/test_*_*.tcl) | grep -Eo 'test_[0-9]+' ))
.PHONY: clean tests asm $(discovered_tests) $(patsubst %,asm%,$(discovered_tests))

define RULE

$(1) : $(call getlogfiles,$(1))

asm$(1) : $(patsubst %.log,%.x,$(call getlogfiles,$(1)))

endef

$(foreach i,$(discovered_tests),$(eval $(call RULE,$(i))))

asm: $(patsubst %,asm%,$(discovered_tests))

clean:
	@ echo -n ""

## target clean - special handling for concurrent builds
# for make -jN clean tests, this will execute clean always before other targets 
ifneq ($(filter clean,$(MAKECMDGOALS)),)
  $(shell rm -rf *.log *.err DVEfiles inter.vpd ucli.key *.ll *.x *.x.as *.x.lst work)
endif

###
