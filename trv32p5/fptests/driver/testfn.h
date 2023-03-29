/*
-- Copyright (c) 2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TESTFN_H__
#define INCLUDED_TESTFN_H__

// float - basic arithmetic operations
float fn_f32_add(float, float);
float fn_f32_sub(float, float);
float fn_f32_mul(float, float);
float fn_f32_div(float, float);
float fn_f32_sqrt(float); // not available

// float - remainder
float fn_f32_rem(float, float); // not available

// float - round-to-integer
float fn_f32_rnd(float); // not available

// float - fused muladd
float fn_f32_fma(float, float, float); // not available

// float comparisons
bool fn_f32_eq(float, float);
bool fn_f32_le(float, float);
bool fn_f32_lt(float, float);

// float<>int32
int fn_f32_to_i32(float);
unsigned fn_f32_to_ui32(float);
float fn_i32_to_f32(int);
float fn_ui32_to_f32(unsigned);

// float<>int64
long long fn_f32_to_i64(float);
unsigned long long fn_f32_to_ui64(float);
float fn_i64_to_f32(long long);
float fn_ui64_to_f32(unsigned long long);

// double - basic arithmetic operations
double fn_f64_add(double, double);
double fn_f64_sub(double, double);
double fn_f64_mul(double, double);
double fn_f64_div(double, double);
double fn_f64_sqrt(double); // not available

// double - remainder
double fn_f64_rem(double, double); // not available

// double - round-to-integer
double fn_f64_rnd(double); // not available

// double - fused muladd
double fn_f64_fma(double, double, double); // not available

// double comparisons
bool fn_f64_eq(double, double);
bool fn_f64_le(double, double);
bool fn_f64_lt(double, double);

// double<>int32
int fn_f64_to_i32(double);
unsigned fn_f64_to_ui32(double);
double fn_i32_to_f64(int);
double fn_ui32_to_f64(unsigned);

// float<>int64
long long fn_f64_to_i64(double);
unsigned long long fn_f64_to_ui64(double);
double fn_i64_to_f64(long long);
double fn_ui64_to_f64(unsigned long long);

// float<>double
double fn_f32_to_f64(float);
float fn_f64_to_f32(double);


#endif // def INCLUDED_TESTFN_H__
