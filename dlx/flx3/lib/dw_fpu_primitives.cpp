/*
-- File : dw_fpu_primitives.cpp
--
-- Contents : C++ implementation of float primitives 
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- stricfly prohibited. 
*/

#ifndef _dw_fpu_primitives_h
#define _dw_fpu_primitives_h
#include <math.h>
#include <iostream>

#include "flx_define.h"

#include "isg/flx_iss_types.h"
#include <verilated.h>
#include "verilated_fpu_models/Vfas.h"
#include "verilated_fpu_models/Vfcp.h"
#include "verilated_fpu_models/Vffi.h"
#include "verilated_fpu_models/Vfif.h"
#include "verilated_fpu_models/Vfmp.h"

// In DW simulation model, it require the return value of $time() is larger than zero
// Verilator will convert the $time() partly by sc_time_stamp(), here modify the return value from 0 to 1
// For example, in DW_fp_mult.v, function rnd_val requires that $time is larger than zero.

vluint64_t main_time = 1;       // Current simulation time
double sc_time_stamp () {       // Called by $time in Verilog
    return main_time;           // converts to double, to match
                                // what SystemC does
}

namespace flx_primitive {

w32 faddsub(uint1 op, w32 a, w32 b)
{
    Vfas fas_model;
    fas_model.ohe_selector_EX = 1;
    fas_model.fasM_in = op.value();
    fas_model.fasA_in = a.value();
    fas_model.fasB_in = b.value();
    fas_model.eval();
    return fas_model.fasC_out;
}

w32 fadd(w32 a, w32 b) { return faddsub(0,a,b); }
w32 fsub(w32 a, w32 b) { return faddsub(1,a,b); }

w32 fmul(w32 a, w32 b)
{
    Vfmp fmp_model;
    fmp_model.ohe_selector_EX = 1;
    fmp_model.fmpA_in = a.value();
    fmp_model.fmpB_in = b.value();
    fmp_model.eval();
    return fmp_model.fmpC_out;
}

w32 sfle(w32 a, w32 b)
{
    Vfcp fcp_model;
    fcp_model.bin_selector_EX = 2;
    fcp_model.fcpA_in = a.value();
    fcp_model.fcpB_in = b.value();
    fcp_model.eval();
    return fcp_model.fcpC_out;
}

w32 sflt(w32 a, w32 b)
{
    Vfcp fcp_model;
    fcp_model.bin_selector_EX = 3;
    fcp_model.fcpA_in = a.value();
    fcp_model.fcpB_in = b.value();
    fcp_model.eval();
    return fcp_model.fcpC_out;

}

w32 sfeq(w32 a, w32 b)
{
    Vfcp fcp_model;
    fcp_model.bin_selector_EX = 1;
    fcp_model.fcpA_in = a.value();
    fcp_model.fcpB_in = b.value();
    fcp_model.eval();
    return fcp_model.fcpC_out;
}

w32 i2f(w32 a)
{
    Vfif fif_model;
    fif_model.ohe_selector_EX = 1;
    fif_model.fifA_in = a.value();
    fif_model.eval();
    return fif_model.fifC_out;
}

w32 f2i(w32 a)
{
    Vffi ffi_model;
    ffi_model.ohe_selector_EX = 1;
    ffi_model.ffiA_in = a.value();
    ffi_model.eval();
    return ffi_model.ffiC_out;
}

} // end namespace  flx_primitive

#endif  // _dw_fpu_primitives_h


