/*
   -- Test: stdarg.h functions.
   --
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


// These #defines must be set externally (via always include or -D command line arguments)
//
// #define HAS_CHAR
// #define HAS_SHORT
// #define HAS_INT
// #define HAS_LONG
// #define HAS_LONG_LONG

#include "stdarg.h"

void test_int(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, ...)
{
    chess_message("// test_int");
    va_list select;
    va_start(select, p8);

    chess_report(va_arg(select, int));
    chess_report(va_arg(select, int));
    chess_report(va_arg(select, int));

    va_end(select);
}

#ifdef HAS_CHAR
void test_char(chess_stack char p0, chess_stack char p1, chess_stack char p2, ...)
{
    chess_message("// test2");
    va_list select;
    va_start(select, p2);

    chess_report(va_arg(select, int));
    chess_report(va_arg(select, int));
    chess_report(va_arg(select, int));

    va_end(select);
}
#endif

#ifdef HAS_SHORT
void test_short(chess_stack short p0, chess_stack short p1, chess_stack short p2, ...)
{
    chess_message("// test_short");
    va_list select;
    va_start(select, p2);

    chess_report(va_arg(select, int));
    chess_report(va_arg(select, int));
    chess_report(va_arg(select, int));

    va_end(select);
}
#endif

#ifdef HAS_LONG
void test_long(chess_stack long p0, chess_stack long p1, chess_stack long p2, ...)
{
    chess_message("// test_long");
    va_list select;
    va_start(select, p2);

    chess_report(va_arg(select, long));
    chess_report(va_arg(select, int ));
    chess_report(va_arg(select, long));

    va_end(select);
}
#endif

#ifdef HAS_LONG_LONG
void test_llong(chess_stack long long p0, chess_stack long long p1, chess_stack long long p2, ...)
{
    chess_message("// test_llong");
    va_list select;
    va_start(select, p2);

    chess_report(va_arg(select, long long));
    chess_report(va_arg(select, int ));
    chess_report(va_arg(select, long long));

    va_end(select);
}
#endif

int main()
{
    test_int  (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
    test_char (1, 2, 3, 5  , 6, 7  );
    test_short(1, 2, 3, 5  , 6, 7  );
    test_long (1, 2, 3, 5L , 6, 7L );
#ifdef HAS_LONG_LONG
    test_llong(1, 2, 3, 5LL, 6, 7LL);
#endif
    return 0;
}
