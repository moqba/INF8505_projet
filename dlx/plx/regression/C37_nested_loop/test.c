/*
-- Test nested loops.
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


#define N 4


int nested_loop(int n)
{
    chess_message( "// nested_loop(" << n << ')' );

    int a, b, c, d, e, f, x=1000;

    for (a = 0; a < n; a++)
        for (b = 0; b < n; b++)
            for (c = 0; c < n; c++)
                for (d = 0; d < n; d++)
                    for (e = 0; e < n; e++)
                        for (f = 0; f < n; f++)
                            x++;
    return x;
}


int main()
{
    for (int n = 0; n <= N; n++)
        chess_report( nested_loop(n) );

    return 0;
}
