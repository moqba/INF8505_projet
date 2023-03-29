/*
-- Benchmark: Factorial function (single recursion)
-- [based on real code]
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

#define N 7

#ifndef DISABLE_RECURSION
// recursive version
NEVER_INLINE int fac_rec(int n)
{
    if (n == 0) return 1;
    int result = n * fac_rec(n - 1);
    UNKNOWN(result); // prevent LLVM from turning this recursive version into an iterative version
    return result;
}
#endif

// iterative version
NEVER_INLINE int fac_it(int n)
{
    int f = 1;
    for (int k = 1; k <= n; ++k) {
        f *= k;
    }
    return f;
}

int main()
{
    for (int n = 0; n <= N; ++n) {
        chess_message("// fac(" << n << ')');
#ifndef DISABLE_RECURSION
        chess_report(fac_rec(n));
#endif
        chess_report(fac_it (n));
    }
    return 0;
}
