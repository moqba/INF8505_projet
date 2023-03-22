/*
-- File: math.h
--
-- Contents: ISO C99 Standard, 7.12 Mathematics <math.h>
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _MATH_H
#define _MATH_H

#if defined(__cplusplus) || defined(__ndl__)
extern "C" {
#endif

inline float fabsf(float a)
{
    return as_float(as_int32(a) & 0x7fffffff);
}

inline float copysignf(float x, float y)
{
    // note: superfluous parentheses to silence clang warnings
    return as_float((as_int32(x) & 0x7fffffff) | (as_int32(y) & 0x80000000));
}

inline double fabs(double a)
{
    return as_double(as_int64(a) & 0x7fffffffffffffff);
}

inline double copysign(double x, double y)
{
    // note: superfluous parentheses to silence clang warnings
    return as_double((as_int64(x) & 0x7fffffffffffffff) | (as_int64(y) & 0x8000000000000000));
}

// Note: loop level annotations are not relevant on TLX.  They are in comments
// in case the code is ported to a processor that does have zero overhead loops!

#define mlib_pure  property(functional)
#define mlib_loop0 //property(loop_free)
#define mlib_loop1 //property(loop_levels_1)

extern float  ff_ldexpf(float , int)    mlib_pure mlib_loop0;
extern double ff_ldexp (double, int)    mlib_pure mlib_loop0;
extern float  ff_ceilf (float )         mlib_pure mlib_loop0;
extern double ff_ceil  (double)         mlib_pure mlib_loop0;
extern float  ff_floorf(float )         mlib_pure mlib_loop0;
extern double ff_floor (double)         mlib_pure mlib_loop0;
extern float  ff_roundf(float )         mlib_pure mlib_loop0;
extern double ff_round (double)         mlib_pure mlib_loop0;
extern float  ff_cosf  (float )         mlib_pure mlib_loop0;
extern double ff_cos   (double)         mlib_pure mlib_loop0;
extern float  ff_sinf  (float )         mlib_pure mlib_loop0;
extern double ff_sin   (double)         mlib_pure mlib_loop0;
extern float  ff_expf  (float )         mlib_pure mlib_loop1;
extern double ff_exp   (double)         mlib_pure mlib_loop1;
extern float  ff_logf  (float )         mlib_pure mlib_loop1;
extern double ff_log   (double)         mlib_pure mlib_loop1;
extern float  ff_log10f(float )         mlib_pure mlib_loop1;
extern double ff_log10 (double)         mlib_pure mlib_loop1;
extern float  ff_sqrtf (float )         mlib_pure mlib_loop1;
extern double ff_sqrt  (double)         mlib_pure mlib_loop1;
extern float  ff_powf  (float , float ) mlib_pure mlib_loop1;
extern double ff_pow   (double, double) mlib_pure mlib_loop1;
extern double ff_fmod  (double, double) mlib_pure mlib_loop1;
extern float  ff_acosf (float )         mlib_pure mlib_loop1;
extern double ff_acos  (double)         mlib_pure mlib_loop1;
extern float  ff_asinf (float )         mlib_pure mlib_loop1;
extern double ff_asin  (double)         mlib_pure mlib_loop1;
extern double ff_atan  (double)         mlib_pure mlib_loop1;
extern float  ff_atan2f(float, float)   mlib_pure mlib_loop1;
extern double ff_atan2 (double,double)  mlib_pure mlib_loop1;

extern float atanf(float)               mlib_pure mlib_loop1;

inline float  ldexpf(float  x, int i) { return ff_ldexpf(x,i); }
inline double ldexp (double x, int i) { return ff_ldexp (x,i); }
inline float  ceilf (float  x) { return ff_ceilf (x); }
inline double ceil  (double x) { return ff_ceil  (x); }
inline float  floorf(float  x) { return ff_floorf(x); }
inline double floor (double x) { return ff_floor (x); }
inline float  roundf(float  x) { return ff_roundf(x); }
inline double round (double x) { return ff_round (x); }
inline float  cosf  (float  x) { return ff_cosf  (x); }
inline double cos   (double x) { return ff_cos   (x); }
inline float  sinf  (float  x) { return ff_sinf  (x); }
inline double sin   (double x) { return ff_sin   (x); }
inline float  expf  (float  x) { return ff_expf  (x); }
inline double exp   (double x) { return ff_exp   (x); }
inline float  logf  (float  x) { return ff_logf  (x); }
inline double log   (double x) { return ff_log   (x); }
inline float  log10f(float  x) { return ff_log10f(x); }
inline double log10 (double x) { return ff_log10 (x); }
inline float  sqrtf (float  x) { return ff_sqrtf (x); }
inline double sqrt  (double x) { return ff_sqrt  (x); }
inline float  powf  (float  x, float  y) { return ff_powf(x,y); }
inline double pow   (double x, double y) { return ff_pow (x,y); }
inline double fmod  (double x, double y) { return ff_fmod (x,y); }
inline float  acosf (float  x) { return ff_acosf  (x); }
inline double acos  (double x) { return ff_acos   (x); }
inline float  asinf (float  x) { return ff_asinf  (x); }
inline double asin  (double x) { return ff_asin   (x); }
inline double atan  (double x) { return ff_atan   (x); }
inline float  atan2f(float y,  float x)  { return ff_atan2f(y,x); }
inline double atan2 (double y, double x) { return ff_atan2(y,x); }

inline float  truncf(float  x) { return x < 0.0 ? ceilf(x) : floorf(x); }
inline double trunc (double x) { return x < 0.0 ? ceil (x) : floor (x); }


inline float  frexpf(float  x, int* e)
{
    if (x == 0.0f)
        *e = 0;
    else {
        *e = ((as_int32(x) >> 23) & 0xff) - 0x7e; //? what if subnormal
        x = ldexpf(x,-*e);
    }
    return x;
}

inline double frexp (double x, int* e)
{
    if (x == 0.0)
        *e = 0;
    else {
        *e = ((int)(as_int64(x) >> 52) & 0x7ff) - 0x3fe; //? what if subnormal
        x = ldexp(x,-*e);
    }
    return x;
}


#undef mlib_pure
#undef mlib_loop0
#undef mlib_loop1

#if defined(__cplusplus) || defined(__ndl__)
} // extern "C"
#endif

#endif /* math.h */
