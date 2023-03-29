/*
-- Test expressions on floats.
-- Copyright (c) 2014 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include <stdint.h>

void test_arith(float a, float b)
{
    chess_message("// test_arith(" << a << ", " << b << ')');

    float c;
    chess_report(c = a + b);
    chess_report(c = a - b);
    chess_report(c = b - a);
    chess_report(c = a * b);
    if (b != 0.0f) chess_report(c = a / b);
    if (a != 0.0f) chess_report(c = b / a);
}

void test_compare(float a, float b)
{
    chess_message("// test_compare(" << a << ", " << b << ')');

    chess_report(a <  b);
    chess_report(a <= b);
    chess_report(a >  b);
    chess_report(a >= b);
    chess_report(a == b);
    chess_report(a != b);
}

void test_bin(float a, float b)
{
    test_arith(a, b);
    test_compare(a, b);
}


float A[] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f };
float B[] = { 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f };

void test_array(float* p, float* q)
{
    chess_message("// test_array()");
    for (int i = 0; i < 8; i++)
        chess_report(p[i] + *q++);
}

void test_f2i(float f)
{
    chess_message("// test_f2i()");
    int32_t i = (int32_t)f;
    chess_report(i);
}

void test_i2f(int32_t i)
{
    chess_message("// test_i2f()");
    float f = (float)i;
    chess_report(f);
}

void test_f2u(float f)
{
    chess_message("// test_f2u()");
    uint32_t u = (uint32_t)f;
    chess_report(u);
}

void test_u2f(uint32_t u)
{
    chess_message("// test_u2f()");
    float f = (float)u;
    chess_report(f);
}

uint32_t T[] = {
    0x3F800000,   //    1.0
    0x4015C28F,   //    2.34
    0xC0490FDB,   //   -3.14159265
    0x42F6E979,   //  123.456
    0xC49A522B,   //-1234.5678
    0xffffffff  // sentinel
};

int main()
{
    float a, b;

    a = 2.5f;  chess_report(a);

    a = 6.5f;   b = 4.25f;      test_bin(a,b);
    a = 0.0f;   b = 1.0f;       test_bin(a,b);
    a = 3.14f;  b = 1.0e-6f;    test_bin(a,b);

    test_array(A, B);

    union { uint32_t u; float f; } ufa, ufb;
    ufa.u = 0x40d00000; ufb.u = 0x40880000; test_bin(ufa.f, ufb.f);
    ufa.u = 0x59416d42; ufb.u = 0x59416d42; test_bin(ufa.f, ufb.f);

    chess_message("// test T array elements()");
    int i = 0, j = 0;
    while (T[i] != 0xffffffff) {
        j = i;
        while (T[j] != 0xffffffff) {
            ufa.u = T[i];
            ufb.u = T[j];
            test_bin(ufa.f, ufb.f);
            j++;
        }
        i++;
    }

    int32_t inan = 0xffc00000;
    float nan = *(float*)&inan;

    test_compare(nan, 6.5);
    test_compare(2.44e4f, nan);
    test_compare(nan, nan);

    test_f2i(6.5f);
    test_f2i(2.44e4f);
    test_f2i(-155.77f);

    test_i2f(155);
    test_i2f(-155);

    test_f2u(10.3f);
    // test_f2u(-22.2f); // undefined
    test_f2u(2.44e4f);
    test_f2u(2.44e8f);
    test_f2u(2.44e9f);

    test_u2f(10);
    test_u2f(0x80000000);
    test_u2f(0xe0000000);

    return 0;
}
