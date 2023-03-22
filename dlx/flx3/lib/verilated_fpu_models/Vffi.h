// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vffi_H_
#define _Vffi_H_

#include "verilated_heavy.h"

class Vffi__Syms;

//----------

VL_MODULE(Vffi) {
  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    // Begin mtask footprint  all:
    VL_IN8(ohe_selector_EX,0,0);
    VL_IN(ffiA_in,31,0);
    VL_OUT(ffiC_out,31,0);

    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Begin mtask footprint  all:
    VL_SIG8(ffi__DOT__dw_ffi__DOT__status_reg,7,0);
    VL_SIG8(ffi__DOT__dw_ffi__DOT__eaf,7,0);
    VL_SIG8(ffi__DOT__dw_ffi__DOT__exp,7,0);
    VL_SIG8(ffi__DOT__dw_ffi__DOT__stk,0,0);
    VL_SIG8(ffi__DOT__dw_ffi__DOT__rnd_val,3,0);
    VL_SIG8(ffi__DOT__dw_ffi__DOT__inf_input,0,0);
    VL_SIG8(ffi__DOT__dw_ffi__DOT__denorm_input,0,0);
    VL_SIG8(ffi__DOT__dw_ffi__DOT__nan_input,0,0);
    VL_SIG8(ffi__DOT__dw_ffi__DOT__zero_input,0,0);
    VL_SIG16(ffi__DOT__dw_ffi__DOT__sig,14,0);
    VL_SIG(ffi__DOT__ffiA,23,0);
    VL_SIG(ffi__DOT__dw_ffi__DOT__af,23,0);
    VL_SIG(ffi__DOT__dw_ffi__DOT__z_reg,31,0);
    VL_SIGW(ffi__DOT__dw_ffi__DOT__mi,65,0,3);
    VL_SIG(ffi__DOT__dw_ffi__DOT__maxneg,31,0);
    VL_SIG(ffi__DOT__dw_ffi__DOT__maxpos,31,0);

    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    // Begin mtask footprint  all:
    VL_SIG8(__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout,3,0);
    VL_SIG8(__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__rnd,2,0);
    VL_SIG8(__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Sign,0,0);
    VL_SIG8(__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__L,0,0);
    VL_SIG8(__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__R,0,0);
    VL_SIG8(__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__stk,0,0);

    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vffi__Syms* __VlSymsp;  // Symbol table

    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vffi);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vffi(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vffi();

    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();

    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vffi__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vffi__Syms* symsp, bool first);
  private:
    static QData _change_request(Vffi__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vffi__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    static void _eval(Vffi__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vffi__Syms* __restrict vlSymsp);
    static void _eval_settle(Vffi__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif // guard
