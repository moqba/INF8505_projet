// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfmp.h for the primary calling header

#include "Vfmp.h"
#include "Vfmp__Syms.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(Vfmp) {
    Vfmp__Syms* __restrict vlSymsp = __VlSymsp = new Vfmp__Syms(this, name());
    Vfmp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values

    // Reset structure values
    _ctor_var_reset();
}

void Vfmp::__Vconfigure(Vfmp__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vfmp::~Vfmp() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vfmp::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vfmp::eval\n"); );
    Vfmp__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vfmp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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

void Vfmp::_eval_initial_loop(Vfmp__Syms* __restrict vlSymsp) {
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

VL_INLINE_OPT void Vfmp::_combo__TOP__1(Vfmp__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfmp::_combo__TOP__1\n"); );
    Vfmp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at ../hdl/designware_vlog/fmp.v:44
    vlTOPp->fmp__DOT__fmpA = (0xffffffU & ((IData)(vlTOPp->ohe_selector_EX)
                                            ? vlTOPp->fmpA_in
                                            : 0U));
    // ALWAYS at ../hdl/designware_vlog/fmp.v:44
    vlTOPp->fmp__DOT__fmpB = (0xffffffU & ((IData)(vlTOPp->ohe_selector_EX)
                                            ? vlTOPp->fmpB_in
                                            : 0U));
    // ALWAYS at /global/apps/syn_2019.03-SP2/dw/sim_ver/DW_fp_mult.v:264
    vlTOPp->fmp__DOT__dw_spmp__DOT__SIGN = (1U & ((vlTOPp->fmp__DOT__fmpA
                                                   ^ vlTOPp->fmp__DOT__fmpB)
                                                  >> 0x17U));
    vlTOPp->fmp__DOT__dw_spmp__DOT__EA = (0xffU & (vlTOPp->fmp__DOT__fmpA
                                                   >> 0xfU));
    vlTOPp->fmp__DOT__dw_spmp__DOT__EB = (0xffU & (vlTOPp->fmp__DOT__fmpB
                                                   >> 0xfU));
    vlTOPp->fmp__DOT__dw_spmp__DOT__SIGA = (0x7fffU
                                            & vlTOPp->fmp__DOT__fmpA);
    vlTOPp->fmp__DOT__dw_spmp__DOT__SIGB = (0x7fffU
                                            & vlTOPp->fmp__DOT__fmpB);
    vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg = 0U;
    vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_INA = 0U;
    vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_INB = 0U;
    vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_IN = 0U;
    vlTOPp->fmp__DOT__dw_spmp__DOT__STK_EXT = 0U;
    vlTOPp->fmp__DOT__dw_spmp__DOT__MaxEXP_A = (0xffU
                                                == (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EA));
    vlTOPp->fmp__DOT__dw_spmp__DOT__MaxEXP_B = (0xffU
                                                == (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EB));
    vlTOPp->fmp__DOT__dw_spmp__DOT__InfSIG_A = (0U
                                                == (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__SIGA));
    vlTOPp->fmp__DOT__dw_spmp__DOT__InfSIG_B = (0U
                                                == (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__SIGB));
    vlTOPp->fmp__DOT__dw_spmp__DOT__Zero_A = ((0U == (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EA))
                                              & (0U
                                                 == (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__SIGA)));
    vlTOPp->fmp__DOT__dw_spmp__DOT__Zero_B = ((0U == (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EB))
                                              & (0U
                                                 == (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__SIGB)));
    vlTOPp->fmp__DOT__dw_spmp__DOT__Denorm_A = ((0U
                                                 == (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EA))
                                                & (0U
                                                   != (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__SIGA)));
    vlTOPp->fmp__DOT__dw_spmp__DOT__Denorm_B = ((0U
                                                 == (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EB))
                                                & (0U
                                                   != (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__SIGB)));
    vlTOPp->fmp__DOT__dw_spmp__DOT__Inf_Sig = 0U;
    vlTOPp->fmp__DOT__dw_spmp__DOT__NaN_Reg = 0x7f8001U;
    vlTOPp->fmp__DOT__dw_spmp__DOT__Inf_Reg = (0x7f8000U
                                               | ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__SIGN)
                                                  << 0x17U));
    vlTOPp->fmp__DOT__dw_spmp__DOT__MA = ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Denorm_A)
                                           ? (0x7fffU
                                              & vlTOPp->fmp__DOT__fmpA)
                                           : (0x8000U
                                              | (0x7fffU
                                                 & vlTOPp->fmp__DOT__fmpA)));
    vlTOPp->fmp__DOT__dw_spmp__DOT__MB = ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Denorm_B)
                                           ? (0x7fffU
                                              & vlTOPp->fmp__DOT__fmpB)
                                           : (0x8000U
                                              | (0x7fffU
                                                 & vlTOPp->fmp__DOT__fmpB)));
    if ((((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__MaxEXP_A)
          & (~ (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__InfSIG_A)))
         | ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__MaxEXP_B)
            & (~ (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__InfSIG_B))))) {
        vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg
            = (4U | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg));
        vlTOPp->fmp__DOT__dw_spmp__DOT__z_reg = vlTOPp->fmp__DOT__dw_spmp__DOT__NaN_Reg;
    } else {
        if (((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__MaxEXP_A)
             | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__MaxEXP_B))) {
            if (((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Zero_A)
                 | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Zero_B))) {
                vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg
                    = (4U | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg));
                vlTOPp->fmp__DOT__dw_spmp__DOT__z_reg
                    = vlTOPp->fmp__DOT__dw_spmp__DOT__NaN_Reg;
            } else {
                vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg
                    = (2U | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg));
                vlTOPp->fmp__DOT__dw_spmp__DOT__z_reg
                    = vlTOPp->fmp__DOT__dw_spmp__DOT__Inf_Reg;
            }
        } else {
            if (((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Zero_A)
                 | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Zero_B))) {
                vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg
                    = (1U | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg));
                vlTOPp->fmp__DOT__dw_spmp__DOT__z_reg = 0U;
                vlTOPp->fmp__DOT__dw_spmp__DOT__z_reg
                    = ((0x7fffffU & vlTOPp->fmp__DOT__dw_spmp__DOT__z_reg)
                       | ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__SIGN)
                          << 0x17U));
            } else {
                vlTOPp->fmp__DOT__dw_spmp__DOT__TMP_MA
                    = vlTOPp->fmp__DOT__dw_spmp__DOT__MA;
                if (vlTOPp->fmp__DOT__dw_spmp__DOT__Denorm_A) {
                    while ((1U & (~ ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__TMP_MA)
                                     >> 0xfU)))) {
                        vlTOPp->fmp__DOT__dw_spmp__DOT__TMP_MA
                            = (0xffffU & ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__TMP_MA)
                                          << 1U));
                        vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_INA
                            = (0x3ffU & ((IData)(1U)
                                         + (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_INA)));
                    }
                }
                vlTOPp->fmp__DOT__dw_spmp__DOT__TMP_MB
                    = vlTOPp->fmp__DOT__dw_spmp__DOT__MB;
                if (vlTOPp->fmp__DOT__dw_spmp__DOT__Denorm_B) {
                    while ((1U & (~ ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__TMP_MB)
                                     >> 0xfU)))) {
                        vlTOPp->fmp__DOT__dw_spmp__DOT__TMP_MB
                            = (0xffffU & ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__TMP_MB)
                                          << 1U));
                        vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_INB
                            = (0x3ffU & ((IData)(1U)
                                         + (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_INB)));
                    }
                }
                vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_IN
                    = (0x3ffU & ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_INA)
                                 + (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_INB)));
                vlTOPp->fmp__DOT__dw_spmp__DOT__EZ
                    = (0x3ffU & (((((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EA)
                                    + (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EB))
                                   - (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_IN))
                                  + (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Denorm_A))
                                 + (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Denorm_B)));
                vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                    = (VL_ULL(0x1ffffffff) & ((QData)((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__MA))
                                              * (QData)((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__MB))));
                vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                    = (VL_ULL(0x1ffffffff) & ((0x20U
                                               >= (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_IN))
                                               ? (vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                                  << (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_IN))
                                               : VL_ULL(0)));
                vlTOPp->fmp__DOT__dw_spmp__DOT__MZ_Movf1
                    = (1U & (IData)((vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                     >> 0x1fU)));
                if ((1U & (IData)((vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                   >> 0x1fU)))) {
                    vlTOPp->fmp__DOT__dw_spmp__DOT__EZ
                        = (0x3ffU & ((IData)(1U) +
                                     VL_EXTENDS_II(10,10, (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ))));
                    vlTOPp->fmp__DOT__dw_spmp__DOT__minnorm_case = 0U;
                } else {
                    vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                        = (VL_ULL(0x1ffffffff) & (vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                                  << 1U));
                    vlTOPp->fmp__DOT__dw_spmp__DOT__minnorm_case
                        = (1U & ((0U == (VL_EXTENDS_II(32,10, (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ))
                                         - (IData)(0x7fU)))
                                  ? 1U : 0U));
                }
                vlTOPp->fmp__DOT__dw_spmp__DOT__Range_Check
                    = (0x3ffU & ((((((((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EA)
                                       + (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EB))
                                      + (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Denorm_A))
                                     + (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Denorm_B))
                                    + (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__MZ_Movf1))
                                   - (IData)(0x7fU))
                                  - (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__LZ_IN))
                                 - (IData)(1U)));
                vlTOPp->fmp__DOT__dw_spmp__DOT__EZ_Shift
                    = (0x3ffU & VL_NEGATE_I((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Range_Check)));
                if (VL_LTES_III(1,32,32, 0U, VL_EXTENDS_II(32,10, (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ_Shift)))) {
                    vlTOPp->fmp__DOT__dw_spmp__DOT__i = 0U;
                    while (VL_LTS_III(1,32,32, vlTOPp->fmp__DOT__dw_spmp__DOT__i,
                                      VL_EXTENDS_II(32,10, (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ_Shift)))) {
                        vlTOPp->fmp__DOT__dw_spmp__DOT____Vconcswap1
                            = (VL_ULL(0x1ffffffff)
                               & (vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                  >> 1U));
                        vlTOPp->fmp__DOT__dw_spmp__DOT____Vconcswap2
                            = (1U & (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__MZ));
                        vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                            = vlTOPp->fmp__DOT__dw_spmp__DOT____Vconcswap1;
                        vlTOPp->fmp__DOT__dw_spmp__DOT__STK_CHECK
                            = vlTOPp->fmp__DOT__dw_spmp__DOT____Vconcswap2;
                        vlTOPp->fmp__DOT__dw_spmp__DOT__STK_EXT
                            = ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__STK_EXT)
                               | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__STK_CHECK));
                        vlTOPp->fmp__DOT__dw_spmp__DOT__i
                            = ((IData)(1U) + vlTOPp->fmp__DOT__dw_spmp__DOT__i);
                    }
                }
                if ((0U != (0xfffffffeU & (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__minnorm_case)))) {
                    vlTOPp->fmp__DOT__dw_spmp__DOT__STK
                        = (0U != ((0xffff0000U & ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__MZ)
                                                  << 0x10U))
                                  | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__STK_EXT)));
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__stk
                        = vlTOPp->fmp__DOT__dw_spmp__DOT__STK;
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__R
                        = (1U & (IData)((vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                         >> 0x10U)));
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__L
                        = (1U & (IData)((vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                         >> 0x11U)));
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Sign
                        = vlTOPp->fmp__DOT__dw_spmp__DOT__SIGN;
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__rnd = 0U;
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                        = (0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout));
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                        = ((0xdU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout))
                           | (((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__R)
                               | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__stk))
                              << 1U));
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                        = (0xbU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout));
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                        = (7U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout));
                    if ((VL_ULL(0) < VL_TIME_Q())) {
                        if ((4U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__rnd))) {
                            if (VL_UNLIKELY((2U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__rnd)))) {
                                VL_WRITEF("Error! illegal rounding mode.\n\n");
                                VL_WRITEF("a : %b\n",
                                          24,vlTOPp->fmp__DOT__fmpA);
                                VL_WRITEF("rnd : %b\n",
                                          3,vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__rnd);
                            } else {
                                if ((1U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__rnd))) {
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__R)
                                              | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__stk)));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = (4U | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = (8U | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout));
                                } else {
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout))
                                           | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__R));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = (4U | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = (7U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout));
                                }
                            }
                        } else {
                            if ((2U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__rnd))) {
                                if ((1U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__rnd))) {
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Sign)
                                              & ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__R)
                                                 | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__stk))));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = ((0xbU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Sign)
                                              << 2U));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = ((7U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Sign)
                                              << 3U));
                                } else {
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout))
                                           | ((~ (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Sign))
                                              & ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__R)
                                                 | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__stk))));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = ((0xbU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout))
                                           | (4U &
                                              ((~ (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Sign))
                                               << 2U)));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = ((7U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout))
                                           | (8U &
                                              ((~ (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Sign))
                                               << 3U)));
                                }
                            } else {
                                if ((1U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__rnd))) {
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = (0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = (0xbU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = (7U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout));
                                } else {
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__R)
                                              & ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__L)
                                                 | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__stk))));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = (4U | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout
                                        = (7U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout));
                                }
                            }
                        }
                    }
                    vlTOPp->fmp__DOT__dw_spmp__DOT__RND_val
                        = vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout;
                } else {
                    vlTOPp->fmp__DOT__dw_spmp__DOT__STK
                        = (0U != ((0x7fff0000U & ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__MZ)
                                                  << 0x10U))
                                  | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__STK_EXT)));
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__stk
                        = vlTOPp->fmp__DOT__dw_spmp__DOT__STK;
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__R
                        = (1U & (IData)((vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                         >> 0xfU)));
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__L
                        = (1U & (IData)((vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                         >> 0x10U)));
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Sign
                        = vlTOPp->fmp__DOT__dw_spmp__DOT__SIGN;
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__rnd = 0U;
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                        = (0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout));
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                        = ((0xdU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout))
                           | (((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__R)
                               | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__stk))
                              << 1U));
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                        = (0xbU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout));
                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                        = (7U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout));
                    if ((VL_ULL(0) < VL_TIME_Q())) {
                        if ((4U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__rnd))) {
                            if (VL_UNLIKELY((2U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__rnd)))) {
                                VL_WRITEF("Error! illegal rounding mode.\n\n");
                                VL_WRITEF("a : %b\n",
                                          24,vlTOPp->fmp__DOT__fmpA);
                                VL_WRITEF("rnd : %b\n",
                                          3,vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__rnd);
                            } else {
                                if ((1U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__rnd))) {
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__R)
                                              | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__stk)));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = (4U | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = (8U | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout));
                                } else {
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout))
                                           | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__R));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = (4U | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = (7U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout));
                                }
                            }
                        } else {
                            if ((2U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__rnd))) {
                                if ((1U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__rnd))) {
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Sign)
                                              & ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__R)
                                                 | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__stk))));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = ((0xbU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Sign)
                                              << 2U));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = ((7U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Sign)
                                              << 3U));
                                } else {
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout))
                                           | ((~ (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Sign))
                                              & ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__R)
                                                 | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__stk))));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = ((0xbU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout))
                                           | (4U &
                                              ((~ (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Sign))
                                               << 2U)));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = ((7U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout))
                                           | (8U &
                                              ((~ (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Sign))
                                               << 3U)));
                                }
                            } else {
                                if ((1U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__rnd))) {
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = (0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = (0xbU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = (7U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout));
                                } else {
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__R)
                                              & ((IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__L)
                                                 | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__stk))));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = (4U | (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout));
                                    vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout
                                        = (7U & (IData)(vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout));
                                }
                            }
                        }
                    }
                    vlTOPp->fmp__DOT__dw_spmp__DOT__RND_val
                        = vlTOPp->__Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout;
                }
                if ((1U & (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__RND_val))) {
                    vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                        = (VL_ULL(0x1ffffffff) & (VL_ULL(0x10000)
                                                  + vlTOPp->fmp__DOT__dw_spmp__DOT__MZ));
                }
                if ((1U & (IData)((vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                   >> 0x20U)))) {
                    vlTOPp->fmp__DOT__dw_spmp__DOT__EZ
                        = (0x3ffU & ((IData)(1U) +
                                     VL_EXTENDS_II(10,10, (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ))));
                    vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                        = (VL_ULL(0x1ffffffff) & (vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                                  >> 1U));
                }
                if ((0U != (1U & (VL_GTES_III(32,32,32, 0x7fU,
                                              VL_EXTENDS_II(32,10, (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ)))
                                  & (IData)((vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                             >> 0x1fU)))))) {
                    vlTOPp->fmp__DOT__dw_spmp__DOT__EZ
                        = (0x3ffU & ((IData)(1U) +
                                     VL_EXTENDS_II(10,10, (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ))));
                }
                vlTOPp->fmp__DOT__dw_spmp__DOT__EZ
                    = (0x3ffU & (((~ ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ)
                                      >> 9U)) & VL_LTES_III(1,32,32, 0x7fU,
                                                            VL_EXTENDS_II(32,10, (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ))))
                                  ? (VL_EXTENDS_II(10,10, (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ))
                                     - (IData)(0x7fU))
                                  : 0U));
                if (VL_LTES_III(1,32,32, 0xffU, VL_EXTENDS_II(32,10, (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ)))) {
                    vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg
                        = (0x10U | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg));
                    vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg
                        = (0x20U | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg));
                    if ((4U & (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__RND_val))) {
                        vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                            = ((VL_ULL(0x18000ffff)
                                & vlTOPp->fmp__DOT__dw_spmp__DOT__MZ)
                               | ((QData)((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Inf_Sig))
                                  << 0x10U));
                        vlTOPp->fmp__DOT__dw_spmp__DOT__EZ = 0xffU;
                        vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg
                            = (2U | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg));
                    } else {
                        vlTOPp->fmp__DOT__dw_spmp__DOT__EZ = 0xfeU;
                        vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                            = (VL_ULL(0x7fff0000) | vlTOPp->fmp__DOT__dw_spmp__DOT__MZ);
                    }
                } else {
                    if ((0U == VL_EXTENDS_II(32,10, (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ)))) {
                        vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg
                            = (8U | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg));
                        if (((0U == (0x7fffU & (IData)(
                                                       (vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                                        >> 0x10U))))
                             & (0U == (0xffU & (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ))))) {
                            vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg
                                = (1U | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg));
                        }
                    }
                }
                vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg
                    = ((0xdfU & (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg))
                       | (0x20U & ((0xffffffe0U & ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__status_reg)
                                                   | ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__RND_val)
                                                      << 4U)))
                                   | ((((~ ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Zero_A)
                                            | (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__Zero_B)))
                                        & (0U == (0xffU
                                                  & (IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ))))
                                       & (0U == (0x7fffU
                                                 & (IData)(
                                                           (vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                                            >> 0x10U)))))
                                      << 5U))));
                vlTOPp->fmp__DOT__dw_spmp__DOT__z_reg
                    = (((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__SIGN)
                        << 0x17U) | ((0x7f8000U & ((IData)(vlTOPp->fmp__DOT__dw_spmp__DOT__EZ)
                                                   << 0xfU))
                                     | (0x7fffU & (IData)(
                                                          (vlTOPp->fmp__DOT__dw_spmp__DOT__MZ
                                                           >> 0x10U)))));
            }
        }
    }
    vlTOPp->fmpC_out = vlTOPp->fmp__DOT__dw_spmp__DOT__z_reg;
}

void Vfmp::_eval(Vfmp__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfmp::_eval\n"); );
    Vfmp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vfmp::_eval_initial(Vfmp__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfmp::_eval_initial\n"); );
    Vfmp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vfmp::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfmp::final\n"); );
    // Variables
    Vfmp__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vfmp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vfmp::_eval_settle(Vfmp__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfmp::_eval_settle\n"); );
    Vfmp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vfmp::_change_request(Vfmp__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfmp::_change_request\n"); );
    Vfmp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vfmp::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfmp::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clock & 0xfeU))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY((ohe_selector_EX & 0xfeU))) {
        Verilated::overWidthError("ohe_selector_EX");}
}
#endif // VL_DEBUG

void Vfmp::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfmp::_ctor_var_reset\n"); );
    // Body
    clock = VL_RAND_RESET_I(1);
    ohe_selector_EX = VL_RAND_RESET_I(1);
    fmpA_in = VL_RAND_RESET_I(32);
    fmpB_in = VL_RAND_RESET_I(32);
    fmpC_out = VL_RAND_RESET_I(32);
    fmp__DOT__fmpA = VL_RAND_RESET_I(24);
    fmp__DOT__fmpB = VL_RAND_RESET_I(24);
    fmp__DOT__dw_spmp__DOT__z_reg = VL_RAND_RESET_I(24);
    fmp__DOT__dw_spmp__DOT__EA = VL_RAND_RESET_I(8);
    fmp__DOT__dw_spmp__DOT__EB = VL_RAND_RESET_I(8);
    fmp__DOT__dw_spmp__DOT__EZ = VL_RAND_RESET_I(10);
    fmp__DOT__dw_spmp__DOT__Range_Check = VL_RAND_RESET_I(10);
    fmp__DOT__dw_spmp__DOT__EZ_Shift = VL_RAND_RESET_I(10);
    fmp__DOT__dw_spmp__DOT__MA = VL_RAND_RESET_I(16);
    fmp__DOT__dw_spmp__DOT__MB = VL_RAND_RESET_I(16);
    fmp__DOT__dw_spmp__DOT__TMP_MA = VL_RAND_RESET_I(16);
    fmp__DOT__dw_spmp__DOT__TMP_MB = VL_RAND_RESET_I(16);
    fmp__DOT__dw_spmp__DOT__MZ = VL_RAND_RESET_Q(33);
    fmp__DOT__dw_spmp__DOT__STK = VL_RAND_RESET_I(1);
    fmp__DOT__dw_spmp__DOT__SIGN = VL_RAND_RESET_I(1);
    fmp__DOT__dw_spmp__DOT__RND_val = VL_RAND_RESET_I(4);
    fmp__DOT__dw_spmp__DOT__status_reg = VL_RAND_RESET_I(8);
    fmp__DOT__dw_spmp__DOT__MaxEXP_A = VL_RAND_RESET_I(1);
    fmp__DOT__dw_spmp__DOT__MaxEXP_B = VL_RAND_RESET_I(1);
    fmp__DOT__dw_spmp__DOT__InfSIG_A = VL_RAND_RESET_I(1);
    fmp__DOT__dw_spmp__DOT__InfSIG_B = VL_RAND_RESET_I(1);
    fmp__DOT__dw_spmp__DOT__Zero_A = VL_RAND_RESET_I(1);
    fmp__DOT__dw_spmp__DOT__Zero_B = VL_RAND_RESET_I(1);
    fmp__DOT__dw_spmp__DOT__Denorm_A = VL_RAND_RESET_I(1);
    fmp__DOT__dw_spmp__DOT__Denorm_B = VL_RAND_RESET_I(1);
    fmp__DOT__dw_spmp__DOT__LZ_INA = VL_RAND_RESET_I(10);
    fmp__DOT__dw_spmp__DOT__LZ_INB = VL_RAND_RESET_I(10);
    fmp__DOT__dw_spmp__DOT__LZ_IN = VL_RAND_RESET_I(10);
    fmp__DOT__dw_spmp__DOT__SIGA = VL_RAND_RESET_I(15);
    fmp__DOT__dw_spmp__DOT__SIGB = VL_RAND_RESET_I(15);
    fmp__DOT__dw_spmp__DOT__NaN_Reg = VL_RAND_RESET_I(24);
    fmp__DOT__dw_spmp__DOT__Inf_Reg = VL_RAND_RESET_I(24);
    fmp__DOT__dw_spmp__DOT__MZ_Movf1 = VL_RAND_RESET_I(1);
    fmp__DOT__dw_spmp__DOT__STK_EXT = VL_RAND_RESET_I(16);
    fmp__DOT__dw_spmp__DOT__Inf_Sig = VL_RAND_RESET_I(15);
    fmp__DOT__dw_spmp__DOT__STK_CHECK = VL_RAND_RESET_I(1);
    fmp__DOT__dw_spmp__DOT__minnorm_case = VL_RAND_RESET_I(1);
    fmp__DOT__dw_spmp__DOT__i = VL_RAND_RESET_I(32);
    fmp__DOT__dw_spmp__DOT____Vconcswap1 = VL_RAND_RESET_Q(33);
    fmp__DOT__dw_spmp__DOT____Vconcswap2 = VL_RAND_RESET_I(1);
    __Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Vfuncout = VL_RAND_RESET_I(4);
    __Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__rnd = VL_RAND_RESET_I(3);
    __Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__Sign = VL_RAND_RESET_I(1);
    __Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__L = VL_RAND_RESET_I(1);
    __Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__R = VL_RAND_RESET_I(1);
    __Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__0__stk = VL_RAND_RESET_I(1);
    __Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Vfuncout = VL_RAND_RESET_I(4);
    __Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__rnd = VL_RAND_RESET_I(3);
    __Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__Sign = VL_RAND_RESET_I(1);
    __Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__L = VL_RAND_RESET_I(1);
    __Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__R = VL_RAND_RESET_I(1);
    __Vfunc_fmp__DOT__dw_spmp__DOT__rnd_eval__1__stk = VL_RAND_RESET_I(1);
}
