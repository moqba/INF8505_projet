/*
-- Copyright (c) 2014 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include <stdlib.h>

struct S { int a, b, c; long d; };
int  *pi, *pI;
long *pl, *pL;
S    *ps, *pS;

void allocate()
{
    chess_message("// allocate()");
    pi = (int*) malloc(    sizeof(int) );
    pI = (int*) malloc(8 * sizeof(int) );
    pl = (long*)malloc(    sizeof(long));
    pL = (long*)malloc(8 * sizeof(long));
    ps = (S*)   malloc(    sizeof(S)   );
    pS = (S*)   malloc(8 * sizeof(S)   );

    chess_report(pi != 0);
    chess_report(pI != 0);
    chess_report(pl != 0);
    chess_report(pL != 0);
    chess_report(ps != 0);
    chess_report(pS != 0);

    chess_report((void*)pi != (void*)pI);
    chess_report((void*)pi != (void*)pl);
    chess_report((void*)pi != (void*)pL);
    chess_report((void*)pi != (void*)ps);
    chess_report((void*)pi != (void*)pS);

    chess_report((void*)pI != (void*)pl);
    chess_report((void*)pI != (void*)pL);
    chess_report((void*)pI != (void*)ps);
    chess_report((void*)pI != (void*)pS);

    chess_report((void*)pl != (void*)pL);
    chess_report((void*)pl != (void*)ps);
    chess_report((void*)pl != (void*)pS);

    chess_report((void*)pL != (void*)ps);
    chess_report((void*)pL != (void*)pS);

    chess_report((void*)ps != (void*)pS);
}

void fill()
{
    chess_message("// fill()");
    *pi = 0xabcd;
    *pl = 0x9876abcd;
    ps->a = -1;
    ps->d = -2;

    pI[0] = 10;
    pI[7] = 17;

    pL[0] = 100;
    pL[7] = 107;

    pS[0].a = 200;
    pS[0].d = 0xaaaabbbb;
    pS[7].a = 300;
    pS[7].d = 0xccccdddd;
}

void test()
{
    chess_message("// test()");
    chess_report(*pi);
    chess_report(*pl);
    chess_report(ps->a);
    chess_report(ps->d);

    chess_report(pI[0]);
    chess_report(pI[7]);

    chess_report(pL[0]);
    chess_report(pL[7]);

    chess_report(pS[0].a);
    chess_report(pS[0].d);
    chess_report(pS[7].a);
    chess_report(pS[7].d);
}

void deallocate()
{
    chess_message("// deallocate()");

    free(pl);
    free(pI);
    free(ps);
    free(pL);
    free(pi);
    free(pS);
}

int main()
{
    allocate();
    fill();
    test();
    deallocate();
    return 0;
}
