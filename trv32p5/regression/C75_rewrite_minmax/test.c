/*
-- Test rewriting of logical expressions.
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

#define N 8

int A[8][3] = { { 10, 20, 30},
                { 10, 20,-30},
                { 10,-20, 30},
                { 10,-20,-30},
                {-10, 20, 30},
                {-10, 20,-30},
                {-10,-20, 30},
                {-10,-20,-30} };

// test expressions with two terms

#define TEST_2(T)                                               \
    T ta_##T(T a, T b) { return a == 0 && b == 0 ? 101 : 102; } \
    T tb_##T(T a, T b) { return a != 0 || b != 0 ? 201 : 202; } \
    T tc_##T(T a, T b) { return a != 0 && b != 0 ? 301 : 302; } \
    T td_##T(T a, T b) { return a == 0 || b == 0 ? 401 : 402; } \
                                                                \
    void test_2_##T(T a, T b)                                   \
    {                                                           \
        UNKNOWN(a); UNKNOWN(b);                                 \
        chess_report(ta_##T(a, b));                             \
        chess_report(tb_##T(a, b));                             \
        chess_report(tc_##T(a, b));                             \
        chess_report(td_##T(a, b));                             \
    }

TEST_2(int)
TEST_2(unsigned)

void test_2()
{
    chess_message("// test_2()");
    for (int i = 0; i < N; ++i) {
        test_2_int     (A[i][0], A[i][1]);
        test_2_int     (A[i][0], A[i][1]);
        test_2_unsigned(A[i][1], A[i][0]);
        test_2_unsigned(A[i][1], A[i][0]);
    }
}


// test expressions with three terms

#define TEST_3(T)                                                  \
    T te_##T(T a, T b, T c) { return a < c && b < c ? 401 : 402; } \
    T tf_##T(T a, T b, T c) { return a > c && b > c ? 411 : 412; } \
    T tg_##T(T a, T b, T c) { return a < c || b < c ? 421 : 422; } \
    T th_##T(T a, T b, T c) { return a > c || b > c ? 431 : 432; } \
    T ti_##T(T a, T b, T c) { return c > a && c > b ? 511 : 512; } \
    T tj_##T(T a, T b, T c) { return c < a && c < b ? 521 : 522; } \
    T tk_##T(T a, T b, T c) { return c > a || c > b ? 531 : 532; } \
    T tl_##T(T a, T b, T c) { return c < a || c < b ? 541 : 542; } \
                                                                   \
    void test_3_##T(T a, T b, T c)                                 \
    {                                                              \
        UNKNOWN(a); UNKNOWN(b); UNKNOWN(c);                        \
        chess_report(te_##T(a, b, c));                             \
        chess_report(tf_##T(a, b, c));                             \
        chess_report(tg_##T(a, b, c));                             \
        chess_report(th_##T(a, b, c));                             \
        chess_report(ti_##T(a, b, c));                             \
        chess_report(tj_##T(a, b, c));                             \
        chess_report(tk_##T(a, b, c));                             \
        chess_report(tl_##T(a, b, c));                             \
    }

TEST_3(int)
TEST_3(unsigned)

void test_3()
{
    chess_message("// test_3()");
    for (int i = 0; i < N; ++i) {
        test_3_int     (A[i][0], A[i][1], A[i][2]);
        test_3_int     (A[i][0], A[i][2], A[i][1]);
        test_3_int     (A[i][1], A[i][0], A[i][2]);
        test_3_int     (A[i][1], A[i][2], A[i][0]);
        test_3_int     (A[i][2], A[i][0], A[i][1]);
        test_3_int     (A[i][2], A[i][1], A[i][0]);
        test_3_int     (A[i][0], A[i][0], A[i][0]);
        test_3_unsigned(A[i][0], A[i][1], A[i][2]);
        test_3_unsigned(A[i][0], A[i][2], A[i][1]);
        test_3_unsigned(A[i][1], A[i][0], A[i][2]);
        test_3_unsigned(A[i][1], A[i][2], A[i][0]);
        test_3_unsigned(A[i][2], A[i][0], A[i][1]);
        test_3_unsigned(A[i][2], A[i][1], A[i][0]);
        test_3_unsigned(A[i][0], A[i][0], A[i][0]);
    }
}

int main()
{
    test_2();
    test_3();
    return 0;
}
