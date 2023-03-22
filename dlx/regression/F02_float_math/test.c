/*
   -- Test math functions on floats.
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



#include <math.h>
#include <stdint.h>

#ifndef __ndl__
float as_float(uint32_t u) {
    union { uint32_t u; float f; } uf;
    uf.u = u;
    return uf.f;
}
#endif

void test_ldexpf(float a, int e)
{
    chess_message("// test_ldexpf(" << a << ", " << e << ')');

    float c;
    chess_report(c = ldexp(a, e));
}

void test_ceilf_floorf_truncf(float a)
{
    chess_message("// test_ceilf_floorf_truncf(" << a << ')');

    float c;
    chess_report(c = ceilf (a));
    chess_report(c = floorf(a));
    chess_report(c = truncf(a));
}

void test_cosf_sinf(float a)
{
    chess_message("// test_cosf_sinf(" << a << ')');

    float c;
    chess_report(c = cosf(a));
    chess_report(c = sinf(a));
}

/*void test_atrig(float a)
{
    chess_message("// test_atrig(" << a << ')');

    float c;
    chess_report(c = acosf(a));
    chess_report(c = asinf(a));
    chess_report(c = atanf(a));
}*/

void test_expf_logf_log10f_sqrtf(float a)
{
    chess_message("// test_expf_logf_log10f_sqrtf(" << a << ')');

    float c;
    if (a <  50.0f) chess_report(c = expf  (a));
    if (a >   0.0f) chess_report(c = logf  (a));
    if (a >   0.0f) chess_report(c = log10f(a));
    if (a >=  0.0f) chess_report(c = sqrtf (a));
}

void test_powf(float a, float b)
{
    chess_message("// test_powf(" << a << ", " << b << ')');

    float c;
    chess_report(c = powf(a, b));
}

/*void test_fmod(float a, float b)
{
    chess_message("// test_fmod(" << a << ", " << b << ')');

    float c;
    chess_report(c = fmodf(a, b));
}*/

void test_frexpf(float a)
{
    chess_message("// test_frexpf(" << a << ')');

    float c;
    int e;
    chess_report(c = frexpf(a, &e));
    chess_report(e);
}

int main()
{
    test_ldexpf(  1.0f,  1);
    test_ldexpf(  1.0f,  2);
    test_ldexpf( -1.0f,  2);
    test_ldexpf( -1.0f, -2);
    test_ldexpf(100.0f,  5);
    test_ldexpf(100.0f, -9);

    // ceilf(), floorf()
    float F1[] = { 6.5f, 6.01f, 6.99f, -6.5f, -6.01f, -6.99f, 3.4e+38f, 3.4e-29f };
    for (int i = 0; i < sizeof(F1) / sizeof(float); ++i)
        test_ceilf_floorf_truncf(F1[i]);

    // sinf(), cosf()
    uint32_t PI[] = {
        0,
        0x40490fdb,     //  pi/1 =  3.141593  
        0x3fc90fdb,     //  pi/2 =  1.570796  
        0x3f860a92,     //  pi/3 =  1.047198  
        //0x3f490fdb,   //  pi/4 =  0.785398  
        //0x3f060a92,   //  pi/6 =  0.523599  
        0xc0490fdb,     // -pi/1 = -3.141593  
        0xbfc90fdb,     // -pi/2 = -1.570796  
        0xbf860a92,     // -pi/3 = -1.047198  
        //0xbf490fdb,   // -pi/4 = -0.785398  
        //0xbf060a92    // -pi/6 = -0.523599 
    };
    for (int i = 0; i < sizeof(PI) / sizeof(uint32_t); ++i)
        test_cosf_sinf(as_float(PI[i]));

    //test_atrig(0.0f);
    //test_atrig(0.5f);
    //test_atrig(1.0f);

    // _expf(), logf(), log10f(), sqrtf()
    float F2[] = { 0.0f, 1.0f, -1.0f, 100.0f, -1000.0f, 12345.67f };
    for (int i = 0; i < sizeof(F2) / sizeof(float); ++i)
        test_expf_logf_log10f_sqrtf(F2[i]);
    for (int i = 0; i < sizeof(F2) / sizeof(float); ++i)
        test_frexpf(F2[i]);

    test_powf( 0.0f,  1.0f);
    test_powf( 1.0f,  0.0f);
    test_powf( 1.0f,  2.0f);
    test_powf( 2.0f,  1.0f);
    test_powf( 2.0f, -1.0f);
    test_powf(10.0f,  3.0f);
    test_powf(10.0f, -4.0f);

    //test_fmod(  0.5f,   1.0f);
    //test_fmod( 10.3f,   3.0f);
    //test_fmod(123.456f, 2.4f);

    return 0;
}

