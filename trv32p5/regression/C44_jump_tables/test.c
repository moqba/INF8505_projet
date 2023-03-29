/*
-- Test switch statement transformations.
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

int switch_closed_annotated(int k, int a, int b, int c)
{
    chess_message("// switch_closed_annotated(" << k << ')');
    UNKNOWN(k); UNKNOWN(a); UNKNOWN(b); UNKNOWN(c);
    int z = 0;
    switch (k) chess_closed_jump_table {
        case 0:  z += a + b + c + 2; break;
        case 1:  z += c - b + a - 3; break;
        case 3:  z += a - c + b + 4; break;
        case 2:  z += c - a - b - 5; break;
        case 4:  z += 2 * c - b + 6; break;
        default: z += 9;             break;
    }
    return z;
}

int switch_closed_auto(int k, int a, int b, int c)
{
    chess_message("// switch_closed_auto(" << k << ')');
    UNKNOWN(k); UNKNOWN(a); UNKNOWN(b); UNKNOWN(c);
    int z = 0;
    switch (k) {
        case 0:  z += a + b + c + 12; break;
        case 1:  z += c - b + a - 13; break;
        case 3:  z += a - c + b + 14; break;
        case 2:  z += c - a - b - 15; break;
        case 4:  z += 2 * c - b + 16; break;
        default: z += 19;             break;
    }
    return z;
}

int switch_open_annotated(int k, int a, int b, int c)
{
    chess_message( "// switch_open_annotated(" << k << ')' );
    UNKNOWN(k); UNKNOWN(a); UNKNOWN(b); UNKNOWN(c);
    int z = 0;
    switch (k) chess_open_jump_table {
        case 0:  z += a + b + c + 2; break;
        case 1:  z += c - b + a - 3; break;
        case 3:  z += a - c + b + 4; break;
        case 2:  z += c - a - b - 5; break;
        case 4:  z += 2 * c - b + 6; break;
        default: z += 3 * b + a + 9; break;
    }
    return z;
}

int switch_open_auto(int k, int a, int b, int c)
{
    chess_message( "// switch_open_auto(" << k << ')' );
    UNKNOWN(k); UNKNOWN(a); UNKNOWN(b); UNKNOWN(c);
    int z = 0;
    switch (k)  {
        case 0:  z += a + b + c + 12; break;
        case 1:  z += c - b + a - 13; break;
        case 3:  z += a - c + b + 14; break;
        case 2:  z += c - a - b - 15; break;
        case 4:  z += 2 * c - b + 16; break;
        default: z += 3 * b + a + 19; break;
    }
    return z;
}

int main()
{
    chess_report(switch_closed_annotated(0, 10, 20, 30));
    chess_report(switch_closed_annotated(1, 10, 20, 30));
    chess_report(switch_closed_annotated(2, 10, 20, 30));
    chess_report(switch_closed_annotated(3, 10, 20, 30));
    chess_report(switch_closed_annotated(4, 10, 20, 30));

    chess_report(switch_closed_auto     (0, 10, 20, 30));
    chess_report(switch_closed_auto     (1, 10, 20, 30));
    chess_report(switch_closed_auto     (2, 10, 20, 30));
    chess_report(switch_closed_auto     (3, 10, 20, 30));
    chess_report(switch_closed_auto     (4, 10, 20, 30));

    chess_report(switch_open_annotated  (0, 10, 20, 30));
    chess_report(switch_open_annotated  (1, 10, 20, 30));
    chess_report(switch_open_annotated  (2, 10, 20, 30));
    chess_report(switch_open_annotated  (3, 10, 20, 30));
    chess_report(switch_open_annotated  (4, 10, 20, 30));
    chess_report(switch_open_annotated  (7, 10, 20, 30));

    chess_report(switch_open_auto       (0, 10, 20, 30));
    chess_report(switch_open_auto       (1, 10, 20, 30));
    chess_report(switch_open_auto       (2, 10, 20, 30));
    chess_report(switch_open_auto       (3, 10, 20, 30));
    chess_report(switch_open_auto       (4, 10, 20, 30));
    chess_report(switch_open_auto       (7, 10, 20, 30));
    return 0;
}
