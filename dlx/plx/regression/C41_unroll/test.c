/*
-- Test chess_unroll and chess_flatten pragmas.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#define M 11
#define N 5


int test_chess_unroll(int n)
{
    chess_message( "// test_chess_unroll(" << n << ')' );

    int x=0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < M; j++) chess_unroll_loop(3) chess_unroll_loop_preamble // preamble of M%3=2
            x += j;
    return x;
}

int test_chess_unroll_2(int n2)
{
    chess_message( "// test_chess_unroll_2(" << n2 << ')' );

    int x=0;
    for (int j = 0; j < n2; j++) chess_unroll_loop(2)  // no preamble - ! n%2
            x += j;
    return x;
}


int test_chess_flatten(int n)
{
    chess_message( "// test_chess_flatten(" << n << ')' );

    int x=0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < N; j++) chess_flatten_loop
            x += j;
    return x;
}

int A[] = { 0, 55, 110, 165, 220, 275 };

int main()
{
    for (int n = 0; n <= N; n++) {
#if defined(Debug)
        // Preamble generation for M%3=2 is not supported in Debug mode.
        chess_report( A[n] );
#else
        chess_report( test_chess_unroll(n) );
#endif
        chess_report( test_chess_unroll_2(n*2) );
        chess_report( test_chess_flatten(n) );
    }

    return 0;
}
