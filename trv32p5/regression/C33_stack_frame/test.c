/*
-- Test stack frame layout: build area, spill area, locals area, arguments area
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

void* escape_ptr;

NEVER_INLINE int bar(long a, long b, long c, long d, long e)
{
    return a + b + c + d + e;
}

NEVER_INLINE int foo(long a, long b, long c, long d, long e)
{
    chess_message("// foo");
    long AA[5];
    escape_ptr = AA; // to prevent SROA from optimizing away AA[]
    AA[0] = a;
    AA[1] = b;
    AA[2] = c;
    AA[3] = d;
    AA[4] = e;
    clobber();
    int xx = (int)a * (int)b; // to be spilled
    chess_report(bar(AA[0], AA[1], AA[2], AA[3], AA[4]));
    AA[0] += a;               // force AA to be changed
    clobber();
    xx += (int)c * (int)d;    // spill in - compute - spill out
    clobber();
    chess_report(bar(AA[4], AA[3], AA[2], AA[1], AA[0]));
    return xx;
}


const int N = 257;

int large_foo(long a, long b, long c, long d, long e)
{
    chess_message("// large_foo");
    long AA[N];
    escape_ptr = AA; // prevent SROA
    AA[    0] = a;
    AA[    1] = b;
    AA[N - 3] = c;
    AA[N - 2] = d;
    AA[N - 1] = e;
    clobber();
    int xx = (int)a * (int)b; // to be spilled
    chess_report(bar(AA[0], AA[1], AA[N - 3], AA[N - 2], AA[N - 1]));
    AA[0] += a;               // force AA to be changed
    clobber();
    xx += (int)c * (int)d;    // spill in - compute - spill out
    clobber();
    chess_report(bar(AA[N - 1], AA[N - 2], AA[N - 3], AA[1], AA[0]));
    return xx;
}


int main()
{
    chess_report(      foo( 2,  3,  4,  5,  6));
    chess_report(      foo(12, 13, 14, 15, 16));
    chess_report(large_foo( 6,  7,  8,  9, 10));
    chess_report(large_foo(16, 17, 18, 19, 20));
    return 0;
}
