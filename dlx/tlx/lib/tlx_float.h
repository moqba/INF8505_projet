/*
-- File : tlx_float.h
--
-- Contents : Floating point application layer for the TLX processor.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/




#ifndef _tlx_float_h
#define _tlx_float_h

// IEEE 754 single precision
class float  property( 32 bits, ieee, llvm_emulated);


// IEEE 754 double precision
class double property( 64 bits, ieee, llvm_emulated);

// long double is same as double
class long double property( 64 bits, sign_magnitude, 11 exp_bits);

chess_properties {
    representation float       : w32;
    representation double      : dint;
    representation long double : double;
}

typedef tlx_primitive::dint float64;

#include "softfloat/softfloat.h"

inline int f32_to_i32(float32 a) { return float32_to_int32_round_to_zero(a);}
inline float32 i32_to_f32(int a) { return int32_to_float32(a); }

promotion int as_int32(float) property(reinterpret) = nil;
promotion float as_float(int) property(reinterpret) = nil;

promotion operator int  (float) = int f32_to_i32(float32);
promotion operator float(int  ) = float32 i32_to_f32(int);

inline operator signed char (float  a) { return (signed char )(int)a; }
inline operator float (signed char  a) { return (float)(int)a; }

inline operator signed short(float  a) { return (signed short)(int)a; }
inline operator float (signed short a) { return (float)(int)a; }

inline operator unsigned(float a) {
    if (a >= 0x1p31F)
        return (int)(a-0x1p31F) + 0x80000000;
    else
        return (int)a;
}

inline operator float(unsigned a) {
    if (a >= 0x80000000)
        return (float)(int)(a-0x80000000) + 0x1p31F;
    else
        return (float)(int)a;
}

inline operator unsigned char(float a) { return (unsigned char)(unsigned)a; }
inline operator float (unsigned char  a) { return (float)(unsigned)a; }

inline operator unsigned short(float a) { return (unsigned short)(unsigned)a; }
inline operator float (unsigned short a) { return (float)(unsigned)a; }

promotion operator signed long long(float) = undefined;
promotion operator float(signed long long) = undefined;

promotion operator unsigned long long(float) = undefined;
promotion operator float(unsigned long long) = undefined;

inline float32 f32_add(float32 a, float32 b) { return float32_add(a,b); }
inline float32 f32_sub(float32 a, float32 b) { return float32_sub(a,b); }
inline float32 f32_mul(float32 a, float32 b) { return float32_mul(a,b); }
inline float32 f32_div(float32 a, float32 b) { return float32_div(a,b); }
inline float32 f32_neg(float32 a) { a ^= 0x80000000; return a; }

promotion float operator+(float,float) = float32 f32_add(float32,float32);
promotion float operator-(float,float) = float32 f32_sub(float32,float32);
promotion float operator*(float,float) = float32 f32_mul(float32,float32);
promotion float operator/(float,float) = float32 f32_div(float32,float32);
promotion float operator-(float) = float32 f32_neg(float32);

inline bool f32_le(float32 a, float32 b) { return float32_le(a,b); }
inline bool f32_lt(float32 a, float32 b) { return float32_lt(a,b); }
inline bool f32_eq(float32 a, float32 b) { return float32_eq(a,b); }

promotion bool operator<=(float,float) = bool f32_le(float32,float32);
promotion bool operator< (float,float) = bool f32_lt(float32,float32);
promotion bool operator==(float,float) = bool f32_eq(float32,float32) ;

inline bool operator>=(float a, float b) { return (b<=a); }
inline bool operator> (float a, float b) { return (b<a); }
inline bool operator!=(float a, float b) { return !(a==b); }

#endif /* _tlx_float_h */
