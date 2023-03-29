/*
-- Test expressions on "double int's" (typically double the natural size of the ASIP).
--
-- Copyright (c) 2014 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


// These #defines must be set externally (via always include or -D command line arguments)
// For instance when dint is a 32-bit type on the ASIP:
//
// #define DINT_      long  /* typically long or long long */
// #define DINT_X0AAA 0x0aaaaaaa
// #define DINT_X8000 0x80000000
// #define DINT_X7FFF 0x7fffffff
// #define DINT_XFFFF 0xffffffff
// #define INT_NBIT  32
// #define INT_MAXSH 31
//
// NATIVE CODE ONLY: zero/sign extend function if native and asip type does not exactly match
// #define DINT_ZE(a) (a) /* if -m64 then ((a) & 0xffffffff) */
// #define DINT_SE(a) (a) /* if -m64 then (((a) << 32) >> 32)  */

#include "regression.h"

#ifdef HAS_DINT

// derived types
#define STYPE   signed DINT_
#define UTYPE unsigned DINT_
#define VAL(A)         DINT_##A

/* (only) apply mask to native code if asip and native type are not exactly matching (eg. 24bit) */
#define SE(A)   DINT_##SE(A)
#define ZE(A)   DINT_##ZE(A)

#define SVAL(A) SE(DINT_##A)
#define UVAL(A) ZE(DINT_##A)

/********* GENERIC FROM HERE *************/

void signed_binary(STYPE a, STYPE b)
{
    UNKNOWN(a); UNKNOWN(b);
    STYPE c;

    chess_message("// signed_binary(" << a << ", " << b << ')');
    chess_report(c = a + b);
    chess_report(c = a - b);
    chess_report(c = a * b);
    chess_report(c = a & b);
    chess_report(c = a | b);
    chess_report(c = a ^ b);

    chess_report(c = ~a);
    chess_report(c = ~b);

    chess_message("// signed_compare(" << a << ", " << b << ')');
    chess_report(a <  b);
    chess_report(a <= b);
    chess_report(a >  b);
    chess_report(a >= b);
    chess_report(a == b);
    chess_report(a != b);
}

void unsigned_binary(UTYPE a, UTYPE b)
{
    UNKNOWN(a); UNKNOWN(b);
    UTYPE c;

    chess_message("// unsigned_binary(" << a << ", " << b << ')');
    chess_report(c = a + b);
    chess_report(c = a - b);
    chess_report(c = a * b);
    chess_report(c = a & b);
    chess_report(c = a | b);
    chess_report(c = a ^ b);

    chess_report(c = ~a);
    chess_report(c = ~b);

    chess_message("// unsigned_compare(" << a << ", " << b << ')');
    chess_report(a <  b);
    chess_report(a <= b);
    chess_report(a >  b);
    chess_report(a >= b);
    chess_report(a == b);
    chess_report(a != b);
}

void signed_shift(STYPE a, STYPE b)
{
    chess_message("// signed_shift(" << a << ", " << b << ')');

    UNKNOWN(a); UNKNOWN(b);
    STYPE c;
    chess_report(c = a << b);
    chess_report(c = a >> b);
}

void unsigned_shift(UTYPE a, STYPE b)
{
    chess_message("// unsigned_shift(" << a << ", " << b << ')');

    UNKNOWN(a); UNKNOWN(b);
    UTYPE c;
    chess_report(c = a << b);
    chess_report(c = a >> b);
}

void test(STYPE a, STYPE b)
{
      signed_binary(   a,     b );
    unsigned_binary(ZE(a), ZE(b));

    UNKNOWN(a); UNKNOWN(b);
    if (b >= 0 && b < SVAL(NBIT)) {
          signed_shift(   a,  b);
        unsigned_shift(ZE(a), b);
    }
}

// test function to enable explicit "out of range" shift factors
void test_shift(STYPE a, STYPE b)
{
      signed_shift(   a,  b);
    unsigned_shift(ZE(a), b);
}

//-----------------------------------------------------------------------------

STYPE A[] = {
    0, 1, -1, 4, 10, -25, -122, 53, SVAL(MAXSH),
    SVAL(X0AAA), -SVAL(X0AAA),
    SVAL(X7FFF), -SVAL(X7FFF),
    SVAL(X8000),  SVAL(X7FFF) - 1,
    SVAL(XFFFF),  SVAL(XFFFF - 1)
};

int main()
{
    STYPE a, b;

    // some initial (simple) values
    a =    0;  b =  0;  test(a, b);
    a =    1;  b =  1;  test(a, b);
    a =   10;  b = 20;  test(a, b);
    a =  -25;  b =  4;  test(a, b);
    a = -122;  b = 53;  test(a, b);

    // more exhaustive data
    int N = sizeof(A) / sizeof(STYPE);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            a = A[i];  b = A[j];  test(a, b);
        }
    }
    return 0;
}

#else

int main()
{
    chess_report(987);
    return 0;
}

#endif
