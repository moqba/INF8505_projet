/*
-- Test expressions on doubles.
-- Copyright (c) 2014 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include <stdint.h>

void test_arith(double a, double b)
{
    chess_message("// test_arith(" << a << ", " << b << ')');

    double c;
    chess_report(c = a + b);
    chess_report(c = a - b);
    chess_report(c = b - a);
    chess_report(c = a * b);
    if (b != 0.0) chess_report(c = a / b);
    if (a != 0.0) chess_report(c = b / a);
}

void test_compare(double a, double b)
{
    chess_message("// test_compare(" << a << ", " << b << ')');

    chess_report(a <  b);
    chess_report(a <= b);
    chess_report(a >  b);
    chess_report(a >= b);
    chess_report(a == b);
    chess_report(a != b);
}

void test_bin(double a, double b)
{
    test_arith(a, b);
    test_compare(a, b);
}

void test_f2i(double f)
{
    chess_message("// test_f2i(" << f << ')');
    int32_t i = (int32_t)f;
    chess_report(i);
}

void test_i2f(int32_t i)
{
    chess_message("// test_i2f(" << i << ')');
    double f = (double)i;
    chess_report(f);
}

void test_f2u(double f)
{
    chess_message("// test_f2u()");
    uint32_t u = (uint32_t)f;
    chess_report(u);
}

void test_u2f(uint32_t u)
{
    chess_message("// test_u2f()");
    double f = (double)u;
    chess_report(f);
}

int main()
{
    double a, b;

    a = 6.5;        b = 4.25;       test_bin(a, b);
    a = 0.0;        b = 1.0;        test_bin(a, b);
    a = 3.14;       b = 1.0e-10;    test_bin(a, b);
    a = 3.4e+28;    b = 3.4e+22;    test_bin(a, b);
    a = 1.9e+101;   b = -6.7e-11;   test_bin(a, b);

    union { uint64_t u; double f; } ufa, ufb;

    ufa.u = 0x4000100000000000ULL;
    ufb.u = 0x4000110000000000ULL;
    test_bin(ufa.f, ufb.f);

    uint64_t inan = 0xfffff0000ULL;
    double nan = *(double*)&inan;

    test_compare(nan, 6.5);
    test_compare(2.44e4, nan);
    test_compare(nan, nan);

    test_f2i(6.5);
    test_f2i(2.44e4);
    test_f2i(-155.77);

    test_i2f(155);
    test_i2f(-155);

    test_f2u(10.3);
    // test_f2u(-22.2); // undefined
    test_f2u(2.44e4);
    test_f2u(2.44e8);
    test_f2u(2.44e9);

    test_u2f(10);
    test_u2f(0x80000000);
    test_u2f(0xe0000000);

    return 0;
}
