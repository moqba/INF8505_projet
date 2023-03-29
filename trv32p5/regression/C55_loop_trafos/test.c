/*
-- Test loop statement transformations.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "regression.h"

// test for initialisation of __fb variable
int while_fb(int c)
{
    chess_message("// while_fb(" << c << ')');
    UNKNOWN(c);
    int x = 0;
    int cc;

    cc = c;
    while (cc--) {
        x += 1; UNKNOWN(x);
    }
    chess_report(x);

    cc = c;
    while (cc) {
        x += 10; UNKNOWN(x);
        cc = cc - 1;
    }
    chess_report(x);

    cc = c;
    while (cc > 0) {
        x += 100; UNKNOWN(x);
        cc = cc - 1;
    }
    chess_report(x);

    return x;
}

// do-while and while-do loops with either a break or a continue stmt
int while_brk_cnt(int c, int k)
{
    chess_message("// while_brk_cnt(" << c << ", " << k << ')');
    UNKNOWN(c); UNKNOWN(k);
    int x = 0;
    int y = 0;
    int cc;

    cc = c;
    do {
        x++; UNKNOWN(x);
        y++; UNKNOWN(y);
    } while (cc--);
    chess_report(x + y);

    cc = c;
    while (cc--) {
        x++; UNKNOWN(x);
        y++; UNKNOWN(y);
    }
    chess_report(x + y);

    cc = c;
    do {
        x++; UNKNOWN(x);
        UNKNOWN(k); // to prevent the optimizer from splitting this into 2 loops
        if (k) break;
        y++; UNKNOWN(y);
    } while (cc--);
    chess_report(x + y);

    cc = c;
    while (cc--) {
        x++; UNKNOWN(x);
        UNKNOWN(k);
        if (k) break;
        y++; UNKNOWN(y);
    }
    chess_report(x + y);

    cc = c;
    do {
        x++; UNKNOWN(x);
        UNKNOWN(k);
        if (k) continue;
        y++; UNKNOWN(y);
    } while (cc--);
    chess_report(x + y);

    cc = c;
    while (cc--) {
        x++; UNKNOWN(x);
        UNKNOWN(k);
        if (k) continue;
        y++; UNKNOWN(y);
    }
    chess_report(x + y);

    return x + y;
}

// for loops with either a break or a continue stmt
int for_brk_cnt(int c, int k)
{
    chess_message("// for_brk_cnt(" << c << ", " << k << ')');
    UNKNOWN(c); UNKNOWN(k);
    int x = 0;
    int y = 0;

    for (int j = 0; j < c; ++j) {
        x++; UNKNOWN(x);
        y++; UNKNOWN(y);
    }
    chess_report(x + y);

    for (int j = 0; j < c; ++j) {
        x++; UNKNOWN(x);
        UNKNOWN(k);
        if (k) break;
        y++; UNKNOWN(y);
    }
    chess_report(x + y);

    for (int j = 0; j < c; ++j) {
        x++; UNKNOWN(x);
        UNKNOWN(k);
        if (k) continue;
        y++; UNKNOWN(y);
    }
    chess_report(x + y);

    return x + y;
}

// do-while loop with both a break and a continue stmt
int while_brk_cnt_2(int c, int k, int l)
{
    chess_message("// while_brk_cnt_2(" << c << ", " << k << ", " << l << ')');
    UNKNOWN(c); UNKNOWN(k); UNKNOWN(l);
    int x = 0;

    do {
        x += 1; UNKNOWN(x);
        UNKNOWN(k);
        if (k) break;
        x += 10; UNKNOWN(x);
        UNKNOWN(l);
        if (l) continue;
        x += 100; UNKNOWN(x);
    } while (c--);
    chess_report(x);
    return x;
}

// for loop with nested break and continue
int for_nested_1(int c, int k)
{
    chess_message("// for_nested_1(" << c << ", " << k << ')');
    UNKNOWN(c); UNKNOWN(k);
    int x = 0;

    for (int j = 0; j < c; ++j) {
        x += 1; UNKNOWN(x);
        if (j == 3) {
            x += 10; UNKNOWN(x);
            UNKNOWN(k);
            if (k) continue;
            x += 100; UNKNOWN(x);
        } else {
            x += 1000; UNKNOWN(x);
        }
    }
    chess_report(x);
    return x;
}

// for loop with nested break and continue
int for_nested_2(int c, int k)
{
    chess_message("// for_nested_2(" << c << ", " << k << ')');
    UNKNOWN(c); UNKNOWN(k);
    int x = 0;
    int y = 0;

    for (int i = 0; i < c; ++i) {
        x += 1; UNKNOWN(x);
        for (int j = i; j < c; ++j) {
            y += 1; UNKNOWN(y);
            UNKNOWN(k);
            if (k) {
                y += 1000; UNKNOWN(y);
                break;
            }
            y += 10; UNKNOWN(y);
        }
    }
    chess_report(x);
    chess_report(y);
    return x;
}

int main()
{
    while_fb(4);
    while_fb(5);

    while_brk_cnt(5, 0);
    while_brk_cnt(5, 1);
    while_brk_cnt(6, 0);
    while_brk_cnt(6, 1);
    while_brk_cnt(1, 0);
    while_brk_cnt(1, 1);
    while_brk_cnt(0, 0);
    while_brk_cnt(0, 1);

    for_brk_cnt(5, 0);
    for_brk_cnt(5, 1);
    for_brk_cnt(6, 0);
    for_brk_cnt(6, 1);
    for_brk_cnt(1, 0);
    for_brk_cnt(1, 1);
    for_brk_cnt(0, 0);
    for_brk_cnt(0, 1);

    while_brk_cnt_2(4, 0, 0);
    while_brk_cnt_2(4, 0, 1);
    while_brk_cnt_2(4, 1, 0);
    while_brk_cnt_2(4, 1, 1);

    for_nested_1(7, 0);
    for_nested_1(8, 0);
    for_nested_1(7, 1);
    for_nested_1(8, 1);

    for_nested_2(3, 0);
    for_nested_2(3, 1);
    return 0;
}
