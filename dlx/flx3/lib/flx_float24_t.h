/*
-- File : flx_float24_t.h
--
-- Contents : Floating point application layer for the FLX processor.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef _flx_float24_t_h
#define _flx_float24_t_h

//chess_properties {
//    representation float       : undefined;
//    representation double      : undefined;
//    representation long double : undefined;
//}


class float24_t {
    float24_t(int);
    operator int() const;

    inline float24_t(signed char);
    inline operator signed char() const;

    inline float24_t(signed short);
    inline operator signed short() const;

    inline float24_t(unsigned a);
    inline operator unsigned() const;

    inline float24_t(unsigned char);
    inline operator unsigned char() const;

    inline float24_t(unsigned short);
    inline operator unsigned short() const;

    float24_t(float);
    float24_t(double);

};

promotion float24_t::operator int() const property(generate_opaque_native) = w32 f2i(w32);
promotion operator float24_t(int) = w32 i2f(w32);

promotion operator float24_t(float) = undefined;
promotion operator float24_t(double) = undefined;

promotion int       as_int32(float24_t) property(reinterpret) = nil;
promotion float24_t as_float24_t(int)   property(reinterpret) = nil;

inline float24_t::operator signed char() const property(generate_opaque_native) { return (signed char)(int)(*this); }
inline float24_t::float24_t(signed char  a) { *this = (float24_t)(int)a; }

inline float24_t::operator signed short() const property(generate_opaque_native) { return (signed short)(int)(*this); }
inline float24_t::float24_t(signed short  a) { *this = (float24_t)(int)a; }

inline float24_t::operator unsigned() const property(generate_opaque_native) {
     if (*this >= as_float24_t(0x4f0000))
         return (unsigned)(int)(*this-as_float24_t(0x4f0000)) + 0x80000000U;
     else
         return (unsigned)(int)(*this);
}

inline float24_t::float24_t(unsigned a) {
    if (a >= 0x80000000U)
        *this = (float24_t)(int)(a-0x80000000U) + as_float24_t(0x4f0000);
    else
        *this = (float24_t)(int)a;
}

inline float24_t::operator unsigned char() const property(generate_opaque_native) { return (unsigned char)(unsigned)(*this); }
inline float24_t::float24_t (unsigned char  a) { *this = (float24_t)(unsigned)a; }

inline float24_t::operator unsigned short() const property(generate_opaque_native) { return (unsigned short)(unsigned)(*this); }
inline float24_t::float24_t (unsigned short a) { *this = (float24_t)(unsigned)a; }


promotion float24_t operator+(float24_t,float24_t) = w32 fadd(w32,w32);
promotion float24_t operator-(float24_t,float24_t) = w32 fsub(w32,w32);
promotion float24_t operator*(float24_t,float24_t) = w32 fmul(w32,w32);

promotion bool operator<=(float24_t,float24_t) = w32 sfle(w32,w32);
promotion bool operator< (float24_t,float24_t) = w32 sflt(w32,w32);
promotion bool operator==(float24_t,float24_t) = w32 sfeq(w32,w32);

inline bool operator>=(float24_t a, float24_t b) { return (b<=a); }
inline bool operator> (float24_t a, float24_t b) { return (b<a); }
inline bool operator!=(float24_t a, float24_t b) { return !(a==b); }

namespace flx_primitive {
  promotion float24_t fround(float24_t,int) = w32 fround(w32,w32 mode);
}

inline float24_t roundf(float24_t a) { return flx_primitive::fround(a,0); }
inline float24_t floorf(float24_t a) { return flx_primitive::fround(a,1); }
inline float24_t ceilf (float24_t a) { return flx_primitive::fround(a,2); }
inline float24_t truncf(float24_t a) { return flx_primitive::fround(a,3); }

promotion void fdiv(float24_t,float24_t,float24_t&) property(dont_generate_native)
        = void fdivide(w32,w32,w32&);

inline float24_t operator/(float24_t a, float24_t b)
{
    float24_t q;
    fdiv(a,b,q);
    return q;
}

promotion void fsqrt(float24_t,float24_t&)  property(dont_generate_native)
        = void fsqrt(w32,w32&);

inline float24_t fsqrt(float24_t a) property(dont_generate_native)
{
    float24_t q;
    fsqrt(a,q);
    return q;
}

#endif /* _flx_float24_t_h */
