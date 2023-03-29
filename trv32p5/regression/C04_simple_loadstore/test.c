/*
-- Test load/stores of byte/short/int/long/longlong
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

#define INT_SVAL(A) INT_SE(INT_##A)
#define INT_UVAL(A) INT_ZE(INT_##A)

int A[] = {
    0, 1, -1, 4, 10, -25, -122, 53,
    INT_SVAL(XCDEF), -INT_SVAL(XCDEF),
    INT_SVAL(X3210), -INT_SVAL(X3210),
    INT_SVAL(X0AAA), -INT_SVAL(X0AAA),
    INT_SVAL(X7FFF), -INT_SVAL(X7FFF),
    INT_SVAL(X8000),  INT_SVAL(X7FFF) - 1,
    INT_SVAL(XFFFF),  INT_SVAL(XFFFF - 1)
};

int T_int[32];

int main()
{
    int N = sizeof(A) / sizeof(int);

    chess_message("// load int");
    for (int i = 0; i < N; ++i) {
        chess_report(A[i]);
    }

    chess_message("// store int (and load back)");
    clobber();
    for (int i = 0; i < N; ++i) {
        T_int[i] = A[i];
    }
    clobber();

    for (int i = 0; i < N; ++i) {
        chess_report(T_int[i]);
    }
    return 0;
}
