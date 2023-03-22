set _hector_comp_use_new_flow true
set _hector_softfloat_version custom

proc compile_spec {} {
    create_design -name spec -top hector_wrapper
    cppan -I../softfloat-3e/source/include \
        -I../softfloat-3e/source/flx \
        -I../softfloat-3e/build/HECTOR \
        ../c/i2f.cc \
        ../softfloat-3e/source/i32_to_f32.c \
        ../softfloat-3e/source/s_addMagsF32.c \
        ../softfloat-3e/source/s_subMagsF32.c \
        ../softfloat-3e/source/s_normRoundPackToF32.c \
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
        ../softfloat-3e/source/softfloat_state.c

    compile_design spec
}

proc compile_impl {} {
    create_design -name impl -top fif

    vcs -sverilog -f ../rtl/files_fif

    compile_design impl
}

proc ual {} {
    assume impl.ohe_selector_EX(1) == 1

    map_by_name -inputs -specphase 1 -implphase 1

    assume inp1 = impl.fifA_in(1) == spec.in_a(1)

    assume spec.rounding_mode(1) == 0

    lemma check = spec.result(1) == impl.fifC_out(1)
}

proc make {} {
    compile_spec
    compile_impl
    compose
}

proc run_main {} {
    solveNB p -ual "ual"
}

make
run_main