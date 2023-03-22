/*
-- Test fibonacci function (deep/recurrent recursion).
-- [based on "Doug's shootout" http://www.bagley.org/~doug]
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#define N 10


int fib(int n) { return n < 2 ? 1 : fib(n-2) + fib(n-1); }


int main()
{
    for (int n = 0; n <= N; n++) {
        chess_message( "// fib(" << n << ')' );
        chess_report( fib(n) );
    }

    return 0;
}
