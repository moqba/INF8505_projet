/*
-- Test: expressions on TYPE
--
-- Copyright (c) 2014-2017 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

// The purpose of this test is :
//  - tests basic operations themselves
//  - as well as overflow detection (which depends on these basic operations).
// In other words, this test should not trigger any undefined behavior.

#define TYPE long
#define BITS 32

#include "regression.h"
// Calculate some constants based on the number of bits

#define S_1 ((TYPE)(((TYPE)1) << (BITS - 2)))                  // 0x40000000_00000000
#define S_2 ((TYPE)(S_1 | (S_1 >> 1)))                         // 0x60000000_00000000
#define S_4 ((TYPE)(S_2 | (S_2 >> 2)))                         // 0x78000000_00000000
#define S_8 ((TYPE)(S_4 | (S_4 >> 4)))                         // 0x7F800000_00000000
#define S16 ((TYPE)((BITS >  8) ? (S_8 | (S_8 >>  8)) : S_8))  // 0x7FFF8000_00000000
#define S32 ((TYPE)((BITS > 16) ? (S16 | (S16 >> 16)) : S16))  // 0x7FFFFFFF_80000000
#define S64 ((TYPE)((BITS > 32) ? (S32 | (S32 >> 32)) : S32))  // 0x7FFFFFFF_FFFFFFFF

#define S_MAX S64
#define S_MIN ((TYPE)(~S_MAX))   // assumes 2 complements
#define S0A ((TYPE)(((S_MAX >> 3) / 0xF) * 0xA))

#if (BITS == 8)
#define XIX (int) // needed for legible print
#else
#define XIX /**/
#endif



void test_unary_minus(TYPE x)
{
    UNKNOWN(x);
    bool overflow = (x == S_MIN);
    TYPE y = overflow ? 0 : -x;
    chess_report(overflow);
    chess_report(y);
}

void test_add(TYPE x, TYPE y)
{
    UNKNOWN(x); UNKNOWN(y);
    bool overflow = (x >= 0) ? ((S_MAX - x) < y)
                             : (y < (S_MIN - x));
    TYPE z = overflow ? 0 : x + y;
    chess_report(overflow);
    chess_report(z);
}

void test_sub(TYPE x, TYPE y)
{
    UNKNOWN(x); UNKNOWN(y);
    bool overflow = (x >= 0) ? (y <= (S_MIN + x))
                             : (-(S_MIN - x) < y);
    TYPE z = overflow ? 0 : x - y;
    chess_report(overflow);
    chess_report(z);
}

void test_mul(TYPE x, TYPE y)
{
    UNKNOWN(x); UNKNOWN(y);
    bool overflow = ((x > 0) && (y > 0) && (x > (S_MAX / y))) ||
                    ((x > 0) && (y < 0) && (y < (S_MIN / x))) ||
                    ((x < 0) && (y > 0) && (x < (S_MIN / y))) ||
                    ((x < 0) && (y < 0) && (y < (S_MAX / x)));
    TYPE z = overflow ? 0 : x * y;
    chess_report(overflow);
    chess_report(z);
}

void test_div_mod(TYPE x, TYPE y)
{
    UNKNOWN(x); UNKNOWN(y);
    bool overflow = (y == 0) || ((x == S_MIN) && (y == -1));

    TYPE z = overflow ? 0 : x / y;
    chess_report(overflow);
    chess_report(z);

    TYPE w = overflow ? 0 : x % y;
    chess_report(overflow);
    chess_report(w);
}

void test_shift_left(TYPE x, TYPE y)
{
    UNKNOWN(x); UNKNOWN(y);
    bool overflow = (y < 0) || (y >= BITS) ||
                    ((y != 0) && ((x < 0) || (x > (S_MAX >> y))));
    TYPE z = overflow ? 0 : x << y;
    chess_report(overflow);
    chess_report(z);
}

void test_shift_right(TYPE x, TYPE y)
{
    UNKNOWN(x); UNKNOWN(y);
    bool overflow = (y < 0) || (y >= BITS) ||
                    ((y != 0) && (x < 0));
    TYPE z = overflow ? 0 : x >> y;
    chess_report(overflow);
    chess_report(z);
}


void test(TYPE x, TYPE y)
{
    chess_message("// test_signed(" << XIX x << ", " << XIX y << ')');

    // these can trigger undefined behavior
    test_unary_minus(x);
    test_add        (x, y);
    test_sub        (x, y);
    test_mul        (x, y);
    test_div_mod    (x, y);
    test_shift_left (x, y);
    test_shift_right(x, y);

    // these are always OK
    TYPE z;
    UNKNOWN(x); UNKNOWN(y);
    chess_report(z = ~x);
    chess_report(z = x & y);
    chess_report(z = x | y);
    chess_report(z = x ^ y);
    chess_report(x == y); chess_report(!(x == y));
    chess_report(x != y); chess_report(!(x != y));
    chess_report(x <  y); chess_report(!(x <  y));
    chess_report(x <= y); chess_report(!(x <= y));
    chess_report(x >  y); chess_report(!(x >  y));
    chess_report(x >= y); chess_report(!(x >= y));
}

int main()
{
    static const TYPE a[] = {
        0, 1, -1, 2, -2, 3, 4, 5, -16, 27, 42, 64, 97,
        S0A, S_MAX, S_MIN,
    };
    const int N = sizeof(a) / sizeof(*a);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            test(a[i], a[j]);
        }
    }
}
