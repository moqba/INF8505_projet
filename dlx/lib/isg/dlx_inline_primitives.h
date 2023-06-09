
// File generated by pdg version Q-2020.03#7e5ed72dc8#200717
// Copyright 2014-2020 Synopsys, Inc. All rights reserved.
// pdg -P -Iisg +wisg -Iruntime/include -DCHESS_CXX_ATTRIBUTES -D__tct_patch__=300 -D__checkers__ dlx

#ifndef DLX_INLINE_PRIMITIVES_H
#define DLX_INLINE_PRIMITIVES_H

#ifdef __checkers__
#include "Mdl_dlx.h"

#include "checkers_errors.h"
#endif // __checkers__

#include <sstream>

#include <iostream>
#include <cstdlib>
#ifndef PDG_NATIVE_HANDLE_ERR
#define PDG_NATIVE_HANDLE_ERR(msg, loc) \
  std::cerr << "An error occurred: " << msg << " at: " << loc << '\n'; \
  std::cerr << "Exiting..\n"; \
  exit(1);
#endif

#ifndef PDG_NATIVE_HANDLE_WRN
#define PDG_NATIVE_HANDLE_WRN(msg, loc) \
  std::cerr << "Warning: " << msg << " at: " << loc << '\n';
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"
#endif

namespace dlx_primitive {

    const int controller_module_id = 0;
    const int div_module_id = 1;
    const int banks_module_id = 2;

    inline dlx_primitive::w32 add(dlx_primitive::w32 a, dlx_primitive::w32 b, dlx_primitive::uint1& co) {
        VBit<33, false> aa = VBit<33, false>(VBit<32, false>(a.val));
        VBit<33, false> bb = VBit<33, false>(VBit<32, false>(b.val));
        VBit<33, false> rr = (aa + bb);
        co = rr.extract(0x20u);
        return dlx_primitive::w32(VBit<32, false>(rr.extract(0x1Fu, 0x0u)));
    }

    inline dlx_primitive::w32 add(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return (a.val + b.val);
    }

    inline dlx_primitive::w32 sub(dlx_primitive::w32 a, dlx_primitive::w32 b, dlx_primitive::uint1& co) {
        VBit<33, false> aa = VBit<33, false>(VBit<32, false>(a.val));
        VBit<33, false> bb = VBit<33, false>(VBit<32, false>(b.val));
        VBit<33, false> rr = (aa - bb);
        co = rr.extract(0x20u);
        return dlx_primitive::w32(VBit<32, false>(rr.extract(0x1Fu, 0x0u)));
    }

    inline dlx_primitive::w32 addx(dlx_primitive::w32 a, dlx_primitive::w32 b, dlx_primitive::uint1 ci, dlx_primitive::uint1& co) {
        VBit<33, false> aa = VBit<33, false>(VBit<32, false>(a.val));
        VBit<33, false> bb = VBit<33, false>(VBit<32, false>(b.val));
        VBit<33, false> rr = ((aa + bb) + VBit<33, false>(ci.val));
        co = rr.extract(0x20u);
        return dlx_primitive::w32(VBit<32, false>(rr.extract(0x1Fu, 0x0u)));
    }

    inline dlx_primitive::w32 subx(dlx_primitive::w32 a, dlx_primitive::w32 b, dlx_primitive::uint1 ci, dlx_primitive::uint1& co) {
        VBit<33, false> aa = VBit<33, false>(VBit<32, false>(a.val));
        VBit<33, false> bb = VBit<33, false>(VBit<32, false>(b.val));
        VBit<33, false> rr = ((aa - bb) - VBit<33, false>(ci.val));
        co = rr.extract(0x20u);
        return dlx_primitive::w32(VBit<32, false>(rr.extract(0x1Fu, 0x0u)));
    }

    inline dlx_primitive::w32 band(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return (a.val & b.val);
    }

    inline dlx_primitive::w32 bor(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return (a.val | b.val);
    }

    inline dlx_primitive::w32 bxor(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return (a.val ^ b.val);
    }

    inline dlx_primitive::w32 sge(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return dlx_primitive::w32((a.val >= b.val));
    }

    inline dlx_primitive::w32 sgt(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return dlx_primitive::w32((a.val > b.val));
    }

    inline dlx_primitive::w32 sle(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return dlx_primitive::w32((a.val <= b.val));
    }

    inline dlx_primitive::w32 slt(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return dlx_primitive::w32((a.val < b.val));
    }

    inline dlx_primitive::w32 seq(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return dlx_primitive::w32((a.val == b.val));
    }

    inline dlx_primitive::w32 sne(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return dlx_primitive::w32((a.val != b.val));
    }

    inline dlx_primitive::w32 sgeu(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return dlx_primitive::w32((VBit<32, false>(a.val) >= VBit<32, false>(b.val)));
    }

    inline dlx_primitive::w32 sgtu(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return dlx_primitive::w32((VBit<32, false>(a.val) > VBit<32, false>(b.val)));
    }

    inline dlx_primitive::w32 sleu(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return dlx_primitive::w32((VBit<32, false>(a.val) <= VBit<32, false>(b.val)));
    }

    inline dlx_primitive::w32 sltu(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return dlx_primitive::w32((VBit<32, false>(a.val) < VBit<32, false>(b.val)));
    }

    inline dlx_primitive::w32 sra(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return (a.val >> VBit<5, false>(VBit<5, true>(b.val.extract(0x4u, 0x0u))));
    }

    inline dlx_primitive::w32 sll(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return dlx_primitive::w32((VBit<32, false>(a.val) << VBit<5, false>(VBit<5, true>(b.val.extract(0x4u, 0x0u)))));
    }

    inline dlx_primitive::w32 srl(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return dlx_primitive::w32((VBit<32, false>(a.val) >> VBit<5, false>(VBit<5, true>(b.val.extract(0x4u, 0x0u)))));
    }

    inline dlx_primitive::w32 xtd(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        VBit<5, false> f = VBit<5, false>((VBit<32, true>(0x20) - b.val));
        return ((a.val << f) >> f);
    }

    inline dlx_primitive::w32 mul(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return dlx_primitive::w32((a.val * b.val));
    }

    inline void lmulss(dlx_primitive::w32 a, dlx_primitive::w32 b, dlx_primitive::w32& lo, dlx_primitive::w32& hi) {
        VBit<64, true> p = (a.val * b.val);
        lo = VBit<32, true>(p.extract(0x1Fu, 0x0u));
        hi = VBit<32, true>(p.extract(0x3Fu, 0x20u));
    }

    inline void lmulsu(dlx_primitive::w32 a, dlx_primitive::w32 b, dlx_primitive::w32& lo, dlx_primitive::w32& hi) {
        VBit<64, true> p = (a.val * VBit<32, false>(b.val));
        lo = VBit<32, true>(p.extract(0x1Fu, 0x0u));
        hi = VBit<32, true>(p.extract(0x3Fu, 0x20u));
    }

    inline void lmuluu(dlx_primitive::w32 a, dlx_primitive::w32 b, dlx_primitive::w32& lo, dlx_primitive::w32& hi) {
        VBit<64, true> p = VBit<64, true>((VBit<32, false>(a.val) * VBit<32, false>(b.val)));
        lo = VBit<32, true>(p.extract(0x1Fu, 0x0u));
        hi = VBit<32, true>(p.extract(0x3Fu, 0x20u));
    }

    inline dlx_primitive::w32 clb(dlx_primitive::w32 a) {
        VBit<6, false> r{VBitInitializeTag{}};
        dlx_primitive::w32 t{VBitInitializeTag{}};
        if ((a.val < VBit<32, true>(0x0))) {
            t = ~a.val;
        } else {
            t = a.val;
        }
        dlx_primitive::w32 tmp = t.val;
        if ((VBit<32, true>(tmp.val.extract(0x1Fu, 0x0u)) == VBit<32, true>(0x0))) {
            r = VBit<6, false>(0x20u);
        } else if ((VBit<31, true>(tmp.val.extract(0x1Fu, 0x1u)) == VBit<31, true>(0x0))) {
            r = VBit<6, false>(0x1Fu);
        } else if ((VBit<30, true>(tmp.val.extract(0x1Fu, 0x2u)) == VBit<30, true>(0x0))) {
            r = VBit<6, false>(0x1Eu);
        } else if ((VBit<29, true>(tmp.val.extract(0x1Fu, 0x3u)) == VBit<29, true>(0x0))) {
            r = VBit<6, false>(0x1Du);
        } else if ((VBit<28, true>(tmp.val.extract(0x1Fu, 0x4u)) == VBit<28, true>(0x0))) {
            r = VBit<6, false>(0x1Cu);
        } else if ((VBit<27, true>(tmp.val.extract(0x1Fu, 0x5u)) == VBit<27, true>(0x0))) {
            r = VBit<6, false>(0x1Bu);
        } else if ((VBit<26, true>(tmp.val.extract(0x1Fu, 0x6u)) == VBit<26, true>(0x0))) {
            r = VBit<6, false>(0x1Au);
        } else if ((VBit<25, true>(tmp.val.extract(0x1Fu, 0x7u)) == VBit<25, true>(0x0))) {
            r = VBit<6, false>(0x19u);
        } else if ((VBit<24, true>(tmp.val.extract(0x1Fu, 0x8u)) == VBit<24, true>(0x0))) {
            r = VBit<6, false>(0x18u);
        } else if ((VBit<23, true>(tmp.val.extract(0x1Fu, 0x9u)) == VBit<23, true>(0x0))) {
            r = VBit<6, false>(0x17u);
        } else if ((VBit<22, true>(tmp.val.extract(0x1Fu, 0xAu)) == VBit<22, true>(0x0))) {
            r = VBit<6, false>(0x16u);
        } else if ((VBit<21, true>(tmp.val.extract(0x1Fu, 0xBu)) == VBit<21, true>(0x0))) {
            r = VBit<6, false>(0x15u);
        } else if ((VBit<20, true>(tmp.val.extract(0x1Fu, 0xCu)) == VBit<20, true>(0x0))) {
            r = VBit<6, false>(0x14u);
        } else if ((VBit<19, true>(tmp.val.extract(0x1Fu, 0xDu)) == VBit<19, true>(0x0))) {
            r = VBit<6, false>(0x13u);
        } else if ((VBit<18, true>(tmp.val.extract(0x1Fu, 0xEu)) == VBit<18, true>(0x0))) {
            r = VBit<6, false>(0x12u);
        } else if ((VBit<17, true>(tmp.val.extract(0x1Fu, 0xFu)) == VBit<17, true>(0x0))) {
            r = VBit<6, false>(0x11u);
        } else if ((VBit<16, true>(tmp.val.extract(0x1Fu, 0x10u)) == VBit<16, true>(0x0))) {
            r = VBit<6, false>(0x10u);
        } else if ((VBit<15, true>(tmp.val.extract(0x1Fu, 0x11u)) == VBit<15, true>(0x0))) {
            r = VBit<6, false>(0xFu);
        } else if ((VBit<14, true>(tmp.val.extract(0x1Fu, 0x12u)) == VBit<14, true>(0x0))) {
            r = VBit<6, false>(0xEu);
        } else if ((VBit<13, true>(tmp.val.extract(0x1Fu, 0x13u)) == VBit<13, true>(0x0))) {
            r = VBit<6, false>(0xDu);
        } else if ((VBit<12, true>(tmp.val.extract(0x1Fu, 0x14u)) == VBit<12, true>(0x0))) {
            r = VBit<6, false>(0xCu);
        } else if ((VBit<11, true>(tmp.val.extract(0x1Fu, 0x15u)) == VBit<11, true>(0x0))) {
            r = VBit<6, false>(0xBu);
        } else if ((VBit<10, true>(tmp.val.extract(0x1Fu, 0x16u)) == VBit<10, true>(0x0))) {
            r = VBit<6, false>(0xAu);
        } else if ((VBit<9, true>(tmp.val.extract(0x1Fu, 0x17u)) == VBit<9, true>(0x0))) {
            r = VBit<6, false>(0x9u);
        } else if ((VBit<8, true>(tmp.val.extract(0x1Fu, 0x18u)) == VBit<8, true>(0x0))) {
            r = VBit<6, false>(0x8u);
        } else if ((VBit<7, true>(tmp.val.extract(0x1Fu, 0x19u)) == VBit<7, true>(0x0))) {
            r = VBit<6, false>(0x7u);
        } else if ((VBit<6, true>(tmp.val.extract(0x1Fu, 0x1Au)) == VBit<6, true>(0x0))) {
            r = VBit<6, false>(0x6u);
        } else if ((VBit<5, true>(tmp.val.extract(0x1Fu, 0x1Bu)) == VBit<5, true>(0x0))) {
            r = VBit<6, false>(0x5u);
        } else if ((VBit<4, true>(tmp.val.extract(0x1Fu, 0x1Cu)) == VBit<4, true>(0x0))) {
            r = VBit<6, false>(0x4u);
        } else if ((VBit<3, true>(tmp.val.extract(0x1Fu, 0x1Du)) == VBit<3, true>(0x0))) {
            r = VBit<6, false>(0x3u);
        } else if ((VBit<2, true>(tmp.val.extract(0x1Fu, 0x1Eu)) == VBit<2, true>(0x0))) {
            r = VBit<6, false>(0x2u);
        } else {
            r = VBit<6, false>(0x1u);
        }
        return dlx_primitive::w32(r);
    }

    inline dlx_primitive::w32 extend_sign(dlx_primitive::w08 a) {
        return dlx_primitive::w32(a.val);
    }

    inline dlx_primitive::w32 extend_zero(dlx_primitive::w08 a) {
        return dlx_primitive::w32(VBit<8, false>(a.val));
    }

    inline dlx_primitive::w32 extend_sign(dlx_primitive::w16 a) {
        return dlx_primitive::w32(a.val);
    }

    inline dlx_primitive::w32 extend_zero(dlx_primitive::w16 a) {
        return dlx_primitive::w32(VBit<16, false>(a.val));
    }

    inline dlx_primitive::w08 extract_w08(dlx_primitive::w32 a) {
        return VBit<8, true>(a.val.extract(0x7u, 0x0u));
    }

    inline dlx_primitive::w16 extract_w16(dlx_primitive::w32 a) {
        return VBit<16, true>(a.val.extract(0xFu, 0x0u));
    }

    inline bool eqz(dlx_primitive::w32 a) {
        return (a.val == VBit<32, true>(0x0));
    }

    inline bool nez(dlx_primitive::w32 a) {
        return (a.val != VBit<32, true>(0x0));
    }

    inline void nop() {
    }

    inline dlx_primitive::w32 pcadd(dlx_primitive::w32 a, dlx_primitive::w32 b) {
        return (a.val + b.val);
    }

    inline dlx_primitive::uint2 incr(dlx_primitive::uint2 a) {
        return (a.val + VBit<2, false>(0x1u));
    }

    inline void divide(dlx_primitive::w32 numerator, dlx_primitive::w32 denominator, dlx_primitive::w32& quotient, dlx_primitive::w32& remainder) {
        quotient = dlx_primitive::w32((VBit<32, false>(numerator.val) / VBit<32, false>(denominator.val))).val;
        remainder = dlx_primitive::w32((VBit<32, false>(numerator.val) % VBit<32, false>(denominator.val))).val;
    }

    inline VBit<64, false> div_step(VBit<64, false> pa, VBit<32, false> b) {
        VBit<64, false> new_pa = (pa << VBit<1, false>(0x1u));
        VBit<33, false> diff = (VBit<33, false>(VBit<32, false>(new_pa.extract(0x3Fu, 0x20u))) - VBit<33, false>(b));
        if ((diff.extract(0x20u) == VBit<1, false>(0x0u))) {
            new_pa.deposit(VBit<32, false>(diff), 0x3Fu, 0x20u);
            new_pa.deposit(VBit<1, false>(0x1u), 0x0u);
        }
        return new_pa;
    }

    inline dlx_primitive::w32 div_clb(dlx_primitive::w32 a) {
        VBit<5, false> r{VBitInitializeTag{}};
        dlx_primitive::w32 tmp = a.val;
        if ((VBit<32, true>(tmp.val.extract(0x1Fu, 0x0u)) == VBit<32, true>(0x0))) {
            r = VBit<5, false>(0x1Fu);
        } else if ((VBit<31, true>(tmp.val.extract(0x1Fu, 0x1u)) == VBit<31, true>(0x0))) {
            r = VBit<5, false>(0x1Eu);
        } else if ((VBit<30, true>(tmp.val.extract(0x1Fu, 0x2u)) == VBit<30, true>(0x0))) {
            r = VBit<5, false>(0x1Du);
        } else if ((VBit<29, true>(tmp.val.extract(0x1Fu, 0x3u)) == VBit<29, true>(0x0))) {
            r = VBit<5, false>(0x1Cu);
        } else if ((VBit<28, true>(tmp.val.extract(0x1Fu, 0x4u)) == VBit<28, true>(0x0))) {
            r = VBit<5, false>(0x1Bu);
        } else if ((VBit<27, true>(tmp.val.extract(0x1Fu, 0x5u)) == VBit<27, true>(0x0))) {
            r = VBit<5, false>(0x1Au);
        } else if ((VBit<26, true>(tmp.val.extract(0x1Fu, 0x6u)) == VBit<26, true>(0x0))) {
            r = VBit<5, false>(0x19u);
        } else if ((VBit<25, true>(tmp.val.extract(0x1Fu, 0x7u)) == VBit<25, true>(0x0))) {
            r = VBit<5, false>(0x18u);
        } else if ((VBit<24, true>(tmp.val.extract(0x1Fu, 0x8u)) == VBit<24, true>(0x0))) {
            r = VBit<5, false>(0x17u);
        } else if ((VBit<23, true>(tmp.val.extract(0x1Fu, 0x9u)) == VBit<23, true>(0x0))) {
            r = VBit<5, false>(0x16u);
        } else if ((VBit<22, true>(tmp.val.extract(0x1Fu, 0xAu)) == VBit<22, true>(0x0))) {
            r = VBit<5, false>(0x15u);
        } else if ((VBit<21, true>(tmp.val.extract(0x1Fu, 0xBu)) == VBit<21, true>(0x0))) {
            r = VBit<5, false>(0x14u);
        } else if ((VBit<20, true>(tmp.val.extract(0x1Fu, 0xCu)) == VBit<20, true>(0x0))) {
            r = VBit<5, false>(0x13u);
        } else if ((VBit<19, true>(tmp.val.extract(0x1Fu, 0xDu)) == VBit<19, true>(0x0))) {
            r = VBit<5, false>(0x12u);
        } else if ((VBit<18, true>(tmp.val.extract(0x1Fu, 0xEu)) == VBit<18, true>(0x0))) {
            r = VBit<5, false>(0x11u);
        } else if ((VBit<17, true>(tmp.val.extract(0x1Fu, 0xFu)) == VBit<17, true>(0x0))) {
            r = VBit<5, false>(0x10u);
        } else if ((VBit<16, true>(tmp.val.extract(0x1Fu, 0x10u)) == VBit<16, true>(0x0))) {
            r = VBit<5, false>(0xFu);
        } else if ((VBit<15, true>(tmp.val.extract(0x1Fu, 0x11u)) == VBit<15, true>(0x0))) {
            r = VBit<5, false>(0xEu);
        } else if ((VBit<14, true>(tmp.val.extract(0x1Fu, 0x12u)) == VBit<14, true>(0x0))) {
            r = VBit<5, false>(0xDu);
        } else if ((VBit<13, true>(tmp.val.extract(0x1Fu, 0x13u)) == VBit<13, true>(0x0))) {
            r = VBit<5, false>(0xCu);
        } else if ((VBit<12, true>(tmp.val.extract(0x1Fu, 0x14u)) == VBit<12, true>(0x0))) {
            r = VBit<5, false>(0xBu);
        } else if ((VBit<11, true>(tmp.val.extract(0x1Fu, 0x15u)) == VBit<11, true>(0x0))) {
            r = VBit<5, false>(0xAu);
        } else if ((VBit<10, true>(tmp.val.extract(0x1Fu, 0x16u)) == VBit<10, true>(0x0))) {
            r = VBit<5, false>(0x9u);
        } else if ((VBit<9, true>(tmp.val.extract(0x1Fu, 0x17u)) == VBit<9, true>(0x0))) {
            r = VBit<5, false>(0x8u);
        } else if ((VBit<8, true>(tmp.val.extract(0x1Fu, 0x18u)) == VBit<8, true>(0x0))) {
            r = VBit<5, false>(0x7u);
        } else if ((VBit<7, true>(tmp.val.extract(0x1Fu, 0x19u)) == VBit<7, true>(0x0))) {
            r = VBit<5, false>(0x6u);
        } else if ((VBit<6, true>(tmp.val.extract(0x1Fu, 0x1Au)) == VBit<6, true>(0x0))) {
            r = VBit<5, false>(0x5u);
        } else if ((VBit<5, true>(tmp.val.extract(0x1Fu, 0x1Bu)) == VBit<5, true>(0x0))) {
            r = VBit<5, false>(0x4u);
        } else if ((VBit<4, true>(tmp.val.extract(0x1Fu, 0x1Cu)) == VBit<4, true>(0x0))) {
            r = VBit<5, false>(0x3u);
        } else if ((VBit<3, true>(tmp.val.extract(0x1Fu, 0x1Du)) == VBit<3, true>(0x0))) {
            r = VBit<5, false>(0x2u);
        } else if ((VBit<2, true>(tmp.val.extract(0x1Fu, 0x1Eu)) == VBit<2, true>(0x0))) {
            r = VBit<5, false>(0x1u);
        } else {
            r = VBit<5, false>(0x0u);
        }
        return dlx_primitive::w32(r);
    }

#ifdef __checkers__
    class div {
    public:
        div(dlx* p) : mdl(p) {}

#ifdef __checkers__
        void main() {
            VBit<6, false> new_cnt = VBit<6, false>(0x0u);
            if (mdl->vd_divide_divA_divB_wl_wh_div_EX_sig.readNoMark()) {
                VBit<5, false> n = VBit<5, false>(div_clb(dlx_primitive::w32(VBit<32, false>(mdl->divA.read().val))).val);
                mdl->div__PA.assign(1, VBit<64, false>((VBit<32, false>(mdl->divA.read().val) << n)));
                mdl->div__B.assign(1, VBit<32, false>(mdl->divB.read().val));
                new_cnt = (VBit<6, false>(0x21u) - VBit<6, false>(n));
            } else if ((mdl->div__cnt.pdgValue() > VBit<6, false>(0x1u))) {
                mdl->div__PA.assign(1, div_step(mdl->div__PA.pdgValue(), mdl->div__B.pdgValue()));
                new_cnt = (mdl->div__cnt.pdgValue() - VBit<6, false>(0x1u));
            } else if ((mdl->div__cnt.pdgValue() == VBit<6, false>(0x1u))) {
                VBit<64, false> pa = mdl->div__PA.pdgValue();
                {
                    dlx_primitive::w32 __pdg_tmp__pa_el31to0 = dlx_primitive::w32(VBit<32, false>(pa.extract(0x1Fu, 0x0u))).val;
                    mdl->PL.assign(1, __pdg_tmp__pa_el31to0);
                    mdl->wl.write(__pdg_tmp__pa_el31to0);
                    mdl->wl.markRead();
                };
                {
                    dlx_primitive::w32 __pdg_tmp__pa_el63to32 = dlx_primitive::w32(VBit<32, false>(pa.extract(0x3Fu, 0x20u))).val;
                    mdl->PH.assign(1, __pdg_tmp__pa_el63to32);
                    mdl->wh.write(__pdg_tmp__pa_el63to32);
                    mdl->wh.markRead();
                };
                new_cnt = (mdl->div__cnt.pdgValue() - VBit<6, false>(0x1u));
            }
            mdl->div__cnt.assign(1, new_cnt);
            mdl->div_busy_wb.write(dlx_primitive::uint1(((mdl->vd_divide_divA_divB_wl_wh_div_EX_sig.readNoMark() && (new_cnt > VBit<6, false>(0x2u))) || (mdl->div__cnt.pdgValue() > VBit<6, false>(0x3u)))));
        }

#endif // __checkers__

#ifdef __checkers__
        void div_busy_raw_writer() {
            mdl->div_busy_raw.write(dlx_primitive::uint1((mdl->vd_divide_divA_divB_wl_wh_div_EX_sig.readNoMark() || (mdl->div__cnt.pdgValue() != VBit<6, false>(0x0u)))));
        }

#endif // __checkers__

#ifdef __checkers__
        void div_busy_writer() {
            mdl->div_busy.write(dlx_primitive::uint1((mdl->vd_divide_divA_divB_wl_wh_div_EX_sig.readNoMark() || (mdl->div__cnt.pdgValue() > VBit<6, false>(0x1u)))));
        }

#endif // __checkers__

#ifdef __checkers__
        void update_status() {
            mdl->div__B.update(1);
            mdl->div__PA.update(1);
            mdl->div__cnt.update(1);
            mdl->PH.update(1);
            mdl->PL.update(1);
        }

#endif // __checkers__

#ifdef __checkers__
        void clear_update() {
            mdl->div__B.clear_update(1);
            mdl->div__PA.clear_update(1);
            mdl->div__cnt.clear_update(1);
            mdl->PH.clear_update(1);
            mdl->PL.clear_update(1);
        }

#endif // __checkers__

    private:
        dlx* mdl;
    };

    class banks {
    public:
        banks(dlx* p) : mdl(p) {}

#ifdef __checkers__
        void process_result() {
            if ((mdl->banks__ld0_ff.pdgValue()).to_bool()) {
                mdl->dmh_rd.write(dlx_primitive::w16(concat(mdl->dm0_rd.read().val, mdl->dm1_rd.read().val)));
            } else if ((mdl->banks__ld2_ff.pdgValue()).to_bool()) {
                mdl->dmh_rd.write(dlx_primitive::w16(concat(mdl->dm2_rd.read().val, mdl->dm3_rd.read().val)));
            }
            if ((mdl->banks__ld0_ff.pdgValue()).to_bool()) {
                mdl->dmb_rd.write(mdl->dm0_rd.read());
            } else if ((mdl->banks__ld1_ff.pdgValue()).to_bool()) {
                mdl->dmb_rd.write(mdl->dm1_rd.read());
            } else if ((mdl->banks__ld2_ff.pdgValue()).to_bool()) {
                mdl->dmb_rd.write(mdl->dm2_rd.read());
            } else if ((mdl->banks__ld3_ff.pdgValue()).to_bool()) {
                mdl->dmb_rd.write(mdl->dm3_rd.read());
            }
        }

#endif // __checkers__

#ifdef __checkers__
        void process_request() {
            VBit<2, false> dma2 = VBit<2, false>(mdl->dm_addr.read().val.extract(0x1u, 0x0u));
            VBit<1, false> tld0 = (((mdl->ld_dmb.read() && (dma2 == VBit<2, false>(0x0u))) || (mdl->ld_dmh.read() && (dma2 == VBit<2, false>(0x0u)))) || mdl->ld_dmw.read());
            VBit<1, false> tld1 = (((mdl->ld_dmb.read() && (dma2 == VBit<2, false>(0x1u))) || (mdl->ld_dmh.read() && (dma2 == VBit<2, false>(0x0u)))) || mdl->ld_dmw.read());
            VBit<1, false> tld2 = (((mdl->ld_dmb.read() && (dma2 == VBit<2, false>(0x2u))) || (mdl->ld_dmh.read() && (dma2 == VBit<2, false>(0x2u)))) || mdl->ld_dmw.read());
            VBit<1, false> tld3 = (((mdl->ld_dmb.read() && (dma2 == VBit<2, false>(0x3u))) || (mdl->ld_dmh.read() && (dma2 == VBit<2, false>(0x2u)))) || mdl->ld_dmw.read());
            mdl->ld0.write((tld0).to_bool());
            mdl->ld1.write((tld1).to_bool());
            mdl->ld2.write((tld2).to_bool());
            mdl->ld3.write((tld3).to_bool());
            mdl->banks__ld0_ff.assign(2, tld0);
            mdl->banks__ld1_ff.assign(2, tld1);
            mdl->banks__ld2_ff.assign(2, tld2);
            mdl->banks__ld3_ff.assign(2, tld3);
            mdl->st0.write((((mdl->st_dmb.read() && (dma2 == VBit<2, false>(0x0u))) || (mdl->st_dmh.read() && (dma2 == VBit<2, false>(0x0u)))) || mdl->st_dmw.read()));
            mdl->st1.write((((mdl->st_dmb.read() && (dma2 == VBit<2, false>(0x1u))) || (mdl->st_dmh.read() && (dma2 == VBit<2, false>(0x0u)))) || mdl->st_dmw.read()));
            mdl->st2.write((((mdl->st_dmb.read() && (dma2 == VBit<2, false>(0x2u))) || (mdl->st_dmh.read() && (dma2 == VBit<2, false>(0x2u)))) || mdl->st_dmw.read()));
            mdl->st3.write((((mdl->st_dmb.read() && (dma2 == VBit<2, false>(0x3u))) || (mdl->st_dmh.read() && (dma2 == VBit<2, false>(0x2u)))) || mdl->st_dmw.read()));
        }

#endif // __checkers__

#ifdef __checkers__
        void dmw_rd_writer() {
            mdl->dmw_rd.write(dlx_primitive::w32(concat(mdl->dm0_rd.read().val, mdl->dm1_rd.read().val, mdl->dm2_rd.read().val, mdl->dm3_rd.read().val)));
        }

#endif // __checkers__

#ifdef __checkers__
        void dm3_wr_writer() {
            VBit<8, true> t{VBitInitializeTag{}};
            if (mdl->st_dmw.read()) {
                t = VBit<8, true>(mdl->dmw_wr.read().val.extract(0x7u, 0x0u));
            } else {
                VBit<8, true> t_0{VBitInitializeTag{}};
                if (mdl->st_dmh.read()) {
                    t_0 = VBit<8, true>(mdl->dmh_wr.read().val.extract(0x7u, 0x0u));
                } else {
                    t_0 = mdl->dmb_wr.read().val;
                }
                t = t_0;
            }
            mdl->dm3_wr.write(dlx_primitive::w08(t));
        }

#endif // __checkers__

#ifdef __checkers__
        void dm3_addr_writer() {
            mdl->dm3_addr.write(dlx_primitive::addr(VBit<22, false>(mdl->dm_addr.read().val.extract(0x17u, 0x2u))));
        }

#endif // __checkers__

#ifdef __checkers__
        void dm2_wr_writer() {
            VBit<8, true> t{VBitInitializeTag{}};
            if (mdl->st_dmw.read()) {
                t = VBit<8, true>(mdl->dmw_wr.read().val.extract(0xFu, 0x8u));
            } else {
                VBit<8, true> t_0{VBitInitializeTag{}};
                if (mdl->st_dmh.read()) {
                    t_0 = VBit<8, true>(mdl->dmh_wr.read().val.extract(0xFu, 0x8u));
                } else {
                    t_0 = mdl->dmb_wr.read().val;
                }
                t = t_0;
            }
            mdl->dm2_wr.write(dlx_primitive::w08(t));
        }

#endif // __checkers__

#ifdef __checkers__
        void dm2_addr_writer() {
            mdl->dm2_addr.write(dlx_primitive::addr(VBit<22, false>(mdl->dm_addr.read().val.extract(0x17u, 0x2u))));
        }

#endif // __checkers__

#ifdef __checkers__
        void dm1_wr_writer() {
            VBit<8, true> t{VBitInitializeTag{}};
            if (mdl->st_dmw.read()) {
                t = VBit<8, true>(mdl->dmw_wr.read().val.extract(0x17u, 0x10u));
            } else {
                VBit<8, true> t_0{VBitInitializeTag{}};
                if (mdl->st_dmh.read()) {
                    t_0 = VBit<8, true>(mdl->dmh_wr.read().val.extract(0x7u, 0x0u));
                } else {
                    t_0 = mdl->dmb_wr.read().val;
                }
                t = t_0;
            }
            mdl->dm1_wr.write(dlx_primitive::w08(t));
        }

#endif // __checkers__

#ifdef __checkers__
        void dm1_addr_writer() {
            mdl->dm1_addr.write(dlx_primitive::addr(VBit<22, false>(mdl->dm_addr.read().val.extract(0x17u, 0x2u))));
        }

#endif // __checkers__

#ifdef __checkers__
        void dm0_wr_writer() {
            VBit<8, true> t{VBitInitializeTag{}};
            if (mdl->st_dmw.read()) {
                t = VBit<8, true>(mdl->dmw_wr.read().val.extract(0x1Fu, 0x18u));
            } else {
                VBit<8, true> t_0{VBitInitializeTag{}};
                if (mdl->st_dmh.read()) {
                    t_0 = VBit<8, true>(mdl->dmh_wr.read().val.extract(0xFu, 0x8u));
                } else {
                    t_0 = mdl->dmb_wr.read().val;
                }
                t = t_0;
            }
            mdl->dm0_wr.write(dlx_primitive::w08(t));
        }

#endif // __checkers__

#ifdef __checkers__
        void dm0_addr_writer() {
            mdl->dm0_addr.write(dlx_primitive::addr(VBit<22, false>(mdl->dm_addr.read().val.extract(0x17u, 0x2u))));
        }

#endif // __checkers__

#ifdef __checkers__
        void update_status() {
            mdl->banks__ld0_ff.update(2);
            mdl->banks__ld1_ff.update(2);
            mdl->banks__ld2_ff.update(2);
            mdl->banks__ld3_ff.update(2);
        }

#endif // __checkers__

#ifdef __checkers__
        void clear_update() {
            mdl->banks__ld0_ff.clear_update(2);
            mdl->banks__ld1_ff.clear_update(2);
            mdl->banks__ld2_ff.clear_update(2);
            mdl->banks__ld3_ff.clear_update(2);
        }

#endif // __checkers__

        void dbg_access_DMb(unsigned a, dlx_primitive::w08& v, bool read) {
            if ((VBit<2, false>(VBit<32, false>(a).extract(0x1u, 0x0u)) == VBit<2, false>(0x0u))) {
                dbg_access_DM0((VBit<30, false>(VBit<32, false>(a).extract(0x1Fu, 0x2u))).to_unsigned(), v, read);
            } else if ((VBit<2, false>(VBit<32, false>(a).extract(0x1u, 0x0u)) == VBit<2, false>(0x1u))) {
                dbg_access_DM1((VBit<30, false>(VBit<32, false>(a).extract(0x1Fu, 0x2u))).to_unsigned(), v, read);
            } else if ((VBit<2, false>(VBit<32, false>(a).extract(0x1u, 0x0u)) == VBit<2, false>(0x2u))) {
                dbg_access_DM2((VBit<30, false>(VBit<32, false>(a).extract(0x1Fu, 0x2u))).to_unsigned(), v, read);
            } else if ((VBit<2, false>(VBit<32, false>(a).extract(0x1u, 0x0u)) == VBit<2, false>(0x3u))) {
                dbg_access_DM3((VBit<30, false>(VBit<32, false>(a).extract(0x1Fu, 0x2u))).to_unsigned(), v, read);
            }
        }

        void dbg_access_DM0(AddressType dbg_addr, dlx_primitive::w08& dbg_val, bool dbg_read);

        void dbg_access_DM1(AddressType dbg_addr, dlx_primitive::w08& dbg_val, bool dbg_read);

        void dbg_access_DM2(AddressType dbg_addr, dlx_primitive::w08& dbg_val, bool dbg_read);

        void dbg_access_DM3(AddressType dbg_addr, dlx_primitive::w08& dbg_val, bool dbg_read);

    private:
        dlx* mdl;
    };

#endif // __checkers__

} // namespace dlx_primitive
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#endif
