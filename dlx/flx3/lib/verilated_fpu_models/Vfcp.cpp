// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfcp.h for the primary calling header

#include "Vfcp.h"
#include "Vfcp__Syms.h"


//--------------------
// STATIC VARIABLES

// Begin mtask footprint  all:
VL_ST_SIG(Vfcp::__Vtable1_fcp__DOT__fcpC[16],23,0);

//--------------------

VL_CTOR_IMP(Vfcp) {
    Vfcp__Syms* __restrict vlSymsp = __VlSymsp = new Vfcp__Syms(this, name());
    Vfcp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values

    // Reset structure values
    _ctor_var_reset();
}

void Vfcp::__Vconfigure(Vfcp__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vfcp::~Vfcp() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vfcp::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vfcp::eval\n"); );
    Vfcp__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vfcp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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

void Vfcp::_eval_initial_loop(Vfcp__Syms* __restrict vlSymsp) {
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

VL_INLINE_OPT void Vfcp::_combo__TOP__1(Vfcp__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfcp::_combo__TOP__1\n"); );
    Vfcp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at ../hdl/designware_vlog/fcp.v:47
    vlTOPp->fcp__DOT__fcpA = (0xffffffU & ((0U == (IData)(vlTOPp->bin_selector_EX))
                                            ? 0U : vlTOPp->fcpA_in));
    // ALWAYS at ../hdl/designware_vlog/fcp.v:47
    vlTOPp->fcp__DOT__fcpB = (0xffffffU & ((0U == (IData)(vlTOPp->bin_selector_EX))
                                            ? 0U : vlTOPp->fcpB_in));
    // ALWAYS at /global/apps/syn_2019.03-SP2/dw/sim_ver/DW_fp_cmp.v:137
    vlTOPp->fcp__DOT__dw_fcp__DOT__Ea = (0xffU & (vlTOPp->fcp__DOT__fcpA
                                                  >> 0xfU));
    vlTOPp->fcp__DOT__dw_fcp__DOT__Eb = (0xffU & (vlTOPp->fcp__DOT__fcpB
                                                  >> 0xfU));
    vlTOPp->fcp__DOT__dw_fcp__DOT__Fa = (0x7fffU & vlTOPp->fcp__DOT__fcpA);
    vlTOPp->fcp__DOT__dw_fcp__DOT__Fb = (0x7fffU & vlTOPp->fcp__DOT__fcpB);
    vlTOPp->fcp__DOT__dw_fcp__DOT__zer_a = 0U;
    vlTOPp->fcp__DOT__dw_fcp__DOT__zer_b = 0U;
    if ((0U == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Ea))) {
        vlTOPp->fcp__DOT__dw_fcp__DOT__zer_a = (0U
                                                == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fa));
    }
    if ((0U == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Eb))) {
        vlTOPp->fcp__DOT__dw_fcp__DOT__zer_b = (0U
                                                == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fb));
    }
    vlTOPp->fcp__DOT__dw_fcp__DOT__sign = (1U & (((vlTOPp->fcp__DOT__fcpA
                                                   >> 0x17U)
                                                  & (~ (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__zer_a)))
                                                 ^
                                                 ((vlTOPp->fcp__DOT__fcpB
                                                   >> 0x17U)
                                                  & (~ (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__zer_b)))));
    vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int = 0U;
    vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int = 0U;
    vlTOPp->fcp__DOT__dw_fcp__DOT__agtb_int = 0U;
    vlTOPp->fcp__DOT__dw_fcp__DOT__aeqb_int = 0U;
    vlTOPp->fcp__DOT__dw_fcp__DOT__altb_int = 0U;
    vlTOPp->fcp__DOT__dw_fcp__DOT__unordered_int = 0U;
    if ((((0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Ea))
          & (0U != (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fa)))
         | ((0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Eb))
            & (0U != (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fb))))) {
        vlTOPp->fcp__DOT__dw_fcp__DOT__unordered_int = 1U;
    } else {
        if (((0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Ea))
             & (0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Eb)))) {
            if (vlTOPp->fcp__DOT__dw_fcp__DOT__sign) {
                if ((0x800000U & vlTOPp->fcp__DOT__fcpA)) {
                    vlTOPp->fcp__DOT__dw_fcp__DOT__altb_int = 1U;
                } else {
                    vlTOPp->fcp__DOT__dw_fcp__DOT__agtb_int = 1U;
                }
            } else {
                vlTOPp->fcp__DOT__dw_fcp__DOT__aeqb_int = 1U;
            }
        } else {
            if ((0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Ea))) {
                if ((0x800000U & vlTOPp->fcp__DOT__fcpA)) {
                    vlTOPp->fcp__DOT__dw_fcp__DOT__altb_int = 1U;
                } else {
                    vlTOPp->fcp__DOT__dw_fcp__DOT__agtb_int = 1U;
                }
            } else {
                if ((0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Eb))) {
                    if ((0x800000U & vlTOPp->fcp__DOT__fcpB)) {
                        vlTOPp->fcp__DOT__dw_fcp__DOT__agtb_int = 1U;
                    } else {
                        vlTOPp->fcp__DOT__dw_fcp__DOT__altb_int = 1U;
                    }
                } else {
                    if (((IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__zer_a)
                         & (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__zer_b))) {
                        vlTOPp->fcp__DOT__dw_fcp__DOT__aeqb_int = 1U;
                    } else {
                        if (vlTOPp->fcp__DOT__dw_fcp__DOT__zer_a) {
                            if ((0x800000U & vlTOPp->fcp__DOT__fcpB)) {
                                vlTOPp->fcp__DOT__dw_fcp__DOT__agtb_int = 1U;
                            } else {
                                vlTOPp->fcp__DOT__dw_fcp__DOT__altb_int = 1U;
                            }
                        } else {
                            if (vlTOPp->fcp__DOT__dw_fcp__DOT__zer_b) {
                                if ((0x800000U & vlTOPp->fcp__DOT__fcpA)) {
                                    vlTOPp->fcp__DOT__dw_fcp__DOT__altb_int = 1U;
                                } else {
                                    vlTOPp->fcp__DOT__dw_fcp__DOT__agtb_int = 1U;
                                }
                            } else {
                                if (vlTOPp->fcp__DOT__dw_fcp__DOT__sign) {
                                    if ((0x800000U
                                         & vlTOPp->fcp__DOT__fcpA)) {
                                        vlTOPp->fcp__DOT__dw_fcp__DOT__altb_int = 1U;
                                    } else {
                                        vlTOPp->fcp__DOT__dw_fcp__DOT__agtb_int = 1U;
                                    }
                                } else {
                                    if (((IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Ea)
                                         != (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Eb))) {
                                        if ((((~ (vlTOPp->fcp__DOT__fcpA
                                                  >> 0x17U))
                                              & ((IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Ea)
                                                 > (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Eb)))
                                             | ((vlTOPp->fcp__DOT__fcpA
                                                 >> 0x17U)
                                                & ((IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Ea)
                                                   < (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Eb))))) {
                                            vlTOPp->fcp__DOT__dw_fcp__DOT__agtb_int = 1U;
                                        } else {
                                            vlTOPp->fcp__DOT__dw_fcp__DOT__altb_int = 1U;
                                        }
                                    } else {
                                        if ((((~ (vlTOPp->fcp__DOT__fcpA
                                                  >> 0x17U))
                                              & ((IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fa)
                                                 > (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fb)))
                                             | ((vlTOPp->fcp__DOT__fcpA
                                                 >> 0x17U)
                                                & ((IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fa)
                                                   < (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fb))))) {
                                            vlTOPp->fcp__DOT__dw_fcp__DOT__agtb_int = 1U;
                                        } else {
                                            if (((IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fa)
                                                 == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fb))) {
                                                vlTOPp->fcp__DOT__dw_fcp__DOT__aeqb_int = 1U;
                                            } else {
                                                vlTOPp->fcp__DOT__dw_fcp__DOT__altb_int = 1U;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->fcp__DOT__dw_fcp__DOT__chk = (3U & ((((IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__agtb_int)
                                                  + (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__aeqb_int))
                                                 + (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__altb_int))
                                                + (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__unordered_int)));
    if (VL_UNLIKELY((1U != (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__chk)))) {
        VL_WRITEF("Error! agtb, aeqb, altb, and unordered are NOT mutually exclusive.\n");
    }
    if ((((IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__altb_int)
          | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__aeqb_int))
         | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__unordered_int))) {
        vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int
            = (0x80U | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int));
        if (((0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Eb))
             & (0U != (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fb)))) {
            vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int
                = (4U | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int));
        }
        if (((0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Ea))
             & (0U != (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fa)))) {
            vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int
                = (4U | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int));
        }
        if (((0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Eb))
             & (0U == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fb)))) {
            vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int
                = (2U | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int));
        }
        if (((0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Ea))
             & (0U == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fa)))) {
            vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int
                = (2U | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int));
        }
        vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int
            = ((0xfeU & (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int))
               | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__zer_b));
        vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int
            = ((0xfeU & (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int))
               | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__zer_a));
    } else {
        if (((0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Eb))
             & (0U != (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fb)))) {
            vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int
                = (4U | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int));
        }
        if (((0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Ea))
             & (0U != (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fa)))) {
            vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int
                = (4U | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int));
        }
        if (((0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Eb))
             & (0U == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fb)))) {
            vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int
                = (2U | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int));
        }
        if (((0xffU == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Ea))
             & (0U == (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__Fa)))) {
            vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int
                = (2U | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int));
        }
        vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int
            = ((0xfeU & (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status0_int))
               | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__zer_b));
        vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int
            = ((0xfeU & (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int))
               | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__zer_a));
        vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int
            = (0x80U | (IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__status1_int));
    }
    // ALWAYS at ../hdl/designware_vlog/fcp.v:76
    vlTOPp->__Vtableidx1 = (((IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__aeqb_int)
                             << 3U) | (((IData)(vlTOPp->fcp__DOT__dw_fcp__DOT__altb_int)
                                        << 2U) | (IData)(vlTOPp->bin_selector_EX)));
    vlTOPp->fcp__DOT__fcpC = vlTOPp->__Vtable1_fcp__DOT__fcpC
        [vlTOPp->__Vtableidx1];
    vlTOPp->fcpC_out = vlTOPp->fcp__DOT__fcpC;
}

void Vfcp::_eval(Vfcp__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfcp::_eval\n"); );
    Vfcp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vfcp::_eval_initial(Vfcp__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfcp::_eval_initial\n"); );
    Vfcp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vfcp::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfcp::final\n"); );
    // Variables
    Vfcp__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vfcp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vfcp::_eval_settle(Vfcp__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfcp::_eval_settle\n"); );
    Vfcp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vfcp::_change_request(Vfcp__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfcp::_change_request\n"); );
    Vfcp* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vfcp::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfcp::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((bin_selector_EX & 0xfcU))) {
        Verilated::overWidthError("bin_selector_EX");}
}
#endif // VL_DEBUG

void Vfcp::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfcp::_ctor_var_reset\n"); );
    // Body
    bin_selector_EX = VL_RAND_RESET_I(2);
    fcpA_in = VL_RAND_RESET_I(32);
    fcpB_in = VL_RAND_RESET_I(32);
    fcpC_out = VL_RAND_RESET_I(32);
    fcp__DOT__fcpA = VL_RAND_RESET_I(24);
    fcp__DOT__fcpB = VL_RAND_RESET_I(24);
    fcp__DOT__fcpC = VL_RAND_RESET_I(24);
    fcp__DOT__dw_fcp__DOT__sign = VL_RAND_RESET_I(1);
    fcp__DOT__dw_fcp__DOT__Ea = VL_RAND_RESET_I(8);
    fcp__DOT__dw_fcp__DOT__Eb = VL_RAND_RESET_I(8);
    fcp__DOT__dw_fcp__DOT__Fa = VL_RAND_RESET_I(15);
    fcp__DOT__dw_fcp__DOT__Fb = VL_RAND_RESET_I(15);
    fcp__DOT__dw_fcp__DOT__status0_int = VL_RAND_RESET_I(8);
    fcp__DOT__dw_fcp__DOT__status1_int = VL_RAND_RESET_I(8);
    fcp__DOT__dw_fcp__DOT__agtb_int = VL_RAND_RESET_I(1);
    fcp__DOT__dw_fcp__DOT__aeqb_int = VL_RAND_RESET_I(1);
    fcp__DOT__dw_fcp__DOT__altb_int = VL_RAND_RESET_I(1);
    fcp__DOT__dw_fcp__DOT__unordered_int = VL_RAND_RESET_I(1);
    fcp__DOT__dw_fcp__DOT__chk = VL_RAND_RESET_I(2);
    fcp__DOT__dw_fcp__DOT__zer_a = VL_RAND_RESET_I(1);
    fcp__DOT__dw_fcp__DOT__zer_b = VL_RAND_RESET_I(1);
    __Vtableidx1 = VL_RAND_RESET_I(4);
    __Vtable1_fcp__DOT__fcpC[0] = 0U;
    __Vtable1_fcp__DOT__fcpC[1] = 0U;
    __Vtable1_fcp__DOT__fcpC[2] = 0U;
    __Vtable1_fcp__DOT__fcpC[3] = 0U;
    __Vtable1_fcp__DOT__fcpC[4] = 0U;
    __Vtable1_fcp__DOT__fcpC[5] = 0U;
    __Vtable1_fcp__DOT__fcpC[6] = 1U;
    __Vtable1_fcp__DOT__fcpC[7] = 1U;
    __Vtable1_fcp__DOT__fcpC[8] = 0U;
    __Vtable1_fcp__DOT__fcpC[9] = 1U;
    __Vtable1_fcp__DOT__fcpC[10] = 1U;
    __Vtable1_fcp__DOT__fcpC[11] = 0U;
    __Vtable1_fcp__DOT__fcpC[12] = 0U;
    __Vtable1_fcp__DOT__fcpC[13] = 1U;
    __Vtable1_fcp__DOT__fcpC[14] = 1U;
    __Vtable1_fcp__DOT__fcpC[15] = 1U;
}
