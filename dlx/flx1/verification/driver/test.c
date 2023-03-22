/*
-- Copyright (c) 2018 Synopsys, Inc. This Synopsys processor model
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

float f32_add(float x, float y) { return x+y; }
float f32_sub(float x, float y) { return x-y; }
float f32_mul(float x, float y) { return x*y; }
float f32_div(float x, float y) { return x/y; }
float f32_sqrt(float x) { return sqrtf(x); }
float f32_rnd(float x) { return roundf(x); }
int f32_to_i32(float x) { return (int)x; }
unsigned f32_to_ui32(float x) { return (unsigned)x; }
float i32_to_f32(int x) { return (float)x; }
float ui32_to_f32(unsigned x) { return (float)x; }
bool f32_eq(float x, float y) { return x == y; }
bool f32_le(float x, float y) { return x <= y; }
bool f32_lt(float x, float y) { return x < y; }

int main( int argc, char *argv[] )
{
  bool test_f32_add = false;
  bool test_f32_sub = false;
  bool test_f32_mul = false;
  bool test_f32_div = false;
  bool test_f32_sqrt = false;
  bool test_f32_rnd = false;
  bool test_f32_to_i32 = false;
  bool test_f32_to_ui32 = false;
  bool test_i32_to_f32 = false;
  bool test_ui32_to_f32 = false;
  bool test_f32_eq = false;
  bool test_f32_le = false;
  bool test_f32_lt = false;

  // parse command line
  const char *argPtr;
  for (;;) {
    --argc;
    if ( ! argc ) break;
    argPtr = *++argv;
    if ( ! argPtr ) break;
    // ---------
    if ( ! strcmp( argPtr, "f32_add" ) ) {
      test_f32_add = true;
    } else if ( ! strcmp( argPtr, "f32_sub" ) ) {
      test_f32_sub = true;
    } else if ( ! strcmp( argPtr, "f32_mul" ) ) {
      test_f32_mul = true;
    } else if ( ! strcmp( argPtr, "f32_div" ) ) {
      test_f32_div = true;
    } else if ( ! strcmp( argPtr, "f32_sqrt" ) ) {
      test_f32_sqrt = true;
    } else if ( ! strcmp( argPtr, "f32_roundToInt" ) ) {
      test_f32_rnd = true;
    } else if ( ! strcmp( argPtr, "f32_to_i32" ) ) {
      test_f32_to_i32 = true;
    } else if ( ! strcmp( argPtr, "f32_to_ui32" ) ) {
      test_f32_to_ui32 = true;
    } else if ( ! strcmp( argPtr, "i32_to_f32" ) ) {
      test_i32_to_f32 = true;
    } else if ( ! strcmp( argPtr, "ui32_to_f32" ) ) {
      test_ui32_to_f32 = true;
    } else if ( ! strcmp( argPtr, "f32_eq" ) ) {
      test_f32_eq = true;
    } else if ( ! strcmp( argPtr, "f32_le" ) ) {
      test_f32_le = true;
    } else if ( ! strcmp( argPtr, "f32_lt" ) ) {
      test_f32_lt = true;
    }
  }

  // NOTE We copy the flags from input to output.
  // NOTE Unsupported test cases can simply be discarded, e.g. if denormals
  //      are not supported. Reference result is part of input.
  int flags;

  if (test_f32_add) {
    uint32_t x, y, z;
    while (1) {
      if(scanf("%08X %08X %08X %02X", &x, &y, &z, &flags)==EOF){break;}
      uint32_t r = as_int32(f32_add(as_float(x),as_float(y)));
      printf("%08X %08X %08X %02X\n",x,y,r,flags);
    }
  } else if (test_f32_sub) {
    uint32_t x, y, z;
    while (1) {
      if(scanf("%08X %08X %08X %02X", &x, &y, &z, &flags)==EOF){break;}
      uint32_t r = as_int32(f32_sub(as_float(x),as_float(y)));
      printf("%08X %08X %08X %02X\n",x,y,r,flags);
    }
  } else if (test_f32_mul) {
    uint32_t x, y, z;
    while (1) {
      if(scanf("%08X %08X %08X %02X", &x, &y, &z, &flags)==EOF){break;}
      uint32_t r = as_int32(f32_mul(as_float(x),as_float(y)));
      printf("%08X %08X %08X %02X\n",x,y,r,flags);
    }
  } else if (test_f32_div) {
    uint32_t x, y, z;
    while (1) {
      if(scanf("%08X %08X %08X %02X", &x, &y, &z, &flags)==EOF){break;}
      uint32_t r = as_int32(f32_div(as_float(x),as_float(y)));
      printf("%08X %08X %08X %02X\n",x,y,r,flags);
    }
  } else if (test_f32_sqrt) {
    uint32_t x, z;
    while (1) {
      if(scanf("%08X %08X %02X", &x, &z, &flags)==EOF){break;}
      uint32_t r = as_int32(f32_sqrt(as_float(x)));
      printf("%08X %08X %02X\n",x,r,flags);
    }
  } else if (test_f32_rnd) {
    uint32_t x, z;
    while (1) {
      if(scanf("%08X %08X %02X", &x, &z, &flags)==EOF){break;}
      uint32_t r = as_int32(f32_rnd(as_float(x)));
      printf("%08X %08X %02X\n",x,r,flags);
    }
  } else if (test_f32_to_i32) {
    uint32_t x, z;
    while (1) {
      if(scanf("%08X %08X %02X", &x, &z, &flags)==EOF){break;}
      uint32_t r = f32_to_i32(as_float(x));
      printf("%08X %08X %02X\n",x,r,flags);
    }
  } else if (test_f32_to_ui32) {
    uint32_t x, z;
    while (1) {
      if(scanf("%08X %08X %02X", &x, &z, &flags)==EOF){break;}
      uint32_t r = f32_to_ui32(as_float(x));
      printf("%08X %08X %02X\n",x,r,flags);
    }
  } else if (test_i32_to_f32) {
    uint32_t x, z;
    while (1) {
      if(scanf("%08X %08X %02X", &x, &z, &flags)==EOF){break;}
      uint32_t r = as_int32(i32_to_f32(x));
      printf("%08X %08X %02X\n",x,r,flags);
    }
  } else if (test_ui32_to_f32) {
    uint32_t x, z;
    while (1) {
      if(scanf("%08X %08X %02X", &x, &z, &flags)==EOF){break;}
      uint32_t r = as_int32(ui32_to_f32(x));
      printf("%08X %08X %02X\n",x,r,flags);
    }
  } else if (test_f32_eq) {
    uint32_t x, y, z;
    while (1) {
      if(scanf("%08X %08X %01X %02X", &x, &y, &z, &flags)==EOF){break;}
      bool r = f32_eq(as_float(x),as_float(y));
      printf("%08X %08X %01X %02X\n",x,y,r,flags);
    }
  } else if (test_f32_lt) {
    uint32_t x, y, z;
    while (1) {
      if(scanf("%08X %08X %01X %02X", &x, &y, &z, &flags)==EOF){break;}
      bool r = f32_lt(as_float(x),as_float(y));
      printf("%08X %08X %01X %02X\n",x,y,r,flags);
    }
  } else if (test_f32_le) {
    uint32_t x, y, z;
    while (1) {
      if(scanf("%08X %08X %01X %02X", &x, &y, &z, &flags)==EOF){break;}
      bool r = f32_le(as_float(x),as_float(y));
      printf("%08X %08X %01X %02X\n",x,y,r,flags);
    }
  }
  return 0;
}
