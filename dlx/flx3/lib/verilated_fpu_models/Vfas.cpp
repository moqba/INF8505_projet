// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfas.h for the primary calling header

#include "Vfas.h"
#include "Vfas__Syms.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(Vfas) {
    Vfas__Syms* __restrict vlSymsp = __VlSymsp = new Vfas__Syms(this, name());
    Vfas* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values

    // Reset structure values
    _ctor_var_reset();
}

void Vfas::__Vconfigure(Vfas__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vfas::~Vfas() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vfas::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vfas::eval\n"); );
    Vfas__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vfas* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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

void Vfas::_eval_initial_loop(Vfas__Syms* __restrict vlSymsp) {
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

VL_INLINE_OPT void Vfas::_combo__TOP__1(Vfas__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfas::_combo__TOP__1\n"); );
    Vfas* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at ../hdl/designware_vlog/fas.v:45
    vlTOPp->fas__DOT__fasA = (0xffffffU & ((IData)(vlTOPp->ohe_selector_EX)
                                            ? vlTOPp->fasA_in
                                            : 0U));
    // ALWAYS at ../hdl/designware_vlog/fas.v:45
    vlTOPp->fas__DOT__fasB = (0xffffffU & ((IData)(vlTOPp->ohe_selector_EX)
                                            ? vlTOPp->fasB_in
                                            : 0U));
    // ALWAYS at ../hdl/designware_vlog/fas.v:45
    vlTOPp->fas__DOT__fasM = ((IData)(vlTOPp->ohe_selector_EX)
                              & (IData)(vlTOPp->fasM_in));
    // ALWAYS at /global/apps/syn_2019.03-SP2/dw/sim_ver/DW_fp_addsub.v:200
    vlTOPp->fas__DOT__dw_fas__DOT__NaNFp = 0x7f8001U;
    vlTOPp->fas__DOT__dw_fas__DOT__status_int = 0U;
    vlTOPp->fas__DOT__dw_fas__DOT__b_int = vlTOPp->fas__DOT__fasB;
    vlTOPp->fas__DOT__dw_fas__DOT__b_int = ((0x7fffffU
                                             & vlTOPp->fas__DOT__dw_fas__DOT__b_int)
                                            | (0x800000U
                                               & (((IData)(vlTOPp->fas__DOT__fasM)
                                                    ?
                                                   (~
                                                    (vlTOPp->fas__DOT__fasB
                                                     >> 0x17U))
                                                    :
                                                   (vlTOPp->fas__DOT__fasB
                                                    >> 0x17U))
                                                  << 0x17U)));
    vlTOPp->fas__DOT__dw_fas__DOT__subtract = (1U &
                                               ((vlTOPp->fas__DOT__fasA
                                                 ^ vlTOPp->fas__DOT__dw_fas__DOT__b_int)
                                                >> 0x17U));
    vlTOPp->fas__DOT__dw_fas__DOT__swap = ((0x7fffffU
                                            & vlTOPp->fas__DOT__fasA)
                                           < (0x7fffffU
                                              & vlTOPp->fas__DOT__fasB));
    vlTOPp->fas__DOT__dw_fas__DOT__Large = ((IData)(vlTOPp->fas__DOT__dw_fas__DOT__swap)
                                             ? vlTOPp->fas__DOT__dw_fas__DOT__b_int
                                             : vlTOPp->fas__DOT__fasA);
    vlTOPp->fas__DOT__dw_fas__DOT__Small = ((IData)(vlTOPp->fas__DOT__dw_fas__DOT__swap)
                                             ? vlTOPp->fas__DOT__fasA
                                             : vlTOPp->fas__DOT__dw_fas__DOT__b_int);
    vlTOPp->fas__DOT__dw_fas__DOT__E_Large = (0xffU
                                              & (vlTOPp->fas__DOT__dw_fas__DOT__Large
                                                 >> 0xfU));
    vlTOPp->fas__DOT__dw_fas__DOT__E_Small = (0xffU
                                              & (vlTOPp->fas__DOT__dw_fas__DOT__Small
                                                 >> 0xfU));
    vlTOPp->fas__DOT__dw_fas__DOT__F_Large = (0x7fffU
                                              & vlTOPp->fas__DOT__dw_fas__DOT__Large);
    vlTOPp->fas__DOT__dw_fas__DOT__F_Small = (0x7fffU
                                              & vlTOPp->fas__DOT__dw_fas__DOT__Small);
    if ((((0xffU == (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Large))
          & (0U != (IData)(vlTOPp->fas__DOT__dw_fas__DOT__F_Large)))
         | ((0xffU == (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Small))
            & (0U != (IData)(vlTOPp->fas__DOT__dw_fas__DOT__F_Large))))) {
        vlTOPp->fas__DOT__dw_fas__DOT__z_temp = vlTOPp->fas__DOT__dw_fas__DOT__NaNFp;
        vlTOPp->fas__DOT__dw_fas__DOT__status_int =
            (4U | (IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int));
    } else {
        if (((0xffU == (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Large))
             & (0U == (IData)(vlTOPp->fas__DOT__dw_fas__DOT__F_Large)))) {
            vlTOPp->fas__DOT__dw_fas__DOT__status_int
                = (2U | (IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int));
            vlTOPp->fas__DOT__dw_fas__DOT__z_temp = vlTOPp->fas__DOT__dw_fas__DOT__Large;
            vlTOPp->fas__DOT__dw_fas__DOT__z_temp =
                (0xff8000U & vlTOPp->fas__DOT__dw_fas__DOT__z_temp);
            if ((((0xffU == (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Small))
                  & (0U == (IData)(vlTOPp->fas__DOT__dw_fas__DOT__F_Large)))
                 & (IData)(vlTOPp->fas__DOT__dw_fas__DOT__subtract))) {
                vlTOPp->fas__DOT__dw_fas__DOT__status_int
                    = (4U | (IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int));
                vlTOPp->fas__DOT__dw_fas__DOT__z_temp
                    = vlTOPp->fas__DOT__dw_fas__DOT__NaNFp;
                vlTOPp->fas__DOT__dw_fas__DOT__status_int
                    = (0xfdU & (IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int));
            }
        } else {
            if (((0U == (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Small))
                 & (0U == (IData)(vlTOPp->fas__DOT__dw_fas__DOT__F_Small)))) {
                vlTOPp->fas__DOT__dw_fas__DOT__z_temp
                    = vlTOPp->fas__DOT__dw_fas__DOT__Large;
                if (((0U == (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Large))
                     & (0U == (IData)(vlTOPp->fas__DOT__dw_fas__DOT__F_Large)))) {
                    vlTOPp->fas__DOT__dw_fas__DOT__status_int
                        = (1U | (IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int));
                    vlTOPp->fas__DOT__dw_fas__DOT__z_temp = 0U;
                    vlTOPp->fas__DOT__dw_fas__DOT__z_temp
                        = ((0x7fffffU & vlTOPp->fas__DOT__dw_fas__DOT__z_temp)
                           | (0x800000U & (((~ (IData)(vlTOPp->fas__DOT__dw_fas__DOT__subtract))
                                            << 0x17U)
                                           & vlTOPp->fas__DOT__fasA)));
                }
            } else {
                if (((0U == (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Large))
                     & (0U != (IData)(vlTOPp->fas__DOT__dw_fas__DOT__F_Large)))) {
                    vlTOPp->fas__DOT__dw_fas__DOT__M_Large
                        = ((IData)(vlTOPp->fas__DOT__dw_fas__DOT__F_Large)
                           << 3U);
                    vlTOPp->fas__DOT__dw_fas__DOT__Denormal_Large = 1U;
                } else {
                    vlTOPp->fas__DOT__dw_fas__DOT__M_Large
                        = (0x40000U | ((IData)(vlTOPp->fas__DOT__dw_fas__DOT__F_Large)
                                       << 3U));
                    vlTOPp->fas__DOT__dw_fas__DOT__Denormal_Large = 0U;
                }
                if (((0U == (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Small))
                     & (0U != (IData)(vlTOPp->fas__DOT__dw_fas__DOT__F_Small)))) {
                    vlTOPp->fas__DOT__dw_fas__DOT__M_Small
                        = ((IData)(vlTOPp->fas__DOT__dw_fas__DOT__F_Small)
                           << 3U);
                    vlTOPp->fas__DOT__dw_fas__DOT__Denormal_Small = 1U;
                } else {
                    vlTOPp->fas__DOT__dw_fas__DOT__M_Small
                        = (0x40000U | ((IData)(vlTOPp->fas__DOT__dw_fas__DOT__F_Small)
                                       << 3U));
                    vlTOPp->fas__DOT__dw_fas__DOT__Denormal_Small = 0U;
                }
                vlTOPp->fas__DOT__dw_fas__DOT__E_Diff
                    = (0xffU & (((IData)(vlTOPp->fas__DOT__dw_fas__DOT__Denormal_Large)
                                 ^ (IData)(vlTOPp->fas__DOT__dw_fas__DOT__Denormal_Small))
                                 ? (((IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Large)
                                     - (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Small))
                                    - (IData)(1U)) :
                                ((IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Large)
                                 - (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Small))));
                vlTOPp->fas__DOT__dw_fas__DOT__STK = 0U;
                while (((0U != vlTOPp->fas__DOT__dw_fas__DOT__M_Small)
                        & (0U != (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Diff)))) {
                    vlTOPp->fas__DOT__dw_fas__DOT__STK
                        = (1U & (vlTOPp->fas__DOT__dw_fas__DOT__M_Small
                                 | (IData)(vlTOPp->fas__DOT__dw_fas__DOT__STK)));
                    vlTOPp->fas__DOT__dw_fas__DOT__M_Small
                        = (0xfffffU & (vlTOPp->fas__DOT__dw_fas__DOT__M_Small
                                       >> 1U));
                    vlTOPp->fas__DOT__dw_fas__DOT__E_Diff
                        = (0xffU & ((IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Diff)
                                    - (IData)(1U)));
                }
                vlTOPp->fas__DOT__dw_fas__DOT__M_Small
                    = ((0xffffeU & vlTOPp->fas__DOT__dw_fas__DOT__M_Small)
                       | (1U & (vlTOPp->fas__DOT__dw_fas__DOT__M_Small
                                | (IData)(vlTOPp->fas__DOT__dw_fas__DOT__STK))));
                vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                    = (0xfffffU & ((IData)(vlTOPp->fas__DOT__dw_fas__DOT__subtract)
                                    ? (vlTOPp->fas__DOT__dw_fas__DOT__M_Large
                                       - vlTOPp->fas__DOT__dw_fas__DOT__M_Small)
                                    : (vlTOPp->fas__DOT__dw_fas__DOT__M_Large
                                       + vlTOPp->fas__DOT__dw_fas__DOT__M_Small)));
                vlTOPp->fas__DOT__dw_fas__DOT__E_Comp
                    = vlTOPp->fas__DOT__dw_fas__DOT__E_Large;
                if ((0U == vlTOPp->fas__DOT__dw_fas__DOT__M_Z)) {
                    vlTOPp->fas__DOT__dw_fas__DOT__status_int
                        = (1U | (IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int));
                    vlTOPp->fas__DOT__dw_fas__DOT__z_temp = 0U;
                } else {
                    if ((0x80000U & vlTOPp->fas__DOT__dw_fas__DOT__M_Z)) {
                        vlTOPp->fas__DOT__dw_fas__DOT__E_Comp
                            = (0x3ffU & ((IData)(1U)
                                         + (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Comp)));
                        vlTOPp->fas__DOT__dw_fas__DOT__STK
                            = (1U & vlTOPp->fas__DOT__dw_fas__DOT__M_Z);
                        vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                            = (0xfffffU & (vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                           >> 1U));
                        vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                            = ((0xffffeU & vlTOPp->fas__DOT__dw_fas__DOT__M_Z)
                               | (1U & (vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                        | (IData)(vlTOPp->fas__DOT__dw_fas__DOT__STK))));
                    }
                    while (((~ (vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                >> 0x12U)) & (1U < (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Comp)))) {
                        vlTOPp->fas__DOT__dw_fas__DOT__E_Comp
                            = (0x3ffU & ((IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Comp)
                                         - (IData)(1U)));
                        vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                            = (0xfffffU & (vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                           << 1U));
                    }
                    if ((0U == (3U & (vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                      >> 0x12U)))) {
                        vlTOPp->fas__DOT__dw_fas__DOT__z_temp
                            = ((0x800000U & vlTOPp->fas__DOT__dw_fas__DOT__Large)
                               | (0x7fffU & (vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                             >> 3U)));
                        vlTOPp->fas__DOT__dw_fas__DOT__status_int
                            = (0xf7U & (IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int));
                        if (((IData)(vlTOPp->fas__DOT__dw_fas__DOT__STK)
                             | (0U != (7U & vlTOPp->fas__DOT__dw_fas__DOT__M_Z)))) {
                            vlTOPp->fas__DOT__dw_fas__DOT__status_int
                                = (0x20U | (IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int));
                        }
                        if ((0U == (0x7fffU & (vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                               >> 3U)))) {
                            vlTOPp->fas__DOT__dw_fas__DOT__status_int
                                = (1U | (IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int));
                        }
                    } else {
                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__STK
                            = (0U != (3U & vlTOPp->fas__DOT__dw_fas__DOT__M_Z));
                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__R
                            = (1U & (vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                     >> 2U));
                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__L
                            = (1U & (vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                     >> 3U));
                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Sign
                            = (1U & (vlTOPp->fas__DOT__dw_fas__DOT__Large
                                     >> 0x17U));
                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__RND = 0U;
                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                            = (0xeU & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout));
                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                            = ((0xdU & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout))
                               | (((IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__R)
                                   | (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__STK))
                                  << 1U));
                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                            = (0xbU & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout));
                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                            = (7U & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout));
                        if ((VL_ULL(0) < VL_TIME_Q())) {
                            if ((4U & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__RND))) {
                                if (VL_UNLIKELY((2U
                                                 & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__RND)))) {
                                    VL_WRITEF("Error! illegal rounding mode.\n\n");
                                } else {
                                    if ((1U & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__RND))) {
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = ((0xeU
                                                & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout))
                                               | ((IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__R)
                                                  | (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__STK)));
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = (4U | (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout));
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = (8U | (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout));
                                    } else {
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = ((0xeU
                                                & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout))
                                               | (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__R));
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = (4U | (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout));
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = (7U & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout));
                                    }
                                }
                            } else {
                                if ((2U & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__RND))) {
                                    if ((1U & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__RND))) {
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = ((0xeU
                                                & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout))
                                               | ((IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Sign)
                                                  & ((IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__R)
                                                     | (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__STK))));
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = ((0xbU
                                                & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout))
                                               | ((IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Sign)
                                                  << 2U));
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = ((7U
                                                & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout))
                                               | ((IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Sign)
                                                  << 3U));
                                    } else {
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = ((0xeU
                                                & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout))
                                               | ((~ (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Sign))
                                                  & ((IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__R)
                                                     | (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__STK))));
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = ((0xbU
                                                & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout))
                                               | (4U
                                                  & ((~ (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Sign))
                                                     << 2U)));
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = ((7U
                                                & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout))
                                               | (8U
                                                  & ((~ (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Sign))
                                                     << 3U)));
                                    }
                                } else {
                                    if ((1U & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__RND))) {
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = (0xeU
                                               & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout));
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = (0xbU
                                               & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout));
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = (7U & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout));
                                    } else {
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = ((0xeU
                                                & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout))
                                               | ((IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__R)
                                                  & ((IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__L)
                                                     | (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__STK))));
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = (4U | (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout));
                                        vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout
                                            = (7U & (IData)(vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout));
                                    }
                                }
                            }
                        }
                        vlTOPp->fas__DOT__dw_fas__DOT__RND_val
                            = vlTOPp->__Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout;
                        if ((1U & (IData)(vlTOPp->fas__DOT__dw_fas__DOT__RND_val))) {
                            vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                = (0xfffffU & ((IData)(8U)
                                               + vlTOPp->fas__DOT__dw_fas__DOT__M_Z));
                        }
                        if ((0x80000U & vlTOPp->fas__DOT__dw_fas__DOT__M_Z)) {
                            vlTOPp->fas__DOT__dw_fas__DOT__E_Comp
                                = (0x3ffU & ((IData)(1U)
                                             + (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Comp)));
                            vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                = (0xfffffU & (vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                               >> 1U));
                        }
                        if ((0xffU <= (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Comp))) {
                            vlTOPp->fas__DOT__dw_fas__DOT__status_int
                                = (0x10U | (IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int));
                            vlTOPp->fas__DOT__dw_fas__DOT__status_int
                                = (0x20U | (IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int));
                            if ((4U & (IData)(vlTOPp->fas__DOT__dw_fas__DOT__RND_val))) {
                                vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                    = (0xc0007U & vlTOPp->fas__DOT__dw_fas__DOT__M_Z);
                                vlTOPp->fas__DOT__dw_fas__DOT__E_Comp = 0xffU;
                                vlTOPp->fas__DOT__dw_fas__DOT__status_int
                                    = (2U | (IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int));
                            } else {
                                vlTOPp->fas__DOT__dw_fas__DOT__E_Comp = 0xfeU;
                                vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                    = (0x3fff8U | vlTOPp->fas__DOT__dw_fas__DOT__M_Z);
                            }
                        } else {
                            if ((0U >= (IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Comp))) {
                                vlTOPp->fas__DOT__dw_fas__DOT__E_Comp = 1U;
                            }
                        }
                        vlTOPp->fas__DOT__dw_fas__DOT__status_int
                            = ((0xdfU & (IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int))
                               | (0x20U & ((IData)(vlTOPp->fas__DOT__dw_fas__DOT__status_int)
                                           | ((IData)(vlTOPp->fas__DOT__dw_fas__DOT__RND_val)
                                              << 4U))));
                        vlTOPp->fas__DOT__dw_fas__DOT__z_temp
                            = ((0x800000U & vlTOPp->fas__DOT__dw_fas__DOT__Large)
                               | ((0x7f8000U & ((IData)(vlTOPp->fas__DOT__dw_fas__DOT__E_Comp)
                                                << 0xfU))
                                  | (0x7fffU & (vlTOPp->fas__DOT__dw_fas__DOT__M_Z
                                                >> 3U))));
                    }
                }
            }
        }
    }
    vlTOPp->fasC_out = vlTOPp->fas__DOT__dw_fas__DOT__z_temp;
}

void Vfas::_eval(Vfas__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfas::_eval\n"); );
    Vfas* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vfas::_eval_initial(Vfas__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfas::_eval_initial\n"); );
    Vfas* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vfas::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfas::final\n"); );
    // Variables
    Vfas__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vfas* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vfas::_eval_settle(Vfas__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfas::_eval_settle\n"); );
    Vfas* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vfas::_change_request(Vfas__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfas::_change_request\n"); );
    Vfas* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vfas::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfas::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clock & 0xfeU))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY((ohe_selector_EX & 0xfeU))) {
        Verilated::overWidthError("ohe_selector_EX");}
    if (VL_UNLIKELY((fasM_in & 0xfeU))) {
        Verilated::overWidthError("fasM_in");}
}
#endif // VL_DEBUG

void Vfas::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfas::_ctor_var_reset\n"); );
    // Body
    clock = VL_RAND_RESET_I(1);
    ohe_selector_EX = VL_RAND_RESET_I(1);
    fasA_in = VL_RAND_RESET_I(32);
    fasB_in = VL_RAND_RESET_I(32);
    fasM_in = VL_RAND_RESET_I(1);
    fasC_out = VL_RAND_RESET_I(32);
    fas__DOT__fasA = VL_RAND_RESET_I(24);
    fas__DOT__fasB = VL_RAND_RESET_I(24);
    fas__DOT__fasM = VL_RAND_RESET_I(1);
    fas__DOT__dw_fas__DOT__status_int = VL_RAND_RESET_I(8);
    fas__DOT__dw_fas__DOT__z_temp = VL_RAND_RESET_I(24);
    fas__DOT__dw_fas__DOT__Large = VL_RAND_RESET_I(24);
    fas__DOT__dw_fas__DOT__Small = VL_RAND_RESET_I(24);
    fas__DOT__dw_fas__DOT__swap = VL_RAND_RESET_I(1);
    fas__DOT__dw_fas__DOT__subtract = VL_RAND_RESET_I(1);
    fas__DOT__dw_fas__DOT__STK = VL_RAND_RESET_I(1);
    fas__DOT__dw_fas__DOT__E_Large = VL_RAND_RESET_I(8);
    fas__DOT__dw_fas__DOT__E_Small = VL_RAND_RESET_I(8);
    fas__DOT__dw_fas__DOT__E_Diff = VL_RAND_RESET_I(8);
    fas__DOT__dw_fas__DOT__F_Large = VL_RAND_RESET_I(15);
    fas__DOT__dw_fas__DOT__F_Small = VL_RAND_RESET_I(15);
    fas__DOT__dw_fas__DOT__E_Comp = VL_RAND_RESET_I(10);
    fas__DOT__dw_fas__DOT__M_Large = VL_RAND_RESET_I(20);
    fas__DOT__dw_fas__DOT__M_Small = VL_RAND_RESET_I(20);
    fas__DOT__dw_fas__DOT__M_Z = VL_RAND_RESET_I(20);
    fas__DOT__dw_fas__DOT__RND_val = VL_RAND_RESET_I(4);
    fas__DOT__dw_fas__DOT__NaNFp = VL_RAND_RESET_I(24);
    fas__DOT__dw_fas__DOT__b_int = VL_RAND_RESET_I(24);
    fas__DOT__dw_fas__DOT__Denormal_Large = VL_RAND_RESET_I(1);
    fas__DOT__dw_fas__DOT__Denormal_Small = VL_RAND_RESET_I(1);
    __Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Vfuncout = VL_RAND_RESET_I(4);
    __Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__RND = VL_RAND_RESET_I(3);
    __Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__Sign = VL_RAND_RESET_I(1);
    __Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__L = VL_RAND_RESET_I(1);
    __Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__R = VL_RAND_RESET_I(1);
    __Vfunc_fas__DOT__dw_fas__DOT__RND_eval__0__STK = VL_RAND_RESET_I(1);
}
