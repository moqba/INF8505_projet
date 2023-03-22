// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vfmp_H_
#define _Vfmp_H_

#include "verilated_heavy.h"

class Vfmp__Syms;

//----------

VL_MODULE(Vfmp) {
  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    // Begin mtask footprint  all:
    VL_IN8(clock,0,0);
    VL_IN8(ohe_selector_EX,0,0);
    VL_IN(fmpA_in,31,0);
    VL_IN(fmpB_in,31,0);
    VL_OUT(fmpC_out,31,0);

    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Begin mtask footprint  all:
    VL_SIG8(fmp__DOT__dw_spmp__DOT__EA,7,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__EB,7,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__STK,0,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__SIGN,0,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__RND_val,3,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__status_reg,7,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__MaxEXP_A,0,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__MaxEXP_B,0,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__InfSIG_A,0,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__InfSIG_B,0,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__Zero_A,0,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__Zero_B,0,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__Denorm_A,0,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__Denorm_B,0,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__MZ_Movf1,0,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__STK_CHECK,0,0);
    VL_SIG8(fmp__DOT__dw_spmp__DOT__minnorm_case,0,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__EZ,9,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__Range_Check,9,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__EZ_Shift,9,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__MA,15,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__MB,15,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__TMP_MA,15,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__TMP_MB,15,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__LZ_INA,9,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__LZ_INB,9,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__LZ_IN,9,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__SIGA,14,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__SIGB,14,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__STK_EXT,15,0);
    VL_SIG16(fmp__DOT__dw_spmp__DOT__Inf_Sig,14,0);
    VL_SIG(fmp__DOT__fmpA,23,0);
    VL_SIG(fmp__DOT__fmpB,23,0);
    VL_SIG(fmp__DOT__dw_spmp__DOT__z_reg,23,0);
    VL_SIG(fmp__DOT__dw_spmp__DOT__NaN_Reg,23,0);
    VL_SIG(fmp__DOT__dw_spmp__DOT__Inf_Reg,23,0);
    VL_SIG(fmp__DOT__dw_spmp__DOT__i,31,0);
    VL_SIG64(fmp__DOT__dw_spmp__DOT__MZ,32,0);

    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    // Begin mtask footprint  all:
    VL_SIG8(fmp__DOT__dw_spmp__DOT____Vconcswap2,0,0);
    VL_SIG8(__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout,3,0);
    VL_SIG8(__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__rnd,2,0);
    VL_SIG8(__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Sign,0,0);
    VL_SIG8(__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__L,0,0);
    VL_SIG8(__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__R,0,0);
    VL_SIG8(__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__stk,0,0);
    VL_SIG8(__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout,3,0);
    VL_SIG8(__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__rnd,2,0);
    VL_SIG8(__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Sign,0,0);
    VL_SIG8(__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__L,0,0);
    VL_SIG8(__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__R,0,0);
    VL_SIG8(__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__stk,0,0);
    VL_SIG64(fmp__DOT__dw_spmp__DOT____Vconcswap1,32,0);

    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vfmp__Syms* __VlSymsp;  // Symbol table

    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vfmp);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vfmp(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vfmp();

    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();

    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vfmp__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vfmp__Syms* symsp, bool first);
  private:
    static QData _change_request(Vfmp__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vfmp__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    static void _eval(Vfmp__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vfmp__Syms* __restrict vlSymsp);
    static void _eval_settle(Vfmp__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif // guard
