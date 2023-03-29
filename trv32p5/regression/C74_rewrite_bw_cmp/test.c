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

void* escape_ptr;

// Test data: Permutations of 4 values without repetition

int A[24][4] = { {10, 20, 30, 40},
                 {10, 20, 40, 30},
                 {10, 30, 20, 40},
                 {10, 30, 40, 20},
                 {10, 40, 20, 30},
                 {10, 40, 30, 20},
                 {20, 10, 30, 40},
                 {20, 10, 40, 30},
                 {20, 30, 10, 40},
                 {20, 30, 40, 10},
                 {20, 40, 10, 30},
                 {20, 40, 30, 10},
                 {30, 10, 20, 40},
                 {30, 10, 40, 20},
                 {30, 20, 10, 40},
                 {30, 20, 40, 10},
                 {30, 40, 10, 20},
                 {30, 40, 20, 10},
                 {40, 10, 20, 30},
                 {40, 10, 30, 20},
                 {40, 20, 10, 30},
                 {40, 20, 30, 10},
                 {40, 30, 10, 20},
                 {40, 30, 20, 10} };

// test expressions with two terms

#define TEST_CMP_OP_CMP(T)                                                \
    T t1_##T(T a, T b, T c, T d) { return a <  b & c >  d ? 101 : 201; }  \
    T t2_##T(T a, T b, T c, T d) { return a <= b & c <  d ? 102 : 202; }  \
    T t3_##T(T a, T b, T c, T d) { return a == b & c >= d ? 103 : 203; }  \
    T t4_##T(T a, T b, T c, T d) { return a >  b | c <= d ? 104 : 204; }  \
    T t5_##T(T a, T b, T c, T d) { return a <= b | c == d ? 105 : 205; }  \
    T t6_##T(T a, T b, T c, T d) { return a != b | c >= d ? 106 : 206; }  \
                                                                          \
    void test_cmp_op_cmp_##T(T a, T b, T c, T d)                          \
    {                                                                     \
        UNKNOWN(a); UNKNOWN(b); UNKNOWN(c); UNKNOWN(d);                   \
        chess_report(t1_##T(a, b, c, d));                                 \
        chess_report(t2_##T(a, b, c, d));                                 \
        chess_report(t3_##T(a, b, c, d));                                 \
        chess_report(t4_##T(a, b, c, d));                                 \
        chess_report(t5_##T(a, b, c, d));                                 \
        chess_report(t6_##T(a, b, c, d));                                 \
    }

TEST_CMP_OP_CMP(int)
TEST_CMP_OP_CMP(unsigned)

void test1()
{
    chess_message("// test1()");
    for (int i = 0; i < 24; ++i) {
        test_cmp_op_cmp_int     (A[i][0], A[i][1], A[i][2], A[i][3]);
        test_cmp_op_cmp_unsigned(A[i][0], A[i][1], A[i][2], A[i][3]);
    }
}


// test expressions with three terms

int ta(int a, int b, int c, int d) { return  a < b &  c > d  & a < c  ? 501 : 601; }
int tb(int a, int b, int c, int d) { return  a < b |  c > d  & a > c  ? 502 : 602; }
int tc(int a, int b, int c, int d) { return  a < b &  c > d  | a > c  ? 503 : 603; }
int td(int a, int b, int c, int d) { return  a < b |  c > d  | a > c  ? 504 : 604; }
int te(int a, int b, int c, int d) { return  a < b & (c > d  | a > c) ? 505 : 605; }
int tf(int a, int b, int c, int d) { return (a < b |  c > d) & a > c  ? 506 : 606; }
int tg(int a, int b, int c, int d) { return  a < b | (c > d  | a > c) ? 507 : 607; }
int th(int a, int b, int c, int d) { return  a < b & (c > d  & a > c) ? 508 : 608; }

void test2()
{
    chess_message("// test2()");
    escape_ptr = A; clobber();
    for (int i = 0; i < 24; ++i) {
        chess_report(ta(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(tb(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(tc(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(td(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(te(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(tf(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(tg(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(th(A[i][0], A[i][1], A[i][2], A[i][3]));
    }
}


// test expressions with four terms

int qa(int a, int b, int c, int d) { return a < b &  c < d &  a < c & b < d  ? 701 : 801; }
int qb(int a, int b, int c, int d) { return a < b &  c < d &  a < c | b < d  ? 702 : 802; }
int qc(int a, int b, int c, int d) { return a < b &  c < d |  a < c & b < d  ? 703 : 803; }
int qd(int a, int b, int c, int d) { return a < b &  c < d |  a < c | b < d  ? 704 : 804; }
int qe(int a, int b, int c, int d) { return a < b |  c < d &  a < c & b < d  ? 705 : 805; }
int qf(int a, int b, int c, int d) { return a < b |  c < d &  a < c | b < d  ? 706 : 806; }
int qg(int a, int b, int c, int d) { return a < b |  c < d |  a < c & b < d  ? 707 : 807; }
int qh(int a, int b, int c, int d) { return a < b |  c < d |  a < c | b < d  ? 708 : 808; }
int qi(int a, int b, int c, int d) { return a < b | (c < d |  a < c | b < d) ? 708 : 808; }
int qj(int a, int b, int c, int d) { return a < b |  c < d | (a < c | b < d) ? 708 : 808; }

void test3()
{
    chess_message("// test3()");
    escape_ptr = A; clobber();
    for (int i = 0; i < 24; ++i) {
        chess_report(qa(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(qb(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(qc(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(qd(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(qe(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(qf(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(qg(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(qh(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(qi(A[i][0], A[i][1], A[i][2], A[i][3]));
        chess_report(qj(A[i][0], A[i][1], A[i][2], A[i][3]));
    }
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}
