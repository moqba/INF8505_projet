/*
-- Test expressions on floats.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



void test_arith(float a, float b)
{
    chess_message( "// test_arith(" << a << ',' << b << ')' );

    float c;
    chess_report( c = a + b );
    chess_report( c = a - b );
    chess_report( c = b - a );
    chess_report( c = a * b );
    if (b != 0.0)
        chess_report( c = a / b );
    if (a != 0.0)
        chess_report( c = b / a );
}

void test_compare(float a, float b)
{
    chess_message( "// test_compare(" << a << ',' << b << ')' );

    chess_report( a < b );
    chess_report( a <= b );
    chess_report( a > b );
    chess_report( a >= b );
    chess_report( a == b );
    chess_report( a != b );
}

void test_bin(float a, float b)
{
    test_arith(a,b);
    test_compare(a,b);
}




float A[] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8 };
float B[] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8 };

void test_array(float* p, float* q)
{
    chess_message( "// test_array()" );
    for (int i = 1; i < 8; i++)
        chess_report(p[i] + *q++);
}

void test_f2i(float f)
{
    chess_message( "// test_f2i()" );
    int i = (int)f;
    chess_report(i);
}

void test_i2f(int i)
{
    chess_message( "// test_i2f()" );
    float f = (float)i;
    chess_report(f);
}

void test_f2u(float f)
{
    chess_message( "// test_f2u()" );
    unsigned u = (unsigned)f;
    chess_report(u);
}

void test_u2f(unsigned u)
{
    chess_message( "// test_u2f()" );
    float f = (float)u;
    chess_report(f);
}

unsigned T[] = { 0x3F800000,   //    1.0
                 0x4015C28F,   //    2.34
                 0xC0490FDB,   //   -3.14159265
                 0x42F6E979,   //  123.456
                 0xC49A522B,   //-1234.5678
                 0xffffffff  // sentinel
               };

int main()
{
    float a, b;

    a = 2.5;  chess_report(a);

    a = 6.5;    b = 4.25;       test_bin(a,b);
    a = 0.0;    b = 1.0;        test_bin(a,b);
    a = 3.14;   b = 1.0e-6;     test_bin(a,b);

    test_array(A,B);

    union { unsigned u; float f; } ufa, ufb;
    ufa.u = 0x40d00000; ufb.u = 0x40880000; test_bin(ufa.f,ufb.f);
    ufa.u = 0x59416d42; ufb.u = 0x59416d42; test_bin(ufa.f,ufb.f);

    chess_message( "// test T array elements()" );
    int i=0, j=0;
    while (T[i] != 0xffffffff) {
        j = i;
        while (T[j] != 0xffffffff) {
            ufa.u = T[i];
            ufb.u = T[j];
            test_bin(ufa.f,ufb.f);
            j++;
        }
        i++;
    }

    int inan = 0xffc00000;
    float nan = *(float *)&inan;

    test_compare(nan,6.5);
    test_compare(2.44e4,nan);
    test_compare(nan,nan);

    test_f2i(6.5);
    test_f2i(2.44e4);
    test_f2i(-155.77);

    test_i2f(155);
    test_i2f(-155);

    test_f2u(10.3);
    test_f2u(-22.2);
    test_f2u(2.44e4);
    test_f2u(2.44e8);
    test_f2u(2.44e9);

    test_u2f(10);
    test_u2f(0x80000000);
    test_u2f(0xe0000000);

    return 0;
}

