// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfif.h for the primary calling header

#include "Vfif.h"
#include "Vfif__Syms.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(Vfif) {
    Vfif__Syms* __restrict vlSymsp = __VlSymsp = new Vfif__Syms(this, name());
    Vfif* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values

    // Reset structure values
    _ctor_var_reset();
}

void Vfif::__Vconfigure(Vfif__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vfif::~Vfif() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vfif::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vfif::eval\n"); );
    Vfif__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vfif* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT(__FILE__,__LINE__,__FILE__,"Verilated model didn't converge");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vfif::_eval_initial_loop(Vfif__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT(__FILE__,__LINE__,__FILE__,"Verilated model didn't DC converge");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

//--------------------
// Internal Methods

VL_INLINE_OPT void Vfif::_combo__TOP__1(Vfif__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfif::_combo__TOP__1\n"); );
    Vfif* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at ../hdl/designware_vlog/fif.v:35
    vlTOPp->fif__DOT__fifA = ((IData)(vlTOPp->ohe_selector_EX)
                               ? vlTOPp->fifA_in : 0U);
    // ALWAYS at /global/apps/syn_2019.03-SP2/dw/sim_ver/DW_fp_i2flt.v:219
    vlTOPp->fif__DOT__dw_fif__DOT__Ai = vlTOPp->fif__DOT__fifA;
    vlTOPp->fif__DOT__dw_fif__DOT__status_reg = 0U;
    vlTOPp->fif__DOT__dw_fif__DOT__LZ = 0U;
    vlTOPp->fif__DOT__dw_fif__DOT__Mf = 0U;
    vlTOPp->fif__DOT__dw_fif__DOT__EXP = 0U;
    vlTOPp->fif__DOT__dw_fif__DOT__STK = 0U;
    if ((0U == vlTOPp->fif__DOT__dw_fif__DOT__Ai)) {
        vlTOPp->fif__DOT__dw_fif__DOT__status_reg =
            (1U | (IData)(vlTOPp->fif__DOT__dw_fif__DOT__status_reg));
        vlTOPp->fif__DOT__dw_fif__DOT__z_reg = 0U;
    } else {
        if ((0x80000000U & vlTOPp->fif__DOT__dw_fif__DOT__Ai)) {
            vlTOPp->fif__DOT__dw_fif__DOT__Ai = ((IData)(1U)
                                                 +
                                                 (~ vlTOPp->fif__DOT__dw_fif__DOT__Ai));
            vlTOPp->fif__DOT__dw_fif__DOT__z_reg =
                (0x800000U | vlTOPp->fif__DOT__dw_fif__DOT__z_reg);
        } else {
            vlTOPp->fif__DOT__dw_fif__DOT__z_reg =
                (0x7fffffU & vlTOPp->fif__DOT__dw_fif__DOT__z_reg);
        }
        while ((1U & (~ (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                         >> 0x1fU)))) {
            vlTOPp->fif__DOT__dw_fif__DOT__Ai = (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                 << 1U);
            vlTOPp->fif__DOT__dw_fif__DOT__LZ = ((IData)(1U)
                                                 + vlTOPp->fif__DOT__dw_fif__DOT__LZ);
        }
        vlTOPp->fif__DOT__dw_fif__DOT__EXP = (0x1ffU
                                              & ((0xffU
                                                  <=
                                                  ((IData)(0x7fU)
                                                   +
                                                   ((IData)(0x1fU)
                                                    - vlTOPp->fif__DOT__dw_fif__DOT__LZ)))
                                                  ? 0xffU
                                                  :
                                                 ((IData)(0x7fU)
                                                  +
                                                  ((IData)(0x1fU)
                                                   - vlTOPp->fif__DOT__dw_fif__DOT__LZ))));
        vlTOPp->fif__DOT__dw_fif__DOT__Mf = ((0x40001U
                                              & vlTOPp->fif__DOT__dw_fif__DOT__Mf)
                                             | (0x3fffeU
                                                & (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                   >> 0xeU)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                               >> 0xeU));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                  >> 0xdU)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                  >> 0xcU)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                  >> 0xbU)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                  >> 0xaU)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                  >> 9U)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                  >> 8U)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                  >> 7U)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                  >> 6U)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                  >> 5U)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                  >> 4U)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                  >> 3U)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                  >> 2U)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | (vlTOPp->fif__DOT__dw_fif__DOT__Ai
                                                  >> 1U)));
        vlTOPp->fif__DOT__dw_fif__DOT__STK = (1U &
                                              ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK)
                                               | vlTOPp->fif__DOT__dw_fif__DOT__Ai));
        vlTOPp->fif__DOT__dw_fif__DOT__Mf = ((0x7fffeU
                                              & vlTOPp->fif__DOT__dw_fif__DOT__Mf)
                                             | (IData)(vlTOPp->fif__DOT__dw_fif__DOT__STK));
        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__stk
            = (1U & vlTOPp->fif__DOT__dw_fif__DOT__Mf);
        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__R
            = (1U & (vlTOPp->fif__DOT__dw_fif__DOT__Mf
                     >> 1U));
        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__L
            = (1U & (vlTOPp->fif__DOT__dw_fif__DOT__Mf
                     >> 2U));
        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Sign
            = (1U & (vlTOPp->fif__DOT__dw_fif__DOT__z_reg
                     >> 0x17U));
        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__rnd = 0U;
        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
            = (0xeU & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout));
        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
            = ((0xdU & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout))
               | (((IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__R)
                   | (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__stk))
                  << 1U));
        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
            = (0xbU & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout));
        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
            = (7U & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout));
        if ((VL_ULL(0) < VL_TIME_Q())) {
            if ((4U & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__rnd))) {
                if (VL_UNLIKELY((2U & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__rnd)))) {
                    VL_WRITEF("Error! illegal rounding mode.\n\n");
                    VL_WRITEF("a : %b\n",32,vlTOPp->fif__DOT__fifA);
                    VL_WRITEF("rnd : %b\n",3,vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__rnd);
                } else {
                    if ((1U & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__rnd))) {
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = ((0xeU & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout))
                               | ((IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__R)
                                  | (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__stk)));
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = (4U | (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout));
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = (8U | (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout));
                    } else {
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = ((0xeU & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout))
                               | (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__R));
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = (4U | (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout));
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = (7U & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout));
                    }
                }
            } else {
                if ((2U & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__rnd))) {
                    if ((1U & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__rnd))) {
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = ((0xeU & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout))
                               | ((IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Sign)
                                  & ((IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__R)
                                     | (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__stk))));
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = ((0xbU & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout))
                               | ((IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Sign)
                                  << 2U));
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = ((7U & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout))
                               | ((IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Sign)
                                  << 3U));
                    } else {
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = ((0xeU & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout))
                               | ((~ (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Sign))
                                  & ((IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__R)
                                     | (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__stk))));
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = ((0xbU & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout))
                               | (4U & ((~ (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Sign))
                                        << 2U)));
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = ((7U & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout))
                               | (8U & ((~ (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Sign))
                                        << 3U)));
                    }
                } else {
                    if ((1U & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__rnd))) {
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = (0xeU & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout));
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = (0xbU & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout));
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = (7U & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout));
                    } else {
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = ((0xeU & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout))
                               | ((IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__R)
                                  & ((IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__L)
                                     | (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__stk))));
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = (4U | (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout));
                        vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout
                            = (7U & (IData)(vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout));
                    }
                }
            }
        }
        vlTOPp->fif__DOT__dw_fif__DOT__rnd_val = vlTOPp->__Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout;
        if ((1U & (IData)(vlTOPp->fif__DOT__dw_fif__DOT__rnd_val))) {
            vlTOPp->fif__DOT__dw_fif__DOT__Mf = (0x7ffffU
                                                 & ((IData)(4U)
                                                    + vlTOPp->fif__DOT__dw_fif__DOT__Mf));
        }
        vlTOPp->fif__DOT__dw_fif__DOT__status_reg =
            ((0xdfU & (IData)(vlTOPp->fif__DOT__dw_fif__DOT__status_reg))
             | (0x20U & ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__rnd_val)
                         << 4U)));
        if ((0x40000U & vlTOPp->fif__DOT__dw_fif__DOT__Mf)) {
            vlTOPp->fif__DOT__dw_fif__DOT__EXP = (0x1ffU
                                                  & ((IData)(1U)
                                                     + (IData)(vlTOPp->fif__DOT__dw_fif__DOT__EXP)));
            vlTOPp->fif__DOT__dw_fif__DOT__Mf = (0x7ffffU
                                                 & (vlTOPp->fif__DOT__dw_fif__DOT__Mf
                                                    >> 1U));
        }
        if ((0xffU <= (IData)(vlTOPp->fif__DOT__dw_fif__DOT__EXP))) {
            vlTOPp->fif__DOT__dw_fif__DOT__status_reg
                = (0x10U | (IData)(vlTOPp->fif__DOT__dw_fif__DOT__status_reg));
            vlTOPp->fif__DOT__dw_fif__DOT__status_reg
                = (0x20U | (IData)(vlTOPp->fif__DOT__dw_fif__DOT__status_reg));
            if ((4U & (IData)(vlTOPp->fif__DOT__dw_fif__DOT__rnd_val))) {
                vlTOPp->fif__DOT__dw_fif__DOT__EXP = 0xffU;
                vlTOPp->fif__DOT__dw_fif__DOT__Mf =
                    (0x60003U & vlTOPp->fif__DOT__dw_fif__DOT__Mf);
                vlTOPp->fif__DOT__dw_fif__DOT__status_reg
                    = (2U | (IData)(vlTOPp->fif__DOT__dw_fif__DOT__status_reg));
            } else {
                vlTOPp->fif__DOT__dw_fif__DOT__EXP = 0xfeU;
                vlTOPp->fif__DOT__dw_fif__DOT__Mf =
                    (0x1fffcU | vlTOPp->fif__DOT__dw_fif__DOT__Mf);
            }
        }
        vlTOPp->fif__DOT__dw_fif__DOT__z_reg = ((0x800000U
                                                 & vlTOPp->fif__DOT__dw_fif__DOT__z_reg)
                                                | ((0x7f8000U
                                                    & ((IData)(vlTOPp->fif__DOT__dw_fif__DOT__EXP)
                                                       << 0xfU))
                                                   | (0x7fffU
                                                      & (vlTOPp->fif__DOT__dw_fif__DOT__Mf
                                                         >> 2U))));
    }
    vlTOPp->fifC_out = vlTOPp->fif__DOT__dw_fif__DOT__z_reg;
}

void Vfif::_eval(Vfif__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfif::_eval\n"); );
    Vfif* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vfif::_eval_initial(Vfif__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfif::_eval_initial\n"); );
    Vfif* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vfif::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfif::final\n"); );
    // Variables
    Vfif__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vfif* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vfif::_eval_settle(Vfif__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfif::_eval_settle\n"); );
    Vfif* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vfif::_change_request(Vfif__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfif::_change_request\n"); );
    Vfif* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vfif::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfif::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((ohe_selector_EX & 0xfeU))) {
        Verilated::overWidthError("ohe_selector_EX");}
}
#endif // VL_DEBUG

void Vfif::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfif::_ctor_var_reset\n"); );
    // Body
    ohe_selector_EX = VL_RAND_RESET_I(1);
    fifA_in = VL_RAND_RESET_I(32);
    fifC_out = VL_RAND_RESET_I(32);
    fif__DOT__fifA = VL_RAND_RESET_I(32);
    fif__DOT__dw_fif__DOT__Ai = VL_RAND_RESET_I(32);
    fif__DOT__dw_fif__DOT__status_reg = VL_RAND_RESET_I(8);
    fif__DOT__dw_fif__DOT__z_reg = VL_RAND_RESET_I(24);
    fif__DOT__dw_fif__DOT__LZ = VL_RAND_RESET_I(32);
    fif__DOT__dw_fif__DOT__Mf = VL_RAND_RESET_I(19);
    fif__DOT__dw_fif__DOT__EXP = VL_RAND_RESET_I(9);
    fif__DOT__dw_fif__DOT__STK = VL_RAND_RESET_I(1);
    fif__DOT__dw_fif__DOT__rnd_val = VL_RAND_RESET_I(4);
    __Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Vfuncout = VL_RAND_RESET_I(4);
    __Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__rnd = VL_RAND_RESET_I(3);
    __Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__Sign = VL_RAND_RESET_I(1);
    __Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__L = VL_RAND_RESET_I(1);
    __Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__R = VL_RAND_RESET_I(1);
    __Vfunc_fif__DOT__dw_fif__DOT__rnd_eval__0__stk = VL_RAND_RESET_I(1);
}
