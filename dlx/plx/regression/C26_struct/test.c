/*
-- Test structs.
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


struct dlb_int { int a, b; };


inline int add(dlb_int d)       // add struct members with inline function
{
    return d.a + d.b;
}


struct qint { int a, b, c, d; };


int add(qint q)                 // add struct members with called function
{
    return q.a + q.b + q.c + q.d;
}


struct U1 {
    int  i;
    dlb_int d;
    qint q;
};


void set_i(U1& u) { u.i = 10; }


void set_d(U1& u)
{
                   chess_separator() ;
    u.d.a = 166;   chess_separator() ;
    u.d.b = -66;   chess_separator() ;
}

void set_q(U1& u)
{
                    chess_separator() ;
    u.q.a = 1000;   chess_separator() ;
    u.q.b = 2020;   chess_separator() ;
    u.q.c = 3003;   chess_separator() ;
    u.q.d = 9000;   chess_separator() ;
}

int add(U1& u)
{
    int r = 0;     chess_separator();
    r += u.i;      chess_separator();
    r += u.d.a;    chess_separator();
    r += u.d.b;    chess_separator();
    r += u.q.a;    chess_separator();
    r += u.q.b;    chess_separator();
    r += u.q.c;    chess_separator();
    r += u.q.d;    chess_separator();
    return r;
}


int add(U1* u)
{
    int r = 0;     chess_separator();
    r += u->i;      chess_separator();
    r += u->d.a;    chess_separator();
    r += u->d.b;    chess_separator();
    r += u->q.a;    chess_separator();
    r += u->q.b;    chess_separator();
    r += u->q.c;    chess_separator();
    r += u->q.d;    chess_separator();
    return r;
}



void test_U1()
{
    chess_message( "// test_U1" );

    static U1 u;

    set_i(u);
    set_d(u);
    set_q(u);
    chess_report( add(u) );
    chess_report( add(u.d) );
    chess_report( add(u.q) );
    chess_report( add(&u) );

    U1 v;

    set_i(v);
    set_d(v);
    set_q(v);
    chess_report( add(v) );
    chess_report( add(v.d) );
    chess_report( add(v.q) );
    chess_report( add(&v) );
}


//-----------------------------------------------------------------------------


union U2 {
    dlb_int d;
    int  i;
};

U2 uu = { 11, 22 };

U2 UU[4] = { { 1, 6 }, { 11, 16 }, { 101, 606 }, { 1111, 6666 } };


int sum(U2& u) { return u.d.a + u.d.b + u.i; }


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

    U2 vv;
    vv.d.a = UU[1].d.a;
    vv.d.b = UU[1].d.b;
    vv.i = -101;
    chess_report( sum(vv) );
    chess_report( add(vv.d) );

    U2 VV[2];
    VV[0].d.a = UU[1].d.a;
    VV[0].d.b = UU[1].d.b;
    VV[0].i = 444;
    VV[1].d.a = UU[3].d.a;
    VV[1].d.b = UU[3].d.b;
    VV[1].i = -555;
    chess_report( sum(VV[0]) );
    chess_report( sum(VV[1]) );
    chess_report( add(VV[0].d) );
    chess_report( add(VV[1].d) );
}


//-----------------------------------------------------------------------------


int main()
{
    test_U1();
    test_U2();

    return 0;
}
