// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vspdv24.h for the primary calling header

#include "Vspdv24.h"
#include "Vspdv24__Syms.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(Vspdv24) {
    Vspdv24__Syms* __restrict vlSymsp = __VlSymsp = new Vspdv24__Syms(this, name());
    Vspdv24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values

    // Reset structure values
    _ctor_var_reset();
}

void Vspdv24::__Vconfigure(Vspdv24__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vspdv24::~Vspdv24() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vspdv24::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vspdv24::eval\n"); );
    Vspdv24__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vspdv24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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

void Vspdv24::_eval_initial_loop(Vspdv24__Syms* __restrict vlSymsp) {
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

VL_INLINE_OPT void Vspdv24::_combo__TOP__1(Vspdv24__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspdv24::_combo__TOP__1\n"); );
    Vspdv24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at /global/apps/syn_2019.03-SP2/dw/sim_ver/DW_fp_div.v:314
    vlTOPp->spdv24__DOT__U1__DOT__lO011100 = (1U &
                                              ((vlTOPp->spdvAf_in
                                                ^ vlTOPp->spdvBf_in)
                                               >> 0x17U));
    vlTOPp->spdv24__DOT__U1__DOT__lO101111 = (0xffU
                                              & (vlTOPp->spdvAf_in
                                                 >> 0xfU));
    vlTOPp->spdv24__DOT__U1__DOT__lI00O00I = (0xffU
                                              & (vlTOPp->spdvBf_in
                                                 >> 0xfU));
    vlTOPp->spdv24__DOT__U1__DOT__O00O1Ol1 = (0x7fffU
                                              & vlTOPp->spdvAf_in);
    vlTOPp->spdv24__DOT__U1__DOT__II01O1O0 = (0x7fffU
                                              & vlTOPp->spdvBf_in);
    vlTOPp->spdv24__DOT__U1__DOT__OIIO0OOl = 0U;
    vlTOPp->spdv24__DOT__U1__DOT__l0III011 = 0U;
    vlTOPp->spdv24__DOT__U1__DOT__IOIlII10 = 0U;
    vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0 = 0U;
    vlTOPp->spdv24__DOT__U1__DOT__lOI111I1 = ((0xffU
                                               == (IData)(vlTOPp->spdv24__DOT__U1__DOT__lO101111))
                                              & (0U
                                                 == (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00O1Ol1)));
    vlTOPp->spdv24__DOT__U1__DOT__O100O11l = ((0xffU
                                               == (IData)(vlTOPp->spdv24__DOT__U1__DOT__lI00O00I))
                                              & (0U
                                                 == (IData)(vlTOPp->spdv24__DOT__U1__DOT__II01O1O0)));
    vlTOPp->spdv24__DOT__U1__DOT__l10OO1I0 = ((0xffU
                                               == (IData)(vlTOPp->spdv24__DOT__U1__DOT__lO101111))
                                              & (0U
                                                 != (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00O1Ol1)));
    vlTOPp->spdv24__DOT__U1__DOT__l1O1Ol0O = ((0xffU
                                               == (IData)(vlTOPp->spdv24__DOT__U1__DOT__lI00O00I))
                                              & (0U
                                                 != (IData)(vlTOPp->spdv24__DOT__U1__DOT__II01O1O0)));
    vlTOPp->spdv24__DOT__U1__DOT__I000lO00 = ((0U == (IData)(vlTOPp->spdv24__DOT__U1__DOT__lO101111))
                                              & (0U
                                                 == (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00O1Ol1)));
    vlTOPp->spdv24__DOT__U1__DOT__l1OllI0I = ((0U == (IData)(vlTOPp->spdv24__DOT__U1__DOT__lI00O00I))
                                              & (0U
                                                 == (IData)(vlTOPp->spdv24__DOT__U1__DOT__II01O1O0)));
    vlTOPp->spdv24__DOT__U1__DOT__lO00I10I = ((0U == (IData)(vlTOPp->spdv24__DOT__U1__DOT__lO101111))
                                              & (0U
                                                 != (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00O1Ol1)));
    vlTOPp->spdv24__DOT__U1__DOT__IIIl11O1 = ((0U == (IData)(vlTOPp->spdv24__DOT__U1__DOT__lI00O00I))
                                              & (0U
                                                 != (IData)(vlTOPp->spdv24__DOT__U1__DOT__II01O1O0)));
    vlTOPp->spdv24__DOT__U1__DOT__IIl1O10O = (0x7f8000U
                                              | ((IData)(vlTOPp->spdv24__DOT__U1__DOT__lO011100)
                                                 << 0x17U));
    vlTOPp->spdv24__DOT__U1__DOT__I00lIO1l = 0x7f8001U;
    vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0 = ((0x7fU
                                               & (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0))
                                              | (((IData)(vlTOPp->spdv24__DOT__U1__DOT__l1OllI0I)
                                                  & (~
                                                     (((IData)(vlTOPp->spdv24__DOT__U1__DOT__I000lO00)
                                                       | (IData)(vlTOPp->spdv24__DOT__U1__DOT__l10OO1I0))
                                                      | (IData)(vlTOPp->spdv24__DOT__U1__DOT__lOI111I1))))
                                                 << 7U));
    if (((((IData)(vlTOPp->spdv24__DOT__U1__DOT__l10OO1I0)
           | (IData)(vlTOPp->spdv24__DOT__U1__DOT__l1O1Ol0O))
          | ((IData)(vlTOPp->spdv24__DOT__U1__DOT__lOI111I1)
             & (IData)(vlTOPp->spdv24__DOT__U1__DOT__O100O11l)))
         | ((IData)(vlTOPp->spdv24__DOT__U1__DOT__I000lO00)
            & (IData)(vlTOPp->spdv24__DOT__U1__DOT__l1OllI0I)))) {
        vlTOPp->spdv24__DOT__U1__DOT__l1l1O100 = vlTOPp->spdv24__DOT__U1__DOT__I00lIO1l;
        vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0 = (4U
                                                  | (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0));
    } else {
        if (((IData)(vlTOPp->spdv24__DOT__U1__DOT__lOI111I1)
             | (IData)(vlTOPp->spdv24__DOT__U1__DOT__l1OllI0I))) {
            vlTOPp->spdv24__DOT__U1__DOT__l1l1O100
                = vlTOPp->spdv24__DOT__U1__DOT__IIl1O10O;
            vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0
                = (2U | (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0));
        } else {
            if (((IData)(vlTOPp->spdv24__DOT__U1__DOT__I000lO00)
                 | (IData)(vlTOPp->spdv24__DOT__U1__DOT__O100O11l))) {
                vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0
                    = (1U | (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0));
                vlTOPp->spdv24__DOT__U1__DOT__l1l1O100 = 0U;
                vlTOPp->spdv24__DOT__U1__DOT__l1l1O100
                    = ((0x7fffffU & vlTOPp->spdv24__DOT__U1__DOT__l1l1O100)
                       | ((IData)(vlTOPp->spdv24__DOT__U1__DOT__lO011100)
                          << 0x17U));
            } else {
                if (vlTOPp->spdv24__DOT__U1__DOT__lO00I10I) {
                    vlTOPp->spdv24__DOT__U1__DOT__OOIl0010
                        = (0x7fffU & vlTOPp->spdvAf_in);
                    while ((1U & (~ ((IData)(vlTOPp->spdv24__DOT__U1__DOT__OOIl0010)
                                     >> 0xfU)))) {
                        vlTOPp->spdv24__DOT__U1__DOT__OOIl0010
                            = (0xffffU & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__OOIl0010)
                                          << 1U));
                        vlTOPp->spdv24__DOT__U1__DOT__OIIO0OOl
                            = (0xffU & ((IData)(1U)
                                        + (IData)(vlTOPp->spdv24__DOT__U1__DOT__OIIO0OOl)));
                    }
                } else {
                    vlTOPp->spdv24__DOT__U1__DOT__OOIl0010
                        = (0x8000U | (0x7fffU & vlTOPp->spdvAf_in));
                }
                if (vlTOPp->spdv24__DOT__U1__DOT__IIIl11O1) {
                    vlTOPp->spdv24__DOT__U1__DOT__IOOl0lII
                        = (0x7fffU & vlTOPp->spdvBf_in);
                    while ((1U & (~ ((IData)(vlTOPp->spdv24__DOT__U1__DOT__IOOl0lII)
                                     >> 0xfU)))) {
                        vlTOPp->spdv24__DOT__U1__DOT__IOOl0lII
                            = (0xffffU & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__IOOl0lII)
                                          << 1U));
                        vlTOPp->spdv24__DOT__U1__DOT__l0III011
                            = (0xffU & ((IData)(1U)
                                        + (IData)(vlTOPp->spdv24__DOT__U1__DOT__l0III011)));
                    }
                } else {
                    vlTOPp->spdv24__DOT__U1__DOT__IOOl0lII
                        = (0x8000U | (0x7fffU & vlTOPp->spdvBf_in));
                }
                vlTOPp->spdv24__DOT__U1__DOT__II0IIO1O
                    = vlTOPp->spdv24__DOT__U1__DOT__OOIl0010;
                vlTOPp->spdv24__DOT__U1__DOT__O1lO00O0
                    = vlTOPp->spdv24__DOT__U1__DOT__IOOl0lII;
                vlTOPp->spdv24__DOT__U1__DOT__I0I0Il0O
                    = (0xfffeU & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__O1lO00O0)
                                  << 1U));
                vlTOPp->spdv24__DOT__U1__DOT__l110l11I
                    = (0x1ffU & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__I0I0Il0O)
                                 >> 6U));
                vlTOPp->spdv24__DOT__U1__DOT__IOOlIOOO
                    = (0x200U | (IData)(vlTOPp->spdv24__DOT__U1__DOT__l110l11I));
                vlTOPp->spdv24__DOT__U1__DOT__IO00O1O1
                    = (0x1ffU & VL_DIV_III(32, (IData)(0x40000U),
                                           ((IData)(1U)
                                            + (IData)(vlTOPp->spdv24__DOT__U1__DOT__IOOlIOOO))));
                vlTOPp->spdv24__DOT__U1__DOT__OOI10OIO
                    = (0x1ffffffU & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__IO00O1O1)
                                     * (IData)(vlTOPp->spdv24__DOT__U1__DOT__II0IIO1O)));
                vlTOPp->spdv24__DOT__U1__DOT__l0IO1lOO
                    = (1U & (vlTOPp->spdv24__DOT__U1__DOT__OOI10OIO
                             >> 0x18U));
                vlTOPp->spdv24__DOT__U1__DOT__O00OI010
                    = (0x1ffffffU & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__I0I0Il0O)
                                     * (IData)(vlTOPp->spdv24__DOT__U1__DOT__IO00O1O1)));
                vlTOPp->spdv24__DOT__U1__DOT__IOIlOO00
                    = (0x1ffffU & (~ vlTOPp->spdv24__DOT__U1__DOT__O00OI010));
                vlTOPp->spdv24__DOT__U1__DOT__O101OOOO
                    = (0xfffffffU & ((0x3fffU & (vlTOPp->spdv24__DOT__U1__DOT__OOI10OIO
                                                 >> 0xbU))
                                     * (0x3fffU & (vlTOPp->spdv24__DOT__U1__DOT__IOIlOO00
                                                   >> 3U))));
                vlTOPp->spdv24__DOT__U1__DOT__O010OOO1
                    = (0x3fffU & (vlTOPp->spdv24__DOT__U1__DOT__O101OOOO
                                  >> 0xeU));
                vlTOPp->spdv24__DOT__U1__DOT__O1I10I10
                    = (0x1fffffU & (vlTOPp->spdv24__DOT__U1__DOT__OOI10OIO
                                    >> 4U));
                vlTOPp->spdv24__DOT__U1__DOT__l101O0Ol
                    = (0x1fffffU & (vlTOPp->spdv24__DOT__U1__DOT__O1I10I10
                                    + vlTOPp->spdv24__DOT__U1__DOT__O010OOO1));
                vlTOPp->spdv24__DOT__U1__DOT__O0O0IIII
                    = (0xffffffU & ((0xfffU & (vlTOPp->spdv24__DOT__U1__DOT__OOI10OIO
                                               >> 0xdU))
                                    * (0xfffU & (vlTOPp->spdv24__DOT__U1__DOT__IOIlOO00
                                                 >> 5U))));
                vlTOPp->spdv24__DOT__U1__DOT__l0101100
                    = (0xfffU & (vlTOPp->spdv24__DOT__U1__DOT__O0O0IIII
                                 >> 0xcU));
                vlTOPp->spdv24__DOT__U1__DOT__II11llO0
                    = (0x7ffffU & (vlTOPp->spdv24__DOT__U1__DOT__OOI10OIO
                                   >> 6U));
                vlTOPp->spdv24__DOT__U1__DOT__Ol1O10O0
                    = (0x7ffffU & (vlTOPp->spdv24__DOT__U1__DOT__l101O0Ol
                                   >> 2U));
                vlTOPp->spdv24__DOT__U1__DOT__O1l11OIO
                    = (0x3ffU & ((0x1fU & (vlTOPp->spdv24__DOT__U1__DOT__IOIlOO00
                                           >> 0xcU))
                                 * (0x1fU & (vlTOPp->spdv24__DOT__U1__DOT__IOIlOO00
                                             >> 0xcU))));
                vlTOPp->spdv24__DOT__U1__DOT__Il101Il1
                    = (0x1fU & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__O1l11OIO)
                                >> 5U));
                vlTOPp->spdv24__DOT__U1__DOT__IOll10OO
                    = (0x3ffU & ((0x1fU & (vlTOPp->spdv24__DOT__U1__DOT__Ol1O10O0
                                           >> 0xeU))
                                 * (IData)(vlTOPp->spdv24__DOT__U1__DOT__Il101Il1)));
                vlTOPp->spdv24__DOT__U1__DOT__O0l0O011
                    = (0x7ffffU & (vlTOPp->spdv24__DOT__U1__DOT__Ol1O10O0
                                   + (0x1fU & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__IOll10OO)
                                               >> 5U))));
                vlTOPp->spdv24__DOT__U1__DOT__OOO01OO1
                    = (1U & (vlTOPp->spdv24__DOT__U1__DOT__O0l0O011
                             >> 0x12U));
                vlTOPp->spdv24__DOT__U1__DOT__O0O1011O
                    = ((IData)(vlTOPp->spdv24__DOT__U1__DOT__OOO01OO1)
                        ? vlTOPp->spdv24__DOT__U1__DOT__O0l0O011
                        : (0x7fffeU & (vlTOPp->spdv24__DOT__U1__DOT__O0l0O011
                                       << 1U)));
                vlTOPp->spdv24__DOT__U1__DOT__I110OIOO
                    = (1U & (IData)(vlTOPp->spdv24__DOT__U1__DOT__l0OOOIll));
                vlTOPp->spdv24__DOT__U1__DOT__O0OOIl0l
                    = (3U & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__I110OIOO)
                             * (IData)(vlTOPp->spdv24__DOT__U1__DOT__I110OIOO)));
                vlTOPp->spdv24__DOT__U1__DOT__lI0I111I
                    = (1U & (IData)(vlTOPp->spdv24__DOT__U1__DOT__O0OOIl0l));
                vlTOPp->spdv24__DOT__U1__DOT__O10I0O00
                    = (1U & vlTOPp->spdv24__DOT__U1__DOT__O0O1011O);
                vlTOPp->spdv24__DOT__U1__DOT__lI100I0I
                    = vlTOPp->spdv24__DOT__U1__DOT__O0O1011O;
                vlTOPp->spdv24__DOT__U1__DOT__I10l01Il
                    = (1U & (vlTOPp->spdv24__DOT__U1__DOT__lI100I0I
                             >> 0x12U));
                vlTOPp->spdv24__DOT__U1__DOT__O1O0011O
                    = ((IData)(vlTOPp->spdv24__DOT__U1__DOT__I10l01Il)
                        ? vlTOPp->spdv24__DOT__U1__DOT__lI100I0I
                        : (0x7fffeU & (vlTOPp->spdv24__DOT__U1__DOT__lI100I0I
                                       << 1U)));
                vlTOPp->spdv24__DOT__U1__DOT__IIOI0lOO
                    = (0x7ffffU & ((IData)(8U) + vlTOPp->spdv24__DOT__U1__DOT__O0O1011O));
                vlTOPp->spdv24__DOT__U1__DOT__O10110O1
                    = (VL_ULL(0x1ffffffff) & VL_DIV_QQQ(33,
                                                        ((QData)((IData)(vlTOPp->spdv24__DOT__U1__DOT__OOIl0010))
                                                         << 0x11U), (QData)((IData)(vlTOPp->spdv24__DOT__U1__DOT__IOOl0lII))));
                vlTOPp->spdv24__DOT__U1__DOT__O011IOO0
                    = (0xffffU & (IData)((VL_ULL(0x1ffffffff)
                                          & VL_MODDIV_QQQ(33,
                                                          ((QData)((IData)(vlTOPp->spdv24__DOT__U1__DOT__OOIl0010))
                                                           << 0x11U), (QData)((IData)(vlTOPp->spdv24__DOT__U1__DOT__IOOl0lII))))));
                vlTOPp->spdv24__DOT__U1__DOT__IOO1O01O
                    = (0x3ffU & ((IData)(0x7fU) + (
                                                   (((IData)(
                                                             (VL_ULL(0x1ffffffff)
                                                              & VL_EXTENDS_QI(33,9, (IData)(vlTOPp->spdv24__DOT__U1__DOT__lO101111))))
                                                     - (IData)(
                                                               (VL_ULL(0x1ffffffff)
                                                                & VL_EXTENDS_QI(33,9, (IData)(vlTOPp->spdv24__DOT__U1__DOT__OIIO0OOl)))))
                                                    + (IData)(
                                                              (VL_ULL(0x1ffffffff)
                                                               & VL_EXTENDS_QI(33,2, (IData)(vlTOPp->spdv24__DOT__U1__DOT__lO00I10I)))))
                                                   -
                                                   (((IData)(
                                                             (VL_ULL(0x1ffffffff)
                                                              & VL_EXTENDS_QI(33,9, (IData)(vlTOPp->spdv24__DOT__U1__DOT__lI00O00I))))
                                                     - (IData)(
                                                               (VL_ULL(0x1ffffffff)
                                                                & VL_EXTENDS_QI(33,9, (IData)(vlTOPp->spdv24__DOT__U1__DOT__l0III011)))))
                                                    + (IData)(
                                                              (VL_ULL(0x1ffffffff)
                                                               & VL_EXTENDS_QI(33,2, (IData)(vlTOPp->spdv24__DOT__U1__DOT__IIIl11O1))))))));
                vlTOPp->spdv24__DOT__U1__DOT__O10101O1
                    = (0x3ffU & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__IOO1O01O)
                                 - (IData)(1U)));
                vlTOPp->spdv24__DOT__U1__DOT__lO001Ol0
                    = (0xffffU & ((1U & (IData)((vlTOPp->spdv24__DOT__U1__DOT__O10110O1
                                                 >> 0x11U)))
                                   ? (IData)((vlTOPp->spdv24__DOT__U1__DOT__O10110O1
                                              >> 2U))
                                   : (IData)((vlTOPp->spdv24__DOT__U1__DOT__O10110O1
                                              >> 1U))));
                vlTOPp->spdv24__DOT__U1__DOT__I11IO1I1
                    = (3U & ((1U & (IData)((vlTOPp->spdv24__DOT__U1__DOT__O10110O1
                                            >> 0x11U)))
                              ? (IData)((vlTOPp->spdv24__DOT__U1__DOT__O10110O1
                                         >> 1U)) : (IData)(vlTOPp->spdv24__DOT__U1__DOT__O10110O1)));
                vlTOPp->spdv24__DOT__U1__DOT__l10OO10O
                    = ((1U & (IData)((vlTOPp->spdv24__DOT__U1__DOT__O10110O1
                                      >> 0x11U))) ? (IData)(vlTOPp->spdv24__DOT__U1__DOT__IOO1O01O)
                        : (IData)(vlTOPp->spdv24__DOT__U1__DOT__O10101O1));
                vlTOPp->spdv24__DOT__U1__DOT__I101O11O
                    = (1U & ((0U == (IData)(vlTOPp->spdv24__DOT__U1__DOT__O011IOO0))
                              ? 0U : 1U));
                vlTOPp->spdv24__DOT__U1__DOT__Ol01O010 = 0U;
                if ((VL_GTES_III(1,32,32, 0U, VL_EXTENDS_II(32,10, (IData)(vlTOPp->spdv24__DOT__U1__DOT__l10OO10O)))
                     | VL_GTS_III(1,32,32, 0U, VL_EXTENDS_II(32,10, (IData)(vlTOPp->spdv24__DOT__U1__DOT__l10OO10O))))) {
                    vlTOPp->spdv24__DOT__U1__DOT__OO0lIO1O
                        = (0x3ffU & (((IData)(1U) - (IData)(vlTOPp->spdv24__DOT__U1__DOT__l10OO10O))
                                     + (IData)(vlTOPp->spdv24__DOT__U1__DOT__Ol01O010)));
                    vlTOPp->spdv24__DOT__U1__DOT____Vconcswap1
                        = (0xffffU & (((0x1fU >= (IData)(vlTOPp->spdv24__DOT__U1__DOT__OO0lIO1O))
                                        ? (((IData)(vlTOPp->spdv24__DOT__U1__DOT__lO001Ol0)
                                            << 0x10U)
                                           >> (IData)(vlTOPp->spdv24__DOT__U1__DOT__OO0lIO1O))
                                        : 0U) >> 0x10U));
                    vlTOPp->spdv24__DOT__U1__DOT____Vconcswap2
                        = (0xffffU & ((0x1fU >= (IData)(vlTOPp->spdv24__DOT__U1__DOT__OO0lIO1O))
                                       ? (((IData)(vlTOPp->spdv24__DOT__U1__DOT__lO001Ol0)
                                           << 0x10U)
                                          >> (IData)(vlTOPp->spdv24__DOT__U1__DOT__OO0lIO1O))
                                       : 0U));
                    vlTOPp->spdv24__DOT__U1__DOT__lO001Ol0
                        = vlTOPp->spdv24__DOT__U1__DOT____Vconcswap1;
                    vlTOPp->spdv24__DOT__U1__DOT__IOIlII10
                        = vlTOPp->spdv24__DOT__U1__DOT____Vconcswap2;
                    if (VL_LTS_III(1,32,32, 0x10U,
                                   VL_EXTENDS_II(32,10, (IData)(vlTOPp->spdv24__DOT__U1__DOT__OO0lIO1O)))) {
                        vlTOPp->spdv24__DOT__U1__DOT__I101O11O = 1U;
                    }
                    vlTOPp->spdv24__DOT__U1__DOT__I11IO1I1
                        = ((1U & (IData)(vlTOPp->spdv24__DOT__U1__DOT__I11IO1I1))
                           | (2U & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__lO001Ol0)
                                    << 1U)));
                    vlTOPp->spdv24__DOT__U1__DOT__I11IO1I1
                        = ((2U & (IData)(vlTOPp->spdv24__DOT__U1__DOT__I11IO1I1))
                           | (1U & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__IOIlII10)
                                    >> 0xfU)));
                    if ((0U != (0x7fffU & (IData)(vlTOPp->spdv24__DOT__U1__DOT__IOIlII10)))) {
                        vlTOPp->spdv24__DOT__U1__DOT__I101O11O = 1U;
                    }
                }
                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__I101O11O
                    = vlTOPp->spdv24__DOT__U1__DOT__I101O11O;
                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__O011IOO0
                    = (1U & (IData)(vlTOPp->spdv24__DOT__U1__DOT__I11IO1I1));
                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__I0O0O0OO
                    = (1U & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__I11IO1I1)
                             >> 1U));
                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__lO011100
                    = vlTOPp->spdv24__DOT__U1__DOT__lO011100;
                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__rnd = 0U;
                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                    = (0xeU & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout));
                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                    = ((0xdU & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout))
                       | (((IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__O011IOO0)
                           | (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__I101O11O))
                          << 1U));
                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                    = (0xbU & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout));
                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                    = (7U & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout));
                if ((VL_ULL(0) < VL_TIME_Q())) {
                    if ((4U & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__rnd))) {
                        if (VL_UNLIKELY((2U & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__rnd)))) {
                            VL_WRITEF("error! illegal rounding mode.\n\n");
                            VL_WRITEF("a : %b\n",24,
                                      (0xffffffU & vlTOPp->spdvAf_in));
                            VL_WRITEF("rnd : %b\n",
                                      3,vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__rnd);
                        } else {
                            if ((1U & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__rnd))) {
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = ((0xeU & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout))
                                       | ((IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__O011IOO0)
                                          | (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__I101O11O)));
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = (4U | (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout));
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = (8U | (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout));
                            } else {
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = ((0xeU & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout))
                                       | (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__O011IOO0));
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = (4U | (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout));
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = (7U & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout));
                            }
                        }
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__rnd))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__rnd))) {
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = ((0xeU & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout))
                                       | ((IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__lO011100)
                                          & ((IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__O011IOO0)
                                             | (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__I101O11O))));
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = ((0xbU & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout))
                                       | ((IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__lO011100)
                                          << 2U));
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = ((7U & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout))
                                       | ((IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__lO011100)
                                          << 3U));
                            } else {
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = ((0xeU & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout))
                                       | ((~ (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__lO011100))
                                          & ((IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__O011IOO0)
                                             | (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__I101O11O))));
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = ((0xbU & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout))
                                       | (4U & ((~ (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__lO011100))
                                                << 2U)));
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = ((7U & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout))
                                       | (8U & ((~ (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__lO011100))
                                                << 3U)));
                            }
                        } else {
                            if ((1U & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__rnd))) {
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = (0xeU & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout));
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = (0xbU & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout));
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = (7U & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout));
                            } else {
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = ((0xeU & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout))
                                       | ((IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__O011IOO0)
                                          & ((IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__I0O0O0OO)
                                             | (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__I101O11O))));
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = (4U | (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout));
                                vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout
                                    = (7U & (IData)(vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout));
                            }
                        }
                    }
                }
                vlTOPp->spdv24__DOT__U1__DOT__OO000O0O
                    = vlTOPp->__Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout;
                vlTOPp->spdv24__DOT__U1__DOT__I0OI1lO0
                    = (0xffffU & ((1U & (IData)(vlTOPp->spdv24__DOT__U1__DOT__OO000O0O))
                                   ? ((IData)(1U) + (IData)(vlTOPp->spdv24__DOT__U1__DOT__lO001Ol0))
                                   : (IData)(vlTOPp->spdv24__DOT__U1__DOT__lO001Ol0)));
                if ((VL_LTES_III(1,32,32, 0xffU, VL_EXTENDS_II(32,10, (IData)(vlTOPp->spdv24__DOT__U1__DOT__l10OO10O)))
                     & VL_LTES_III(1,32,32, 0U, VL_EXTENDS_II(32,10, (IData)(vlTOPp->spdv24__DOT__U1__DOT__l10OO10O))))) {
                    vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0
                        = (0x10U | (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0));
                    vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0
                        = (0x20U | (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0));
                    if ((4U & (IData)(vlTOPp->spdv24__DOT__U1__DOT__OO000O0O))) {
                        vlTOPp->spdv24__DOT__U1__DOT__l11Illl0
                            = (0xffffU & vlTOPp->spdv24__DOT__U1__DOT__IIl1O10O);
                        vlTOPp->spdv24__DOT__U1__DOT__IO10IOO1 = 0xffU;
                        vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0
                            = (2U | (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0));
                    } else {
                        vlTOPp->spdv24__DOT__U1__DOT__l11Illl0 = 0xffffU;
                        vlTOPp->spdv24__DOT__U1__DOT__IO10IOO1 = 0xfeU;
                    }
                } else {
                    if (VL_GTES_III(1,32,32, 0U, VL_EXTENDS_II(32,10, (IData)(vlTOPp->spdv24__DOT__U1__DOT__l10OO10O)))) {
                        vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0
                            = (8U | (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0));
                        vlTOPp->spdv24__DOT__U1__DOT__l11Illl0
                            = vlTOPp->spdv24__DOT__U1__DOT__I0OI1lO0;
                        vlTOPp->spdv24__DOT__U1__DOT__IO10IOO1
                            = (1U & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__I0OI1lO0)
                                     >> 0xfU));
                    } else {
                        vlTOPp->spdv24__DOT__U1__DOT__l11Illl0
                            = vlTOPp->spdv24__DOT__U1__DOT__I0OI1lO0;
                        vlTOPp->spdv24__DOT__U1__DOT__IO10IOO1
                            = vlTOPp->spdv24__DOT__U1__DOT__l10OO10O;
                    }
                }
                if (((0U == (0x7fffU & (IData)(vlTOPp->spdv24__DOT__U1__DOT__l11Illl0)))
                     & (0U == (0xffU & (IData)(vlTOPp->spdv24__DOT__U1__DOT__IO10IOO1))))) {
                    vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0
                        = (1U | (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0));
                }
                vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0
                    = ((0xdfU & (IData)(vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0))
                       | (0x20U & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__O00OO1I0)
                                   | ((IData)(vlTOPp->spdv24__DOT__U1__DOT__OO000O0O)
                                      << 4U))));
                vlTOPp->spdv24__DOT__U1__DOT__l1l1O100
                    = (((IData)(vlTOPp->spdv24__DOT__U1__DOT__lO011100)
                        << 0x17U) | ((0x7f8000U & ((IData)(vlTOPp->spdv24__DOT__U1__DOT__IO10IOO1)
                                                   << 0xfU))
                                     | (0x7fffU & (IData)(vlTOPp->spdv24__DOT__U1__DOT__l11Illl0))));
            }
        }
    }
    vlTOPp->spdvRf_out = ((0x1000000U & vlTOPp->spdvRf_out)
                          | vlTOPp->spdv24__DOT__U1__DOT__l1l1O100);
}

void Vspdv24::_eval(Vspdv24__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspdv24::_eval\n"); );
    Vspdv24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vspdv24::_eval_initial(Vspdv24__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspdv24::_eval_initial\n"); );
    Vspdv24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vspdv24::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspdv24::final\n"); );
    // Variables
    Vspdv24__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vspdv24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vspdv24::_eval_settle(Vspdv24__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspdv24::_eval_settle\n"); );
    Vspdv24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vspdv24::_change_request(Vspdv24__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspdv24::_change_request\n"); );
    Vspdv24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vspdv24::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspdv24::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((spdvAf_in & 0xfe000000U))) {
        Verilated::overWidthError("spdvAf_in");}
    if (VL_UNLIKELY((spdvBf_in & 0xfe000000U))) {
        Verilated::overWidthError("spdvBf_in");}
}
#endif // VL_DEBUG

void Vspdv24::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspdv24::_ctor_var_reset\n"); );
    // Body
    spdvAf_in = VL_RAND_RESET_I(25);
    spdvBf_in = VL_RAND_RESET_I(25);
    spdvRf_out = VL_RAND_RESET_I(25);
    spdv24__DOT__U1__DOT__l1l1O100 = VL_RAND_RESET_I(24);
    spdv24__DOT__U1__DOT__lO101111 = VL_RAND_RESET_I(8);
    spdv24__DOT__U1__DOT__lI00O00I = VL_RAND_RESET_I(8);
    spdv24__DOT__U1__DOT__IOO1O01O = VL_RAND_RESET_I(10);
    spdv24__DOT__U1__DOT__O10101O1 = VL_RAND_RESET_I(10);
    spdv24__DOT__U1__DOT__IO10IOO1 = VL_RAND_RESET_I(10);
    spdv24__DOT__U1__DOT__l10OO10O = VL_RAND_RESET_I(10);
    spdv24__DOT__U1__DOT__OOIl0010 = VL_RAND_RESET_I(16);
    spdv24__DOT__U1__DOT__IOOl0lII = VL_RAND_RESET_I(16);
    spdv24__DOT__U1__DOT__l11Illl0 = VL_RAND_RESET_I(16);
    spdv24__DOT__U1__DOT__lO001Ol0 = VL_RAND_RESET_I(16);
    spdv24__DOT__U1__DOT__I0OI1lO0 = VL_RAND_RESET_I(16);
    spdv24__DOT__U1__DOT__IOIlII10 = VL_RAND_RESET_I(16);
    spdv24__DOT__U1__DOT__O10110O1 = VL_RAND_RESET_Q(33);
    spdv24__DOT__U1__DOT__O011IOO0 = VL_RAND_RESET_I(16);
    spdv24__DOT__U1__DOT__I101O11O = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__lO011100 = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__I11IO1I1 = VL_RAND_RESET_I(2);
    spdv24__DOT__U1__DOT__OO000O0O = VL_RAND_RESET_I(4);
    spdv24__DOT__U1__DOT__O00OO1I0 = VL_RAND_RESET_I(8);
    spdv24__DOT__U1__DOT__IIl1O10O = VL_RAND_RESET_I(24);
    spdv24__DOT__U1__DOT__I00lIO1l = VL_RAND_RESET_I(24);
    spdv24__DOT__U1__DOT__lOI111I1 = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__O100O11l = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__l10OO1I0 = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__l1O1Ol0O = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__I000lO00 = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__l1OllI0I = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__lO00I10I = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__IIIl11O1 = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__O00O1Ol1 = VL_RAND_RESET_I(15);
    spdv24__DOT__U1__DOT__II01O1O0 = VL_RAND_RESET_I(15);
    spdv24__DOT__U1__DOT__OIIO0OOl = VL_RAND_RESET_I(8);
    spdv24__DOT__U1__DOT__l0III011 = VL_RAND_RESET_I(8);
    spdv24__DOT__U1__DOT__OO0lIO1O = VL_RAND_RESET_I(10);
    spdv24__DOT__U1__DOT__II0IIO1O = VL_RAND_RESET_I(16);
    spdv24__DOT__U1__DOT__O1lO00O0 = VL_RAND_RESET_I(16);
    spdv24__DOT__U1__DOT__I0I0Il0O = VL_RAND_RESET_I(16);
    spdv24__DOT__U1__DOT__l110l11I = VL_RAND_RESET_I(9);
    spdv24__DOT__U1__DOT__IO00O1O1 = VL_RAND_RESET_I(9);
    spdv24__DOT__U1__DOT__IOOlIOOO = VL_RAND_RESET_I(10);
    spdv24__DOT__U1__DOT__OOI10OIO = VL_RAND_RESET_I(25);
    spdv24__DOT__U1__DOT__l0IO1lOO = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__O00OI010 = VL_RAND_RESET_I(25);
    spdv24__DOT__U1__DOT__IOIlOO00 = VL_RAND_RESET_I(17);
    spdv24__DOT__U1__DOT__O0O0IIII = VL_RAND_RESET_I(24);
    spdv24__DOT__U1__DOT__II11llO0 = VL_RAND_RESET_I(19);
    spdv24__DOT__U1__DOT__l0101100 = VL_RAND_RESET_I(19);
    spdv24__DOT__U1__DOT__Ol1O10O0 = VL_RAND_RESET_I(19);
    spdv24__DOT__U1__DOT__O1l11OIO = VL_RAND_RESET_I(10);
    spdv24__DOT__U1__DOT__Il101Il1 = VL_RAND_RESET_I(5);
    spdv24__DOT__U1__DOT__IOll10OO = VL_RAND_RESET_I(10);
    spdv24__DOT__U1__DOT__O0l0O011 = VL_RAND_RESET_I(19);
    spdv24__DOT__U1__DOT__OOO01OO1 = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__O0O1011O = VL_RAND_RESET_I(19);
    spdv24__DOT__U1__DOT__lI100I0I = VL_RAND_RESET_I(19);
    spdv24__DOT__U1__DOT__I10l01Il = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__O1O0011O = VL_RAND_RESET_I(19);
    spdv24__DOT__U1__DOT__IIOI0lOO = VL_RAND_RESET_I(19);
    spdv24__DOT__U1__DOT__Ol01O010 = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__I110OIOO = VL_RAND_RESET_I(2);
    spdv24__DOT__U1__DOT__O0OOIl0l = VL_RAND_RESET_I(2);
    spdv24__DOT__U1__DOT__lI0I111I = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__O10I0O00 = VL_RAND_RESET_I(1);
    spdv24__DOT__U1__DOT__l0OOOIll = VL_RAND_RESET_I(5);
    spdv24__DOT__U1__DOT__O101OOOO = VL_RAND_RESET_I(28);
    spdv24__DOT__U1__DOT__O010OOO1 = VL_RAND_RESET_I(21);
    spdv24__DOT__U1__DOT__O1I10I10 = VL_RAND_RESET_I(21);
    spdv24__DOT__U1__DOT__l101O0Ol = VL_RAND_RESET_I(21);
    spdv24__DOT__U1__DOT____Vconcswap1 = VL_RAND_RESET_I(16);
    spdv24__DOT__U1__DOT____Vconcswap2 = VL_RAND_RESET_I(16);
    __Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__Vfuncout = VL_RAND_RESET_I(4);
    __Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__rnd = VL_RAND_RESET_I(3);
    __Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__lO011100 = VL_RAND_RESET_I(1);
    __Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__I0O0O0OO = VL_RAND_RESET_I(1);
    __Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__O011IOO0 = VL_RAND_RESET_I(1);
    __Vfunc_spdv24__DOT__U1__DOT__lOOOII1l__0__I101O11O = VL_RAND_RESET_I(1);
}
