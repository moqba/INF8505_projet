/*
-- Test argument passing via registers and via the stack.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

//skip one arg (s|t|u) to create a difference


int int26(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j,
          int k, int l, int m, int n, int o, int p, int q, int r, int s, int t,
          int u, int v, int w, int x, int y, int z )
{
    return a+b+c+d+e+f+g+h+i+j+
           k+l+m+n+o+p+q+r/*+s*/+t+
           u+v+w+x+y+z;
}

void test_int26()
{
    chess_message( "// test_int26" );
    chess_report( int26( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                     10,11,12,13,14,15,16,17,18,19,
                     20,21,22,23,24,25) );
}

long long long26(long long a, long long b, long long chess_stack c, long long chess_stack d,
long long chess_stack e, long long f)
{
    return a+b+c+e+f;
}

void test_long26()
{
    chess_message( "// test_long26" );
    chess_report( long26( 10,11,12,13,14,15) );
}

int ptr26(int* a, int* b, int* c, int* d, int* e, int* f, int* g, int* h,
          int* i, int* j, int* k, int* l, int* m, int* n, int* o, int* p,
          int* q, int* r, int* s, int* t, int* u, int* v, int* w, int* x,
          int* y, int* z )
{
    return *a+*b+*c+*d+*e+*f+*g+*h+*i+*j+*k+*l+*m+*n+*o+*p+*q+*r+*s+*t
        /*+*u*/+*v+*w+*x+*y+*z;
}

void test_ptr26()
{
    chess_message( "// test_ptr26" );
    static int A[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                       10,11,12,13,14,15,16,17,18,19,
                       20,21,22,23,24,25 };

    chess_report( ptr26( A+0, A+1, A+2, A+3, A+4, A+5, A+6, A+7, A+8, A+9,
                      A+10,A+11,A+12,A+13,A+14,A+15,A+16,A+17,A+18,A+19,
                      A+20,A+21,A+22,A+23,A+24,A+25) );
}

long long mixed(long long a, long long b,
           int* i, int* j, int* k, int* l, int* m, int* n, int* o, int* p,
           int* q, int* r, int* s, int* t, int* u, int* v, int* w, int* x,
           int* y, int* z,
           long long c, long long d, long long e)
{
    return a+*i+*p+*u+*z+d+e;
}


void test_mixed()
{
    chess_message( "// test_mixed" );
    int A[1024];                        // large stack frame

    A[100] = 100;
    A[200] = 200;
    A[300] = 300;
    A[400] = 400;
    A[500] = 500;
    A[600] = 600;
    A[700] = 700;
    A[800] = 800;
    A[900] = 900;
    A[800] = 800;
    A[1000] = 1000;

    chess_report( mixed(0, 1,
                     A+100,A+200,A+300,A+400,A+500,A+600,A+700,A+800,
                     A+100,A+200,A+300,A+400,A+500,A+600,A+700,A+800,
                     A+900,A+1000,
                     2, 3, 4) );
}


int main()
{
    test_int26();
    test_long26();
    test_ptr26();
    test_mixed();

    return 0;
}

