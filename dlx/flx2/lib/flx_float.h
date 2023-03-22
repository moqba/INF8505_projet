/*
-- File : flx_float.h
--
-- Contents : Floating point application layer for the FLX processor.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/




#ifndef _flx_float_h
#define _flx_float_h

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

typedef flx_primitive::dint float64;

#include "softfloat/softfloat.h"

promotion operator int  (float) = w32 f2i(w32);
promotion operator float(int  ) = w32 i2f(w32);

promotion int as_int32(float) property(reinterpret) = nil;
promotion float as_float(int) property(reinterpret) = nil;

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

promotion float operator+(float,float) = w32 fadd(w32,w32);
promotion float operator-(float,float) = w32 fsub(w32,w32);
promotion float operator*(float,float) = w32 fmul(w32,w32);

promotion bool operator<=(float,float) = w32 sfle(w32,w32);
promotion bool operator< (float,float) = w32 sflt(w32,w32);
promotion bool operator==(float,float) = w32 sfeq(w32,w32);

namespace flx_primitive {
  promotion float fround(float,int) = w32 fround(w32,w32 mode);
}

inline float roundf(float a) property(dont_generate_native fround) { return flx_primitive::fround(a,0); }
inline float floorf(float a) property(dont_generate_native ffloor) { return flx_primitive::fround(a,1); }
inline float ceilf(float a)  property(dont_generate_native fceil ) { return flx_primitive::fround(a,2); }
inline float truncf(float a) property(dont_generate_native ftrunc) { return flx_primitive::fround(a,3); }


promotion void fdiv(float,float,float&) property(dont_generate)
        = void fdivide(w32,w32,w32&);

inline float operator/(float a, float b)
{
    float q;
    fdiv(a,b,q);
    return q;
}

promotion void fsqrt(float,float&) property(dont_generate)
        = void fsqrt(w32,w32&);

inline float sqrtf(float a) property(dont_generate_native fsqrt)
{
    float q;
    fsqrt(a,q);
    return q;
}

inline bool operator>=(float a, float b) { return (b<=a); }
inline bool operator> (float a, float b) { return (b<a); }
inline bool operator!=(float a, float b) { return !(a==b); }
#endif /* _flx_float_h */


