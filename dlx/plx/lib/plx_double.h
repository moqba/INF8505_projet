/*
-- File : plx_double.h
--
-- Contents : Double precision floating  point application layer for
--            the PLX processor.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _plx_double_h
#define _plx_double_h

#if defined(__chess__)

inline int f64_to_i32(float64 a) { return float64_to_int32_round_to_zero(a);}
inline float64 i32_to_f64(int a)     { return int32_to_float64(a); }
inline float64 f32_to_f64(float32 a) { return float32_to_float64(a); }
inline float32 f64_to_f32(float64 a) { return float64_to_float32(a); }

promotion long long as_int64(double) property(reinterpret) = nil;
promotion double as_double(long long) property(reinterpret) = nil;

promotion operator int  (double) = int f64_to_i32(float64);
promotion operator double(int  ) = float64 i32_to_f64(int);

inline operator double (signed char  a) { return (double)(int)a; }
inline operator double (signed short a) { return (double)(int)a; }

inline operator signed char (double  a) { return (signed char )(int)a; }
inline operator signed short(double  a) { return (signed short)(int)a; }

promotion operator double(float ) = float64 f32_to_f64(float32 a);
promotion operator float (double) = float32 f64_to_f32(float64 a);

inline operator unsigned(double a) {
    if (a >= 0x1p31)
        return (int)(a-0x1p31) + 0x80000000;
    else
        return (int)a;
}

inline operator double(unsigned a) {
    if (a >= 0x80000000)
        return (double)(int)(a-0x80000000) + 0x1p31;
    else
        return (double)(int)a;
}

promotion operator double(unsigned char) = undefined;
promotion operator unsigned char(double) = undefined;

promotion operator double(unsigned short) = undefined;
promotion operator unsigned short(double) = undefined;

promotion operator double(signed long long) = undefined;
promotion operator signed long long(double) = undefined;

promotion operator double(unsigned long long) = undefined;
promotion operator unsigned long long(double) = undefined;

inline float64 f64_add(float64 a, float64 b) { return float64_add(a,b); }
inline float64 f64_sub(float64 a, float64 b) { return float64_sub(a,b); }
inline float64 f64_mul(float64 a, float64 b) { return float64_mul(a,b); }
inline float64 f64_div(float64 a, float64 b) { return float64_div(a,b); }

promotion double operator+(double,double) = float64 f64_add(float64,float64);
promotion double operator-(double,double) = float64 f64_sub(float64,float64);
promotion double operator*(double,double) = float64 f64_mul(float64,float64);
promotion double operator/(double,double) = float64 f64_div(float64,float64);

inline bool f64_le(float64 a, float64 b) { return float64_le(a,b); }
inline bool f64_lt(float64 a, float64 b) { return float64_lt(a,b); }
inline bool f64_eq(float64 a, float64 b) { return float64_eq(a,b); }

promotion bool operator<=(double,double) = bool f64_le(float64,float64);
promotion bool operator< (double,double) = bool f64_lt(float64,float64);
promotion bool operator==(double,double) = bool f64_eq(float64,float64) ;

inline bool operator>=(double a, double b) { return (b<=a); }
inline bool operator> (double a, double b) { return (b<a); }
inline bool operator!=(double a, double b) { return !(a==b); }

#endif /* __chess__ */

#endif /* _plx_double_h */
