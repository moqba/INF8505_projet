/*
-- Test chess mem copy.
--
-- Copyright (c) 2016-2021 Synopsys, Inc. This Synopsys processor model
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


struct A01 { char a,b,c,d; };
int sum(A01& a) { return a.a+a.b+a.c+a.d; }
A01 a01 = { 1 };

struct A02 { char a,b,c,d; };
int sum(A02& a) { return a.a+a.b+a.c+a.d; }
A02 a02 = { 1,2 };

struct A03 { char a,b,c,d; };
int sum(A03& a) { return a.a+a.b+a.c+a.d; }
A03 a03 = { 1,2,3 };

struct A04 { char a,b,c,d; };
int sum(A04& a) { return a.a+a.b+a.c+a.d; }
A04 a04 = { 1,2,3,4 };

struct A05 { char a,b,c,d,e; };
int sum(A05& a) { return a.a+a.b+a.c+a.d+a.e; }
A05 a05 = { 1,2,3,4,5 };

struct A06 { char a,b,c,d,e,f; };
int sum(A06& a) { return a.a+a.b+a.c+a.d+a.e+a.f; }
A06 a06 = { 1,2,3,4,5,6 };

struct A07 { char a,b,c,d,e,f,g; };
int sum(A07& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g; }
A07 a07 = { 1,2,3,4,5,6,7 };

struct A08 { char a,b,c,d,e,f,g,h; };
int sum(A08& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h; }
A08 a08 = { 1,2,3,4,5,6,7,8 };

struct A09 { char a,b,c,d,e,f,g,h,i; };
int sum(A09& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i; }
A09 a09 = { 1,2,3,4,5,6,7,8,9 };

struct A10 { char a,b,c,d,e,f,g,h,i,j; };
int sum(A10& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j; }
A10 a10 = { 1,2,3,4,5,6,7,8,9,10 };

struct A11 { char a,b,c,d,e,f,g,h,i,j,k; };
int sum(A11& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k; }
A11 a11 = { 1,2,3,4,5,6,7,8,9,10,11 };

struct A12 { char a,b,c,d,e,f,g,h,i,j,k,l; };
int sum(A12& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l; ; }
A12 a12 = { 1,2,3,4,5,6,7,8,9,10,11,12 };

struct A13 { char a,b,c,d,e,f,g,h,i,j,k,l,m; };
int sum(A13& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m; }
A13 a13 = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };

struct A14 { char a,b,c,d,e,f,g,h,i,j,k,l,m,n; };
int sum(A14& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m+a.n; }
A14 a14 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14 };

struct A15 { char a,b,c,d,e,f,g,h,i,j,k,l,m,n,o; };
int sum(A15& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m+a.n+a.o; }
A15 a15 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

struct A16 { char a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p; };
int sum(A16& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m+a.n+a.o+a.p; }
A16 a16 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

struct A17 { char a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q; };
int sum(A17& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m+a.n+a.o+a.p+a.q; }
A17 a17 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17 };

struct A18 { char a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r; };
int sum(A18& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m+a.n+a.o+a.p+a.q+a.r; }
A18 a18 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };

struct A19 { char a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s; };
int sum(A19& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m+a.n+a.o+a.p+a.q+a.r+a.s; }
A19 a19 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };

struct A20 { char a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t; };
int sum(A20& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m+a.n+a.o+a.p+a.q+a.r+a.s+a.t; }
A20 a20 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };

struct A21 { char a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u; };
int sum(A21& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m+a.n+a.o+a.p+a.q+a.r+a.s+a.t+a.u; }
A21 a21 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 };

struct A22 { char a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v; };
int sum(A22& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m+a.n+a.o+a.p+a.q+a.r+a.s+a.t+a.u+a.v; }
A22 a22 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22 };

struct A23 { char a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w; };
int sum(A23& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m+a.n+a.o+a.p+a.q+a.r+a.s+a.t+a.u+a.v+a.w; }
A23 a23 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };

struct A24 { char a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x; };
int sum(A24& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m+a.n+a.o+a.p+a.q+a.r+a.s+a.t+a.u+a.v+a.w+a.x; }
A24 a24 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };

struct A25 { char a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y; };
int sum(A25& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m+a.n+a.o+a.p+a.q+a.r+a.s+a.t+a.u+a.v+a.w+a.x+a.y; }
A25 a25 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25 };

struct A26 { char a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z; };
int sum(A26& a) { return a.a+a.b+a.c+a.d+a.e+a.f+a.g+a.h+a.i+a.j+a.k+a.l+a.m+a.n+a.o+a.p+a.q+a.r+a.s+a.t+a.u+a.v+a.w+a.x+a.y+a.z; }
A26 a26 = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26 };

void test_01() { A01 x = a01; chess_report(sum(x)); }
void test_02() { A02 x = a02; chess_report(sum(x)); }
void test_03() { A03 x = a03; chess_report(sum(x)); }
void test_04() { A04 x = a04; chess_report(sum(x)); }
void test_05() { A05 x = a05; chess_report(sum(x)); }
void test_06() { A06 x = a06; chess_report(sum(x)); }
void test_07() { A07 x = a07; chess_report(sum(x)); }
void test_08() { A08 x = a08; chess_report(sum(x)); }
void test_09() { A09 x = a09; chess_report(sum(x)); }
void test_10() { A10 x = a10; chess_report(sum(x)); }
void test_11() { A11 x = a11; chess_report(sum(x)); }
void test_12() { A12 x = a12; chess_report(sum(x)); }
void test_13() { A13 x = a13; chess_report(sum(x)); }
void test_14() { A14 x = a14; chess_report(sum(x)); }
void test_15() { A15 x = a15; chess_report(sum(x)); }
void test_16() { A16 x = a16; chess_report(sum(x)); }
void test_17() { A17 x = a17; chess_report(sum(x)); }
void test_18() { A18 x = a18; chess_report(sum(x)); }
void test_19() { A19 x = a19; chess_report(sum(x)); }
void test_20() { A20 x = a20; chess_report(sum(x)); }
void test_21() { A21 x = a21; chess_report(sum(x)); }
void test_22() { A22 x = a22; chess_report(sum(x)); }
void test_23() { A23 x = a23; chess_report(sum(x)); }
void test_24() { A24 x = a24; chess_report(sum(x)); }
void test_25() { A25 x = a25; chess_report(sum(x)); }
void test_26() { A26 x = a26; chess_report(sum(x)); }

int main()
{
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    test_07();
    test_08();
    test_09();
    test_10();
    test_11();
    test_12();
    test_13();
    test_14();
    test_15();
    test_16();
    test_17();
    test_18();
    test_19();
    test_20();
    test_21();
    test_22();
    test_23();
    test_24();
    test_25();
    test_26();

    return 0;
}
