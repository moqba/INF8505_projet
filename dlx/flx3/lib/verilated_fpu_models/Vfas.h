// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vfas_H_
#define _Vfas_H_

#include "verilated_heavy.h"

class Vfas__Syms;

//----------

VL_MODULE(Vfas) {
  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    // Begin mtask footprint  all:
    VL_IN8(clock,0,0);
    VL_IN8(ohe_selector_EX,0,0);
    VL_IN8(fasM_in,0,0);
    VL_IN(fasA_in,31,0);
    VL_IN(fasB_in,31,0);
    VL_OUT(fasC_out,31,0);

    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Begin mtask footprint  all:
    VL_SIG8(fas__DOT__fasM,0,0);
    VL_SIG8(fas__DOT__dw_fas__DOT__status_int,7,0);
    VL_SIG8(fas__DOT__dw_fas__DOT__swap,0,0);
    VL_SIG8(fas__DOT__dw_fas__DOT__subtract,0,0);
    VL_SIG8(fas__DOT__dw_fas__DOT__STK,0,0);
    VL_SIG8(fas__DOT__dw_fas__DOT__E_Large,7,0);
    VL_SIG8(fas__DOT__dw_fas__DOT__E_Small,7,0);
    VL_SIG8(fas__DOT__dw_fas__DOT__E_Diff,7,0);
    VL_SIG8(fas__DOT__dw_fas__DOT__RND_val,3,0);
    VL_SIG8(fas__DOT__dw_fas__DOT__Denormal_Large,0,0);
    VL_SIG8(fas__DOT__dw_fas__DOT__Denormal_Small,0,0);
    VL_SIG16(fas__DOT__dw_fas__DOT__F_Large,14,0);
    VL_SIG16(fas__DOT__dw_fas__DOT__F_Small,14,0);
    VL_SIG16(fas__DOT__dw_fas__DOT__E_Comp,9,0);
    VL_SIG(fas__DOT__fasA,23,0);
    VL_SIG(fas__DOT__fasB,23,0);
    VL_SIG(fas__DOT__dw_fas__DOT__z_temp,23,0);
    VL_SIG(fas__DOT__dw_fas__DOT__Large,23,0);
    VL_SIG(fas__DOT__dw_fas__DOT__Small,23,0);
    VL_SIG(fas__DOT__dw_fas__DOT__M_Large,19,0);
    VL_SIG(fas__DOT__dw_fas__DOT__M_Small,19,0);
    VL_SIG(fas__DOT__dw_fas__DOT__M_Z,19,0);
    VL_SIG(fas__DOT__dw_fas__DOT__NaNFp,23,0);
    VL_SIG(fas__DOT__dw_fas__DOT__b_int,23,0);

    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    // Begin mtask footprint  all:
    VL_SIG8(__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout,3,0);
    VL_SIG8(__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__RND,2,0);
    VL_SIG8(__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Sign,0,0);
    VL_SIG8(__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__L,0,0);
    VL_SIG8(__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__R,0,0);
    VL_SIG8(__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__STK,0,0);

    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vfas__Syms* __VlSymsp;  // Symbol table

    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vfas);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vfas(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vfas();

    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();

    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vfas__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vfas__Syms* symsp, bool first);
  private:
    static QData _change_request(Vfas__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vfas__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    static void _eval(Vfas__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vfas__Syms* __restrict vlSymsp);
    static void _eval_settle(Vfas__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif // guard
