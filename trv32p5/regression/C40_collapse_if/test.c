/*
-- Test collapsing of successive if-stmts on same condition.
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

NEVER_INLINE int my_add(int a, int b) { return a + b; }
NEVER_INLINE int my_sub(int a, int b) { return a - b; }

int collapse_1(int a, int b)
{
    chess_message("// collapse_1(" << a << ", " << b << ')');
    UNKNOWN(a); UNKNOWN(b);
    int x = 100;
    if (a < b) x += a; else x -= a;
    if (a < b) x += b; else x -= b;
    chess_report(x);
    return x;
}

int collapse_2(int a, int b)
{
    chess_message("// collapse_2(" << a << ", " << b << ')');
    UNKNOWN(a); UNKNOWN(b);
    int x = 100;
    if (a < b) x = my_add(x, a); else x = my_sub(x, a);
    if (a < b) x = my_add(x, b); else x = my_sub(x, b);
    chess_report(x);
    return x;
}

int collapse_3(int a, int b)
{
    chess_message("// collapse_3(" << a << ", " << b << ')');
    UNKNOWN(a); UNKNOWN(b);
    int x = 100;
    int y = 1000;
    if (a < b) { x += a; y += b; } else { x -= a;     y -= b; }
    if (a < b) { x += x;         } else { x -= a + b;         }
    chess_report(x + y);
    return x;
}

int collapse_4(int a, int b)
{
    chess_message("// collapse_4(" << a << ", " << b << ')');
    UNKNOWN(a); UNKNOWN(b);
    int x = 100;
    int y = 1000;
    if (a < b) { x += a; y += b; }
    if (a < b) { x += x;         }
    chess_report(x + y);
    return x;
}

int collapse_5(int a, int b)
{
    chess_message("// collapse_5(" << a << ", " << b << ')');
    UNKNOWN(a); UNKNOWN(b);
    int x = 100;
    int y = 1000;
    if (a < b) { x += a;     y += b;    }
    if (a < b) { x += x;                }
    if (a < b) { x -= a & b; y &= 0xaa; }
    chess_report(x + y);
    return x;
}

int main()
{
    chess_report(collapse_1( 2, 9));
    chess_report(collapse_1(11, 9));

    chess_report(collapse_2(2,  9));
    chess_report(collapse_2(2, -9));

    chess_report(collapse_3( 2, 9));
    chess_report(collapse_3(11, 9));

    chess_report(collapse_4( 2, 9));
    chess_report(collapse_4(11, 9));

    chess_report(collapse_5(3, 5));
    chess_report(collapse_5(5, 3));
    return 0;
}
