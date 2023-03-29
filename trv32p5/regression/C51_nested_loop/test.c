/*
-- Test nested loops.
-- [based on "Doug's shootout" http://www.bagley.org/~doug]
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

#define N 4

int nested_loop(int n)
{
    chess_message("// nested_loop(" << n << ')');
    UNKNOWN(n); // to prevent constant propagation (and based on that loop unrolling)

    int x = 1000;

    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            for (int c = 0; c < n; c++) {
                for (int d = 0; d < n; d++) {
                    for (int e = 0; e < n; e++) {
                        for (int f = 0; f < n; f++) {
                            x += 1; UNKNOWN(x);
                        }
                        x += 2; UNKNOWN(x); // to prevent to compiler from collapsing everything into one loop with more iterations
                    }
                    x += 3; UNKNOWN(x);
                }
                x += 4; UNKNOWN(x);
            }
            x += 5; UNKNOWN(x);
        }
        x += 6; UNKNOWN(x);
    }
    return x;
}

int main()
{
    for (int n = 0; n <= N; n++) {
        chess_report(nested_loop(n));
    }
    return 0;
}
