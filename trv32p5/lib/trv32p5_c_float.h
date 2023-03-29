/*
-- File : trv32p5_c_float.h
--
-- Contents : Single-precision floating point application layer for
--            the trv32p5 processor.
--
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P5_C_FLOAT_H_
#define INCLUDED_TRV32P5_C_FLOAT_H_

#include "trv32p5_c_softfloat.h"

// Concept:
// wrapper intrinsic: call softfloat function
// promote builtin operator on wrapper intrinsic that calls the emulation library

// NOTE: Application types float & double have property llvm_emulated. The
// LLVM frontend hence ignores the following promotions. It uses its own
// emulation layer from the compiler-rt library.

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Inline Intrinsics - Calling SoftFloat library functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ SoftFloat: float <> int conversions

inline   signed int wrap_f32_to_i32  (float32_t a)    property(dont_generate) { return f32_to_i32_r_minMag  (a, true); }
inline unsigned int wrap_f32_to_ui32 (float32_t a)    property(dont_generate) { return f32_to_ui32_r_minMag (a, true); }
inline float32_t    wrap_i32_to_f32  (  signed int a) property(dont_generate) { return i32_to_f32           (a); }
inline float32_t    wrap_ui32_to_f32 (unsigned int a) property(dont_generate) { return ui32_to_f32          (a); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ SoftFloat: float <> long long conversions

inline   signed long long wrap_f32_to_i64  (float32_t a)          property(dont_generate) { return f32_to_i64_r_minMag  (a, true); }
inline unsigned long long wrap_f32_to_ui64 (float32_t a)          property(dont_generate) { return f32_to_ui64_r_minMag (a, true); }
inline float32_t          wrap_i64_to_f32  (  signed long long a) property(dont_generate) { return i64_to_f32           (a); }
inline float32_t          wrap_ui64_to_f32 (unsigned long long a) property(dont_generate) { return ui64_to_f32          (a); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ SoftFloat: Arithmetic Operations

inline float32_t wrap_f32_add (float32_t a, float32_t b) property(dont_generate) { return f32_add (a,b); }
inline float32_t wrap_f32_sub (float32_t a, float32_t b) property(dont_generate) { return f32_sub (a,b); }
inline float32_t wrap_f32_mul (float32_t a, float32_t b) property(dont_generate) { return f32_mul (a,b); }
inline float32_t wrap_f32_div (float32_t a, float32_t b) property(dont_generate) { return f32_div (a,b); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ SoftFloat: Comparisons

inline bool wrap_f32_lt (float32_t a, float32_t b) property(dont_generate) { return f32_lt (a,b); }
inline bool wrap_f32_le (float32_t a, float32_t b) property(dont_generate) { return f32_le (a,b); }
inline bool wrap_f32_eq (float32_t a, float32_t b) property(dont_generate) { return f32_eq (a,b); }


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Type Conversions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Emulated: float <> int

promotion operator   signed int ( float )        =   signed int wrap_f32_to_i32  (float32_t);
promotion operator unsigned int ( float )        = unsigned int wrap_f32_to_ui32 (float32_t);
promotion operator float        (   signed int ) = float32_t    wrap_i32_to_f32  (  signed int);
promotion operator float        ( unsigned int ) = float32_t    wrap_ui32_to_f32 (unsigned int);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Emulated: float <> long long

promotion operator   signed long long ( float )              =   signed long long wrap_f32_to_i64 (float32_t);
promotion operator unsigned long long ( float )              = unsigned long long wrap_f32_to_ui64 (float32_t);
promotion operator float              (   signed long long ) = float32_t          wrap_i64_to_f32  (  signed long long);
promotion operator float              ( unsigned long long ) = float32_t          wrap_ui64_to_f32 (unsigned long long);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Remap: float <> char - reuse float <> int

inline operator  float         (   signed char a ) { return (float)         (  signed int)a; }
inline operator  float         ( unsigned char a ) { return (float)         (unsigned int)a; }
inline operator    signed char ( float a )         { return (  signed char) (  signed int)a; }
inline operator  unsigned char ( float a )         { return (unsigned char) (unsigned int)a; }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Remap: float <> short - reuse float <> int

inline operator float          (   signed short a ) { return (float)          (  signed int)a; }
inline operator float          ( unsigned short a ) { return (float)          (unsigned int)a; }
inline operator   signed short ( float a )          { return (  signed short) (  signed int)a; }
inline operator unsigned short ( float a )          { return (unsigned short) (unsigned int)a; }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Arithmetic Operators
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Emulated: Binary Operators

promotion float operator + (float,float) = float32_t wrap_f32_add (float32_t,float32_t);
promotion float operator - (float,float) = float32_t wrap_f32_sub (float32_t,float32_t);
promotion float operator * (float,float) = float32_t wrap_f32_mul (float32_t,float32_t);
promotion float operator / (float,float) = float32_t wrap_f32_div (float32_t,float32_t);


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Comparison Operators
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Emulated
promotion bool operator <  (float a, float b) = bool wrap_f32_lt (float32_t,float32_t);
promotion bool operator <= (float a, float b) = bool wrap_f32_le (float32_t,float32_t);
promotion bool operator == (float a, float b) = bool wrap_f32_eq (float32_t,float32_t);
inline    bool operator != (float a, float b) { return !(a==b); }
inline    bool operator >  (float a, float b) { return (b <  a); } // a,b swapped
inline    bool operator >= (float a, float b) { return (b <= a); } // a,b swapped


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Reinterpret Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// float behaves like unsigned int
promotion int   as_int32 (float) property(reinterpret) = nil;
promotion float as_float (int)   property(reinterpret) = nil;

#endif /* INCLUDED_TRV32P5_C_FLOAT_H_ */
