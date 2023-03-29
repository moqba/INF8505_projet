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

#define TYPE unsigned
#define BITS 32

#include "regression.h"
// Calculate some constants based on the number of bits
#define U80 ((TYPE)(((TYPE)1) << (BITS - 1)))
#define U7F ((TYPE)(U80 - 1))
#define UFF ((TYPE)(~((TYPE)0)))
#define UFE ((TYPE)(~((TYPE)1)))
#define U0A ((TYPE)(((UFF >> 4) / 0xF) * 0xA))

#if (BITS == 8)
#define XIX (int) // needed for legible print
#else
#define XIX /**/
#endif



void test_div_mod(TYPE x, TYPE y)
{
    UNKNOWN(x); UNKNOWN(y);
    bool overflow = (y == 0);

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
    bool overflow = (y >= BITS);
    TYPE z = overflow ? 0 : x << y;
    chess_report(overflow);
    chess_report(z);
}

void test_shift_right(TYPE x, TYPE y)
{
    UNKNOWN(x); UNKNOWN(y);
    bool overflow = (y >= BITS);
    TYPE z = overflow ? 0 : x >> y;
    chess_report(overflow);
    chess_report(z);
}


void test(TYPE x, TYPE y)
{
    chess_message("// test_unsigned(" << XIX x << ", " << XIX y << ')');

    // (only) these can trigger undefined behavior
    test_div_mod    (x, y);
    test_shift_left (x, y);
    test_shift_right(x, y);

    // these are always OK
    TYPE z;
    UNKNOWN(x); UNKNOWN(y);
    chess_report(z = -x);
    chess_report(z = x + y);
    chess_report(z = x - y);
    chess_report(z = x * y);
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
        0, 1, 2, 3, 4, 5, 16, 27, 42, 64, 97,
        U0A, U7F, U80, UFE, UFF,
    };
    const int N = sizeof(a) / sizeof(*a);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            test(a[i], a[j]);
        }
    }
}
