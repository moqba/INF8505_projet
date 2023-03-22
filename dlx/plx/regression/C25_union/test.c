/*
-- Test unions.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



//-----------------------------------------------------------------------------


struct dbl_int { int a, b; };

struct qint { int a, b, c, d; };


union U1 {
    int  i;
    dbl_int d;
    qint q;
};


void set_i(U1& u) { u.i = 10; }


int add_i(U1& u) { return u.i; }


void set_d(U1& u)
{
                   chess_separator() ;
    u.d.a = 166;   chess_separator() ;
    u.d.b = -66;   chess_separator() ;
}


int add_d(U1& u)
{
    int r = 0;     chess_separator();
    r += u.d.a;    chess_separator();
    r += u.d.b;    chess_separator();
    return r;
}


void set_q(U1& u)
{
                   chess_separator() ;
    u.q.a = 100;   chess_separator() ;
    u.q.b = 200;   chess_separator() ;
    u.q.c = 300;   chess_separator() ;
    u.q.d = 400;   chess_separator() ;
}


int add_q(U1& u)
{
    int r = 0;     chess_separator();
    r += u.q.a;    chess_separator();
    r += u.q.b;    chess_separator();
    r += u.q.c;    chess_separator();
    r += u.q.d;    chess_separator();
    return r;
}


void test_U1()
{
    chess_message( "// test_U1" );

    U1 u;

    set_i(u);                   // u = [    10,    0,    0,    0 ]
    chess_report( add_i(u) );   // --> 10

    set_d(u);                   // u = [   166,  -66,    0,    0 ]
    chess_report( add_d(u) );   // --> 100

    set_q(u);                   // u = [   100,  200,  300,  400 ]
    chess_report( add_q(u) );   // --> 1000

    set_i(u);                   // u = [    10,  200,  300,  400 ]
    chess_report( add_q(u) );   // --> 910
}


//-----------------------------------------------------------------------------


union U2 {
    dbl_int d;
    int  i;
};


U2 uu = { 11, 22 };


U2 UU[4] = { { 1, 6 }, { 11, 16 }, { 101, 606 }, { 1111, 6666 } };


int sum(U2& u) { return u.d.a + u.d.b; }


int sum(U2 U[4])
{
    int r = 0;
    for (int i = 0; i < 4; i++)
        r += sum(U[i]);
    return r;
}


void test_U2()
{
    chess_message( "// test_U2" );

    chess_report( sum(uu) );
    chess_report( sum(UU) );
}


//-----------------------------------------------------------------------------


int main()
{
    test_U1();
    test_U2();

    return 0;
}
