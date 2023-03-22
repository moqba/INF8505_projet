/*
-- Test indirect function calls.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



#define N 7

static int bigi = 0;

int foo(int in)
{
    return in << 2;
}
int bar(int in)
{
    return in + 13;
}
int testFptr(int z, int (*fptr)(int))
{
    return foo(z) + fptr(z);
}


int (*gfptr)(int) = foo;
int testGptr(int z)
{
    return gfptr(z);
}


void big(int a, int b, int c, int d, int e, int f, int g, int h)
{
    bigi = a + b + c + e + d + f + g + h;
}
int testFbigptr(int a, int b, int c, int d, int e, int f, int g, int h,
                void (*fptr)(int, int, int, int, int, int, int, int))
{
    fptr(a, b, c, d, e, f, g, h);
    return bigi;
}


// test if there are sufficient pointer argument registers 
int foo2(int* a, int *b, int* c, int* d, int* e, int* f, int* g, int* h)
{
    return *a + *b + *c + *d + *e + *f + *g + *h;
}
int (*fptr2)(int*, int*, int*, int*, int*, int*, int*, int*) = foo2;
int testFptr2(int* p)
{
    return fptr2(p, p, p, p, p, p, p, p);
}


int main()
{
    chess_message("// testFptr foo");
    for (int n = 0; n < N; ++n)
        chess_report(testFptr(n, foo));

    chess_message("// testGptr foo");
    for (int n = 0; n < N; ++n)
        chess_report(testGptr(n));

    chess_message("// testGptr bar");
    gfptr = bar;
    for (int n = 0; n < N; ++n)
        chess_report(testGptr(n));

    chess_message("// testFbigptr big");
    chess_report(testFbigptr(1, 2, 3, 4, 5, 6, 7, 8, big));

    chess_message("// testFptr2 big");
    int v = 10;
    chess_report(testFptr2(&v));

    return 0;
}

