set _hector_comp_use_new_flow true
set _hector_softfloat_version custom

proc compile_spec {} {
    create_design -name spec -top hector_wrapper
    cppan -I../softfloat-3e/source/include \
        -I../softfloat-3e/source/flx \
        -I../softfloat-3e/build/HECTOR \
        ../c/mul32.cc \
        ../softfloat-3e/source/f32_mul.c \
        ../softfloat-3e/source/s_normSubnormalF32Sig.c \
        ../softfloat-3e/source/s_shortShiftRightJam64.c \
        ../softfloat-3e/source/s_countLeadingZeros32.c \
        ../softfloat-3e/source/s_roundPackToF32.c \
        ../softfloat-3e/source/s_shiftRightJam32.c \
        ../softfloat-3e/source/s_shiftRightJam64.c \
        ../softfloat-3e/source/flx/s_propagateNaNF32UI.c \
        ../softfloat-3e/source/flx/softfloat_raiseFlags.c \
        ../softfloat-3e/source/s_countLeadingZeros8.c \
        ../softfloat-3e/source/s_countLeadingZeros16.c \
        ../softfloat-3e/source/s_countLeadingZeros64.c \
        ../softfloat-3e/source/s_mul64To128M.c \
        ../softfloat-3e/source/softfloat_state.c

    compile_design spec
}

proc compile_impl {} {
    create_design -name impl -top fmp -clock clock

    vcs -sverilog -f ../rtl/files_fmp

    compile_design impl
}

proc ual {} {
    assume impl.ohe_selector_EX(1) == 1

    map_by_name -inputs -specphase 1 -implphase 2

    assume inp1 = impl.fmpA_in(1) == spec.multiplier(1)
    assume inp2 = impl.fmpB_in(1) == spec.multiplicand(1)

    assume spec.rounding_mode(1) == 0

    lemma check = spec.product(1) == impl.fmpC_out(2)
}

proc case_split_32 {} {
    caseSplitStrategy basic

    caseBegin dnorm_norm_32
    caseAssume (spec.multiplier(1)[30:23] == 8'h00)
    caseAssume (spec.multiplicand(1)[30:23] != 8'h00)
    caseAssume (spec.multiplicand(1)[30:23] != 8'hff)
#    caseEnumerate dnn -expr spec.multiplicand[22:0] -parent dnorm_norm_32 -type leading1
    caseEnumerate dnn1 -expr spec.multiplier[22:0] -parent dnorm_norm_32 -type leading1

    caseBegin norm_dnorm_32
    caseAssume (spec.multiplier(1)[30:23] != 8'h00)
    caseAssume (spec.multiplier(1)[30:23] != 8'hff)
    caseAssume (spec.multiplicand(1)[30:23] == 8'h00)
#    caseEnumerate ndn -expr spec.multiplier[22:0] -parent norm_dnorm_32 -type leading1
    caseEnumerate ndn1 -expr spec.multiplicand[22:0] -parent norm_dnorm_32 -type leading1

    caseBegin A_inf_NaN_32
    caseAssume (spec.multiplier(1)[30:23] == 8'hff)

    caseBegin B_inf_NaN_32
    caseAssume (spec.multiplicand(1)[30:23] == 8'hff)

    caseBegin dnorm_dnorm_32
    caseAssume (spec.multiplier(1)[30:23] == 8'h00)
    caseAssume (spec.multiplicand(1)[30:23] == 8'h00)

    caseBegin norm_norm_32
    caseAssume (spec.multiplier(1)[30:23] != 8'h00)
    caseAssume (spec.multiplier(1)[30:23] != 8'hff)
    caseAssume (spec.multiplicand(1)[30:23] != 8'h00)
    caseAssume (spec.multiplicand(1)[30:23] != 8'hff)
}

proc make {} {
    compile_spec
    compile_impl
    compose
}

proc run_main {} {
    set_user_assumes_lemmas_procedure "ual"
    set_hector_case_splitting_procedure "case_split_32"
    solveNB p
}

make
run_main