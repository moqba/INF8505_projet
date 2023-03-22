
// File generated by noodle version Q-2020.03#7e5ed72dc8#200717, Wed Mar 22 14:16:27 2023
// Copyright 2014-2020 Synopsys, Inc. All rights reserved.
// noodle -Pc -Iisg +wisg -Iruntime/include -DCHESS_CXX_ATTRIBUTES -D__tct_patch__=300 +NOrlt -D__chess__ -D__programmers_view__ dlx

#ifdef __chess__
#error "generated native file not intended for compilation by chess"
#endif

#ifndef _dlx_chess_opns_h
#define _dlx_chess_opns_h

// Native equivalent of Chess promoted operations

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"
#endif

#ifdef CHESS_NATIVE_NAMESPACE
namespace CHESS_NATIVE_NAMESPACE {
#endif


class keep_in_registers_wrapper__slonglong {
    long long val;
public:
    keep_in_registers_wrapper__slonglong(long long v) : val(v) {}
    unsigned value_high() const;
    unsigned value_low() const;
};


class keep_in_registers_wrapper__ulonglong {
    unsigned long long val;
public:
    keep_in_registers_wrapper__ulonglong(unsigned long long v) : val(v) {}
    unsigned value_high() const;
    unsigned value_low() const;
};

bool land(bool, bool) chess_property(commutative);
bool lor(bool, bool) chess_property(commutative);
bool lxor(bool, bool) chess_property(commutative);
bool nez(int);
bool eqz(int);
bool nez(unsigned);
bool eqz(unsigned);
//!bool nez(void *);
//!bool eqz(void *);
//!void udiv(unsigned, unsigned, unsigned &, unsigned &);
int clb(int);
unsigned clb(unsigned);
#if 0//!
namespace dlx_primitive{
    /*inline*/ dint to_dint_se(int);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ dint to_dint_ze(int);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ int to_int(dint);
} //namespace dlx_primitive
#endif//!
namespace dlx_primitive{
unsigned add(unsigned, unsigned, uint1 &) chess_property(commutative duplicate_at_using_opn2 addc);
} //namespace dlx_primitive
namespace dlx_primitive{
unsigned sub(unsigned, unsigned, uint1 &) chess_property(duplicate_at_using_opn2 subc);
} //namespace dlx_primitive
namespace dlx_primitive{
unsigned addx(unsigned, unsigned, uint1, uint1 &) chess_property(commutative adde);
} //namespace dlx_primitive
namespace dlx_primitive{
unsigned subx(unsigned, unsigned, uint1, uint1 &) chess_property(sube);
} //namespace dlx_primitive
#if 0//!
namespace dlx_primitive{
    /*inline*/ dint l_add(dint, dint);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ dint l_sub(dint, dint);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ dint l_and(dint, dint);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ dint l_or(dint, dint);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ dint l_xor(dint, dint);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ dint l_complement(dint);
} //namespace dlx_primitive
#endif//!
namespace dlx_primitive{
void lmuluu(unsigned, unsigned, unsigned &, unsigned &) chess_property(commutative umul_lohi);
} //namespace dlx_primitive
namespace dlx_primitive{
void lmulss(int, int, unsigned &, int &) chess_property(commutative smul_lohi);
} //namespace dlx_primitive
#if 0//!
namespace dlx_primitive{
    /*inline*/ dint l_mul(dint, dint);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ bool l_lts(dint, dint);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ bool l_les(dint, dint);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ bool l_ltu(dint, dint);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ bool l_leu(dint, dint);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ bool l_eq(dint, dint);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ bool l_ne(dint, dint);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ dint l_lsl(dint, int);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ dint l_asr(dint, int);
} //namespace dlx_primitive
#endif//!
#if 0//!
namespace dlx_primitive{
    /*inline*/ dint l_lsr(dint, int);
} //namespace dlx_primitive
#endif//!


// do_generate[_native] inline functions

extern long long div_called(long long, long long, chess_output long long &) chess_property(functional);

    inline long long div_remainder(long long a, long long b, long long &r) chess_property(functional)
    {
     return div_called(a,b,r);
    }

extern unsigned long long div_called(unsigned long long, unsigned long long, chess_output unsigned long long &) chess_property(functional);

    inline unsigned long long div_remainder(unsigned long long a, unsigned long long b, unsigned long long &r) chess_property(functional)
    {
     return div_called(a,b,r);
    }

    inline int clb(long long a)
    {
     int h = (int)(a >> 32);
     int l = (int)a;
     if (h == 0)
      if (l < 0)
       return 32;
      else
       return 32 + clb(l);
     else
      if (h == -1)
       if (l >= 0)
        return 32;
       else
        return 32 + clb(l);
      else
       return clb(h);
    }

    inline int clb(unsigned long long a)
    {
     return clb((long long)a);
    }

    inline void char_memory_copy(volatile char *l, const volatile char *r, const int sz)
    {
     char *ll = (char *)l;
     char *rr = (char *)r;
     if (chess_manifest(sz < 5))
      {
       if (sz >= 1)
        * ll++ = * rr++;
       else
        ;
       if (sz >= 2)
        * ll++ = * rr++;
       else
        ;
       if (sz >= 3)
        * ll++ = * rr++;
       else
        ;
       if (sz >= 4)
        *ll = *rr;
       else
        ;
      }
     else
      for (int ii = 0;
           ii < sz; ii++)
       ll[ii] = rr[ii];
    }

    inline void short_memory_copy(volatile short *l, const volatile short *r, const int sz)
    {
     short *ll = (short *)l;
     short *rr = (short *)r;
     if (chess_manifest(sz < 5))
      {
       if (sz >= 1)
        * ll++ = * rr++;
       else
        ;
       if (sz >= 2)
        * ll++ = * rr++;
       else
        ;
       if (sz >= 3)
        * ll++ = * rr++;
       else
        ;
       if (sz >= 4)
        *ll = *rr;
       else
        ;
      }
     else
      for (int ii = 0;
           ii < sz; ii++)
       ll[ii] = rr[ii];
    }

    inline void int_memory_copy(volatile int *l, const volatile int *r, const int sz)
    {
     int *ll = (int *)l;
     int *rr = (int *)r;
     if (chess_manifest(sz < 5))
      {
       if (sz >= 1)
        * ll++ = * rr++;
       else
        ;
       if (sz >= 2)
        * ll++ = * rr++;
       else
        ;
       if (sz >= 3)
        * ll++ = * rr++;
       else
        ;
       if (sz >= 4)
        *ll = *rr;
       else
        ;
      }
     else
      for (int ii = 0;
           ii < sz; ii++)
       ll[ii] = rr[ii];
    }

    inline void float_raise(int flags)
    {
    }

extern "C" unsigned int32_to_float32(int) chess_property(functional loop_free);

extern "C" dlx_primitive::dint int32_to_float64(int) chess_property(functional loop_free);

extern "C" int float32_to_int32(unsigned);

extern "C" int float32_to_int32_round_to_zero(unsigned) chess_property(functional loop_free);

extern "C" dlx_primitive::dint float32_to_float64(unsigned) chess_property(functional loop_free);

extern "C" unsigned float32_round_to_int(unsigned) chess_property(functional loop_free);

extern "C" unsigned float32_add(unsigned, unsigned) chess_property(functional loop_free);

extern "C" unsigned float32_sub(unsigned, unsigned) chess_property(functional loop_free);

extern "C" unsigned float32_mul(unsigned, unsigned) chess_property(functional loop_free);

extern "C" unsigned float32_div(unsigned, unsigned) chess_property(functional loop_free);

extern "C" unsigned float32_rem(unsigned, unsigned) chess_property(functional loop_free);

extern "C" unsigned float32_sqrt(unsigned) chess_property(functional loop_free);

extern "C" int float32_eq(unsigned, unsigned) chess_property(functional loop_free);

extern "C" int float32_le(unsigned, unsigned) chess_property(functional loop_free);

extern "C" int float32_lt(unsigned, unsigned) chess_property(functional loop_free);

extern "C" int float32_eq_signaling(unsigned, unsigned);

extern "C" int float32_le_quiet(unsigned, unsigned);

extern "C" int float32_lt_quiet(unsigned, unsigned);

    inline int float32_is_signaling_nan(unsigned a)
    {
     return (a >> 22 & 511) == 510 && a & 4194303;
    }

extern "C" int float64_to_int32(dlx_primitive::dint);

extern "C" int float64_to_int32_round_to_zero(dlx_primitive::dint) chess_property(functional loop_free);

extern "C" unsigned float64_to_float32(dlx_primitive::dint) chess_property(functional loop_free);

extern "C" dlx_primitive::dint float64_round_to_int(dlx_primitive::dint) chess_property(functional loop_free);

extern "C" dlx_primitive::dint float64_add(dlx_primitive::dint, dlx_primitive::dint) chess_property(functional loop_free);

extern "C" dlx_primitive::dint float64_sub(dlx_primitive::dint, dlx_primitive::dint) chess_property(functional loop_free);

extern "C" dlx_primitive::dint float64_mul(dlx_primitive::dint, dlx_primitive::dint) chess_property(functional loop_free);

extern "C" dlx_primitive::dint float64_div(dlx_primitive::dint, dlx_primitive::dint) chess_property(functional loop_free);

extern "C" dlx_primitive::dint float64_rem(dlx_primitive::dint, dlx_primitive::dint) chess_property(functional loop_free);

extern "C" dlx_primitive::dint float64_sqrt(dlx_primitive::dint) chess_property(functional loop_free);

extern "C" int float64_eq(dlx_primitive::dint, dlx_primitive::dint) chess_property(functional loop_free);

extern "C" int float64_le(dlx_primitive::dint, dlx_primitive::dint) chess_property(functional loop_free);

extern "C" int float64_lt(dlx_primitive::dint, dlx_primitive::dint) chess_property(functional loop_free);

extern "C" int float64_eq_signaling(dlx_primitive::dint, dlx_primitive::dint);

extern "C" int float64_le_quiet(dlx_primitive::dint, dlx_primitive::dint);

extern "C" int float64_lt_quiet(dlx_primitive::dint, dlx_primitive::dint);

    inline int float64_is_signaling_nan(dlx_primitive::dint a)
    {
     return (a.high >> 19 & 4095) == 4094 && (a.low || a.high & 524287);
    }

    inline int f32_to_i32(unsigned a)
    {
     return float32_to_int32_round_to_zero(a);
    }

    inline unsigned i32_to_f32(int a)
    {
     return int32_to_float32(a);
    }

    inline unsigned f32_add(unsigned a, unsigned b)
    {
     return float32_add(a,b);
    }

    inline unsigned f32_sub(unsigned a, unsigned b)
    {
     return float32_sub(a,b);
    }

    inline unsigned f32_mul(unsigned a, unsigned b)
    {
     return float32_mul(a,b);
    }

    inline unsigned f32_div(unsigned a, unsigned b)
    {
     return float32_div(a,b);
    }

    inline unsigned f32_neg(unsigned a)
    {
     a ^= 2147483648U;
     return a;
    }

    inline bool f32_le(unsigned a, unsigned b)
    {
     return float32_le(a,b);
    }

    inline bool f32_lt(unsigned a, unsigned b)
    {
     return float32_lt(a,b);
    }

    inline bool f32_eq(unsigned a, unsigned b)
    {
     return float32_eq(a,b);
    }

    inline int f64_to_i32(dlx_primitive::dint a)
    {
     return float64_to_int32_round_to_zero(a);
    }

    inline dlx_primitive::dint i32_to_f64(int a)
    {
     return int32_to_float64(a);
    }

    inline dlx_primitive::dint f32_to_f64(unsigned a)
    {
     return float32_to_float64(a);
    }

    inline unsigned f64_to_f32(dlx_primitive::dint a)
    {
     return float64_to_float32(a);
    }

    inline dlx_primitive::dint f64_add(dlx_primitive::dint a, dlx_primitive::dint b)
    {
     return float64_add(a,b);
    }

    inline dlx_primitive::dint f64_sub(dlx_primitive::dint a, dlx_primitive::dint b)
    {
     return float64_sub(a,b);
    }

    inline dlx_primitive::dint f64_mul(dlx_primitive::dint a, dlx_primitive::dint b)
    {
     return float64_mul(a,b);
    }

    inline dlx_primitive::dint f64_div(dlx_primitive::dint a, dlx_primitive::dint b)
    {
     return float64_div(a,b);
    }

    inline dlx_primitive::dint f64_neg(dlx_primitive::dint a)
    {
     a.high ^= 2147483648U;
     return a;
    }

    inline bool f64_le(dlx_primitive::dint a, dlx_primitive::dint b)
    {
     return float64_le(a,b);
    }

    inline bool f64_lt(dlx_primitive::dint a, dlx_primitive::dint b)
    {
     return float64_lt(a,b);
    }

    inline bool f64_eq(dlx_primitive::dint a, dlx_primitive::dint b)
    {
     return float64_eq(a,b);
    }

#ifdef tentative_generate_member_fn_defns
    inline dlx_primitive::dint::dint(unsigned h, unsigned l)
    : high(h), low(l)
    {
    }

#endif


// composed promotion conversions
namespace dlx_primitive {
    w32 __promo_bool_on_w32(bool);
    bool __promo_w32_to_bool(w32);
} //namespace dlx_primitive


#ifdef CHESS_NATIVE_NAMESPACE
} //namespace CHESS_NATIVE_NAMESPACE
#endif

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif


#endif /*_dlx_chess_opns_h*/