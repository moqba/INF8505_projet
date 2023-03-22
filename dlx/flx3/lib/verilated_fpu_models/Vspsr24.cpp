// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vspsr24.h for the primary calling header

#include "Vspsr24.h"
#include "Vspsr24__Syms.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(Vspsr24) {
    Vspsr24__Syms* __restrict vlSymsp = __VlSymsp = new Vspsr24__Syms(this, name());
    Vspsr24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values

    // Reset structure values
    _ctor_var_reset();
}

void Vspsr24::__Vconfigure(Vspsr24__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vspsr24::~Vspsr24() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vspsr24::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vspsr24::eval\n"); );
    Vspsr24__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vspsr24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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

void Vspsr24::_eval_initial_loop(Vspsr24__Syms* __restrict vlSymsp) {
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

VL_INLINE_OPT void Vspsr24::_combo__TOP__1(Vspsr24__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspsr24::_combo__TOP__1\n"); );
    Vspsr24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at /global/apps/syn_2019.03-SP2/dw/sim_ver/DW_fp_sqrt.v:243
    vlTOPp->spsr24__DOT__U1__DOT__EA = (0xffU & (vlTOPp->spsrAf_in
                                                 >> 0xfU));
    vlTOPp->spsr24__DOT__U1__DOT__SIGA = (0x7fffU & vlTOPp->spsrAf_in);
    vlTOPp->spsr24__DOT__U1__DOT__status_reg = 0U;
    vlTOPp->spsr24__DOT__U1__DOT__MAX_EXP_A = (0xffU
                                               == (IData)(vlTOPp->spsr24__DOT__U1__DOT__EA));
    vlTOPp->spsr24__DOT__U1__DOT__InfSig_A = (0U == (IData)(vlTOPp->spsr24__DOT__U1__DOT__SIGA));
    vlTOPp->spsr24__DOT__U1__DOT__LZ_INA = 0U;
    vlTOPp->spsr24__DOT__U1__DOT__Zero_A = ((0U == (IData)(vlTOPp->spsr24__DOT__U1__DOT__EA))
                                            & (0U == (IData)(vlTOPp->spsr24__DOT__U1__DOT__SIGA)));
    vlTOPp->spsr24__DOT__U1__DOT__Denorm_A = ((0U == (IData)(vlTOPp->spsr24__DOT__U1__DOT__EA))
                                              & (0U
                                                 != (IData)(vlTOPp->spsr24__DOT__U1__DOT__SIGA)));
    vlTOPp->spsr24__DOT__U1__DOT__NaN_Reg = 0x7f8001U;
    vlTOPp->spsr24__DOT__U1__DOT__Inf_Reg = 0x7f8000U;
    vlTOPp->spsr24__DOT__U1__DOT__MA = ((IData)(vlTOPp->spsr24__DOT__U1__DOT__Denorm_A)
                                         ? (0x7fffU
                                            & vlTOPp->spsrAf_in)
                                         : (0x8000U
                                            | (0x7fffU
                                               & vlTOPp->spsrAf_in)));
    vlTOPp->spsr24__DOT__U1__DOT__NegInput = (1U &
                                              ((~ (IData)(vlTOPp->spsr24__DOT__U1__DOT__Zero_A))
                                               & (vlTOPp->spsrAf_in
                                                  >> 0x17U)));
    if ((((IData)(vlTOPp->spsr24__DOT__U1__DOT__MAX_EXP_A)
          & (~ (IData)(vlTOPp->spsr24__DOT__U1__DOT__InfSig_A)))
         | (IData)(vlTOPp->spsr24__DOT__U1__DOT__NegInput))) {
        vlTOPp->spsr24__DOT__U1__DOT__status_reg =
            (4U | (IData)(vlTOPp->spsr24__DOT__U1__DOT__status_reg));
        vlTOPp->spsr24__DOT__U1__DOT__z_reg = vlTOPp->spsr24__DOT__U1__DOT__NaN_Reg;
    } else {
        if (vlTOPp->spsr24__DOT__U1__DOT__MAX_EXP_A) {
            if (vlTOPp->spsr24__DOT__U1__DOT__Zero_A) {
                vlTOPp->spsr24__DOT__U1__DOT__status_reg
                    = (4U | (IData)(vlTOPp->spsr24__DOT__U1__DOT__status_reg));
                vlTOPp->spsr24__DOT__U1__DOT__z_reg
                    = vlTOPp->spsr24__DOT__U1__DOT__NaN_Reg;
            } else {
                vlTOPp->spsr24__DOT__U1__DOT__status_reg
                    = (2U | (IData)(vlTOPp->spsr24__DOT__U1__DOT__status_reg));
                vlTOPp->spsr24__DOT__U1__DOT__z_reg
                    = vlTOPp->spsr24__DOT__U1__DOT__Inf_Reg;
            }
        } else {
            if (vlTOPp->spsr24__DOT__U1__DOT__Zero_A) {
                vlTOPp->spsr24__DOT__U1__DOT__status_reg
                    = (1U | (IData)(vlTOPp->spsr24__DOT__U1__DOT__status_reg));
                vlTOPp->spsr24__DOT__U1__DOT__z_reg
                    = (0x800000U & vlTOPp->spsrAf_in);
            } else {
                if (vlTOPp->spsr24__DOT__U1__DOT__Denorm_A) {
                    while ((1U & (~ ((IData)(vlTOPp->spsr24__DOT__U1__DOT__MA)
                                     >> 0xfU)))) {
                        vlTOPp->spsr24__DOT__U1__DOT__MA
                            = (0xffffU & ((IData)(vlTOPp->spsr24__DOT__U1__DOT__MA)
                                          << 1U));
                        vlTOPp->spsr24__DOT__U1__DOT__LZ_INA
                            = (0x3ffU & ((IData)(1U)
                                         + (IData)(vlTOPp->spsr24__DOT__U1__DOT__LZ_INA)));
                    }
                }
                vlTOPp->spsr24__DOT__U1__DOT__EM =
                    (0x3ffU & ((((IData)(vlTOPp->spsr24__DOT__U1__DOT__EA)
                                 - (IData)(vlTOPp->spsr24__DOT__U1__DOT__LZ_INA))
                                + (IData)(vlTOPp->spsr24__DOT__U1__DOT__Denorm_A))
                               - (IData)(0x7fU)));
                vlTOPp->spsr24__DOT__U1__DOT__EZ =
                    (0x7ffU & VL_EXTENDS_II(11,9, (0x1ffU
                                                   & ((IData)(vlTOPp->spsr24__DOT__U1__DOT__EM)
                                                      >> 1U))));
                vlTOPp->spsr24__DOT__U1__DOT__EZ =
                    (0x7ffU & ((IData)(0x7fU) + VL_EXTENDS_II(11,11, (IData)(vlTOPp->spsr24__DOT__U1__DOT__EZ))));
                vlTOPp->spsr24__DOT__U1__DOT__Sqrt_in
                    = ((1U & (IData)(vlTOPp->spsr24__DOT__U1__DOT__EM))
                        ? ((QData)((IData)(vlTOPp->spsr24__DOT__U1__DOT__MA))
                           << 0x12U) : ((QData)((IData)(vlTOPp->spsr24__DOT__U1__DOT__MA))
                                        << 0x11U));
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A
                    = vlTOPp->spsr24__DOT__U1__DOT__Sqrt_in;
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v = 0U;
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (0x10000U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0xffffU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (0x8000U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x17fffU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (0x4000U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1bfffU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (0x2000U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1dfffU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (0x1000U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1efffU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (0x800U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1f7ffU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (0x400U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1fbffU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (0x200U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1fdffU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (0x100U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1feffU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (0x80U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1ff7fU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (0x40U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1ffbfU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (0x20U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1ffdfU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (0x10U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1ffefU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (8U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1fff7U & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (4U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1fffbU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (2U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1fffdU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                    = (1U | vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                if (((VL_ULL(0x7ffffffff) & ((QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))
                                             * (QData)((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v))))
                     > vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A)) {
                    vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v
                        = (0x1fffeU & vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v);
                }
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__Vfuncout
                    = vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v;
                vlTOPp->spsr24__DOT__U1__DOT__MZ = vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__Vfuncout;
                vlTOPp->spsr24__DOT__U1__DOT__Square
                    = (VL_ULL(0x3ffffffff) & ((QData)((IData)(vlTOPp->spsr24__DOT__U1__DOT__MZ))
                                              * (QData)((IData)(vlTOPp->spsr24__DOT__U1__DOT__MZ))));
                vlTOPp->spsr24__DOT__U1__DOT__REMAINDER
                    = (0x3ffffU & ((IData)(vlTOPp->spsr24__DOT__U1__DOT__Sqrt_in)
                                   - (IData)(vlTOPp->spsr24__DOT__U1__DOT__Square)));
                vlTOPp->spsr24__DOT__U1__DOT__Sticky
                    = (1U & ((0U == vlTOPp->spsr24__DOT__U1__DOT__REMAINDER)
                              ? 0U : 1U));
                if (((0U == VL_EXTENDS_II(32,11, (IData)(vlTOPp->spsr24__DOT__U1__DOT__EZ)))
                     | VL_GTS_III(1,32,32, 0U, VL_EXTENDS_II(32,11, (IData)(vlTOPp->spsr24__DOT__U1__DOT__EZ))))) {
                    vlTOPp->spsr24__DOT__U1__DOT__Sticky
                        = (1U & ((IData)(vlTOPp->spsr24__DOT__U1__DOT__Sticky)
                                 | vlTOPp->spsr24__DOT__U1__DOT__MZ));
                    vlTOPp->spsr24__DOT__U1__DOT__MZ
                        = (0x1ffffU & (vlTOPp->spsr24__DOT__U1__DOT__MZ
                                       >> 1U));
                }
                vlTOPp->spsr24__DOT__U1__DOT__Mantissa
                    = (0xffffU & (vlTOPp->spsr24__DOT__U1__DOT__MZ
                                  >> 1U));
                vlTOPp->spsr24__DOT__U1__DOT__Round_Bit
                    = (1U & vlTOPp->spsr24__DOT__U1__DOT__MZ);
                vlTOPp->spsr24__DOT__U1__DOT__Guard_Bit
                    = (1U & (vlTOPp->spsr24__DOT__U1__DOT__MZ
                             >> 1U));
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__stk
                    = vlTOPp->spsr24__DOT__U1__DOT__Sticky;
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__R
                    = vlTOPp->spsr24__DOT__U1__DOT__Round_Bit;
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__L
                    = vlTOPp->spsr24__DOT__U1__DOT__Guard_Bit;
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Sign = 0U;
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__rnd = 0U;
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                    = (0xeU & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout));
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                    = ((0xdU & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout))
                       | (((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__R)
                           | (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__stk))
                          << 1U));
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                    = (0xbU & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout));
                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                    = (7U & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout));
                if ((VL_ULL(0) < VL_TIME_Q())) {
                    if ((4U & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__rnd))) {
                        if (VL_UNLIKELY((2U & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__rnd)))) {
                            VL_WRITEF("Error! illegal rounding mode.\n\n");
                            VL_WRITEF("a : %b\n",24,
                                      (0xffffffU & vlTOPp->spsrAf_in));
                            VL_WRITEF("rnd : %b\n",
                                      3,vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__rnd);
                        } else {
                            if ((1U & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__rnd))) {
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = ((0xeU & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout))
                                       | ((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__R)
                                          | (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__stk)));
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = (4U | (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout));
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = (8U | (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout));
                            } else {
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = ((0xeU & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout))
                                       | (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__R));
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = (4U | (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout));
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = (7U & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout));
                            }
                        }
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__rnd))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__rnd))) {
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = ((0xeU & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout))
                                       | ((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Sign)
                                          & ((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__R)
                                             | (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__stk))));
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = ((0xbU & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout))
                                       | ((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Sign)
                                          << 2U));
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = ((7U & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout))
                                       | ((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Sign)
                                          << 3U));
                            } else {
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = ((0xeU & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout))
                                       | ((~ (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Sign))
                                          & ((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__R)
                                             | (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__stk))));
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = ((0xbU & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout))
                                       | (4U & ((~ (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Sign))
                                                << 2U)));
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = ((7U & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout))
                                       | (8U & ((~ (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Sign))
                                                << 3U)));
                            }
                        } else {
                            if ((1U & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__rnd))) {
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = (0xeU & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout));
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = (0xbU & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout));
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = (7U & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout));
                            } else {
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = ((0xeU & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout))
                                       | ((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__R)
                                          & ((IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__L)
                                             | (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__stk))));
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = (4U | (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout));
                                vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout
                                    = (7U & (IData)(vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout));
                            }
                        }
                    }
                }
                vlTOPp->spsr24__DOT__U1__DOT__RND_val
                    = vlTOPp->__Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout;
                vlTOPp->spsr24__DOT__U1__DOT__temp_mantissa
                    = (0x1ffffU & ((1U & (IData)(vlTOPp->spsr24__DOT__U1__DOT__RND_val))
                                    ? ((IData)(1U)
                                       + (IData)(vlTOPp->spsr24__DOT__U1__DOT__Mantissa))
                                    : (IData)(vlTOPp->spsr24__DOT__U1__DOT__Mantissa)));
                vlTOPp->spsr24__DOT__U1__DOT__Movf
                    = (1U & (vlTOPp->spsr24__DOT__U1__DOT__temp_mantissa
                             >> 0x10U));
                if (vlTOPp->spsr24__DOT__U1__DOT__Movf) {
                    vlTOPp->spsr24__DOT__U1__DOT__EZ
                        = (0x7ffU & ((IData)(1U) +
                                     VL_EXTENDS_II(11,11, (IData)(vlTOPp->spsr24__DOT__U1__DOT__EZ))));
                    vlTOPp->spsr24__DOT__U1__DOT__temp_mantissa
                        = (0x1ffffU & (vlTOPp->spsr24__DOT__U1__DOT__temp_mantissa
                                       >> 1U));
                }
                vlTOPp->spsr24__DOT__U1__DOT__Mantissa
                    = (0xffffU & vlTOPp->spsr24__DOT__U1__DOT__temp_mantissa);
                if ((0U == VL_EXTENDS_II(32,11, (IData)(vlTOPp->spsr24__DOT__U1__DOT__EZ)))) {
                    vlTOPp->spsr24__DOT__U1__DOT__status_reg
                        = (8U | (IData)(vlTOPp->spsr24__DOT__U1__DOT__status_reg));
                    if (((0U == (0x7fffU & (IData)(vlTOPp->spsr24__DOT__U1__DOT__Mantissa)))
                         & (0U == (0xffU & (IData)(vlTOPp->spsr24__DOT__U1__DOT__EZ))))) {
                        vlTOPp->spsr24__DOT__U1__DOT__status_reg
                            = (1U | (IData)(vlTOPp->spsr24__DOT__U1__DOT__status_reg));
                    }
                }
                vlTOPp->spsr24__DOT__U1__DOT__status_reg
                    = ((0xdfU & (IData)(vlTOPp->spsr24__DOT__U1__DOT__status_reg))
                       | (0x20U & ((IData)(vlTOPp->spsr24__DOT__U1__DOT__RND_val)
                                   << 4U)));
                if (VL_GTS_III(1,32,32, 0U, VL_EXTENDS_II(32,11, (IData)(vlTOPp->spsr24__DOT__U1__DOT__EZ)))) {
                    vlTOPp->spsr24__DOT__U1__DOT__EZ = 0U;
                }
                vlTOPp->spsr24__DOT__U1__DOT__z_reg
                    = ((0x7f8000U & ((IData)(vlTOPp->spsr24__DOT__U1__DOT__EZ)
                                     << 0xfU)) | (0x7fffU
                                                  & (IData)(vlTOPp->spsr24__DOT__U1__DOT__Mantissa)));
            }
        }
    }
    vlTOPp->spsrRf_out = ((0xff000000U & vlTOPp->spsrRf_out)
                          | vlTOPp->spsr24__DOT__U1__DOT__z_reg);
}

void Vspsr24::_eval(Vspsr24__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspsr24::_eval\n"); );
    Vspsr24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vspsr24::_eval_initial(Vspsr24__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspsr24::_eval_initial\n"); );
    Vspsr24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vspsr24::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspsr24::final\n"); );
    // Variables
    Vspsr24__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vspsr24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vspsr24::_eval_settle(Vspsr24__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspsr24::_eval_settle\n"); );
    Vspsr24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vspsr24::_change_request(Vspsr24__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspsr24::_change_request\n"); );
    Vspsr24* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vspsr24::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspsr24::_eval_debug_assertions\n"); );
}
#endif // VL_DEBUG

void Vspsr24::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vspsr24::_ctor_var_reset\n"); );
    // Body
    spsrAf_in = VL_RAND_RESET_I(32);
    spsrRf_out = VL_RAND_RESET_I(32);
    spsr24__DOT__U1__DOT__EA = VL_RAND_RESET_I(8);
    spsr24__DOT__U1__DOT__SIGA = VL_RAND_RESET_I(15);
    spsr24__DOT__U1__DOT__MAX_EXP_A = VL_RAND_RESET_I(1);
    spsr24__DOT__U1__DOT__InfSig_A = VL_RAND_RESET_I(1);
    spsr24__DOT__U1__DOT__Zero_A = VL_RAND_RESET_I(1);
    spsr24__DOT__U1__DOT__Denorm_A = VL_RAND_RESET_I(1);
    spsr24__DOT__U1__DOT__NaN_Reg = VL_RAND_RESET_I(24);
    spsr24__DOT__U1__DOT__Inf_Reg = VL_RAND_RESET_I(24);
    spsr24__DOT__U1__DOT__MA = VL_RAND_RESET_I(16);
    spsr24__DOT__U1__DOT__Sqrt_in = VL_RAND_RESET_Q(34);
    spsr24__DOT__U1__DOT__LZ_INA = VL_RAND_RESET_I(10);
    spsr24__DOT__U1__DOT__MZ = VL_RAND_RESET_I(17);
    spsr24__DOT__U1__DOT__Square = VL_RAND_RESET_Q(34);
    spsr24__DOT__U1__DOT__REMAINDER = VL_RAND_RESET_I(18);
    spsr24__DOT__U1__DOT__z_reg = VL_RAND_RESET_I(24);
    spsr24__DOT__U1__DOT__status_reg = VL_RAND_RESET_I(8);
    spsr24__DOT__U1__DOT__EZ = VL_RAND_RESET_I(11);
    spsr24__DOT__U1__DOT__EM = VL_RAND_RESET_I(10);
    spsr24__DOT__U1__DOT__Sticky = VL_RAND_RESET_I(1);
    spsr24__DOT__U1__DOT__Round_Bit = VL_RAND_RESET_I(1);
    spsr24__DOT__U1__DOT__Guard_Bit = VL_RAND_RESET_I(1);
    spsr24__DOT__U1__DOT__Mantissa = VL_RAND_RESET_I(16);
    spsr24__DOT__U1__DOT__RND_val = VL_RAND_RESET_I(4);
    spsr24__DOT__U1__DOT__temp_mantissa = VL_RAND_RESET_I(17);
    spsr24__DOT__U1__DOT__Movf = VL_RAND_RESET_I(1);
    spsr24__DOT__U1__DOT__NegInput = VL_RAND_RESET_I(1);
    __Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__Vfuncout = VL_RAND_RESET_I(17);
    __Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__A = VL_RAND_RESET_Q(34);
    __Vfunc_spsr24__DOT__U1__DOT__DWF_sqrt_uns__0__ROOT_v = VL_RAND_RESET_I(17);
    __Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Vfuncout = VL_RAND_RESET_I(4);
    __Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__rnd = VL_RAND_RESET_I(3);
    __Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__Sign = VL_RAND_RESET_I(1);
    __Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__L = VL_RAND_RESET_I(1);
    __Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__R = VL_RAND_RESET_I(1);
    __Vfunc_spsr24__DOT__U1__DOT__rnd_eval__1__stk = VL_RAND_RESET_I(1);
}
