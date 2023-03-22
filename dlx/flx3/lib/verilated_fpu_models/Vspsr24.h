// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vspsr24_H_
#define _Vspsr24_H_

#include "verilated_heavy.h"

class Vspsr24__Syms;

//----------

VL_MODULE(Vspsr24) {
  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    // Begin mtask footprint  all:
    VL_IN(spsrAf_in,31,0);
    VL_OUT(spsrRf_out,31,0);

    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Begin mtask footprint  all:
    VL_SIG8(spsr24__DOT__U1__DOT__EA,7,0);
    VL_SIG8(spsr24__DOT__U1__DOT__MAX_EXP_A,0,0);
    VL_SIG8(spsr24__DOT__U1__DOT__InfSig_A,0,0);
    VL_SIG8(spsr24__DOT__U1__DOT__Zero_A,0,0);
    VL_SIG8(spsr24__DOT__U1__DOT__Denorm_A,0,0);
    VL_SIG8(spsr24__DOT__U1__DOT__status_reg,7,0);
    VL_SIG8(spsr24__DOT__U1__DOT__Sticky,0,0);
    VL_SIG8(spsr24__DOT__U1__DOT__Round_Bit,0,0);
    VL_SIG8(spsr24__DOT__U1__DOT__Guard_Bit,0,0);
    VL_SIG8(spsr24__DOT__U1__DOT__RND_val,3,0);
    VL_SIG8(spsr24__DOT__U1__DOT__Movf,0,0);
    VL_SIG8(spsr24__DOT__U1__DOT__NegInput,0,0);
    VL_SIG16(spsr24__DOT__U1__DOT__SIGA,14,0);
    VL_SIG16(spsr24__DOT__U1__DOT__MA,15,0);
    VL_SIG16(spsr24__DOT__U1__DOT__LZ_INA,9,0);
    VL_SIG16(spsr24__DOT__U1__DOT__EZ,10,0);
    VL_SIG16(spsr24__DOT__U1__DOT__EM,9,0);
    VL_SIG16(spsr24__DOT__U1__DOT__Mantissa,16,1);
    VL_SIG(spsr24__DOT__U1__DOT__NaN_Reg,23,0);
    VL_SIG(spsr24__DOT__U1__DOT__Inf_Reg,23,0);
    VL_SIG(spsr24__DOT__U1__DOT__MZ,16,0);
    VL_SIG(spsr24__DOT__U1__DOT__REMAINDER,17,0);
    VL_SIG(spsr24__DOT__U1__DOT__z_reg,23,0);
    VL_SIG(spsr24__DOT__U1__DOT__temp_mantissa,17,1);
    VL_SIG64(spsr24__DOT__U1__DOT__Sqrt_in,33,0);
    VL_SIG64(spsr24__DOT__U1__DOT__Square,33,0);

    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    // Begin mtask footprint  all:
    VL_SIG8(__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout,3,0);
    VL_SIG8(__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__rnd,2,0);
    VL_SIG8(__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Sign,0,0);
    VL_SIG8(__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__L,0,0);
    VL_SIG8(__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__R,0,0);
    VL_SIG8(__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__stk,0,0);
    VL_SIG(__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__Vfuncout,16,0);
    VL_SIG(__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v,16,0);
    VL_SIG64(__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A,33,0);

    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vspsr24__Syms* __VlSymsp;  // Symbol table

    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vspsr24);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vspsr24(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vspsr24();

    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();

    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vspsr24__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vspsr24__Syms* symsp, bool first);
  private:
    static QData _change_request(Vspsr24__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vspsr24__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    static void _eval(Vspsr24__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vspsr24__Syms* __restrict vlSymsp);
    static void _eval_settle(Vspsr24__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif // guard
