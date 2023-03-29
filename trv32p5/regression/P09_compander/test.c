/*
-- Benchmark: mimic code with switch statements
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

int foo(int r, int a)
{
    return r + a * 1000;
}

int state;

int compander(int a)
{
    chess_message("// compander(" << a << ")  state = " << state);
    UNKNOWN(a);

    int value = 0;
    switch (state) {
        case 1:
            state = 6;
            break;

        case 2:
            if ((a & 3) == 1) {
                value = foo(value, 1);
            } else {
                if ((a & 3) == 2) {
                    value = foo(value, 2);
                } else {
                    if ((a & 3) == 3) {
                        value = foo(value, 3);
                    } else {
                        value = foo(value, 4);
                    }
                }
            }
            state = 7;
            break;

        case 3:
            state = 8;
            break;

        case 4:
            state = 9;
            break;

        case 5:
            state = 10;
            break;

        case 6:
            state = 2;
            break;

        case 7:
            if ((a & 3) == 1) {
                value = foo(value, 5);
            } else {
                if ((a & 3) == 2) {
                    value = foo(value, 6);
                } else {
                    if ((a & 3) == 3) {
                        value = foo(value, 7);
                    } else {
                        value = foo(value, 8);
                    }
                }
            }
            state = 3;
            break;

        case 8:
            state = 4;
            break;

        case 9:
            state = 5;
            break;

        case 10:
            state = 1;
            break;
    }

    value += state;
    chess_report(value);
    return value;
}

int main()
{
    state = 1;
    int a = 1;
    for (int i = 0; i < 100; ++i) {
        compander(a++);
    }
    return 0;
}
