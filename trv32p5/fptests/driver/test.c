/*
-- Copyright (c) 2018-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "testfn.h"

// NOTE We copy the flags from input to output.
// NOTE Unsupported test cases can simply be discarded, e.g. if denormals
//      are not supported. Reference result is part of input.

void testfn_f32_op1_ff(float fn(float)) {
  int flags;
  uint32_t x, z;
  while (scanf("%08X %08X %02X", &x, &z, &flags)!=EOF) {
    uint32_t r = as_int32(fn(as_float(x)));
    printf("%08X %08X %02X\n",x,r,flags);
  }
}

void testfn_f32_op2_fff(float fn(float,float)) {
  int flags;
  uint32_t x, y, z;
  while (scanf("%08X %08X %08X %02X", &x, &y, &z, &flags)!=EOF) {
    uint32_t r = as_int32(fn(as_float(x),as_float(y)));
    printf("%08X %08X %08X %02X\n",x,y,r,flags);
  }
}

void testfn_f32_op3_ffff(float fn(float,float,float)) {
  int flags;
  uint32_t x, y, z, w;
  while (scanf("%08X %08X %08X %08X %02X", &x, &y, &z, &w, &flags)!=EOF) {
    uint32_t r = as_int32(fn(as_float(x),as_float(y),as_float(z)));
    printf("%08X %08X %08X %08X %02X\n",x,y,z,r,flags);
  }
}

void testfn_f32_op2_bff(bool fn(float,float)) {
  int flags;
  uint32_t x, y, z;
  while (scanf("%08X %08X %01X %02X", &x, &y, &z, &flags)!=EOF) {
    bool r = fn(as_float(x),as_float(y));
    printf("%08X %08X %01X %02X\n",x,y,r,flags);
  }
}

void testfn_f32_to_i32() {
  int flags;
  uint32_t x, z;
  while (scanf("%08X %08X %02X", &x, &z, &flags)!=EOF) {
    int32_t r = fn_f32_to_i32(as_float(x));
    printf("%08X %08X %02X\n",x,r,flags);
  }
}

void testfn_f32_to_ui32() {
  int flags;
  uint32_t x, z;
  while (scanf("%08X %08X %02X", &x, &z, &flags)!=EOF) {
    uint32_t r = fn_f32_to_ui32(as_float(x));
    printf("%08X %08X %02X\n",x,r,flags);
  }
}

void testfn_i32_to_f32() {
  int flags;
  int32_t x;
  uint32_t z;
  while (scanf("%08X %08X %02X", &x, &z, &flags)!=EOF) {
    uint32_t r = as_int32(fn_i32_to_f32(x));
    printf("%08X %08X %02X\n",x,r,flags);
  }
}

void testfn_ui32_to_f32() {
  int flags;
  uint32_t x, z;
  while (scanf("%08X %08X %02X", &x, &z, &flags)!=EOF) {
    uint32_t r = as_int32(fn_ui32_to_f32(x));
    printf("%08X %08X %02X\n",x,r,flags);
  }
}

void testfn_f32_to_i64() {
  int flags;
  uint32_t x;
  uint64_t z;
  while (scanf("%08X %016llX %02X", &x, &z, &flags)!=EOF) {
    int64_t r = fn_f32_to_i64(as_float(x));
    printf("%08X %016llX %02X\n",x,r,flags);
  }
}

void testfn_f32_to_ui64() {
  int flags;
  uint32_t x;
  uint64_t z;
  while (scanf("%08X %016llX %02X", &x, &z, &flags)!=EOF) {
    uint64_t r = fn_f32_to_ui64(as_float(x));
    printf("%08X %016llX %02X\n",x,r,flags);
  }
}

void testfn_i64_to_f32() {
  int flags;
  int64_t x;
  uint32_t z;
  while (scanf("%016llX %08X %02X", &x, &z, &flags)!=EOF) {
    uint32_t r = as_int32(fn_i64_to_f32(x));
    printf("%016llX %08X %02X\n",x,r,flags);
  }
}

void testfn_ui64_to_f32() {
  int flags;
  uint64_t x;
  uint32_t z;
  while (scanf("%016llX %08X %02X", &x, &z, &flags)!=EOF) {
    uint32_t r = as_int32(fn_ui64_to_f32(x));
    printf("%016llX %08X %02X\n",x,r,flags);
  }
}

void testfn_f64_op2_ddd(double fn(double,double)) {
  int flags;
  uint64_t x, y, z;
  while (scanf("%016llX %016llX %016llX %02X", &x, &y, &z, &flags)!=EOF) {
    uint64_t r = as_int64(fn(as_double(x),as_double(y)));
    printf("%016llX %016llX %016llX %02X\n",x,y,r,flags);
  }
}

void testfn_f64_op3_dddd(double fn(double,double,double)) {
  int flags;
  uint64_t x, y, z, w;
  while (scanf("%016llX %016llX %016llX %016llX %02X", &x, &y, &z, &w, &flags)!=EOF) {
    uint64_t r = as_int64(fn(as_double(x),as_double(y),as_double(z)));
    printf("%016llX %016llX %016llX %016llX %02X\n",x,y,z,r,flags);
  }
}

void testfn_f64_op1_dd(double fn(double)) {
  int flags;
  uint64_t x, z;
  while (scanf("%016llX %016llX %02X", &x, &z, &flags)!=EOF) {
    uint64_t r = as_int64(fn(as_double(x)));
    printf("%016llX %016llX %02X\n",x,r,flags);
  }
}

void testfn_f64_to_i32() {
  int flags;
  uint64_t x;
  uint32_t z;
  while (scanf("%016llX %08X %02X", &x, &z, &flags)!=EOF) {
    int32_t r = fn_f64_to_i32(as_double(x));
    printf("%016llX %08X %02X\n",x,r,flags);
  }
}

void testfn_f64_to_ui32() {
  int flags;
  uint64_t x;
  uint32_t z;
  while (scanf("%016llX %08X %02X", &x, &z, &flags)!=EOF) {
    uint32_t r = fn_f64_to_ui32(as_double(x));
    printf("%016llX %08X %02X\n",x,r,flags);
  }
}

void testfn_i32_to_f64() {
  int flags;
  int32_t x;
  uint64_t z;
  while (scanf("%08X %016llX %02X", &x, &z, &flags)!=EOF) {
    uint64_t r = as_int64(fn_i32_to_f64(x));
    printf("%08X %016llX %02X\n",x,r,flags);
  }
}

void testfn_ui32_to_f64() {
  int flags;
  uint32_t x;
  uint64_t z;
  while (scanf("%08X %016llX %02X", &x, &z, &flags)!=EOF) {
    uint64_t r = as_int64(fn_ui32_to_f64(x));
    printf("%08X %016llX %02X\n",x,r,flags);
  }
}

void testfn_f64_to_i64() {
  int flags;
  uint64_t x, z;
  while (scanf("%016llX %016llX %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(x)) continue;
    int64_t r = fn_f64_to_i64(as_double(x));
    printf("%016llX %016llX %02X\n",x,r,flags);
  }
}

void testfn_f64_to_ui64() {
  int flags;
  uint64_t x, z;
  while (scanf("%016llX %016llX %02X", &x, &z, &flags)!=EOF) {
    uint64_t r = fn_f64_to_ui64(as_double(x));
    printf("%016llX %016llX %02X\n",x,r,flags);
  }
}

void testfn_i64_to_f64() {
  int flags;
  int64_t x;
  uint64_t z;
  while (scanf("%016llX %016llX %02X", &x, &z, &flags)!=EOF) {
    uint64_t r = as_int64(fn_i64_to_f64(x));
    printf("%016llX %016llX %02X\n",x,r,flags);
  }
}

void testfn_ui64_to_f64() {
  int flags;
  uint64_t x, z;
  while (scanf("%016llX %016llX %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(z)) continue;
    uint64_t r = as_int64(fn_ui64_to_f64(x));
    printf("%016llX %016llX %02X\n",x,r,flags);
  }
}

void testfn_f64_op2_bdd(bool fn(double,double)) {
  int flags;
  uint64_t x, y, z;
  while (scanf("%016llX %016llX %01X %02X", &x, &y, &z, &flags)!=EOF) {
    bool r = fn(as_double(x),as_double(y));
    printf("%016llX %016llX %01X %02X\n",x,y,r,flags);
  }
}

void testfn_f32_to_f64() {
  int flags;
  uint32_t x;
  uint64_t z;
  while (scanf("%08X %016llX %02X", &x, &z, &flags)!=EOF) {
    uint64_t r = as_int64(fn_f32_to_f64(as_float(x)));
    printf("%08X %016llX %02X\n",x,r,flags);
  }
}

void testfn_f64_to_f32() {
  int flags;
  uint64_t x;
  uint32_t z;
  while (scanf("%016llX %08X %02X", &x, &z, &flags)!=EOF) {
    uint32_t r = as_int32(fn_f64_to_f32(as_double(x)));
    printf("%016llX %08X %02X\n",x,r,flags);
  }
}

void rv_write_frm(int) {}

int main(int argc, char *argv[]) {
  // parse command line
  const char *argPtr;
  for (;;) {
    --argc;
    if ( ! argc ) break;
    argPtr = *++argv;
    if ( ! argPtr ) break;
    //
    if ( ! strcmp( argPtr, "near_even" ) )     { rv_write_frm(0); continue; }
    if ( ! strcmp( argPtr, "minMag" ) )        { rv_write_frm(1); continue; }
    if ( ! strcmp( argPtr, "min" ) )           { rv_write_frm(2); continue; }
    if ( ! strcmp( argPtr, "max" ) )           { rv_write_frm(3); continue; }
    if ( ! strcmp( argPtr, "near_maxMag" ) )   { rv_write_frm(4); continue; }
    // ---------
    if ( ! strcmp( argPtr, "f32_add" ) )        { testfn_f32_op2_fff(fn_f32_add); return 0; }
    if ( ! strcmp( argPtr, "f32_sub" ) )        { testfn_f32_op2_fff(fn_f32_sub); return 0; }
    if ( ! strcmp( argPtr, "f32_mul" ) )        { testfn_f32_op2_fff(fn_f32_mul); return 0; }
    if ( ! strcmp( argPtr, "f32_div" ) )        { testfn_f32_op2_fff(fn_f32_div); return 0; }
    if ( ! strcmp( argPtr, "f32_rem" ) )        { testfn_f32_op2_fff(fn_f32_rem); return 0; }
    if ( ! strcmp( argPtr, "f32_mulAdd" ) )     { testfn_f32_op3_ffff(fn_f32_fma); return 0; }
    if ( ! strcmp( argPtr, "f32_sqrt" ) )       { testfn_f32_op1_ff(fn_f32_sqrt); return 0; }
    if ( ! strcmp( argPtr, "f32_roundToInt" ) ) { testfn_f32_op1_ff(fn_f32_rnd); return 0; }
    if ( ! strcmp( argPtr, "f32_to_i32" ) )     { testfn_f32_to_i32(); return 0; }
    if ( ! strcmp( argPtr, "f32_to_ui32" ) )    { testfn_f32_to_ui32(); return 0; }
    if ( ! strcmp( argPtr, "i32_to_f32" ) )     { testfn_i32_to_f32(); return 0; }
    if ( ! strcmp( argPtr, "ui32_to_f32" ) )    { testfn_ui32_to_f32(); return 0; }
    if ( ! strcmp( argPtr, "f32_to_i64" ) )     { testfn_f32_to_i64(); return 0; }
    if ( ! strcmp( argPtr, "f32_to_ui64" ) )    { testfn_f32_to_ui64(); return 0; }
    if ( ! strcmp( argPtr, "i64_to_f32" ) )     { testfn_i64_to_f32(); return 0; }
    if ( ! strcmp( argPtr, "ui64_to_f32" ) )    { testfn_ui64_to_f32(); return 0; }
    if ( ! strcmp( argPtr, "f32_eq" ) )         { testfn_f32_op2_bff(fn_f32_eq); return 0; }
    if ( ! strcmp( argPtr, "f32_le" ) )         { testfn_f32_op2_bff(fn_f32_le); return 0; }
    if ( ! strcmp( argPtr, "f32_lt" ) )         { testfn_f32_op2_bff(fn_f32_lt); return 0; }
    if ( ! strcmp( argPtr, "f64_add" ) )        { testfn_f64_op2_ddd(fn_f64_add); return 0; }
    if ( ! strcmp( argPtr, "f64_sub" ) )        { testfn_f64_op2_ddd(fn_f64_sub); return 0; }
    if ( ! strcmp( argPtr, "f64_mul" ) )        { testfn_f64_op2_ddd(fn_f64_mul); return 0; }
    if ( ! strcmp( argPtr, "f64_div" ) )        { testfn_f64_op2_ddd(fn_f64_div); return 0; }
    if ( ! strcmp( argPtr, "f64_rem" ) )        { testfn_f64_op2_ddd(fn_f64_rem); return 0; }
    if ( ! strcmp( argPtr, "f64_mulAdd" ) )     { testfn_f64_op3_dddd(fn_f64_fma); return 0; }
    if ( ! strcmp( argPtr, "f64_sqrt" ) )       { testfn_f64_op1_dd(fn_f64_sqrt); return 0; }
    if ( ! strcmp( argPtr, "f64_roundToInt" ) ) { testfn_f64_op1_dd(fn_f64_rnd); return 0; }
    if ( ! strcmp( argPtr, "f64_to_i32" ) )     { testfn_f64_to_i32(); return 0; }
    if ( ! strcmp( argPtr, "f64_to_ui32" ) )    { testfn_f64_to_ui32(); return 0; }
    if ( ! strcmp( argPtr, "i32_to_f64" ) )     { testfn_i32_to_f64(); return 0; }
    if ( ! strcmp( argPtr, "ui32_to_f64" ) )    { testfn_ui32_to_f64(); return 0; }
    if ( ! strcmp( argPtr, "f64_to_i64" ) )     { testfn_f64_to_i64(); return 0; }
    if ( ! strcmp( argPtr, "f64_to_ui64" ) )    { testfn_f64_to_ui64(); return 0; }
    if ( ! strcmp( argPtr, "i64_to_f64" ) )     { testfn_i64_to_f64(); return 0; }
    if ( ! strcmp( argPtr, "ui64_to_f64" ) )    { testfn_ui64_to_f64(); return 0; }
    if ( ! strcmp( argPtr, "f64_eq" ) )         { testfn_f64_op2_bdd(fn_f64_eq); return 0; }
    if ( ! strcmp( argPtr, "f64_le" ) )         { testfn_f64_op2_bdd(fn_f64_le); return 0; }
    if ( ! strcmp( argPtr, "f64_lt" ) )         { testfn_f64_op2_bdd(fn_f64_lt); return 0; }
    if ( ! strcmp( argPtr, "f32_to_f64" ) )     { testfn_f32_to_f64(); return 0; }
    if ( ! strcmp( argPtr, "f64_to_f32" ) )     { testfn_f64_to_f32(); return 0; }
    fprintf(stderr, "unknown: %s\n", argPtr);
    return -1;
  }

  return -1;
}
