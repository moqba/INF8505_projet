/*
-- Copyright (c) 2018-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/
// maybe put -tininessbefore
// $ <path>/testfloat_gen <function>  |& \
     chessmk -C <config> driver/test -Ss +X <function> |& \
     <path>/testfloat_ver <function>

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "testfn.h"

#define NO_SUBNORMALS false

bool is_subnormal(uint32_t x)  {
  return ((x) & 0x7F800000) == 0 &&
         ((x) & 0x007FFFFF) != 0;
}

bool is_subnormal(uint64_t x) {
  return ((x) & 0x7FF0000000000000ULL) == 0 &&
         ((x) & 0x000FFFFFFFFFFFFFULL) != 0;
}

bool skip_subnormal(uint32_t x) {
  return NO_SUBNORMALS && (is_subnormal(x));
}
bool skip_subnormal(uint32_t x, uint32_t z) {
  return NO_SUBNORMALS && (is_subnormal(x) || is_subnormal(z));
}
bool skip_subnormal(uint32_t x, uint32_t y, uint32_t z) {
  return NO_SUBNORMALS && (is_subnormal(x) || is_subnormal(y) || is_subnormal(z));
}

bool skip_subnormal(uint64_t x) {
  return NO_SUBNORMALS && (is_subnormal(x));
}
bool skip_subnormal(uint64_t x, uint64_t z) {
  return NO_SUBNORMALS && (is_subnormal(x) || is_subnormal(z));
}
bool skip_subnormal(uint64_t x, uint64_t y, uint64_t z) {
  return NO_SUBNORMALS && (is_subnormal(x) || is_subnormal(y) || is_subnormal(z));
}

// interpret testfloat_gen flags
bool flag_inexact(int f)   { return (f &  1) != 0; }
bool flag_underflow(int f) { return (f &  2) != 0; }
bool flag_overflow(int f)  { return (f &  4) != 0; }
bool flag_infinite(int f)  { return (f &  8) != 0; }
bool flag_invalid(int f)   { return (f & 16) != 0; }




// NOTE We copy the flags from input to output.
// NOTE Unsupported test cases can simply be discarded, e.g. if denormals
//      are not supported. Reference result is part of input.



void testfn_f32_add() {
  int flags;
  uint32_t x, y, z;
  while (scanf("%08X %08X %08X %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y,z)) continue;
    uint32_t r = as_int32(fn_f32_add(as_float(x),as_float(y)));
    printf("%08X %08X %08X %02X\n",x,y,r,flags);
  }
}
void testfn_f32_sub() {
  int flags;
  uint32_t x, y, z;
  while (scanf("%08X %08X %08X %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y,z)) continue;
    uint32_t r = as_int32(fn_f32_sub(as_float(x),as_float(y)));
    printf("%08X %08X %08X %02X\n",x,y,r,flags);
  }
}
void testfn_f32_mul() {
  int flags;
  uint32_t x, y, z;
  while (scanf("%08X %08X %08X %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y,z)) continue;
    uint32_t r = as_int32(fn_f32_mul(as_float(x),as_float(y)));
    printf("%08X %08X %08X %02X\n",x,y,r,flags);
  }
}
void testfn_f32_div() {
  int flags;
  uint32_t x, y, z;
  while (scanf("%08X %08X %08X %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y,z)) continue;
    uint32_t r = as_int32(fn_f32_div(as_float(x),as_float(y)));
    printf("%08X %08X %08X %02X\n",x,y,r,flags);
  }
}
void testfn_f32_rem() {
  int flags;
  uint32_t x, y, z;
  while (scanf("%08X %08X %08X %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y,z)) continue;
    uint32_t r = as_int32(fn_f32_rem(as_float(x),as_float(y)));
    printf("%08X %08X %08X %02X\n",x,y,r,flags);
  }
}
void testfn_f32_sqrt() {
  int flags;
  uint32_t x, z;
  while (scanf("%08X %08X %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,z)) continue;
    uint32_t r = as_int32(fn_f32_sqrt(as_float(x)));
    printf("%08X %08X %02X\n",x,r,flags);
  }
}
void testfn_f32_rnd() {
  int flags;
  uint32_t x, z;
  while (scanf("%08X %08X %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,z)) continue;
    uint32_t r = as_int32(fn_f32_rnd(as_float(x)));
    printf("%08X %08X %02X\n",x,r,flags);
  }
}
void testfn_f32_to_i32() {
  int flags;
  uint32_t x, z;
  while (scanf("%08X %08X %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(x)) continue;
    int32_t r = fn_f32_to_i32(as_float(x));
    printf("%08X %08X %02X\n",x,r,flags);
  }
}
void testfn_f32_to_ui32() {
  int flags;
  uint32_t x, z;
  while (scanf("%08X %08X %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(x)) continue;
    uint32_t r = fn_f32_to_ui32(as_float(x));
    printf("%08X %08X %02X\n",x,r,flags);
  }
}
void testfn_i32_to_f32() {
  int flags;
  int32_t x;
  uint32_t z;
  while (scanf("%08X %08X %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(z)) continue;
    uint32_t r = as_int32(fn_i32_to_f32(x));
    printf("%08X %08X %02X\n",x,r,flags);
  }
}
void testfn_ui32_to_f32() {
  int flags;
  uint32_t x, z;
  while (scanf("%08X %08X %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(z)) continue;
    uint32_t r = as_int32(fn_ui32_to_f32(x));
    printf("%08X %08X %02X\n",x,r,flags);
  }
}
//void testfn_f32_to_i64() {
//  int flags;
//  uint32_t x;
//  uint64_t z;
//  while (scanf("%08X %016llX %02X", &x, &z, &flags)!=EOF) {
//    //if (skip_subnormal(x)) continue;
//    int64_t r = fn_f32_to_i64(as_float(x));
//    printf("%08X %016llX %02X\n",x,r,flags);
//  }
//}
//void testfn_f32_to_ui64() {
//  int flags;
//  uint32_t x;
//  uint64_t z;
//  while (scanf("%08X %016llX %02X", &x, &z, &flags)!=EOF) {
//    //if (skip_subnormal(x)) continue;
//    uint64_t r = fn_f32_to_ui64(as_float(x));
//    printf("%08X %016llX %02X\n",x,r,flags);
//  }
//}
//void testfn_i64_to_f32() {
//  int flags;
//  int64_t x;
//  uint32_t z;
//  while (scanf("%016llX %08X %02X", &x, &z, &flags)!=EOF) {
//    //if (skip_subnormal(z)) continue;
//    uint32_t r = as_int32(fn_i64_to_f32(x));
//    printf("%016llX %08X %02X\n",x,r,flags);
//  }
//}
//void testfn_ui64_to_f32() {
//  int flags;
//  uint64_t x;
//  uint32_t z;
//  while (scanf("%016llX %08X %02X", &x, &z, &flags)!=EOF) {
//    //if (skip_subnormal(z)) continue;
//    uint32_t r = as_int32(fn_ui64_to_f32(x));
//    printf("%016llX %08X %02X\n",x,r,flags);
//  }
//}
void testfn_f32_eq() {
  int flags;
  uint32_t x, y, z;
  while (scanf("%08X %08X %01X %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y)) continue;
    bool r = fn_f32_eq(as_float(x),as_float(y));
    printf("%08X %08X %01X %02X\n",x,y,r,flags);
  }
}
void testfn_f32_lt() {
  int flags;
  uint32_t x, y, z;
  while (scanf("%08X %08X %01X %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y)) continue;
    bool r = fn_f32_lt(as_float(x),as_float(y));
    printf("%08X %08X %01X %02X\n",x,y,r,flags);
  }
}
void testfn_f32_le() {
  int flags;
  uint32_t x, y, z;
  while (scanf("%08X %08X %01X %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y)) continue;
    bool r = fn_f32_le(as_float(x),as_float(y));
    printf("%08X %08X %01X %02X\n",x,y,r,flags);
  }
}
void testfn_f64_add() {
  int flags;
  uint64_t x, y, z;
  while (scanf("%016llX %016llX %016llX %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y,z)) continue;
    uint64_t r = as_int64(fn_f64_add(as_double(x),as_double(y)));
    printf("%016llX %016llX %016llX %02X\n",x,y,r,flags);
  }
}
void testfn_f64_sub() {
  int flags;
  uint64_t x, y, z;
  while (scanf("%016llX %016llX %016llX %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y,z)) continue;
    uint64_t r = as_int64(fn_f64_sub(as_double(x),as_double(y)));
    printf("%016llX %016llX %016llX %02X\n",x,y,r,flags);
  }
}
void testfn_f64_mul() {
  int flags;
  uint64_t x, y, z;
  while (scanf("%016llX %016llX %016llX %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y,z)) continue;
    uint64_t r = as_int64(fn_f64_mul(as_double(x),as_double(y)));
    printf("%016llX %016llX %016llX %02X\n",x,y,r,flags);
  }
}
void testfn_f64_div() {
  int flags;
  uint64_t x, y, z;
  while (scanf("%016llX %016llX %016llX %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y,z)) continue;
    uint64_t r = as_int64(fn_f64_div(as_double(x),as_double(y)));
    printf("%016llX %016llX %016llX %02X\n",x,y,r,flags);
  }
}
void testfn_f64_rem() {
  int flags;
  uint64_t x, y, z;
  while (scanf("%016llX %016llX %016llX %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y,z)) continue;
    uint64_t r = as_int64(fn_f64_rem(as_double(x),as_double(y)));
    printf("%016llX %016llX %016llX %02X\n",x,y,r,flags);
  }
}
void testfn_f64_sqrt() {
  int flags;
  uint64_t x, z;
  while (scanf("%016llX %016llX %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,z)) continue;
    uint64_t r = as_int64(fn_f64_sqrt(as_double(x)));
    printf("%016llX %016llX %02X\n",x,r,flags);
  }
}
void testfn_f64_rnd() {
  int flags;
  uint64_t x, z;
  while (scanf("%016llX %016llX %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,z)) continue;
    uint64_t r = as_int64(fn_f64_rnd(as_double(x)));
    printf("%016llX %016llX %02X\n",x,r,flags);
  }
}
void testfn_f64_to_i32() {
  int flags;
  uint64_t x;
  uint32_t z;
  while (scanf("%016llX %08X %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(x)) continue;
    int32_t r = fn_f64_to_i32(as_double(x));
    printf("%016llX %08X %02X\n",x,r,flags);
  }
}
void testfn_f64_to_ui32() {
  int flags;
  uint64_t x;
  uint32_t z;
  while (scanf("%016llX %08X %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(x)) continue;
    uint32_t r = fn_f64_to_ui32(as_double(x));
    printf("%016llX %08X %02X\n",x,r,flags);
  }
}
void testfn_i32_to_f64() {
  int flags;
  int32_t x;
  uint64_t z;
  while (scanf("%08X %016llX %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(z)) continue;
    uint64_t r = as_int64(fn_i32_to_f64(x));
    printf("%08X %016llX %02X\n",x,r,flags);
  }
}
void testfn_ui32_to_f64() {
  int flags;
  uint32_t x;
  uint64_t z;
  while (scanf("%08X %016llX %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(z)) continue;
    uint64_t r = as_int64(fn_ui32_to_f64(x));
    printf("%08X %016llX %02X\n",x,r,flags);
  }
}
//void testfn_f64_to_i64() {
//  int flags;
//  uint64_t x, z;
//  while (scanf("%016llX %016llX %02X", &x, &z, &flags)!=EOF) {
//    //if (skip_subnormal(x)) continue;
//    int64_t r = fn_f64_to_i64(as_double(x));
//    printf("%016llX %016llX %02X\n",x,r,flags);
//  }
//}
//void testfn_f64_to_ui64() {
//  int flags;
//  uint64_t x, z;
//  while (scanf("%016llX %016llX %02X", &x, &z, &flags)!=EOF) {
//    //if (skip_subnormal(x)) continue;
//    uint64_t r = fn_f64_to_ui64(as_double(x));
//    printf("%016llX %016llX %02X\n",x,r,flags);
//  }
//}
//void testfn_i64_to_f64() {
//  int flags;
//  int64_t x;
//  uint64_t z;
//  while (scanf("%016llX %016llX %02X", &x, &z, &flags)!=EOF) {
//    //if (skip_subnormal(z)) continue;
//    uint64_t r = as_int64(fn_i64_to_f64(x));
//    printf("%016llX %016llX %02X\n",x,r,flags);
//  }
//}
//void testfn_ui64_to_f64() {
//  int flags;
//  uint64_t x, z;
//  while (scanf("%016llX %016llX %02X", &x, &z, &flags)!=EOF) {
//    //if (skip_subnormal(z)) continue;
//    uint64_t r = as_int64(fn_ui64_to_f64(x));
//    printf("%016llX %016llX %02X\n",x,r,flags);
//  }
//}
void testfn_f64_eq() {
  int flags;
  uint64_t x, y, z;
  while (scanf("%016llX %016llX %01X %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y)) continue;
    bool r = fn_f64_eq(as_double(x),as_double(y));
    printf("%016llX %016llX %01X %02X\n",x,y,r,flags);
  }
}
void testfn_f64_lt() {
  int flags;
  uint64_t x, y, z;
  while (scanf("%016llX %016llX %01X %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y)) continue;
    bool r = fn_f64_lt(as_double(x),as_double(y));
    printf("%016llX %016llX %01X %02X\n",x,y,r,flags);
  }
}
void testfn_f64_le() {
  int flags;
  uint64_t x, y, z;
  while (scanf("%016llX %016llX %01X %02X", &x, &y, &z, &flags)!=EOF) {
    //if (skip_subnormal(x,y)) continue;
    bool r = fn_f64_le(as_double(x),as_double(y));
    printf("%016llX %016llX %01X %02X\n",x,y,r,flags);
  }
}
void testfn_f32_to_f64() {
  int flags;
  uint32_t x;
  uint64_t z;
  while (scanf("%08X %016llX %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(x) || skip_subnormal(z)) continue;
    uint64_t r = as_int64(fn_f32_to_f64(as_float(x)));
    printf("%08X %016llX %02X\n",x,r,flags);
  }
}
void testfn_f64_to_f32() {
  int flags;
  uint64_t x;
  uint32_t z;
  while (scanf("%016llX %08X %02X", &x, &z, &flags)!=EOF) {
    //if (skip_subnormal(x) || skip_subnormal(z)) continue;
    uint32_t r = as_int32(fn_f64_to_f32(as_double(x)));
    printf("%016llX %08X %02X\n",x,r,flags);
  }
}



int main( int argc, char *argv[] )
{
  // parse command line
  const char *argPtr;
  for (;;) {
    --argc;
    if ( ! argc ) break;
    argPtr = *++argv;
    if ( ! argPtr ) break;
    // ---------
    if ( ! strcmp( argPtr, "f32_add" ) ) { testfn_f32_add(); return 0; }
    if ( ! strcmp( argPtr, "f32_sub" ) ) { testfn_f32_sub(); return 0; }
    if ( ! strcmp( argPtr, "f32_mul" ) ) { testfn_f32_mul(); return 0; }
    if ( ! strcmp( argPtr, "f32_div" ) ) { testfn_f32_div(); return 0; }
    if ( ! strcmp( argPtr, "f32_rem" ) ) { testfn_f32_rem(); return 0; }
    if ( ! strcmp( argPtr, "f32_sqrt" ) ) { testfn_f32_sqrt(); return 0; }
    if ( ! strcmp( argPtr, "f32_roundToInt" ) ) { testfn_f32_rnd(); return 0; }
    if ( ! strcmp( argPtr, "f32_to_i32" ) ) { testfn_f32_to_i32(); return 0; }
    if ( ! strcmp( argPtr, "f32_to_ui32" ) ) { testfn_f32_to_ui32(); return 0; }
    if ( ! strcmp( argPtr, "i32_to_f32" ) ) { testfn_i32_to_f32(); return 0; }
    if ( ! strcmp( argPtr, "ui32_to_f32" ) ) { testfn_ui32_to_f32(); return 0; }
//    if ( ! strcmp( argPtr, "f32_to_i64" ) ) { testfn_f32_to_i64(); return 0; }
//    if ( ! strcmp( argPtr, "f32_to_ui64" ) ) { testfn_f32_to_ui64(); return 0; }
//    if ( ! strcmp( argPtr, "i64_to_f32" ) ) { testfn_i64_to_f32(); return 0; }
//    if ( ! strcmp( argPtr, "ui64_to_f32" ) ) { testfn_ui64_to_f32(); return 0; }
    if ( ! strcmp( argPtr, "f32_eq" ) ) { testfn_f32_eq(); return 0; }
    if ( ! strcmp( argPtr, "f32_le" ) ) { testfn_f32_le(); return 0; }
    if ( ! strcmp( argPtr, "f32_lt" ) ) { testfn_f32_lt(); return 0; }
    if ( ! strcmp( argPtr, "f64_add" ) ) { testfn_f64_add(); return 0; }
    if ( ! strcmp( argPtr, "f64_sub" ) ) { testfn_f64_sub(); return 0; }
    if ( ! strcmp( argPtr, "f64_mul" ) ) { testfn_f64_mul(); return 0; }
    if ( ! strcmp( argPtr, "f64_div" ) ) { testfn_f64_div(); return 0; }
    if ( ! strcmp( argPtr, "f64_rem" ) ) { testfn_f64_rem(); return 0; }
    if ( ! strcmp( argPtr, "f64_sqrt" ) ) { testfn_f64_sqrt(); return 0; }
    if ( ! strcmp( argPtr, "f64_roundToInt" ) ) { testfn_f64_rnd(); return 0; }
    if ( ! strcmp( argPtr, "f64_to_i32" ) ) { testfn_f64_to_i32(); return 0; }
    if ( ! strcmp( argPtr, "f64_to_ui32" ) ) { testfn_f64_to_ui32(); return 0; }
    if ( ! strcmp( argPtr, "i32_to_f64" ) ) { testfn_i32_to_f64(); return 0; }
    if ( ! strcmp( argPtr, "ui32_to_f64" ) ) { testfn_ui32_to_f64(); return 0; }
//    if ( ! strcmp( argPtr, "f64_to_i64" ) ) { testfn_f64_to_i64(); return 0; }
//    if ( ! strcmp( argPtr, "f64_to_ui64" ) ) { testfn_f64_to_ui64(); return 0; }
//    if ( ! strcmp( argPtr, "i64_to_f64" ) ) { testfn_i64_to_f64(); return 0; }
//    if ( ! strcmp( argPtr, "ui64_to_f64" ) ) { testfn_ui64_to_f64(); return 0; }
    if ( ! strcmp( argPtr, "f64_eq" ) ) { testfn_f64_eq(); return 0; }
    if ( ! strcmp( argPtr, "f64_le" ) ) { testfn_f64_le(); return 0; }
    if ( ! strcmp( argPtr, "f64_lt" ) ) { testfn_f64_lt(); return 0; }
    if ( ! strcmp( argPtr, "f32_to_f64" ) ) { testfn_f32_to_f64(); return 0; }
    if ( ! strcmp( argPtr, "f64_to_f32" ) ) { testfn_f64_to_f32(); return 0; }
  }

  return -1;
}
