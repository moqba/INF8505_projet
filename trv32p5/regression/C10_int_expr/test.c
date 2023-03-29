/*
-- Test expressions on integers (natural size of the ASIP).
--
-- Copyright (c) 2014 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "regression.h"


// These #defines must be set externally (via always include or -D command line arguments)
// For instance when int is a 16-bit type on the ASIP:
//
// #define INT_      int    /* typically int */
// #define INT_X0AAA 0x0aaa
// #define INT_X8000 0x8000
// #define INT_X7FFF 0x7fff
// #define INT_XFFFF 0xffff
// #define INT_NBIT  16
// #define INT_MAXSH 15
//
// NATIVE CODE ONLY: zero/sign extend function if native and asip type are not exactly match
// #define INT_ZE(a) ((a)&0xffff)
// #define INT_SE(a) (((a)<<16)>>16)


// derived types
#define STYPE   signed INT_
#define UTYPE unsigned INT_

/* (only) apply mask to native code if asip and native type are not exactly matching (eg. 24bit) */
#define SE(A)        INT_##SE(A)
#define ZE(A)        INT_##ZE(A)

#define SVAL(A)      (STYPE)SE(INT_##A)
#define UVAL(A)      (UTYPE)ZE(INT_##A)


/********* GENERIC FROM HERE *************/

void signed_binary(STYPE a, STYPE b)
{
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

    chess_message( "// signed_compare(" << a << ',' << b << ')' );
    chess_report(a <  b);
    chess_report(a <= b);
    chess_report(a >  b);
    chess_report(a >= b);
    chess_report(a == b);
    chess_report(a != b);
}

void unsigned_binary(UTYPE a, UTYPE b)
{
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

    chess_message( "// unsigned_compare(" << a << ',' << b << ')' );
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

    STYPE c;
    chess_report(c = a << b);
    chess_report(c = a >> b);
}

void unsigned_shift(UTYPE a, STYPE b)
{
    chess_message("// unsigned_shift(" << a << ", " << b << ')');

    UTYPE c;
    chess_report(c = a << b);
    chess_report(c = a >> b);
}

void test(STYPE a, STYPE b)
{
      signed_binary(      a,     b);
    unsigned_binary(   ZE(a), ZE(b) );

    if (b>=0 && b<SVAL(NBIT)) {
        signed_shift (    a,  b);
      unsigned_shift ( ZE(a), b);
    }
}

// test function to enable explicit "out of range" shift factors
void test_shift(STYPE a, STYPE b)
{
        signed_shift (    a,  b);
      unsigned_shift ( ZE(a), b);
}

//-----------------------------------------------------------------------------

STYPE A[] = { 0,1,-1,4,10,-25,-122,53, SVAL(MAXSH),
              SVAL(X0AAA), -SVAL(X0AAA),
              SVAL(X7FFF), -SVAL(X7FFF),
              SVAL(X8000),  SVAL(X7FFF)-1,
              SVAL(XFFFF),  SVAL(XFFFF-1) };

int main()
{
    STYPE a, b;

    // some initial (simple) values
    a =            0;  b =            0;  test(a, b);
    a =            1;  b =            1;  test(a, b);
    a =           10;  b =           20;  test(a, b);
    a =          -25;  b =            4;  test(a, b);
    a =         -122;  b =           53;  test(a, b);

    // more exhaustive data
    int N=sizeof(A)/sizeof(STYPE);
    for (int i=0; i<N; i++) {
       for (int j=0; j<N; j++) {
          a =  A[i];  b = A[j];  test(a, b);
       }
    }

    return 0;
}
