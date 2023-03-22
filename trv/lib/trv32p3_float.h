/*
-- File : trv32p3_float.h
--
-- Contents : Floating point application layer for the trv32p3 processor.
--
-- Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P3_FLOAT_H_
#define INCLUDED_TRV32P3_FLOAT_H_

#include "trv32p3_softfloat.h"

// Concept:
// wrapper intrinsic: call softfloat function
// promote builtin operator on wrapper intrinsic that calls the emulation library

// NOTE: Application types float & double have property llvm_emulated. The
// LLVM frontend hence ignores the following promotions. It uses its own
// emulation layer from the compiler-rt library.

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Inline intrinsics - calling SoftFloat library functions

// operations
inline     float32_t           wrap_f32_add      (float32_t a, float32_t b) { return f32_add(a,b); }
inline     float32_t           wrap_f32_sub      (float32_t a, float32_t b) { return f32_sub(a,b); }
inline     float32_t           wrap_f32_mul      (float32_t a, float32_t b) { return f32_mul(a,b); }
inline     float32_t           wrap_f32_div      (float32_t a, float32_t b) { return f32_div(a,b); }

// comparisons
inline     bool                wrap_f32_lt       (float32_t a, float32_t b) { return f32_lt(a,b); }
inline     bool                wrap_f32_le       (float32_t a, float32_t b) { return f32_le(a,b); }
inline     bool                wrap_f32_eq       (float32_t a, float32_t b) { return f32_eq(a,b); }

// float<>int conversions
inline       signed int        wrap_f32_to_i32   (float32_t a)              { return f32_to_i32_r_minMag(a, false); }
inline     unsigned int        wrap_f32_to_ui32  (float32_t a)              { return f32_to_ui32_r_minMag(a, false); }
inline     float32_t           wrap_i32_to_f32   (signed int a)             { return i32_to_f32(a); }
inline     float32_t           wrap_ui32_to_f32  (unsigned int a)           { return ui32_to_f32(a); }

// float<>longlong conversions
inline       signed long long  wrap_f32_to_i64   (float32_t a)              { return f32_to_i64_r_minMag(a, false); }
inline     unsigned long long  wrap_f32_to_ui64  (float32_t a)              { return f32_to_ui64_r_minMag(a, false); }
inline     float32_t           wrap_i64_to_f32   (signed long long a)       { return i64_to_f32(a); }
inline     float32_t           wrap_ui64_to_f32  (unsigned long long a)     { return ui64_to_f32(a); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Operators - promoted onto inline intrinsics

// operations
promotion  float  operator +  (float,float) = float32_t              wrap_f32_add     (float32_t,float32_t);
promotion  float  operator -  (float,float) = float32_t              wrap_f32_sub     (float32_t,float32_t);
promotion  float  operator *  (float,float) = float32_t              wrap_f32_mul     (float32_t,float32_t);
promotion  float  operator /  (float,float) = float32_t              wrap_f32_div     (float32_t,float32_t);

// comparisons
promotion  bool   operator <  (float,float) = bool                   wrap_f32_lt      (float32_t,float32_t);
promotion  bool   operator <= (float,float) = bool                   wrap_f32_le      (float32_t,float32_t);
promotion  bool   operator == (float,float) = bool                   wrap_f32_eq      (float32_t,float32_t);

// float<>int conversions
promotion  operator    signed int(float) =   signed int              wrap_f32_to_i32  (float32_t);
promotion  operator  unsigned int(float) = unsigned int              wrap_f32_to_ui32 (float32_t);
promotion  operator  float(  signed int) = float32_t                 wrap_i32_to_f32  (  signed int);
promotion  operator  float(unsigned int) = float32_t                 wrap_ui32_to_f32 (unsigned int);

// float<>longlong conversions
promotion  operator    signed long long(float) =   signed long long  wrap_f32_to_i64  (float32_t);
promotion  operator  unsigned long long(float) = unsigned long long  wrap_f32_to_ui64 (float32_t);
promotion  operator  float(  signed long long) = float32_t           wrap_i64_to_f32  (  signed long long);
promotion  operator  float(unsigned long long) = float32_t           wrap_ui64_to_f32 (unsigned long long);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Inline operators - defined in terms of other operators

// map comparison operators on counterparts
inline  bool  operator >= (float a, float b) { return (b<=a); }
inline  bool  operator >  (float a, float b) { return (b<a); }
inline  bool  operator != (float a, float b) { return !(a==b); }

// map some conversions onto int<>flt conversions
inline  operator  float(  signed char a) { return (float)(  signed int)a; }
inline  operator    signed char(float a) { return (  signed char)(  signed int)a; }

inline  operator  float(  signed short a) { return (float)(  signed int)a; }
inline  operator    signed short(float a) { return (  signed short)(  signed int)a; }

inline  operator  float(unsigned char a) { return (float)(unsigned int)a; }
inline  operator  unsigned char(float a) { return (unsigned char)(unsigned int)a; }

inline  operator  float(unsigned short a) { return (float)(unsigned int)a; }
inline  operator  unsigned short(float a) { return (unsigned short)(unsigned int)a; }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Reinterpret functions

// float behaves like unsigned int
promotion   signed int as_int32(float) property(reinterpret) = nil;
promotion float as_float(  signed int) property(reinterpret) = nil;

#endif /* INCLUDED_TRV32P3_FLOAT_H_ */
