set _hector_comp_use_new_flow true
set _hector_softfloat_version custom

source $env(VC_STATIC_HOME)/hector/local/divchecks.tcl

proc compile_spec {} {
    create_design -name spec -top hector_wrapper

    cppan ../c/div.cc

    compile_design spec
}

proc compile_impl {} {
    create_design -name impl -top div -clock clock -reset reset

    vcs -sverilog -f ../rtl/files_div

    compile_design impl
}
proc make {} {
  # compile spec & impl, for portability (see DPV manual recommendation)
  # proof only for impl
  compile_spec
  compile_impl
  compose

  # Alternative, but requires to remove 'impl.' from all expressions
  #compile_impl
  #compose -nospec
}

make

# for div1 in cpp file
#
#proc div1_dividend {} {
#  return "{32'b0,spec.a(1)}"
#}
#
#proc div1_divisor {} {
#  return "spec.b(1)"
#}
#
#proc div1_quotient {i} {
#  return "(spec.pquo${i}(1) << [expr 32-$i])"
#}
#proc div1_remainder {i} { return "(spec.prem${i}(1))" }
#
#proc div1_assumptions {} {
#  assume no_divzero = spec.b(1) != 0
#}
#
#solveNB_division \
#        32 \
#        div1_dividend \
#        div1_divisor \
#        div1_quotient \
#        div1_remainder \
#        div1_assumptions \
#        div1_proof

# NOTE
# timesteps t=0, 1, ..
# clock H L H L
# two time steps = one clock cycle

# for div.v without CLB, i.e., for fixed division step count

proc get_dividend {} {
  return "{32'b0,impl.divA_in(1)}"
}

proc get_divisor {} {
  return "impl.divB_in(1)"
}

proc get_quotient {i} {
  return "(impl.AL([expr 2*$i + 2]) << [expr 32-$i])"
}

proc get_remainder {i} {
  return "(\$unsigned({impl.AH([expr 2*$i + 2]),impl.AL([expr 2*$i + 2])}) >> $i)"
}

proc input_assumptions {} {
  # opcode
  assume impl.en_vd_divide_divA_divB_wl_wh_div_EX(0) == 0
  assume impl.en_vd_divide_divA_divB_wl_wh_div_EX(1) == 1
  for {set i 2} {$i < 100} {incr i} {
    assume impl.en_vd_divide_divA_divB_wl_wh_div_EX($i) == 0
  }
  assume -always impl.en_vd_fdivide_divA_divB_wl_div_EX == 0
  assume -always impl.en_vd_fsqrt_divA_wl_div_EX == 0

  assume no_divzero = impl.divB_in(1) != 0
}


#proc case_split_32 {} {
#  caseSplitStrategy basic
#
#  caseBegin divA
#  caseEnumerate divA_lz -expr impl.divA_in(1)[31:0] -parent divA -type leading1
#}

#set_hector_case_splitting_procedure "case_split_32"
#
#solveNB_division \
#        32 \
#        get_dividend \
#        get_divisor \
#        get_quotient \
#        get_remainder \
#        input_assumptions \
#        p

proc mkproc {name arglist body args} {
    set body [string map $args $body]
    proc $name $arglist $body
}

# no CLZ:
# i=0 -> cnt=33 -> t=2
# i=1 -> cnt=32 -> t=4

# CLZ=1 -> PA=A<<0
# t=2 -> cnt=32 -> i = 1
# t=4 -> cnt=31 -> i = 2
# i=0 -> cnt=33 -> Qi=0, Ri=PA>>0

# CLZ=2 -> PA=A<<1
# t=2 -> cnt=31 -> i = 2
# t=4 -> cnt=30 -> i = 3
# i=0 -> cnt=33 -> Qi=0, Ri=PA>>1
# i=1 -> cnt=32 -> Qi=0, Ri=PA>>0

# for div.v with variable division step count
# skips redundant MSBs


for {set lz 0} {$lz <= 32} {incr lz} {

  # redundant MSBs
  # lz=2: 0b001xxx.. => 2 leading zeros, 1 redundant MSB
  # div.v skips redundant MSBs
  if {$lz > 0} {
    set rb [expr $lz - 1]
  } else {
    set rb 0
  }

  mkproc "input_assumptions_$lz" {} {
    if {%LZ% == 32} {
      # all-zero case
      assume "lz%LZ% = impl.divA_in(1)\[31:0\] == 32'b0"
    } else {
      # leading-1 cases
      assume "lz%LZ% = impl.divA_in(1)\[31:[expr 31 - %LZ%]\] == [expr 1 + %LZ%]'b[string repeat 0 %LZ%]1"
    }
    input_assumptions
  } %LZ% $lz

  mkproc "get_quotient_$lz" {i} {
    if {$i > %RB%} {
      set t [expr 2 * ($i - %RB%) + 2]
      return "(impl.AL($t) << [expr 32-$i])"
    } else {
      # Qi for first RB steps are zero
      return "(impl.AL(2) << [expr 32-$i])"
    }
  } %RB% $rb

  mkproc "get_remainder_$lz" {i} {
    if {$i > %RB%} {
      set t [expr 2 * ($i - %RB%) + 2]
      return "(\$unsigned({impl.AH($t),impl.AL($t)}) >> $i)"
    } else {
      # same remainder for the first %RB% steps
      return "(\$unsigned({impl.AH(2),impl.AL(2)}) >> %RB%)"
    }
  } %RB% $rb

  solveNB_division \
          32 \
          get_dividend \
          get_divisor \
          get_quotient_$lz \
          get_remainder_$lz \
          input_assumptions_$lz \
          "p${lz}"
}