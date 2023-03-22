/*
-- Test of PM load/store instructions.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/


// These #defines must be set externally (via always include or -D command line arguments)
// For instance when int is a 16-bit type on the ASIP:
//
// #define PROGRAM_MEMORY  PM

int chess_storage(PROGRAM_MEMORY) A[] = { 10, 20, 30, -11 };

int A1()       { return A[1]; }
int A1a()      { return A[1] + 59; }
int A1b(int b) { return A[1] + b; }
int A2()       { return A[2]; }

int A12()      { return A[1] + A[2]; }
int A0123()    { return A[0] + A[1] + A[2] + A[3]; }

int sum_A()
{
    int sum = 0;
    for (int i = 0; i < sizeof(A) / sizeof(int); ++i)
        sum += A[i];
    return sum;
}

int sum_Aa()
{
    int sum = 0;
    int N = sizeof(A) / sizeof(int);
    for (int i = 0; i < N; i += 2)
        sum += A[i] + A[i + 1];
    return sum;
}

void update_A2(int a)         { A[2] = a;      }
void update_A2a(int a)        { A[2] = a + 33; }
void update_A2b(int a, int b) { A[2] = a + b;  }

void increment_A(int a)
{
    for (int i = 0; i < sizeof(A) / sizeof(int); ++i)
        A[i] += a;
}

int increment_Ab(int a)
{
    int sum = 0;
    for (int i = 0; i < sizeof(A) / sizeof(int); ++i) {
        A[i] += a;
        sum += A[i];
    }
    return sum;
}

int increment_Ac(int a)
{
    int sum = 0;
    for (int i = 0; i < sizeof(A) / sizeof(int); i += 2) {
        A[i] += a;
        sum += A[i] + A[i + 1];
    }
    return sum;
}

int increment_Ad(int a)
{
    int sum = 0;
    for (int i = 0; i < sizeof(A) / sizeof(int); i += 2) {
        sum += A[i] + A[i + 1];
        A[i + 1] += a;
    }
    return sum;
}


int main()
{
    chess_report(A1());
    chess_report(A1a());
    chess_report(A1b(41));

    chess_report(A12());
    chess_report(A0123());

    chess_report(sum_A());
    chess_report(sum_Aa());

    update_A2(123);
    chess_report(A2());

    update_A2a(123);
    chess_report(A2());

    update_A2b(123, 67);
    chess_report(A2());

    increment_A(-3);
    chess_report(sum_A());

    chess_report(increment_Ab(-3));
    chess_report(sum_A());

    chess_report(increment_Ac(-3));
    chess_report(sum_A());

    chess_report(increment_Ad(-3));
    chess_report(sum_A());

    return 0;
}
