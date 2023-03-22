/*
-- Test ackermann function (deep/non-primitive recursion).
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


#define M 2
#define N 3
//3,5 fails! - stack overflow?!


int ack(int m, int n) { return m ? ack(m-1, n ? ack(m,(n-1)) : 1) : n+1; }


int main()
{
    for (int m = 0; m <= M; m++)
        for (int n = 0; n <= N; n++) {
            chess_message( "// ack(" << m << ',' << n << ')' );
            chess_report( ack(m,n) );
        }

    return 0;
}
