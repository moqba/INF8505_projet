/*
-- Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P3_SOFTFLOAT_H__
#define INCLUDED_TRV32P3_SOFTFLOAT_H__

// This is a filtered copy of softfloat/SoftFloat-3e/source/include/softfloat.h
// It includes only function declaration that we need. Also, avoid to import
// too many typedef's into the global namespace.
//
// CHECK consistency with softfloat.h if changes appear

typedef float   float32_t;
typedef double  float64_t;

// noodle +Oextc set in softfloat.prx
extern "C" {

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Integer-to-floating-point conversion routines.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

float32_t  ui32_to_f32 ( unsigned int )                                   [[chess::functional]];
float64_t  ui32_to_f64 ( unsigned int )                                   [[chess::functional]];
float32_t  i32_to_f32  (   signed int )                                   [[chess::functional]];
float64_t  i32_to_f64  (   signed int )                                   [[chess::functional]];
float32_t  ui64_to_f32 ( unsigned long long )                             [[chess::functional]];
float64_t  ui64_to_f64 ( unsigned long long )                             [[chess::functional]];
float32_t  i64_to_f32  (   signed long long )                             [[chess::functional]];
float64_t  i64_to_f64  (   signed long long )                             [[chess::functional]];


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ 32-bit (single-precision) floating-point operations.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

unsigned int       f32_to_ui32_r_minMag ( float32_t, bool )               [[chess::functional]];
unsigned long long f32_to_ui64_r_minMag ( float32_t, bool )               [[chess::functional]];
  signed int       f32_to_i32_r_minMag  ( float32_t, bool )               [[chess::functional]];
  signed long long f32_to_i64_r_minMag  ( float32_t, bool )               [[chess::functional]];
float64_t          f32_to_f64           ( float32_t )                     [[chess::functional]];
float32_t          f32_roundToInt       ( float32_t, unsigned int, bool ) [[chess::functional]];
float32_t          f32_add              ( float32_t, float32_t )          [[chess::functional]];
float32_t          f32_sub              ( float32_t, float32_t )          [[chess::functional]];
float32_t          f32_mul              ( float32_t, float32_t )          [[chess::functional]];
float32_t          f32_div              ( float32_t, float32_t )          [[chess::functional]];
bool               f32_eq               ( float32_t, float32_t )          [[chess::functional]];
bool               f32_le               ( float32_t, float32_t )          [[chess::functional]];
bool               f32_lt               ( float32_t, float32_t )          [[chess::functional]];


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ 64-bit (double-precision) floating-point operations.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

unsigned int       f64_to_ui32_r_minMag ( float64_t, bool )               [[chess::functional]];
unsigned long long f64_to_ui64_r_minMag ( float64_t, bool )               [[chess::functional]];
  signed int       f64_to_i32_r_minMag  ( float64_t, bool )               [[chess::functional]];
  signed long long f64_to_i64_r_minMag  ( float64_t, bool )               [[chess::functional]];
float32_t          f64_to_f32           ( float64_t )                     [[chess::functional]];
float64_t          f64_roundToInt       ( float64_t, unsigned int, bool ) [[chess::functional]];
float64_t          f64_add              ( float64_t, float64_t )          [[chess::functional]];
float64_t          f64_sub              ( float64_t, float64_t )          [[chess::functional]];
float64_t          f64_mul              ( float64_t, float64_t )          [[chess::functional]];
float64_t          f64_div              ( float64_t, float64_t )          [[chess::functional]];
bool               f64_eq               ( float64_t, float64_t )          [[chess::functional]];
bool               f64_le               ( float64_t, float64_t )          [[chess::functional]];
bool               f64_lt               ( float64_t, float64_t )          [[chess::functional]];

} // extern "C"

#endif
