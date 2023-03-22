#
# Tcl srcipt for batch simulation runs using Modelsim.
#

set reset_time 35

set cf [open "Release/test.cyc" r]
gets $cf nr_cycles

# Following  formula is valid for the default Go-generated clock_gen entity.
set sim_time [expr 10 * $nr_cycles + $reset_time + 10]

# Simulate
run $sim_time ns

# for RTL code coverage
set dirn [file tail [pwd]]
coverage attribute -test "$dirn.$env(HDL)"
coverage save "Release/modelsim.$env(HDL).cov"

quit
