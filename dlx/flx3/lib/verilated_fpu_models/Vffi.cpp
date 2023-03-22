// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vffi.h for the primary calling header

#include "Vffi.h"
#include "Vffi__Syms.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(Vffi) {
    Vffi__Syms* __restrict vlSymsp = __VlSymsp = new Vffi__Syms(this, name());
    Vffi* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values

    // Reset structure values
    _ctor_var_reset();
}

void Vffi::__Vconfigure(Vffi__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vffi::~Vffi() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vffi::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vffi::eval\n"); );
    Vffi__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vffi* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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

void Vffi::_eval_initial_loop(Vffi__Syms* __restrict vlSymsp) {
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

VL_INLINE_OPT void Vffi::_combo__TOP__1(Vffi__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vffi::_combo__TOP__1\n"); );
    Vffi* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    // Begin mtask footprint  all:
    VL_SIGW(__Vtemp3,95,0,3);
    VL_SIGW(__Vtemp7,95,0,3);
    VL_SIGW(__Vtemp43,95,0,3);
    VL_SIGW(__Vtemp44,95,0,3);
    // Body
    // ALWAYS at ../hdl/designware_vlog/ffi.v:35
    vlTOPp->ffi__DOT__ffiA = (0xffffffU & ((IData)(vlTOPp->ohe_selector_EX)
                                            ? vlTOPp->ffiA_in
                                            : 0U));
    // ALWAYS at /global/apps/syn_2019.03-SP2/dw/sim_ver/DW_fp_flt2i.v:225
    vlTOPp->ffi__DOT__dw_ffi__DOT__af = vlTOPp->ffi__DOT__ffiA;
    vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg = 0U;
    vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U] = 0U;
    vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U] = 0U;
    vlTOPp->ffi__DOT__dw_ffi__DOT__mi[2U] = 0U;
    vlTOPp->ffi__DOT__dw_ffi__DOT__exp = 0U;
    vlTOPp->ffi__DOT__dw_ffi__DOT__stk = 0U;
    vlTOPp->ffi__DOT__dw_ffi__DOT__eaf = (0xffU & (vlTOPp->ffi__DOT__dw_ffi__DOT__af
                                                   >> 0xfU));
    vlTOPp->ffi__DOT__dw_ffi__DOT__sig = (0x7fffU & vlTOPp->ffi__DOT__dw_ffi__DOT__af);
    vlTOPp->ffi__DOT__dw_ffi__DOT__inf_input = ((0xffU
                                                 == (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__eaf))
                                                & (0U
                                                   == (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__sig)));
    vlTOPp->ffi__DOT__dw_ffi__DOT__nan_input = ((0xffU
                                                 == (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__eaf))
                                                & (0U
                                                   != (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__sig)));
    vlTOPp->ffi__DOT__dw_ffi__DOT__denorm_input = (
                                                   (0U
                                                    == (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__eaf))
                                                   & (0U
                                                      != (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__sig)));
    vlTOPp->ffi__DOT__dw_ffi__DOT__zero_input = ((0U
                                                  == (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__eaf))
                                                 & (0U
                                                    == (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__sig)));
    if (vlTOPp->ffi__DOT__dw_ffi__DOT__inf_input) {
        vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg =
            (4U | (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg));
    } else {
        if (vlTOPp->ffi__DOT__dw_ffi__DOT__nan_input) {
            vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg
                = (4U | (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg));
        } else {
            if (vlTOPp->ffi__DOT__dw_ffi__DOT__zero_input) {
                vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg
                    = (1U | (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg));
            } else {
                vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U]
                    = (2U | vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U]);
                vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                    = ((0x3ffffU & vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U])
                       | (0xfffc0000U & (vlTOPp->ffi__DOT__dw_ffi__DOT__af
                                         << 0x12U)));
                vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U]
                    = ((0xfffffffeU & vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U])
                       | (1U & (vlTOPp->ffi__DOT__dw_ffi__DOT__af
                                >> 0xeU)));
                if ((0x7fU <= (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__eaf))) {
                    vlTOPp->ffi__DOT__dw_ffi__DOT__exp
                        = (0xffU & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__eaf)
                                    - (IData)(0x7fU)));
                    while ((0U != (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__exp))) {
                        if ((1U & (~ (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[2U]
                                      >> 1U)))) {
                            VL_SHIFTL_WWI(66,66,32, __Vtemp3, vlTOPp->ffi__DOT__dw_ffi__DOT__mi, 1U);
                            vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                = __Vtemp3[0U];
                            vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U]
                                = __Vtemp3[1U];
                            vlTOPp->ffi__DOT__dw_ffi__DOT__mi[2U]
                                = (3U & __Vtemp3[2U]);
                        }
                        vlTOPp->ffi__DOT__dw_ffi__DOT__exp
                            = (0xffU & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__exp)
                                        - (IData)(1U)));
                    }
                } else {
                    vlTOPp->ffi__DOT__dw_ffi__DOT__exp
                        = (0xffU & ((IData)(0x7fU)
                                    - (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__eaf)));
                    while ((0U != (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__exp))) {
                        vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                            = (1U & vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]);
                        VL_SHIFTR_WWI(66,66,32, __Vtemp7, vlTOPp->ffi__DOT__dw_ffi__DOT__mi, 1U);
                        vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                            = __Vtemp7[0U];
                        vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U]
                            = __Vtemp7[1U];
                        vlTOPp->ffi__DOT__dw_ffi__DOT__mi[2U]
                            = (3U & __Vtemp7[2U]);
                        vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                            = ((0xfffffffeU & vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U])
                               | (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                        | vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U])));
                        vlTOPp->ffi__DOT__dw_ffi__DOT__exp
                            = (0xffU & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__exp)
                                        - (IData)(1U)));
                    }
                }
                if ((2U & vlTOPp->ffi__DOT__dw_ffi__DOT__mi[2U])) {
                    vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg
                        = (0x40U | (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg
                        = (0x20U | (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg));
                } else {
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                 >> 0x1fU));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x1eU)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x1dU)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x1cU)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x1bU)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x1aU)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x19U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x18U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x17U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x16U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x15U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x14U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x13U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x12U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x11U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0x10U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0xfU)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0xeU)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0xdU)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0xcU)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0xbU)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 0xaU)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 9U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 8U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 7U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 6U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 5U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 4U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 3U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 2U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                    >> 1U)));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__stk
                        = (1U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                 | vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]));
                    vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                        = ((0x7fffffffU & vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U])
                           | (0x80000000U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__stk)
                                             << 0x1fU)));
                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__stk
                        = (1U & (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                                 >> 0x1fU));
                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__R
                        = (1U & vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U]);
                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__L
                        = (1U & (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U]
                                 >> 1U));
                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Sign
                        = (1U & (vlTOPp->ffi__DOT__dw_ffi__DOT__af
                                 >> 0x17U));
                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__rnd = 1U;
                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                        = (0xeU & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout));
                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                        = ((0xdU & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout))
                           | (((IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__R)
                               | (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__stk))
                              << 1U));
                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                        = (0xbU & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout));
                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                        = (7U & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout));
                    if ((VL_ULL(0) < VL_TIME_Q())) {
                        if ((4U & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__rnd))) {
                            if (VL_UNLIKELY((2U & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__rnd)))) {
                                VL_WRITEF("Error! illegal rounding mode.\n\n");
                                VL_WRITEF("a : %b\n",
                                          24,vlTOPp->ffi__DOT__ffiA);
                                VL_WRITEF("rnd : %b\n",
                                          3,vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__rnd);
                            } else {
                                if ((1U & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__rnd))) {
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__R)
                                              | (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__stk)));
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = (4U | (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout));
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = (8U | (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout));
                                } else {
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout))
                                           | (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__R));
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = (4U | (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout));
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = (7U & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout));
                                }
                            }
                        } else {
                            if ((2U & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__rnd))) {
                                if ((1U & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__rnd))) {
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Sign)
                                              & ((IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__R)
                                                 | (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__stk))));
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = ((0xbU & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Sign)
                                              << 2U));
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = ((7U & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Sign)
                                              << 3U));
                                } else {
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout))
                                           | ((~ (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Sign))
                                              & ((IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__R)
                                                 | (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__stk))));
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = ((0xbU & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout))
                                           | (4U &
                                              ((~ (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Sign))
                                               << 2U)));
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = ((7U & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout))
                                           | (8U &
                                              ((~ (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Sign))
                                               << 3U)));
                                }
                            } else {
                                if ((1U & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__rnd))) {
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = (0xeU & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout));
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = (0xbU & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout));
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = (7U & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout));
                                } else {
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = ((0xeU & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout))
                                           | ((IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__R)
                                              & ((IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__L)
                                                 | (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__stk))));
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = (4U | (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout));
                                    vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout
                                        = (7U & (IData)(vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout));
                                }
                            }
                        }
                    }
                    vlTOPp->ffi__DOT__dw_ffi__DOT__rnd_val
                        = vlTOPp->__Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout;
                    if ((1U & (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__rnd_val))) {
                        __Vtemp43[0U] = 0U;
                        __Vtemp43[1U] = 2U;
                        __Vtemp43[2U] = 0U;
                        VL_ADD_W(3, __Vtemp44, __Vtemp43, vlTOPp->ffi__DOT__dw_ffi__DOT__mi);
                        vlTOPp->ffi__DOT__dw_ffi__DOT__mi[0U]
                            = __Vtemp44[0U];
                        vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U]
                            = __Vtemp44[1U];
                        vlTOPp->ffi__DOT__dw_ffi__DOT__mi[2U]
                            = (3U & __Vtemp44[2U]);
                    }
                    vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg
                        = ((0xdfU & (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg))
                           | (0x20U & ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg)
                                       | ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__rnd_val)
                                          << 4U))));
                    if ((2U & vlTOPp->ffi__DOT__dw_ffi__DOT__mi[2U])) {
                        vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg
                            = (0x40U | (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg));
                        vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg
                            = (0x20U | (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg));
                    } else {
                        if ((0U == ((vlTOPp->ffi__DOT__dw_ffi__DOT__mi[2U]
                                     << 0x1fU) | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U]
                                                  >> 1U)))) {
                            vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg
                                = (1U | (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg));
                            if (vlTOPp->ffi__DOT__dw_ffi__DOT__denorm_input) {
                                vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg
                                    = (8U | (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg));
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->ffi__DOT__dw_ffi__DOT__maxneg = 0U;
    vlTOPp->ffi__DOT__dw_ffi__DOT__maxneg = (0x80000000U
                                             | vlTOPp->ffi__DOT__dw_ffi__DOT__maxneg);
    vlTOPp->ffi__DOT__dw_ffi__DOT__maxpos = 0xffffffffU;
    vlTOPp->ffi__DOT__dw_ffi__DOT__maxpos = (0x7fffffffU
                                             & vlTOPp->ffi__DOT__dw_ffi__DOT__maxpos);
    if ((((vlTOPp->ffi__DOT__dw_ffi__DOT__af >> 0x17U)
          & (((vlTOPp->ffi__DOT__dw_ffi__DOT__mi[2U]
               << 0x1fU) | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U]
                            >> 1U)) > vlTOPp->ffi__DOT__dw_ffi__DOT__maxneg))
         | ((~ (vlTOPp->ffi__DOT__dw_ffi__DOT__af >> 0x17U))
            & (((vlTOPp->ffi__DOT__dw_ffi__DOT__mi[2U]
                 << 0x1fU) | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U]
                              >> 1U)) > vlTOPp->ffi__DOT__dw_ffi__DOT__maxpos)))) {
        vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg =
            (0x40U | (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg));
        vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg =
            (0x20U | (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg));
    }
    vlTOPp->ffi__DOT__dw_ffi__DOT__z_reg = ((0x800000U
                                             & vlTOPp->ffi__DOT__dw_ffi__DOT__af)
                                             ? ((1U
                                                 & (((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg)
                                                     >> 6U)
                                                    | ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg)
                                                       >> 2U)))
                                                 ?
                                                VL_NEGATE_I(vlTOPp->ffi__DOT__dw_ffi__DOT__maxneg)
                                                 :
                                                ((1U
                                                  & (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg))
                                                  ? 0U
                                                  :
                                                 VL_NEGATE_I(
                                                             ((vlTOPp->ffi__DOT__dw_ffi__DOT__mi[2U]
                                                               << 0x1fU)
                                                              | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U]
                                                                 >> 1U)))))
                                             : ((1U
                                                 & (((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg)
                                                     >> 6U)
                                                    | ((IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg)
                                                       >> 2U)))
                                                 ? vlTOPp->ffi__DOT__dw_ffi__DOT__maxpos
                                                 :
                                                ((1U
                                                  & (IData)(vlTOPp->ffi__DOT__dw_ffi__DOT__status_reg))
                                                  ? 0U
                                                  :
                                                 ((vlTOPp->ffi__DOT__dw_ffi__DOT__mi[2U]
                                                   << 0x1fU)
                                                  | (vlTOPp->ffi__DOT__dw_ffi__DOT__mi[1U]
                                                     >> 1U)))));
    vlTOPp->ffiC_out = vlTOPp->ffi__DOT__dw_ffi__DOT__z_reg;
}

void Vffi::_eval(Vffi__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vffi::_eval\n"); );
    Vffi* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vffi::_eval_initial(Vffi__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vffi::_eval_initial\n"); );
    Vffi* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vffi::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vffi::final\n"); );
    // Variables
    Vffi__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vffi* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vffi::_eval_settle(Vffi__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vffi::_eval_settle\n"); );
    Vffi* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vffi::_change_request(Vffi__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vffi::_change_request\n"); );
    Vffi* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vffi::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vffi::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((ohe_selector_EX & 0xfeU))) {
        Verilated::overWidthError("ohe_selector_EX");}
}
#endif // VL_DEBUG

void Vffi::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vffi::_ctor_var_reset\n"); );
    // Body
    ohe_selector_EX = VL_RAND_RESET_I(1);
    ffiA_in = VL_RAND_RESET_I(32);
    ffiC_out = VL_RAND_RESET_I(32);
    ffi__DOT__ffiA = VL_RAND_RESET_I(24);
    ffi__DOT__dw_ffi__DOT__af = VL_RAND_RESET_I(24);
    ffi__DOT__dw_ffi__DOT__status_reg = VL_RAND_RESET_I(8);
    ffi__DOT__dw_ffi__DOT__z_reg = VL_RAND_RESET_I(32);
    ffi__DOT__dw_ffi__DOT__eaf = VL_RAND_RESET_I(8);
    VL_RAND_RESET_W(66,ffi__DOT__dw_ffi__DOT__mi);
    ffi__DOT__dw_ffi__DOT__exp = VL_RAND_RESET_I(8);
    ffi__DOT__dw_ffi__DOT__stk = VL_RAND_RESET_I(1);
    ffi__DOT__dw_ffi__DOT__rnd_val = VL_RAND_RESET_I(4);
    ffi__DOT__dw_ffi__DOT__maxneg = VL_RAND_RESET_I(32);
    ffi__DOT__dw_ffi__DOT__maxpos = VL_RAND_RESET_I(32);
    ffi__DOT__dw_ffi__DOT__sig = VL_RAND_RESET_I(15);
    ffi__DOT__dw_ffi__DOT__inf_input = VL_RAND_RESET_I(1);
    ffi__DOT__dw_ffi__DOT__denorm_input = VL_RAND_RESET_I(1);
    ffi__DOT__dw_ffi__DOT__nan_input = VL_RAND_RESET_I(1);
    ffi__DOT__dw_ffi__DOT__zero_input = VL_RAND_RESET_I(1);
    __Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Vfuncout = VL_RAND_RESET_I(4);
    __Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__rnd = VL_RAND_RESET_I(3);
    __Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__Sign = VL_RAND_RESET_I(1);
    __Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__L = VL_RAND_RESET_I(1);
    __Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__R = VL_RAND_RESET_I(1);
    __Vfunc_ffi__DOT__dw_ffi__DOT__rnd_eval__0__stk = VL_RAND_RESET_I(1);
}
