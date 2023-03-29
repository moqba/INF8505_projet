/*
-- Test math functions on doubles.
-- Copyright (c) 2014 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include <math.h>
#include <stdint.h>
#include <stddef.h>

#ifndef __ndl__
double as_double(uint64_t u) {
    union { uint64_t u; double f; } uf;
    uf.u = u;
    return uf.f;
}
#endif

void test_ldexp(double a, int e)
{
    chess_message("// test_ldexp(" << a << ", " << e << ')');

    double c;
    chess_report(c = ldexp(a, e));
}

void test_ceil_floor_trunc(double a)
{
    chess_message("// test_ceil_floor_trunc(" << a << ')');

    double c;
    chess_report(c = ceil (a));
    chess_report(c = floor(a));
    chess_report(c = trunc(a));
}

void test_cos_sin(double a)
{
    chess_message("// test_cos_sin(" << a << ')');

    double c;
    chess_report(c = cos(a));
    chess_report(c = sin(a));
}

void test_atrig(double a)
{
    chess_message("// test_atrig(" << a << ')');

    double c;
    chess_report(c = acos(a));
    chess_report(c = asin(a));
    chess_report(c = atan(a));
}

void test_exp_log_log10_sqrt(double a)
{
    chess_message("// test_exp_log_log10_sqrt(" << a << ')');

    double c;
    if (a <  50.0) chess_report(c = exp  (a));
    if (a >   0.0) chess_report(c = log  (a));
    if (a >   0.0) chess_report(c = log10(a));
    if (a >=  0.0) chess_report(c = sqrt (a));
}

void test_pow(double a, double b)
{
    chess_message("// test_pow(" << a << ", " << b << ')');

    double c;
    chess_report(c = pow(a, b));
}

void test_fmod(double a, double b)
{
    chess_message("// test_fmod(" << a << ", " << b << ')');

    double c;
    chess_report(c = fmod(a, b));
}

void test_frexp(double a)
{
    chess_message("// test_frexp(" << a << ')');

    double c;
    int e;
    chess_report(c = frexp(a, &e));
    chess_report(e);
}

int main()
{
    test_ldexp(  1.0,  1);
    test_ldexp(  1.0,  2);
    test_ldexp( -1.0,  2);
    test_ldexp( -1.0, -2);
    test_ldexp(100.0,  5);
    test_ldexp(100.0, -9);

    // ceil(), floor()
    double F1[] = { 6.5, 6.01, 6.99, -6.5, -6.01, -6.99, 3.4e+38, 3.4e-29 };
    for (size_t i = 0; i < sizeof(F1)/sizeof(double); i++)
        test_ceil_floor_trunc(F1[i]);

    // sin(), cos()
    /*
    uint64_t PI[] = {
        0,
        0x400921fb54442d18ULL,   //  pi/1 =  3.141593
        0x3ff921fb54442d18ULL,   //  pi/2 =  1.570796
        0x3ff0c152382d7365ULL,   //  pi/3 =  1.047198
        0x3fe921fb54442d18ULL,   //  pi/4 =  0.785398
        0x3fe0c152382d7365ULL,   //  pi/6 =  0.523599
        0xc00921fb54442d18ULL,   // -pi/1 = -3.141593
        0xbff921fb54442d18ULL,   // -pi/2 = -1.570796
        0xbff0c152382d7365ULL,   // -pi/3 = -1.047198
        0xbfe921fb54442d18ULL,   // -pi/4 = -0.785398
        0xbfe0c152382d7365ULL    // -pi/6 = -0.523599
    };
    for (size_t i = 0; i < sizeof(PI) / sizeof(uint64_t); ++i)
        test_cos_sin(as_double(PI[i]));
    */

    test_cos_sin(0);
    test_cos_sin( 3.14159265358979323846 - 1);
    test_cos_sin( 3.14159265358979323846 / 2 - 0.5);
    test_cos_sin( 3.14159265358979323846 / 3);
    test_cos_sin( 3.14159265358979323846 / 4);
    test_cos_sin( 3.14159265358979323846 / 6);
    test_cos_sin(-3.14159265358979323846 + 1);
    test_cos_sin(-3.14159265358979323846 / 2 + 0.5);
    test_cos_sin(-3.14159265358979323846 / 3);
    test_cos_sin(-3.14159265358979323846 / 4);
    test_cos_sin(-3.14159265358979323846 / 6);

    test_atrig(0.0);
    test_atrig(0.5);
    test_atrig(1.0);

    // _exp(), log(), log10(), sqrtf()
    double F2[] = { 0.0, 2.0, -1.0, 100.0, -1000.0, 12345.67 };
    for (size_t i = 0; i < sizeof(F2) / sizeof(double); ++i)
        test_exp_log_log10_sqrt(F2[i]);
    for (size_t i = 0; i < sizeof(F2) / sizeof(double); ++i)
        test_frexp(F2[i]);

/* Issue with BR 12 bit in pow function
    test_pow( 0.0,  1.0);
    test_pow( 1.0,  0.0);
    test_pow( 1.0,  2.0);
    test_pow( 2.0,  1.0);
    test_pow( 2.0, -1.0);
    test_pow(10.0,  3.0);
    test_pow(10.0, -4.0);
*/

    test_fmod(  0.5,   1.0);
    test_fmod( 10.3,   3.0);
    test_fmod(123.456, 2.4);

    return 0;
}
