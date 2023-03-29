/*
-- Test: stdarg.h functions.
--
-- Copyright (c) 2014 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "stdlib.h"

const int N = 10;
int A[N] = { 10, -20, 100, -222, 3, 5, -9, 1234, 5678, -9999 };

int fcmp(const void* n1, const void* n2)
{
    return *(int*)n1 - *(int*)n2;
}
void test1()
{
    chess_message("// test1()");
    qsort(A, N, sizeof(int), fcmp);
    for (int i = 0; i < N; ++i) {
        chess_report(A[i]);
    }
}

struct S { int a, b; };
S B[N] = {
    {10,    1 },
    {-20,   2 },
    {100,   3 },
    {-222,  4 },
    {3,     5 },
    {5,     6 },
    {-9,    7 },
    {1234,  8 },
    {5678,  9 },
    {-9999, 10}
};

int Scmp(const void* s1, const void* s2)
{
    return ((S*)s1)->a - ((S*)s2)->a;
}
void test2()
{
    chess_message("// test2()");
    qsort(B, N, sizeof(S), Scmp);
    for (int i = 0; i < N; ++i) {
        chess_report(B[i].b);
    }
}

int main()
{
    test1();
    test2();
    return 0;
}
