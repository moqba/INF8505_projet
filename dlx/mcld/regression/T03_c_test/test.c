/*
-- Copyright (c) 2014-2021 Synopsys Inc.
*/

// Test for multicycle load


int A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
int B[16];

int foo(vint_t* p)
{
    return vsum(*p);   // RAW dependency
}

int main()
{
    vint_t* pvA = (vint_t*)A;
    vint_t* pvB = (vint_t*)B;
    int a = vsum(pvA[0]) + vsum(pvA[1]) + vsum(pvA[2]);
    chess_report(a);
    vint_t v1 = *(vint_t*)(A+1); // unaligned vector load
    vint_t v2 = *(vint_t*)(A+2); // unaligned vector load
    vint_t v3 = *(vint_t*)(A+3); // unaligned vector load
    pvB[0] = v1;
    pvB[1] = v2;
    pvB[2] = v3;
    int b = vsum(pvB[0]) + vsum(pvB[1]) + vsum(pvB[2]);
    chess_report(b);
    return 0;
}


