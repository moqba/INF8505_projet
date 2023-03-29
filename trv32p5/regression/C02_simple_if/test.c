/*
-- Test conditional expressions (basic jump instructions).
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

static int g = 0;

NEVER_INLINE int helper() // not a pure function
{
    g += 3;
    return 4 * g;
}


int greater(int a, int b)
{
    UNKNOWN(a); UNKNOWN(b); // prevent constant-propagation
    return a > b ? a + b : 3 * a;
}

int smaller(int a, int b)
{
    UNKNOWN(a); UNKNOWN(b);
    return a <= b ? a & b : a | b;
}

int equal(int a, int b)
{
    UNKNOWN(a); UNKNOWN(b);
    return (a == b) ? 1 : 0; // can be implemented without jump on some ISAs
}

int not_equal(int a, int b)
{
    UNKNOWN(a); UNKNOWN(b);
    return (a != b) ? g++ : helper(); // branches have side effects, must use jump
}

int main()
{
    chess_report(greater(  11,  44));
    chess_report(greater(  55,  22));
    chess_report(smaller( 123, 456));
    chess_report(smaller(1024, 255));
    chess_report(equal    (3, 5));
    chess_report(equal    (3, 3));
    chess_report(not_equal(0, 3));
    chess_report(not_equal(0, 0));
    return 0;
}
