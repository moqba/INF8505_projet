/*
-- Test: induction analysis and chain building
--
-- Copyright (c) 2014 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "regression.h"

void* escape_ptr;

const int L = 30;

static int AA[L] = {
    0,  1,  2,  3,  4,  5 , 6,  7,  8,  9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29
};

void test_chasing_ptr()
{
    chess_message("// test_chasing_ptr");
    escape_ptr = AA; clobber();
    for (int ii = 0, jj = 1; jj < L; ii++, jj++) {
        AA[ii] = AA[jj];
    }
}

void test_chain_building()
{
    chess_message("// test_chain_building");
    escape_ptr = AA; clobber();
    AA[0] = AA[1];
    AA[1] = AA[2];
    AA[2] = AA[3];
    AA[3] = AA[4];
    AA[4] = AA[5];
    AA[5] = AA[6];
    AA[6] = AA[7];
    AA[7] = AA[8];
    AA[8] = AA[9];
}


#define N 10

int test_sum_iv(int rr[][N])
{
    chess_message("// test_sum_iv");
    escape_ptr = rr; clobber();

    int i, j, s = 0;

    i = 0;
    j = 0;
    for (int k = 0; k < N; k++, i++, j++) {
        s += rr[i][j];
    }
    chess_report(s);

    i = 0;
    j = N - 1;
    for (int k = 0; k < N; k++, i++, j--) {
        s += rr[i][j];
    }
    chess_report(s);

    i = N - 1;
    j = 0;
    for (int k = 0; k < N; k++, i--, j++) {
        s += rr[i][j];
    }
    chess_report(s);

    i = N - 1;
    j = N - 1;
    for (int k = 0; k < N; k++, i--, j--) {
        s += rr[i][j];
    }
    chess_report(s);
    return s;
}


// sum of iv depends on the order of the 2 BIVs
// switching order of first use (upto 05Q3 declaration) switches BIV order
int test_hetero_sum_iv_int_ptr(int jj, int* qq)
{
    chess_message("// test_hetero_sum_iv_int_ptr");
    UNKNOWN(jj); escape_ptr = qq; clobber();
    int xx = 0;
    int ii = jj + 4;
    int* pp = qq + 5;
    for (/**/; ii < 12; ii++, pp += jj) {
        xx += pp[ii];
    }
    return xx;
}

int test_hetero_sum_iv_ptr_int(int jj, int* qq)
{
    chess_message("// test_hetero_sum_iv_ptr_int");
    UNKNOWN(jj); escape_ptr = qq; clobber();
    int xx = 0;
    int* pp = qq + 5;
    int ii = jj + 4;
    for (/**/; ii < 12; ii++, pp += jj) {
        xx += pp[ii];
    }
    return xx;
}

static int IJ[N][N] = {
    {  0,  1,  2,  3,  4,  5 , 6,  7,  8,  9 },
    { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 },
    { 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 },
    { 30, 31, 32, 33, 34, 35, 36, 37, 38, 39 },
    { 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 },
    { 50, 51, 52, 53, 54, 55, 56, 57, 58, 59 },
    { 60, 61, 62, 63, 64, 65, 66, 67, 68, 69 },
    { 70, 71, 72, 73, 74, 75, 76, 77, 78, 79 },
    { 80, 81, 82, 83, 84, 85, 86, 87, 88, 89 },
    { 90, 91, 92, 93, 94, 95, 96, 97, 98, 99 }
};

int main()
{
    chess_report(AA[2]);
    test_chasing_ptr();
    chess_report(AA[2]);
    test_chain_building();
    chess_report(AA[2]);

    test_sum_iv(IJ);

    chess_report(test_hetero_sum_iv_int_ptr(3, &IJ[0][0]));
    chess_report(test_hetero_sum_iv_ptr_int(3, &IJ[0][0]));
    return 0;
}
