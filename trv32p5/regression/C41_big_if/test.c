/*
-- Test Test long (> 128 and > 256) jumps.
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

int jump_less_128(int n, int m, int x)
{
    chess_message("// jump_less_128(" << n << ", " << m << ", " << x << ')');
    UNKNOWN(n); UNKNOWN(m); UNKNOWN(x);
    volatile int one = 1;
    if (n > 0) {
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
    } else {
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
    }
    return m ? x : -x;
}

int jump_more_128(int n, int m, int x)
{
    chess_message("// jump_more_128(" << n << ", " << m << ", " << x << ')');
    UNKNOWN(n); UNKNOWN(m); UNKNOWN(x);
    // note: use volatile instead of UNKNOWN(x) inside the look because
    // otherwise LLVM only factors out the offset (+1 or -1) and shares the
    // same code for the then- and else-block. And to calculate that offset it
    // only needs a short jump.
    volatile int one = 1;
    if (n > 0) {
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;

        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;

        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;

        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;

        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;

        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;

        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;

        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
        x += one; x &= 0xfff;
    } else {
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;

        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;

        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;

        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;

        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;

        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;

        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;

        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
        x -= one; x &= 0xfff;
    }
    return m ? x : -x;
}

int main()
{
    chess_report(jump_less_128(10, 1, 1000));
    chess_report(jump_less_128(-5, 1, 1000));
    chess_report(jump_more_128(10, 1, 1000));
    chess_report(jump_more_128(-5, 1, 1000));
    return 0;
}
