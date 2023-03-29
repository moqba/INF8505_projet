#
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

set _hector_comp_use_new_flow true

source $env(VC_STATIC_HOME)/hector/local/divchecks.tcl

proc compile_ {name} {
  create_design -name $name -top div -clock clock -reset reset

  vcs -sverilog +incdir+../../../hdl/trv32p5_vlog ../../../hdl/trv32p5_vlog/trv32p5/prim/div.v

  compile_design $name
}

proc make {} {
  # compile spec & impl, for portability (see DPV manual recommendation)
  # proof only for impl

  compile_ spec
  compile_ impl
  compose

  # Alternative, but requires to remove 'impl.' from all expressions
  #compile_impl
  #compose -nospec
  # waveforms for counterexamples not shown?
}

make

# NOTE
# timesteps t=0, 1, ..
# clock H L H L
# two time steps = one clock cycle

proc get_dividend {} {
  return "{32'b0,impl.divA_in(1)}"
}

proc get_divisor {} {
  return "impl.divB_in(1)"
}

proc get_quotient {i} {
  return "(impl.PA([expr 2*$i+2])[31:0] << [expr 32-$i])"
}

proc get_remainder {i} {
  return "(impl.PA([expr 2*$i+2]) >> $i)"
}

# no CLZ:
# i=0 -> cnt=33 -> t=2
# i=1 -> cnt=32 -> t=4

proc input_assumptions {} {
  # opcode
  assume impl.en_divR_divu_divA_divB_div_EX(0) == 0
  assume impl.en_divR_divu_divA_divB_div_EX(1) == 1
  for {set i 2} {$i < 100} {incr i} {
    assume impl.en_divR_divu_divA_divB_div_EX($i) == 0
  }

  assume -always impl.en_divR_divs_divA_divB_div_EX == 0
  assume -always impl.en_divR_rems_divA_divB_div_EX == 0
  assume -always impl.en_divR_remu_divA_divB_div_EX == 0

  assume no_divzero = impl.divB_in(1) != 0
  assume no_x0 = impl.div_wad_in(1) != 0

  assume div_ready = impl.cnt(1) == 0
}

# unsigned div
solveNB_division \
        32 \
        get_dividend \
        get_divisor \
        get_quotient \
        get_remainder \
        input_assumptions \
        p
