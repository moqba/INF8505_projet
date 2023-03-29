/*
-- Test simple loop with constant or variable count.
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

int do_100(int in)
{
    chess_message("// do_100(" << in << ')');
    for (int i = 0; i < 100; ++i) { // enough iterations to prevent full unroll
        UNKNOWN(in); // to prebent the compiler from turning this loop into a multiplication
        in += 3;
    }
    return in;
}

int do_n(int n)
{
    UNKNOWN(n); // unknown #iterations to prevent unroll
    chess_message("// do_n(" << n << ')');
    int in = 10;
    for (int i = 0; i < n; ++i) {
        UNKNOWN(in);
        in += 10;
    }
    return in;
}

int do_x(int in, int x)
{
    chess_message("// do_x(" << in << ')');
    for (int i = 0; i < 100; ++i) { // enough iterations
        UNKNOWN(in); UNKNOWN(x);
        in += (x + 3);
    }
    return in;
}

int main()
{
    int x = 0;
    for (int n = 0; n < 5; ++n) { // ok to unroll (or not)
        UNKNOWN(x);
        chess_report(x += do_100(n));
    }

    chess_report(do_n(  4));
    chess_report(do_n(  8));
    chess_report(do_n(255));
    chess_report(do_n(260));
    chess_report(do_n(  0));

    chess_report(do_x(100, 5));
    return 0;
}
