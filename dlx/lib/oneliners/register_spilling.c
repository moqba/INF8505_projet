
// File generated by noodle version Q-2020.03#7e5ed72dc8#200717, Wed Mar 22 14:16:27 2023
// Copyright 2014-2020 Synopsys, Inc. All rights reserved.
// noodle -Pc -Iisg +wisg -Iruntime/include -DCHESS_CXX_ATTRIBUTES -D__tct_patch__=300 +NOrlt -D__chess__ -D__programmers_view__ dlx

// File: register_spilling.c
// Test spilling of registers to stack
// (Each function is required to save and restore one specific register(file) around the call of `foo'.
//  Note that the connection may be direct or indirect, atomic or complex.
//  If a value is moved through some other register, that need not be spilled itself, as it may be clobbered.)

//! Connection analysis may reveal that certain registers are not spillable, and those tests are skipped.

// (It is possible that certain component-registers are not (individually) spillable, yet that the structure is.
//  These are then not a problem for, e.g., a full context switch.)

extern "C" {

void foo() property(loop_free);


void spill_R() clobbers_not(R) { foo(); }


} //extern "C"  (1 functions)
