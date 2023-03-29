/*
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P5_C_SOFTFLOAT_H__
#define INCLUDED_TRV32P5_C_SOFTFLOAT_H__

// This is a filtered copy of softfloat/SoftFloat-3e/source/include/softfloat.h
// It includes only function declaration that we need. Also, avoid to import
// too many typedef's into the global namespace.
//
// CHECK consistency with softfloat.h if changes appear

typedef  float   float32_t  chess_dont_generate;
typedef  double  float64_t  chess_dont_generate;

// noodle +Oextc set in softfloat.prx
extern "C" {

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Integer-to-floating-point Conversion Routines.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

float32_t  ui32_to_f32 ( unsigned int )                                    property(functional dont_generate);
float64_t  ui32_to_f64 ( unsigned int )                                    property(functional dont_generate);
float32_t  i32_to_f32  (   signed int )                                    property(functional dont_generate);
float64_t  i32_to_f64  (   signed int )                                    property(functional dont_generate);
float32_t  ui64_to_f32 ( unsigned long long )                              property(functional dont_generate);
float64_t  ui64_to_f64 ( unsigned long long )                              property(functional dont_generate);
float32_t  i64_to_f32  (   signed long long )                              property(functional dont_generate);
float64_t  i64_to_f64  (   signed long long )                              property(functional dont_generate);


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ 32-bit (single-precision) Floating-point Operations.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

unsigned long      f32_to_ui32_r_minMag ( float32_t, bool )                property(functional dont_generate);
unsigned long long f32_to_ui64_r_minMag ( float32_t, bool )                property(functional dont_generate);
  signed long      f32_to_i32_r_minMag  ( float32_t, bool )                property(functional dont_generate);
  signed long long f32_to_i64_r_minMag  ( float32_t, bool )                property(functional dont_generate);
float64_t          f32_to_f64           ( float32_t )                      property(functional dont_generate);
float32_t          f32_roundToInt       ( float32_t, unsigned long, bool ) property(functional dont_generate);
float32_t          f32_add              ( float32_t, float32_t )           property(functional dont_generate);
float32_t          f32_sub              ( float32_t, float32_t )           property(functional dont_generate);
float32_t          f32_mul              ( float32_t, float32_t )           property(functional dont_generate);
float32_t          f32_div              ( float32_t, float32_t )           property(functional dont_generate);
bool               f32_eq               ( float32_t, float32_t )           property(functional dont_generate);
bool               f32_le               ( float32_t, float32_t )           property(functional dont_generate);
bool               f32_lt               ( float32_t, float32_t )           property(functional dont_generate);


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ 64-bit (double-precision) Floating-point Operations.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

unsigned long      f64_to_ui32_r_minMag ( float64_t, bool )                property(functional dont_generate);
unsigned long long f64_to_ui64_r_minMag ( float64_t, bool )                property(functional dont_generate);
  signed long      f64_to_i32_r_minMag  ( float64_t, bool )                property(functional dont_generate);
  signed long long f64_to_i64_r_minMag  ( float64_t, bool )                property(functional dont_generate);
float32_t          f64_to_f32           ( float64_t )                      property(functional dont_generate);
float64_t          f64_roundToInt       ( float64_t, unsigned long, bool ) property(functional dont_generate);
float64_t          f64_add              ( float64_t, float64_t )           property(functional dont_generate);
float64_t          f64_sub              ( float64_t, float64_t )           property(functional dont_generate);
float64_t          f64_mul              ( float64_t, float64_t )           property(functional dont_generate);
float64_t          f64_div              ( float64_t, float64_t )           property(functional dont_generate);
bool               f64_eq               ( float64_t, float64_t )           property(functional dont_generate);
bool               f64_le               ( float64_t, float64_t )           property(functional dont_generate);
bool               f64_lt               ( float64_t, float64_t )           property(functional dont_generate);

} // extern "C"

#endif // INCLUDED_TRV32P5_C_SOFTFLOAT_H__
