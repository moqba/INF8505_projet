// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vfcp_H_
#define _Vfcp_H_

#include "verilated_heavy.h"

class Vfcp__Syms;

//----------

VL_MODULE(Vfcp) {
  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    // Begin mtask footprint  all:
    VL_IN8(bin_selector_EX,1,0);
    VL_IN(fcpA_in,31,0);
    VL_IN(fcpB_in,31,0);
    VL_OUT(fcpC_out,31,0);

    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Begin mtask footprint  all:
    VL_SIG8(fcp__DOT__dw_fcp__DOT__sign,0,0);
    VL_SIG8(fcp__DOT__dw_fcp__DOT__Ea,7,0);
    VL_SIG8(fcp__DOT__dw_fcp__DOT__Eb,7,0);
    VL_SIG8(fcp__DOT__dw_fcp__DOT__status0_int,7,0);
    VL_SIG8(fcp__DOT__dw_fcp__DOT__status1_int,7,0);
    VL_SIG8(fcp__DOT__dw_fcp__DOT__agtb_int,0,0);
    VL_SIG8(fcp__DOT__dw_fcp__DOT__aeqb_int,0,0);
    VL_SIG8(fcp__DOT__dw_fcp__DOT__altb_int,0,0);
    VL_SIG8(fcp__DOT__dw_fcp__DOT__unordered_int,0,0);
    VL_SIG8(fcp__DOT__dw_fcp__DOT__chk,1,0);
    VL_SIG8(fcp__DOT__dw_fcp__DOT__zer_a,0,0);
    VL_SIG8(fcp__DOT__dw_fcp__DOT__zer_b,0,0);
    VL_SIG16(fcp__DOT__dw_fcp__DOT__Fa,14,0);
    VL_SIG16(fcp__DOT__dw_fcp__DOT__Fb,14,0);
    VL_SIG(fcp__DOT__fcpA,23,0);
    VL_SIG(fcp__DOT__fcpB,23,0);
    VL_SIG(fcp__DOT__fcpC,23,0);

    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    // Begin mtask footprint  all:
    VL_SIG8(__Vtableidx1,3,0);
    static VL_ST_SIG(__Vtable1_fcp__DOT__fcpC[16],23,0);

    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vfcp__Syms* __VlSymsp;  // Symbol table

    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vfcp);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vfcp(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vfcp();

    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();

    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vfcp__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vfcp__Syms* symsp, bool first);
  private:
    static QData _change_request(Vfcp__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vfcp__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    static void _eval(Vfcp__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vfcp__Syms* __restrict vlSymsp);
    static void _eval_settle(Vfcp__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif // guard
