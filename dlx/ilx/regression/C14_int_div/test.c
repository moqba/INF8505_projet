/*
-- Test: division on integers (natural size of the ASIP).
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


// These #defines must be set externally (via always include or -D command line arguments)
// For instance when int is a 16-bit type on the ASIP:
//
// #define INT_      int    /* typically int */
// #define INT_X0AAA 0x0aaa
// #define INT_X8000 0x8000
// #define INT_X7FFF 0x7fff
// #define INT_XFFFF 0xffff
// #define INT_X1000 0x1000
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

void signed_div(STYPE a, STYPE b)
{
    chess_message("// signed_div(" << a << ", " << b << ')');
    if (b == 0) return;
    if (a == SVAL(X8000) && b == -1) return; // Results in "Arithmetic exception" on host, because the most negative value cannot be negated

    STYPE c;
    chess_report(c = a / b);
    chess_report(c = a % b);
}

void unsigned_div(UTYPE a, UTYPE b)
{
    chess_message("// unsigned_div(" << a << ", " << b << ')');
    if (b == 0) return;

    UTYPE c;
    chess_report(c = a / b);
    chess_report(c = a % b);
}

void test(STYPE a, STYPE b)
{
      signed_div(   a,     b );
    unsigned_div(ZE(a), ZE(b));
}


void signed_div_const(STYPE a)
{
    chess_message("// signed_div_const(" << a << ')');
    STYPE c;
    chess_report(c = a / (STYPE) 1);
    chess_report(c = a % (STYPE) 1);
    chess_report(c = a / (STYPE) 2);
    chess_report(c = a % (STYPE) 2);
    chess_report(c = a / (STYPE) 3);
    chess_report(c = a % (STYPE) 3);
    chess_report(c = a / (STYPE) 7);
    chess_report(c = a % (STYPE) 7);
    chess_report(c = a / (STYPE) 8);
    chess_report(c = a % (STYPE) 8);
    chess_report(c = a / (STYPE)-1);
    chess_report(c = a % (STYPE)-1);
    chess_report(c = a / (STYPE)-2);
    chess_report(c = a % (STYPE)-2);
    chess_report(c = a / (STYPE)-3);
    chess_report(c = a % (STYPE)-3);
    chess_report(c = a / (STYPE)-7);
    chess_report(c = a % (STYPE)-7);
    chess_report(c = a / (STYPE)-8);
    chess_report(c = a % (STYPE)-8);
}

void unsigned_div_const(UTYPE a)
{
    chess_message("// unsigned_div_const(" << a << ')');
    UTYPE c;
    chess_report(c = a / (UTYPE)1);
    chess_report(c = a % (UTYPE)1);
    chess_report(c = a / (UTYPE)2);
    chess_report(c = a % (UTYPE)2);
    chess_report(c = a / (UTYPE)3);
    chess_report(c = a % (UTYPE)3);
    chess_report(c = a / (UTYPE)7);
    chess_report(c = a % (UTYPE)7);
    chess_report(c = a / (UTYPE)8);
    chess_report(c = a % (UTYPE)8);
}

void test_const(STYPE a)
{
      signed_div_const(a);
    unsigned_div_const(ZE(a));
}


STYPE A[] = { 0, 1, -1, 10, -25, -122,
    /*   X07FF */ (UVAL(X7FFF)                    )>>4,
    /*   X07FE */ (UVAL(X7FFF)                 - 1)>>4,
    /*   X0700 */ (UVAL(X7FFF) -   UVAL(X1000) + 1)>>4,
    /*   X06FF */ (UVAL(X7FFF) -   UVAL(X1000)    )>>4,
    /*   X0400 */ (UVAL(X7FFF) - 4*UVAL(X1000) + 1)>>4,
    /*   X03FF */ (UVAL(X7FFF) - 4*UVAL(X1000)    )>>4,
    /*   X0300 */ (UVAL(X7FFF) - 5*UVAL(X1000) + 1)>>4,
    SVAL(X8000),
    SVAL(X7FFF),
    /*   X7FFE */ SVAL(X7FFF)-1,
    SVAL(XFFFF),
    /*   XFFFE */ SVAL(XFFFF)-1,
    SVAL(X0AAA)
};

int main()
{
    STYPE a, b;

    // some initial (simple) divisions
    a =        1;  b =        1;  test(a, b);
    a =       10;  b =       20;  test(a, b);
    a =      -25;  b =        4;  test(a, b);
    a =     -122;  b =       53;  test(a, b);


    // some boundary value divisions:
    a =      0x7f;  b =          1;  test(a, b);
    a =      0x7f;  b =       0x7f;  test(a, b);

    a =         0;  b =       0x7f;  test(a, b);
    a =         1;  b =       0x7f;  test(a, b);
    a =        -1;  b =       0x7f;  test(a, b);

    a =     -0x7f;  b =          1;  test(a, b);

    a =         0;  b =      -0x7f;  test(a, b);
    a =         1;  b =      -0x7f;  test(a, b);
    a =        -1;  b =      -0x7f;  test(a, b);
    a =     -0x7f;  b =      -0x7f;  test(a, b);

    a =     -0x80;  b =          1;  test(a, b);

    a =     -0x80;  b =      -0x80;  test(a, b);
    a =         0;  b =      -0x80;  test(a, b);
    a =         1;  b =      -0x80;  test(a, b);
    a =        -1;  b =      -0x80;  test(a, b);

    // more exhaustive data
    int N = sizeof(A) / sizeof(STYPE);
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            a = A[i];
            b = A[j];
            test(a, b);
        }
    }

    // test const division
    a =       0x7f;  test_const(a);
    a =      -0x80;  test_const(a);

    for (int i=0; i<N; i++) {
        a = A[i];
        test_const(a);
    }

    return 0;
}
