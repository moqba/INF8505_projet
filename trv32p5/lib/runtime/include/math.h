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
    (void)y; // suppress warning about unused parts of y
    // note: superfluous parentheses to silence clang warnings
    return as_double((as_int64(x) & 0x7fffffffffffffff) | (as_int64(y) & 0x8000000000000000));
}

#define mlib_pure  property(functional)
#define mlib_loop0 //property(loop_free)
#define mlib_loop1 //property(loop_levels_1)

extern float  ldexpf(float , int)       mlib_pure mlib_loop0;
extern double ldexp (double, int)       mlib_pure mlib_loop0;
extern float  ceilf (float )            mlib_pure mlib_loop0;
extern double ceil  (double)            mlib_pure mlib_loop0;
extern float  floorf(float )            mlib_pure mlib_loop0;
extern double floor (double)            mlib_pure mlib_loop0;
extern float  roundf(float )            mlib_pure mlib_loop0;
extern double round (double)            mlib_pure mlib_loop0;
extern float  cosf  (float )            mlib_pure mlib_loop0;
extern double cos   (double)            mlib_pure mlib_loop0;
extern float  sinf  (float )            mlib_pure mlib_loop0;
extern double sin   (double)            mlib_pure mlib_loop0;
extern float  expf  (float )            mlib_pure mlib_loop1;
extern double exp   (double)            mlib_pure mlib_loop1;
extern float  logf  (float )            mlib_pure mlib_loop1;
extern double log   (double)            mlib_pure mlib_loop1;
extern float  log10f(float )            mlib_pure mlib_loop1;
extern double log10 (double)            mlib_pure mlib_loop1;
extern float  sqrtf (float )            mlib_pure mlib_loop1;
extern double sqrt  (double)            mlib_pure mlib_loop1;
extern float  powf  (float , float )    mlib_pure mlib_loop1;
extern double pow   (double, double)    mlib_pure mlib_loop1;
extern double fmod  (double, double)    mlib_pure mlib_loop1;
extern float  acosf (float )            mlib_pure mlib_loop1;
extern double acos  (double)            mlib_pure mlib_loop1;
extern float  asinf (float )            mlib_pure mlib_loop1;
extern double asin  (double)            mlib_pure mlib_loop1;
extern double atan  (double)            mlib_pure mlib_loop1;
extern float  atan2f(float, float)      mlib_pure mlib_loop1;
extern double atan2 (double,double)     mlib_pure mlib_loop1;

extern float atanf(float)               mlib_pure mlib_loop1;

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

#ifdef __clang__
#define HUGE_VAL (__builtin_huge_val())
#define HUGE_VALF (__builtin_huge_valf())
#define HUGE_VALL (__builtin_huge_vall())
#define INFINITY (__builtin_inff())
#define NAN (__builtin_nanf(""))
#endif

#define MATH_ERRNO       1
#define MATH_ERREXCEPT   2
#define math_errhandling 0

#endif /* math.h */
