/*
-- Test expressions on floats.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include <math.h>

//#if !defined(__chess__)
//#include <iostream>
//#endif

#define ADDSUB
#define MUL
#define COMP
#define ARRAY
#define DIV
#define SQRT
#define ITOF
#define FTOI
#define ROUNDF

// work around chess_report being incapable of correctly reporting NaN
//   chess_report tries to convert native FP representations to FP representation on the core.
//   It doesn't do this for NaN
inline void workaround_chess_report( float c )
{
    union { unsigned u; float f; } uf;
    uf.f = c;
    chess_report(uf.u);
}

void test_arith(float a, float b)
{
    chess_message( "// test_arith(" << a << ',' << b << ')' );

    float c;
#ifdef ADDSUB
    workaround_chess_report( c = a + b );
    workaround_chess_report( c = a - b );
    workaround_chess_report( c = b - a );
#endif
#ifdef MUL
    workaround_chess_report( c = a * b );
#endif
#ifdef DIV
    if (b != 0.0f)
        workaround_chess_report( c = a / b );
    if (a != 0.0f)
        workaround_chess_report( c = b / a );
#endif
}

int isNan(float val)
{
    union { unsigned u; float f; } uf;
    uf.f = val;
    int exp_eq_0xff = ((uf.u&0x7f800000) == 0x7f800000);
    int mant_ne_0 = ((uf.u&0x7fffff) != 0);
    return exp_eq_0xff&mant_ne_0;
}

void test_compare(float a, float b)
{
    // do not test compare if a or b is NaN
    if (isNan(a) || isNan(b)) {
        chess_message( "// skip_compare because nan");
        // chess_report(a);
        // chess_report(b);
    }
    else  {
        chess_message( "// test_compare(" << a << ',' << b << ')' );

        chess_report( a < b );
        chess_report( a <= b );
        chess_report( a > b );
        chess_report( a >= b );
        chess_report( a == b );
        chess_report( a != b );
    }
}

void test_bin(float a, float b)
{
    test_arith(a,b);
#ifdef COMP
    test_compare(a,b);
#endif
}

float A[] = { 1.1, 2.2, 3.3, 4.4, 6.6, 7.7, 8.8 };
float B[] = { 0.1, 0.2, 0.3, 0.4, 0.6, 0.7, 0.8 };

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

void test_sqrtf(float a)
{
    chess_message( "// test_sqrtf(" << a << ')' );
    float c;
    workaround_chess_report( c = sqrtf(a) );
}

void test_itof(unsigned u)
{
    chess_message( "// test_i2f(" << u << ')' );
    int a = (int) u;
    float c;
    workaround_chess_report( c = (float) a );
}

void test_ftoi(float a)
{
    union { unsigned u; float f; } ufa;
    ufa.f = a;
    chess_message( "// test_f2i(" << a << ',' << ufa.u << ')' );
    int c;
    chess_report( c = (int) a );
}

void test_roundf(float a)
{
    union { unsigned u; float f; } ufa;
    ufa.f = a;
    chess_message( "// test_roundf(" << a << ',' << ufa.u << ')' );
    int b = (int) a;
    float c = (float) b;
    float d = roundf(a);
    workaround_chess_report( a );
    //chess_report( b );
    //workaround_chess_report( c );
    workaround_chess_report( d );
}

unsigned T[] = { 0x00000000,   //    sign=0, exp=0, significant=0        ; +0.0
                 0x80000000,   //    sign=1, exp=0, significant=0        ; -0.0
                 0x00000001,   //    sign=0, exp=0, significant=1        ; +e ; smallest positive denormalized number
                 0x80000001,   //    sign=1, exp=0, significant=1        ; -e ; smallest negative denormalized number
                 0x00000002,   //    sign=0, exp=0, significant=2        ; +2*e
                 0x80000002,   //    sign=1, exp=0, significant=2        ; -2*e
                 0x00400000,   //    sign=0, exp=0, significant=0x400000
                 0x80400000,   //    sign=1, exp=0, significant=0x400000
                 0x007ffffe,   //    sign=0, exp=0, significant=0x7ffffe
                 0x807ffffe,   //    sign=1, exp=0, significant=0x7ffffe
                 0x007fffff,   //    sign=0, exp=0, significant=0x7fffff ; largest denormalized positive
                 0x807fffff,   //    sign=1, exp=0, significant=0x7fffff ; largest denormalized negative
                 0x00800000,   //    sign=0, exp=1, significant=0        ; smallest normalized positive
                 0x80800000,   //    sign=1, exp=1, significant=0        ; smallest normalized negative
                 0x00800001,   //    sign=0, exp=1, significant=1
                 0x80800001,   //    sign=1, exp=1, significant=1
                 0x00c00000,   //    sign=0, exp=1, significant=0x400000
                 0x80c00000,   //    sign=1, exp=1, significant=0x400000
                 0x00fffffe,   //    sign=0, exp=1, significant=0x7ffffe
                 0x80fffffe,   //    sign=1, exp=1, significant=0x7ffffe
                 0x00ffffff,   //    sign=0, exp=1, significant=0x7fffff
                 0x80ffffff,   //    sign=1, exp=1, significant=0x7fffff
                 0x3F000000,   //    sign=0, exp=126, significant=0        ;  0.5
                 0xbF000000,   //    sign=1, exp=126, significant=0        ; -0.5
                 0x3F000001,   //    sign=0, exp=126, significant=1        ;
                 0xbF000001,   //    sign=1, exp=126, significant=1        ;
                 0x3F400000,   //    sign=0, exp=126, significant=0x400000
                 0xbF400000,   //    sign=1, exp=126, significant=0x400000
                 0x3F7ffffe,   //    sign=0, exp=126, significant=0x7ffffe
                 0xbF7ffffe,   //    sign=1, exp=126, significant=0x7ffffe
                 0x3F7fffff,   //    sign=0, exp=126, significant=0x7fffff
                 0xbF7fffff,   //    sign=1, exp=126, significant=0x7fffff
                 0x3F800000,   //    sign=0, exp=127, significant=0        ;  1.0
                 0xbF800000,   //    sign=1, exp=127, significant=0        ; -1.0
                 0x3F800001,   //    sign=0, exp=127, significant=1        ;
                 0xbF800001,   //    sign=1, exp=127, significant=1        ;
                 0x3Fc00000,   //    sign=0, exp=127, significant=0x400000
                 0xbFc00000,   //    sign=1, exp=127, significant=0x400000
                 0x3Ffffffe,   //    sign=0, exp=127, significant=0x7ffffe
                 0xbFfffffe,   //    sign=1, exp=127, significant=0x7ffffe
                 0x3Fffffff,   //    sign=0, exp=127, significant=0x7fffff
                 0xbFffffff,   //    sign=1, exp=127, significant=0x7fffff
                 0x40000000,   //    sign=0, exp=128, significant=0        ;  2.0
                 0xc0000000,   //    sign=1, exp=128, significant=0        ; -2.0
                 0x40000001,   //    sign=0, exp=128, significant=1        ;
                 0xc0000001,   //    sign=1, exp=128, significant=1        ;
                 0x40400000,   //    sign=0, exp=128, significant=0x400000
                 0xc0400000,   //    sign=1, exp=128, significant=0x400000
                 0x407ffffe,   //    sign=0, exp=128, significant=0x7ffffe
                 0xc07ffffe,   //    sign=1, exp=128, significant=0x7ffffe
                 0x407fffff,   //    sign=0, exp=128, significant=0x7fffff
                 0xc07fffff,   //    sign=1, exp=128, significant=0x7fffff
                 0x7F000000,   //    sign=0, exp=254, significant=0
                 0xFF000000,   //    sign=1, exp=254, significant=0
                 0x7F000001,   //    sign=0, exp=254, significant=1
                 0xFF000001,   //    sign=1, exp=254, significant=1
                 0x7F000002,   //    sign=0, exp=254, significant=2
                 0xFF000002,   //    sign=1, exp=254, significant=2
                 0x7F400000,   //    sign=0, exp=254, significant=0x400000
                 0xFF400000,   //    sign=1, exp=254, significant=0x400000
                 0x7F7ffffe,   //    sign=0, exp=254, significant=0x7ffffe
                 0xFF7ffffe,   //    sign=1, exp=254, significant=0x7ffffe
                 0x7F7fffff,   //    sign=0, exp=254, significant=0x7fffff
                 0xFF7fffff,   //    sign=1, exp=254, significant=0x7fffff
                 0x7F800000,   //    sign=0, exp=255, significant=0        ; +inf
                 0xFF800000,   //    sign=1, exp=255, significant=0        ; -inf
                 0xffc00000,   //    sign=1, exp=255, significant=0x800000 ; nan
                 0x4015C28F,   //    2.34
                 0xC0490FDB,   //   -3.14159265
                 0x42F6E979,   //  123.456
                 0xC49A522B,   //-1234.5678

// just some random numbers
0x0f7d02eb, /* 1.247443e-29 */
0xa85a088f, /* -1.210329e-14 */
0x462265af, /* 1.039342e+04 */
0xee422592, /* -1.502138e+28 */
0xae5ee6b3, /* -5.068186e-11 */
0x9de6f7ec, /* -6.113684e-21 */
0xaddf7c04, /* -2.540724e-11 */
0x93696b6f, /* -2.946170e-27 */
0xe6ffc5f8, /* -6.039277e+23 */
0x894247a4, /* -2.338559e-33 */
0x3c3bf0cb, /* 1.147098e-02 */
0xdc4e4afd, /* -2.322652e+17 */
0x72aa45c2, /* 6.745188e+30 */
0x0b461de8, /* 3.815591e-32 */
0x48036d0d, /* 1.345802e+05 */
0x9777cbfd, /* -8.006747e-25 */
0x05a24102, /* 1.525829e-35 */
0xd7acff63, /* -3.804258e+14 */
0xc62a7281, /* -1.090863e+04 */
0xe0068217, /* -3.876934e+19 */
0x8675739f, /* -4.616432e-35 */
0xd701f72b, /* -1.428986e+14 */
0x7e791d8a, /* 8.278279e+37 */
0x8c26d5f6, /* -1.285256e-31 */
0xfbeaa4cf, /* -2.436680e+36 */
0x55541141, /* 1.457316e+13 */
0xb1534bf3, /* -3.074771e-09 */
0x28a22876, /* 1.800316e-14 */
0x0d16ff0a, /* 4.652931e-31 */
0x2ab2f4f6, /* 3.178913e-13 */
0xe6048f5b, /* -1.564992e+23 */
0xaaae6cd2, /* -3.098412e-13 */
0xa80fa1a2, /* -7.973143e-15 */
0xf299617c, /* -6.076039e+30 */
0xeb753383, /* -2.964301e+26 */
0x4e05eb32, /* 5.616959e+08 */
0xd6883c3c, /* -7.489614e+13 */
0xcfb49350, /* -6.059106e+09 */
0x99732c52, /* -1.257176e-23 */
0x0b483c47, /* 3.856395e-32 */
0x2aaaaaaa,
0x758a2000,
0xffffffff    // sentinel
};

int main()
{
    float a, b;
    union { unsigned u; float f; } ufa, ufb;
    {
        ufa.u = 0x00400000;//T[3];
        ufb.u = 0x3fffffff;//T[7];
        chess_message( "// test_mul(" << ufa.u << ',' << ufb.u << ')' );
        chess_report(ufa.u);
        chess_report(ufa.f);
        chess_report(ufb.u);
        chess_report(ufb.f);
        chess_report(ufa.f*ufb.f);
    }
    a = 2.5;  chess_report(a);

    a = 6.5;        b = 4.25;        test_bin(a,b);
    a = 0.0;        b = 1.0;        test_bin(a,b);
    a = 3.14;        b = 1.0e-6;     test_bin(a,b);

#ifdef ARRAY
    test_array(A,B);
#endif

    ufa.u = 0x40d00000; ufb.u = 0x40880000; test_bin(ufa.f,ufb.f);
    ufa.u = 0x59416d42; ufb.u = 0x59416d42; test_bin(ufa.f,ufb.f);

    chess_message( "// test T array elements()" );
    int i=0, j=0;
    while (T[i] != 0xffffffff) {
        ufa.u = T[i];
#ifdef SQRT
        test_sqrtf(ufa.f);
#endif
#ifdef ITOF
        test_itof(ufa.u);
#endif
#ifdef FTOI
        test_ftoi(ufa.f);
#endif
#ifdef ROUNDF
        test_roundf(ufa.f);
#endif
#if defined(ADDSUB) || defined(MUL) || defined(DIV)
        j = i;
        while (T[j] != 0xffffffff) {
            ufb.u = T[j];
            chess_message( "// test_bin(" << ufa.u << ',' << ufb.u << ')' );
            chess_report(ufa.u);
            //chess_report(ufa.f);
            chess_report(ufb.u);
            //chess_report(ufb.f);
            test_bin(ufa.f,ufb.f);
            j++;
        }
#endif
        i++;
    }

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

