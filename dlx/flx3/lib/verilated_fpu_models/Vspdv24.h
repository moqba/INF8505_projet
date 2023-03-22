// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vspdv24_H_
#define _Vspdv24_H_

#include "verilated_heavy.h"

class Vspdv24__Syms;

//----------

VL_MODULE(Vspdv24) {
  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    // Begin mtask footprint  all:
    VL_IN(spdvAf_in,24,0);
    VL_IN(spdvBf_in,24,0);
    VL_OUT(spdvRf_out,24,0);

    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        // Begin mtask footprint  all:
        VL_SIG8(spdv24__DOT__U1__DOT__lO101111,7,0);
        VL_SIG8(spdv24__DOT__U1__DOT__lI00O00I,7,0);
        VL_SIG8(spdv24__DOT__U1__DOT__I101O11O,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__lO011100,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__I11IO1I1,1,0);
        VL_SIG8(spdv24__DOT__U1__DOT__OO000O0O,3,0);
        VL_SIG8(spdv24__DOT__U1__DOT__O00OO1I0,7,0);
        VL_SIG8(spdv24__DOT__U1__DOT__lOI111I1,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__O100O11l,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__l10OO1I0,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__l1O1Ol0O,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__I000lO00,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__l1OllI0I,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__lO00I10I,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__IIIl11O1,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__OIIO0OOl,7,0);
        VL_SIG8(spdv24__DOT__U1__DOT__l0III011,7,0);
        VL_SIG8(spdv24__DOT__U1__DOT__l0IO1lOO,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__Il101Il1,4,0);
        VL_SIG8(spdv24__DOT__U1__DOT__OOO01OO1,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__I10l01Il,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__Ol01O010,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__I110OIOO,0,-1);
        VL_SIG8(spdv24__DOT__U1__DOT__O0OOIl0l,0,-1);
        VL_SIG8(spdv24__DOT__U1__DOT__lI0I111I,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__O10I0O00,0,0);
        VL_SIG8(spdv24__DOT__U1__DOT__l0OOOIll,4,0);
        VL_SIG16(spdv24__DOT__U1__DOT__IOO1O01O,9,0);
        VL_SIG16(spdv24__DOT__U1__DOT__O10101O1,9,0);
        VL_SIG16(spdv24__DOT__U1__DOT__IO10IOO1,9,0);
        VL_SIG16(spdv24__DOT__U1__DOT__l10OO10O,9,0);
        VL_SIG16(spdv24__DOT__U1__DOT__OOIl0010,15,0);
        VL_SIG16(spdv24__DOT__U1__DOT__IOOl0lII,15,0);
        VL_SIG16(spdv24__DOT__U1__DOT__l11Illl0,15,0);
        VL_SIG16(spdv24__DOT__U1__DOT__lO001Ol0,15,0);
        VL_SIG16(spdv24__DOT__U1__DOT__I0OI1lO0,15,0);
        VL_SIG16(spdv24__DOT__U1__DOT__IOIlII10,15,0);
        VL_SIG16(spdv24__DOT__U1__DOT__O011IOO0,15,0);
        VL_SIG16(spdv24__DOT__U1__DOT__O00O1Ol1,14,0);
        VL_SIG16(spdv24__DOT__U1__DOT__II01O1O0,14,0);
        VL_SIG16(spdv24__DOT__U1__DOT__OO0lIO1O,9,0);
        VL_SIG16(spdv24__DOT__U1__DOT__II0IIO1O,15,0);
        VL_SIG16(spdv24__DOT__U1__DOT__O1lO00O0,15,0);
        VL_SIG16(spdv24__DOT__U1__DOT__I0I0Il0O,15,0);
        VL_SIG16(spdv24__DOT__U1__DOT__l110l11I,8,0);
        VL_SIG16(spdv24__DOT__U1__DOT__IO00O1O1,8,0);
        VL_SIG16(spdv24__DOT__U1__DOT__IOOlIOOO,9,0);
        VL_SIG16(spdv24__DOT__U1__DOT__O1l11OIO,9,0);
        VL_SIG16(spdv24__DOT__U1__DOT__IOll10OO,9,0);
        VL_SIG(spdv24__DOT__U1__DOT__l1l1O100,23,0);
        VL_SIG(spdv24__DOT__U1__DOT__IIl1O10O,23,0);
        VL_SIG(spdv24__DOT__U1__DOT__I00lIO1l,23,0);
        VL_SIG(spdv24__DOT__U1__DOT__OOI10OIO,24,0);
        VL_SIG(spdv24__DOT__U1__DOT__O00OI010,24,0);
        VL_SIG(spdv24__DOT__U1__DOT__IOIlOO00,16,0);
        VL_SIG(spdv24__DOT__U1__DOT__O0O0IIII,23,0);
        VL_SIG(spdv24__DOT__U1__DOT__II11llO0,18,0);
        VL_SIG(spdv24__DOT__U1__DOT__l0101100,18,0);
        VL_SIG(spdv24__DOT__U1__DOT__Ol1O10O0,18,0);
        VL_SIG(spdv24__DOT__U1__DOT__O0l0O011,18,0);
        VL_SIG(spdv24__DOT__U1__DOT__O0O1011O,18,0);
        VL_SIG(spdv24__DOT__U1__DOT__lI100I0I,18,0);
        VL_SIG(spdv24__DOT__U1__DOT__O1O0011O,18,0);
        VL_SIG(spdv24__DOT__U1__DOT__IIOI0lOO,18,0);
    };
    struct {
        VL_SIG(spdv24__DOT__U1__DOT__O101OOOO,27,0);
        VL_SIG(spdv24__DOT__U1__DOT__O010OOO1,20,0);
        VL_SIG(spdv24__DOT__U1__DOT__O1I10I10,20,0);
        VL_SIG(spdv24__DOT__U1__DOT__l101O0Ol,20,0);
        VL_SIG64(spdv24__DOT__U1__DOT__O10110O1,32,0);
    };

    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    // Begin mtask footprint  all:
    VL_SIG8(__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout,3,0);
    VL_SIG8(__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__rnd,2,0);
    VL_SIG8(__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__lO011100,0,0);
    VL_SIG8(__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__I0O0O0OO,0,0);
    VL_SIG8(__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__O011IOO0,0,0);
    VL_SIG8(__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__I101O11O,0,0);
    VL_SIG16(spdv24__DOT__U1__DOT____Vconcswap1,15,0);
    VL_SIG16(spdv24__DOT__U1__DOT____Vconcswap2,15,0);

    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vspdv24__Syms* __VlSymsp;  // Symbol table

    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vspdv24);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vspdv24(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vspdv24();

    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();

    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vspdv24__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vspdv24__Syms* symsp, bool first);
  private:
    static QData _change_request(Vspdv24__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vspdv24__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    static void _eval(Vspdv24__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vspdv24__Syms* __restrict vlSymsp);
    static void _eval_settle(Vspdv24__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif // guard
