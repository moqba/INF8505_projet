/*
-- Test algebraic optimisations.
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

int reassoc(int i)
{
    chess_message("// reassoc(" << i << ')');
    UNKNOWN(i);
    int r = 0;                           //              (i=1000)

    r += 101 + (112 + i);                //   213 + i #1 '1213
    chess_report(r);
    r += 123 + (i + 134);                //   257 + i #2 '2470
    chess_report(r);
    r += 145 + (156 - i);                //   301 - i #1 '1771
    chess_report(r);
    r += 167 + (i - 178);                //   -11 + i #2 '2760
    chess_report(r);

    r += (211 + i) + 222;                //   433 + i #3 '4193
    chess_report(r);
    r += (i + 233) + 244;                //   477 + i #4 '5670
    chess_report(r);
    r += (255 - i) + 266;                //   521 - i #3 '5191
    chess_report(r);
    r += (i - 277) + 288;                //    11 + i #4 '6202
    chess_report(r);

    r += 301 - (310 + i);                //    -9 - i #3 '5193
    chess_report(r);
    r += 302 - (i + 320);                //   -18 - i #2 '4175
    chess_report(r);
    r += 303 - (330 - i);                //   -27 + i #3 '5148
    chess_report(r);
    r += 304 - (i - 340);                //   644 - i #2 '4792
    chess_report(r);

    r += (491 + i) - 440;                //    51 + i #3 '5843
    chess_report(r);
    r += (i + 492) - 450;                //    42 + i #4 '6885
    chess_report(r);
    r += (493 - i) - 460;                //    33 - i #3 '5918
    chess_report(r);
    r += (i - 494) - 470;                //  -964 + i #4 '5954
    chess_report(r);
    // -------------
    //  1954 * 4*i
    return r;
}

int redistrib(int i)
{
    chess_message("// redistrib(" << i << ')');
    UNKNOWN(i);
    int r = 0;                           //            (i=10)

    r += (i + 10 * i);                   //  11 * i =  110  '110
    chess_report(r);
    r += (i + i * 20);                   //  21 * i =  210  '320
    chess_report(r);
    r += (30 * i + i);                   //  31 * i =  310  '630
    chess_report(r);
    r += (i * 40 + i);                   //  41 * i =  410  '1040
    chess_report(r);
    r += (i - 50 * i);                   // -49 * i = -490  '550
    chess_report(r);
    r += (i - i * 60);                   // -59 * i = -590  '-40
    chess_report(r);
    r += (70 * i - i);                   //  69 * i =  690  '650
    chess_report(r);
    r += (i * 80 - i);                   //  79 * i =  790  '1440
    chess_report(r);
    // -------------
    //  180 * i
    return r;
}

int rewrite1(int i, int j)
{
    chess_message("// rewrite1(" << i << ", " << j << ')');
    UNKNOWN(i); UNKNOWN(j);

    static int A[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

    int r = 0;
    r += A[i][j] + 10 * i + 5 * j - 20;
    chess_report(r);
    r += A[i][j] + 2 * i + 5 * j + 3 * i + 5 * i + j - 22;
    chess_report(r);
    r += A[i][j] + 2 * (i + j) + 3 * (j - i) + 11 * i - 20;
    chess_report(r);
    return r;
}

int rewrite2(int i, int j)
{
    chess_message("// rewrite2(" << i << ", " << j << ')');
    UNKNOWN(i); UNKNOWN(j);

    static int A[2][2][2] = { { {1, 2}, {3, 4} }, { {5, 6}, {7, 8} } };

    int r = 0;
    r += A[i][i][i];
    chess_report(r);
    r += A[i][i][j];
    chess_report(r);
    r += A[i][j][i];
    chess_report(r);
    r += A[i][j][j];
    chess_report(r);
    r += A[j][i][i];
    chess_report(r);
    r += A[j][i][j];
    chess_report(r);
    r += A[j][j][i];
    chess_report(r);
    r += A[j][j][j];
    chess_report(r);
    return r;
}


struct S { int a, b, c, d, e; };

int rewrite3(int i, int j)
{
    chess_message("// rewrite3(" << i << ", " << j << ')');
    UNKNOWN(i); UNKNOWN(j);

    static S A[2][2] = { { {  1,  2,  3,  4,  5 },
        { 11, 12, 13, 14, 15 } },
             { { 21, 22, 23, 24, 25 },
                 { 31, 32, 33, 34, 35 } } };
    int r = 0;
    r += A[i][i].b;
    chess_report(r);
    r += A[i][j].c;
    chess_report(r);
    r += A[j][i].d;
    chess_report(r);
    r += A[j][j].e;
    chess_report(r);
    return r;
}


int main()
{
    chess_report(reassoc(1000));
    chess_report(redistrib(10));

    chess_report(rewrite1(0, 0));
    chess_report(rewrite1(1, 2));
    chess_report(rewrite1(2, 0));

    chess_report(rewrite2(0, 0));
    chess_report(rewrite2(0, 1));
    chess_report(rewrite2(1, 0));
    chess_report(rewrite2(1, 1));

    chess_report(rewrite3(0, 0));
    chess_report(rewrite3(0, 1));
    chess_report(rewrite3(1, 0));
    chess_report(rewrite3(1, 1));
    return 0;
}
