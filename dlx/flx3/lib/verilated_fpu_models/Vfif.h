// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vfif_H_
#define _Vfif_H_

#include "verilated_heavy.h"

class Vfif__Syms;

//----------

VL_MODULE(Vfif) {
  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    // Begin mtask footprint  all:
    VL_IN8(ohe_selector_EX,0,0);
    VL_IN(fifA_in,31,0);
    VL_OUT(fifC_out,31,0);

    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Begin mtask footprint  all:
    VL_SIG8(fif__DOT__dw_fif__DOT__status_reg,7,0);
    VL_SIG8(fif__DOT__dw_fif__DOT__STK,0,0);
    VL_SIG8(fif__DOT__dw_fif__DOT__rnd_val,3,0);
    VL_SIG16(fif__DOT__dw_fif__DOT__EXP,8,0);
    VL_SIG(fif__DOT__fifA,31,0);
    VL_SIG(fif__DOT__dw_fif__DOT__Ai,31,0);
    VL_SIG(fif__DOT__dw_fif__DOT__z_reg,23,0);
    VL_SIG(fif__DOT__dw_fif__DOT__LZ,31,0);
    VL_SIG(fif__DOT__dw_fif__DOT__Mf,18,0);

    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    // Begin mtask footprint  all:
    VL_SIG8(__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout,3,0);
    VL_SIG8(__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__rnd,2,0);
    VL_SIG8(__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Sign,0,0);
    VL_SIG8(__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__L,0,0);
    VL_SIG8(__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__R,0,0);
    VL_SIG8(__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__stk,0,0);

    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vfif__Syms* __VlSymsp;  // Symbol table

    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vfif);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vfif(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vfif();

    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();

    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vfif__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vfif__Syms* symsp, bool first);
  private:
    static QData _change_request(Vfif__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vfif__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    static void _eval(Vfif__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vfif__Syms* __restrict vlSymsp);
    static void _eval_settle(Vfif__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif // guard
