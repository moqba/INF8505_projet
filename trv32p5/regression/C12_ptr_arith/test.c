/*
-- Test: pointer arithmetic
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
#include <stdint.h>

struct SS {
    int a[3];
} ss[4];

void ptr_difference(SS* p, SS* q)
{
    chess_message("// ptr_difference");
    UNKNOWN(p); UNKNOWN(q);
    int t = (intptr_t)q - (intptr_t)p; // 2 * sizeof(SS)
    chess_report((int)(t / (int)sizeof(SS)));
    chess_report((int)(q - p)); // 2
}

void ptr_comparison(SS* p, SS* q)
{
    chess_message("// ptr_comparison");
    UNKNOWN(p); UNKNOWN(q);
    chess_report(p <  q ? 10 : 11);
    chess_report(p >  q ? 20 : 21);
    chess_report(p <= q ? 30 : 31);
    chess_report(p >= q ? 40 : 41);
    chess_report(p != q ? 50 : 51);
    chess_report(p == q ? 60 : 61);
}

int main()
{
    SS* p1 = &ss[1];
    SS* p3 = &ss[3];

    ptr_difference(p1, p3);
    ptr_difference(p3, p1);
    ptr_difference(p1, p1);

    ptr_comparison(p1, p3);
    ptr_comparison(p3, p1);
    ptr_comparison(p1, p1);

    return 0;
}
