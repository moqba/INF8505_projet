#ifndef INCLUDED_TESTFN_H__
#define INCLUDED_TESTFN_H__

// float
float fn_f32_add(float x, float y);

float fn_f32_sub(float x, float y);
float fn_f32_mul(float x, float y);
float fn_f32_div(float x, float y);
float fn_f32_rem(float, float); // not available
float fn_f32_sqrt(float x);
float fn_f32_rnd(float x);

// float comparisons
bool fn_f32_eq(float x, float y);
bool fn_f32_le(float x, float y);
bool fn_f32_lt(float x, float y);

// float<>int32
int fn_f32_to_i32(float x);
unsigned fn_f32_to_ui32(float x);
float fn_i32_to_f32(int x);
float fn_ui32_to_f32(unsigned x);

//// float<>int64
//long long fn_f32_to_i64(float x);
//unsigned long long fn_f32_to_ui64(float x);
//float fn_i64_to_f32(long long x);
//float fn_ui64_to_f32(unsigned long long x);

// double
double fn_f64_add(double x, double y);
double fn_f64_sub(double x, double y);
double fn_f64_mul(double x, double y);
double fn_f64_div(double x, double y);
double fn_f64_rem(double, double); // not available
double fn_f64_sqrt(double x);
double fn_f64_rnd(double x);

// double comparisons
bool fn_f64_eq(double x, double y);
bool fn_f64_le(double x, double y);
bool fn_f64_lt(double x, double y);

// double<>int32
int fn_f64_to_i32(double x);
unsigned fn_f64_to_ui32(double x);
double fn_i32_to_f64(int x);
double fn_ui32_to_f64(unsigned x);

//// double<>int64
//long long fn_f64_to_i64(double x);
//unsigned long long fn_f64_to_ui64(double x);
//double fn_i64_to_f64(long long x);
//double fn_ui64_to_f64(unsigned long long x);

// float<>double
double fn_f32_to_f64(float x);
float fn_f64_to_f32(double x);


#endif // def INCLUDED_TESTFN_H__
