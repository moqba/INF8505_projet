/*
-- Test expressions on floats.
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#include <stdint.h>

#define FLOAT float24_t
#define as_FLOAT as_float24_t

void test_arith(FLOAT a, FLOAT b)
{
    chess_message("// test_arith(" << a << ", " << b << ')');

    FLOAT c;
    chess_report(c = a + b);
    chess_report(c = a - b);
    chess_report(c = b - a);
    chess_report(c = a * b);
    if (b != (FLOAT)0.0f) chess_report(c = a / b);
    if (a != (FLOAT)0.0f) chess_report(c = b / a);
}

void test_compare(FLOAT a, FLOAT b)
{
    chess_message("// test_compare(" << a << ", " << b << ')');

    chess_report(a <  b);
    chess_report(a <= b);
    chess_report(a >  b);
    chess_report(a >= b);
    chess_report(a == b);
    chess_report(a != b);
}

void test_bin(FLOAT a, FLOAT b)
{
    test_arith(a, b);
    test_compare(a, b);
}

void test_f2sc(FLOAT f)
{
    chess_message("// test_f2sc(" << f << ')');
    int8_t i = (int8_t)f;
    chess_report(i);
}

void test_f2ss(FLOAT f)
{
    chess_message("// test_f2ss(" << f << ')');
    int16_t i = (int16_t)f;
    chess_report(i);
}

void test_f2i(FLOAT f)
{
    chess_message("// test_f2i(" << f << ')');
    int32_t i = (int32_t)f;
    chess_report(i);
}
void test_sc2f(int8_t i)
{
    chess_message("// test_sc2f(" << i << ')');
    FLOAT f = (FLOAT)i;
    chess_report(f);
}
void test_ss2f(int32_t i)
{
    chess_message("// test_ss2f(" << i << ')');
    FLOAT f = (FLOAT)i;
    chess_report(f);
}

void test_i2f(int32_t i)
{
    chess_message("// test_i2f(" << i << ')');
    FLOAT f = (FLOAT)i;
    chess_report(f);
}

void test_f2us(FLOAT f)
{
    chess_message("// test_f2us(" << f << ')');
    uint16_t u = (uint16_t)f;
    chess_report(u);
}

void test_f2uc(FLOAT f)
{
    chess_message("// test_f2uc(" << f << ')');
    uint8_t u = (uint8_t)f;
    chess_report(u);
}

void test_f2u(FLOAT f)
{
    chess_message("// test_f2u(" << f << ')');
    uint32_t u = (uint32_t)f;
    chess_report(u);
}

void test_us2f(uint16_t u)
{
    chess_message("// test_us2f(" << u << ')');
    FLOAT f = (FLOAT)u;
    chess_report(f);
}

void test_uc2f(uint8_t u)
{
    chess_message("// test_uc2f(" << u << ')');
    FLOAT f = (FLOAT)u;
    chess_report(f);
}

void test_u2f(uint32_t u)
{
    chess_message("// test_u2f(" << u << ')');
    FLOAT f = (FLOAT)u;
    chess_report(f);
}

void test_round(FLOAT u)
{
    chess_message("// test_round(" << u << ')');
    FLOAT f;
    f = roundf(u); chess_report(f);
    f = floorf(u); chess_report(f);
    f = ceilf (u); chess_report(f);
    f = truncf(u); chess_report(f);
}

void test_fsqrt(FLOAT u)
{
    chess_message("// test_fsqrt(" << u << ')');
    FLOAT f = fsqrt(u);
    chess_report(f);
}


void test_small()
{
    chess_message("// test_small()");

    static FLOAT A[] = { 1.1f, 2.2f, -3.3f, 0.4f };

    for (int i = 0; i < 1; i++) {
        for (int j = i; j < 1; j++) {
            chess_message("// Test small (" << i << ',' << j << ')');
            FLOAT aa = A[i];
            FLOAT bb = A[j];
            chess_report(aa);
            chess_report(bb);
            test_bin(aa,bb);
        }
    }
}

void test_full()
{
    // Critical values for float fields

    static unsigned SGN[] = { 0x000000, 0x800000 };
    static unsigned EXP[] = { 0x000000,  // 2^-126 (denormalized)
                              0x008000,  // 2^-126
                              0x010000,  // 2^-125
                              0x3f0000,  // 2^-1
                              0x3f8000,  // 2^0
                              0x400000,  // 2^1
                              0x7e8000,  // 2^126
                              0x7f0000,  // 2^127
                              0x7f8000,  // 2^128 (Inf or NaN)
                            };
    static unsigned MAN[] = { 0x000000, 0x000001, 0x004000, 0x004001 };

    int NSGN = sizeof(SGN) / sizeof(unsigned);
    int NEXP = sizeof(EXP) / sizeof(unsigned);
    int NMAN = sizeof(MAN) / sizeof(unsigned);

    chess_message("// NSGN(" << NSGN << ')');
    chess_message("// NEXP(" << NEXP << ')');
    chess_message("// NMAN(" << NMAN << ')');

    // Generate combinations

    int NF24 = NSGN * NEXP * NMAN;
    chess_message("// NF24(" << NF24 << ')');

    unsigned F24[1024];
    int f24cnt=0;

    for (int isgn = 0; isgn < NSGN; isgn++) {
        for (int iexp = 0; iexp < NEXP; iexp++) {
            for (int iman = 0; iman < NMAN; iman++) {
                F24[f24cnt++] = SGN[isgn] | EXP[iexp] | MAN[iman];
            }
        }
    }

    for (int ii = 0; ii < NF24; ii++) {
        chess_message("// Report (" << ii << ')');
        chess_report(F24[ii]);
        chess_report(as_FLOAT(F24[ii]));
    }

    // Test float operators

    chess_message("// test F24 array elements");
    for (int ii = 0; ii < NF24; ii++) {
        for (int jj = ii; jj < NF24; jj++) {
            chess_message("// Test operators (" << ii << ',' << jj << ')');
            FLOAT aa = as_FLOAT(F24[ii]);
            FLOAT bb = as_FLOAT(F24[jj]);
            chess_report(aa);
            chess_report(bb);
            test_bin(aa,bb);
        }
    }

    // Test float conversions

    for (int ii = 0; ii < NF24; ii++) {
        chess_message("// Test conversions (" << ii << ')');
        test_i2f(F24[ii]);
        test_f2i(as_FLOAT(F24[ii]));
        test_u2f(F24[ii]);
        test_f2u(as_FLOAT(F24[ii]));


        test_i2f(F24[ii]);
        test_f2i(as_FLOAT(F24[ii]));

        test_sc2f(F24[ii]);
        test_f2sc(as_FLOAT(F24[ii]));

        test_ss2f(F24[ii]);
        test_f2ss(as_FLOAT(F24[ii]));

        test_u2f(F24[ii]);
        test_f2u(as_FLOAT(F24[ii]));

        test_uc2f(F24[ii]);
        test_f2uc(as_FLOAT(F24[ii]));

        test_us2f(F24[ii]);
        test_f2us(as_FLOAT(F24[ii]));

        test_round(as_FLOAT(F24[ii]));

        if((F24[ii]&0x00800000)==0) test_fsqrt(as_FLOAT(F24[ii]));
    }
}

int main()
{
    test_small();
    test_full();

    static FLOAT R[] = { 0.4f, 1.4f, 23546.40843f, 337590.4389202f, 43223.473829f, 589382.4382f, 6823.4832f,
                             0.5f, 1.5f, 23546.50843f, 337590.5389202f, 43223.573829f, 589382.5382f, 6823.5832f,
                             0.6f, 1.6f, 23546.60843f, 337590.6389202f, 43223.673829f, 589382.6382f, 6823.6832f,
                             0.7f, 1.7f, 23546.70843f, 337590.7389202f, 43223.773829f, 589382.7382f, 6823.7832f  };

    for(int i=0;i<7;i++) {
        for(int j=0;j<4;j++) {
            chess_message("// Test round R[" << j << "][" << i <<"]");
            chess_report(R[i+7*j]);
            test_round(R[i+7*j]);
        }
    }

    static FLOAT R2[] = { 0.4f, -0.4f, 0.5f, -0.5f, 0.6f, -0.6f};
    for(int j=0;j<6;j++) {
        chess_message("// Test round R2[" << j << "]");
        chess_report(R2[j]);
        test_round  (R2[j]);
    }


    return 0;
}
