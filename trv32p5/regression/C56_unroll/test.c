/*
-- Test: chess_unroll and chess_flatten pragmas
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

#define M 11
#define N 5

int test_chess_nounroll(int n)
{
    chess_message("// test_chess_nounroll(" << n << ')');
    UNKNOWN(n);
    int x = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < M; j++) { // no unroll
            x += j; UNKNOWN(x);
        }
    }
    return x;
}

int test_chess_unroll(int n)
{
    chess_message("// test_chess_unroll(" << n << ')');
    UNKNOWN(n);
    int x = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < M; j++) chess_unroll_loop(3) chess_unroll_loop_preamble { // preamble of M%3=2
            x += j; UNKNOWN(x);
        }
    }
    return x;
}

int test_chess_unroll_2(int n2)
{
    chess_message("// test_chess_unroll_2(" << n2 << ')');
    UNKNOWN(n2);
    int x = 0;
    for (int j = 0; j < n2; j++) chess_unroll_loop(2) { // no preamble - ! n%2
        x += j; UNKNOWN(x);
    }
    return x;
}

int test_chess_flatten(int n)
{
    chess_message("// test_chess_flatten(" << n << ')');
    UNKNOWN(n);
    int x = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < N; j++) chess_flatten_loop {
            x += j; UNKNOWN(x);
        }
    }
    return x;
}

int main()
{
    for (int n = 0; n <= N; n++) {
        chess_report(test_chess_nounroll(n));
        chess_report(test_chess_unroll(n));
        chess_report(test_chess_unroll_2(n * 2));
        chess_report(test_chess_flatten(n));
    }
    return 0;
}
