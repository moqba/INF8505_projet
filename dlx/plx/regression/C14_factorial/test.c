/*
-- Test factorial function (single recursion).
-- [based on real code]
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#define N 7


int fac(int n)
{
    if (n == 0) return 1;
    return n * fac(n-1);
}


int main()
{
    for (int n = 0; n <= N; n++) {
        chess_message( "// fac(" << n << ')' );
        chess_report( fac(n) );
    }

    return 0;
}
