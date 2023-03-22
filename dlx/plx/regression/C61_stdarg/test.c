/*
-- Test: stdarg.h functions.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#include "stdarg.h"

// Test aligned arguments
typedef int I;
void test1(I p0, I p1, I p2, I p3, I p4, I p5, I p6, I p7, I p8, ...)
{
  va_list select;

  va_start (select, p8);

  chess_report( va_arg(select,I) );
  chess_report( va_arg(select,I) );
  chess_report( va_arg(select,I) );

  va_end (select);
}

// Test unaligned arguments
typedef long long L;
void test2(chess_stack L p0, chess_stack L p1, chess_stack L p2, chess_stack L p4, ...)
{
  va_list select;

  va_start (select, p4);

  chess_report( va_arg(select,L) );
  chess_report( va_arg(select,I) );
  chess_report( va_arg(select,L) );

  va_end (select);
}

int main(void)
{
    test1(0L, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
    test2(1, 2, 3, 4, 5LL, 6, 7LL);
    return 0;
}
