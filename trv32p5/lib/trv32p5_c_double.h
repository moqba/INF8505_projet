/*
-- File : trv32p5_c_double.h
--
-- Contents : Double-precision floating  point application layer for
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

#ifndef INCLUDED_TRV32P5_C_DOUBLE_H_
#define INCLUDED_TRV32P5_C_DOUBLE_H_

// NOTE: Application types float & double have property llvm_emulated. The
// LLVM frontend hence ignores the following promotions. It uses its own
// emulation layer from the compiler-rt library.

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Inline intrinsics - calling SoftFloat library functions

// operations
inline     float64_t           wrap_f64_add      (float64_t a, float64_t b) property(dont_generate) { return f64_add  (a,b); }
inline     float64_t           wrap_f64_sub      (float64_t a, float64_t b) property(dont_generate) { return f64_sub  (a,b); }
inline     float64_t           wrap_f64_mul      (float64_t a, float64_t b) property(dont_generate) { return f64_mul  (a,b); }
inline     float64_t           wrap_f64_div      (float64_t a, float64_t b) property(dont_generate) { return f64_div  (a,b); }

// comparisons
inline     bool                wrap_f64_lt       (float64_t a, float64_t b) property(dont_generate) { return f64_lt   (a,b); }
inline     bool                wrap_f64_le       (float64_t a, float64_t b) property(dont_generate) { return f64_le   (a,b); }
inline     bool                wrap_f64_eq       (float64_t a, float64_t b) property(dont_generate) { return f64_eq   (a,b); }

// double<>float conversions
inline     float64_t           wrap_f32_to_f64   (float32_t a)              property(dont_generate) { return f32_to_f64            (a); }
inline     float32_t           wrap_f64_to_f32   (float64_t a)              property(dont_generate) { return f64_to_f32            (a); }

// double<>int conversions
inline       signed int        wrap_f64_to_i32   (float64_t a)              property(dont_generate) { return f64_to_i32_r_minMag   (a, true); }
inline     unsigned int        wrap_f64_to_ui32  (float64_t a)              property(dont_generate) { return f64_to_ui32_r_minMag  (a, true); }
inline     float64_t           wrap_i32_to_f64   (signed int a)             property(dont_generate) { return i32_to_f64           (a); }
inline     float64_t           wrap_ui32_to_f64  (unsigned int a)           property(dont_generate) { return ui32_to_f64        (a); }

// double<>longlong conversions
inline       signed long long  wrap_f64_to_i64   (float64_t a)              property(dont_generate) { return f64_to_i64_r_minMag   (a, true); }
inline     unsigned long long  wrap_f64_to_ui64  (float64_t a)              property(dont_generate) { return f64_to_ui64_r_minMag  (a, true); }
inline     float64_t           wrap_i64_to_f64   (signed long long a)       property(dont_generate) { return i64_to_f64     (a); }
inline     float64_t           wrap_ui64_to_f64  (unsigned long long a)     property(dont_generate) { return ui64_to_f64  (a); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Operators - promoted onto inline intrinsics

// operations
promotion  double operator +  (double,double) = float64_t             wrap_f64_add     (float64_t,float64_t);
promotion  double operator -  (double,double) = float64_t             wrap_f64_sub     (float64_t,float64_t);
promotion  double operator *  (double,double) = float64_t             wrap_f64_mul     (float64_t,float64_t);
promotion  double operator /  (double,double) = float64_t             wrap_f64_div     (float64_t,float64_t);

// comparisons
promotion  bool   operator <  (double,double) = bool                  wrap_f64_lt      (float64_t,float64_t);
promotion  bool   operator <= (double,double) = bool                  wrap_f64_le      (float64_t,float64_t);
promotion  bool   operator == (double,double) = bool                  wrap_f64_eq      (float64_t,float64_t);

// double<>float conversions
promotion  operator  double(float) = float64_t                        wrap_f32_to_f64  (float32_t);
promotion  operator  float(double) = float32_t                        wrap_f64_to_f32  (float64_t);

// double<>int conversions
promotion  operator    signed int(double) =   signed int              wrap_f64_to_i32  (float64_t);
promotion  operator  unsigned int(double) = unsigned int              wrap_f64_to_ui32 (float64_t);
promotion  operator  double(  signed int) = float64_t                 wrap_i32_to_f64  (  signed int);
promotion  operator  double(unsigned int) = float64_t                 wrap_ui32_to_f64 (unsigned int);

// double<>longlong conversions
promotion  operator    signed long long(double) =   signed long long  wrap_f64_to_i64  (float64_t);
promotion  operator  unsigned long long(double) = unsigned long long  wrap_f64_to_ui64 (float64_t);
promotion  operator  double(  signed long long) = float64_t           wrap_i64_to_f64  (  signed long long);
promotion  operator  double(unsigned long long) = float64_t           wrap_ui64_to_f64 (unsigned long long);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Inline Operators - defined in terms of other operators

// map comparison operators on counterparts
inline  bool  operator >= (double a, double b) { return (b<=a); }
inline  bool  operator >  (double a, double b) { return (b<a); }
inline  bool  operator != (double a, double b) { return !(a==b); }

// map some conversions onto int<>dbl conversions
inline  operator  double (  signed char a)  { return (double)(  signed int)a; }
inline  operator  double (unsigned char a)  { return (double)(unsigned int)a; }
inline  operator    signed char (double a)  { return (  signed char)(  signed int)a; }
inline  operator  unsigned char (double a)  { return (unsigned char)(unsigned int)a; }

inline  operator  double (  signed short a) { return (double)(  signed int)a; }
inline  operator  double (unsigned short a) { return (double)(unsigned int)a; }
inline  operator    signed short (double a) { return (  signed short)(  signed int)a; }
inline  operator  unsigned short (double a) { return (unsigned short)(unsigned int)a; }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Reinterpret Functions

promotion  signed long long as_int64  (double)           property(reinterpret) = nil;
promotion  double           as_double (signed long long) property(reinterpret) = nil;


#endif /* INCLUDED_TRV32P5_C_DOUBLE_H_ */
