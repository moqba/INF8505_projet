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



#include "malloc.h"

struct S { int a; int b; int c; long d; };

int *pi, *pI;

long *pl, *pL;

S *ps, *pS;

void make()
{
   chess_message( "// make()" );

   pi = (int*)malloc(sizeof(int));
   pI = (int*)malloc(8*sizeof(int));

   pl = (long*)malloc(sizeof(long));
   pL = (long*)malloc(8*sizeof(long));

   ps = (S*)malloc(sizeof(S));
   pS = (S*)malloc(8*sizeof(S));
}
void fill()
{
   chess_message( "// fill()" );
   *pi = 0xabcd;
   *pl = 0x9876abcd;
   ps->a = -1;
   ps->d = -2;
}

void test()
{
   chess_message( "// test()" );
   chess_report(*pi);
   chess_report(*pl);
   chess_report(ps->a);
   chess_report(ps->d);
}

int main()
{
    make();
    fill();
    test();
    return 0;
}

