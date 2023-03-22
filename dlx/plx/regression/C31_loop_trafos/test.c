/*
-- Test loop statement transformations.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



// test for initialisation of __fb variable
int while_fb(int c)
{
    chess_message( "// while_fb(" << c << ')' );

    int x = 0;
    int cc;
    cc = c;
    while (cc--)
        x += 1;
    chess_report(x);

    cc = c;
    while (cc) {
        x += 10;
        cc = cc - 1;
    }
    chess_report(x);

    cc = c;
    while (cc > 0) {
        x += 100;
        cc = cc - 1;
    }
    chess_report(x);

    return x;
}


// do-while and while-do loops with either a break or a continue stmt
int while_brk_cnt(int c, int k)
{
    chess_message( "// while_brk_cnt(" << c << ',' << k << ')' );

    int x = 0;
    int y = 0;
    int cc;

    cc = c;
    do {
        x++;
        y++;
    } while (cc--);
    chess_report(x+y);

    cc = c;
    while (cc--) {
        x++;
        y++;
    }
    chess_report(x+y);

    cc = c;
    do {
        x++;
        if (k) break;
        y++;
    } while (cc--);
    chess_report(x+y);

    cc = c;
    while (cc--) {
        x++;
        if (k) break;
        y++;
    }
    chess_report(x+y);

    cc = c;
    do {
        x++;
        if (k) continue;
        y++;
    } while (cc--);
    chess_report(x+y);

    cc = c;
    while (cc--) {
        x++;
        if (k) continue;
        y++;
    }
    chess_report(x+y);

    return x + y;
}


// for loops with either a break or a continue stmt
int for_brk_cnt(int c, int k)
{
    chess_message( "// for_brk_cnt(" << c << ',' << k << ')' );

    int x = 0;
    int y = 0;

    for (int j=0; j < c; j++)
    {
        x++;
        y++;
    }
    chess_report(x+y);

    for (int j=0; j < c; j++)
    {
        x++;
        if (k) break;
        y++;
    }
    chess_report(x+y);

    for (int j=0; j < c; j++)
    {
        x++;
        if (k) continue;
        y++;
    }
    chess_report(x+y);

    return x + y;
}


// do-while loop with both a break and a continue stmt
int while_brk_cnt_2(int c, int k, int l)
{
    chess_message( "// while_brk_cnt_2(" << c << ',' << k <<',' << l << ')' );

    int x = 0;

    do {
        x += 1;
        if (k) break;
        x += 10;
        if (l) continue;
        x += 100;
    } while (c--);
    chess_report(x);

    return x;
}


// for loop with nested break and continue
int for_nested_1(int c, int k)
{
    chess_message( "// for_nested_1(" << c << ',' << k << ')' );

    int x = 0;

    for (int j=0; j < c; j++) {
        x += 1;
        if (j==3) {
            x += 10;
            if (k) continue;
            x += 100;
        }
        else
            x += 1000;
    }
    chess_report(x);

    return x;
}


// for loop with nested break and continue
int for_nested_2(int c, int k)
{
    chess_message( "// for_nested_2(" << c << ',' << k << ')' );

    int x = 0;
    int y = 0;

    for (int i=0; i < c; i++) {
        x += 1;
        for (int j=i; j < c; j++) {
            y += 1;
            if (k) { y += 1000; break; }
            y += 10;
        }
    }
    chess_report(x);
    chess_report(y);

    return x;
}


int main()
{
    while_fb(4);
    while_fb(5);

    while_brk_cnt(5,0);
    while_brk_cnt(5,1);
    while_brk_cnt(6,0);
    while_brk_cnt(6,1);
    while_brk_cnt(1,0);
    while_brk_cnt(1,1);
    while_brk_cnt(0,0);
    while_brk_cnt(0,1);

    for_brk_cnt(5,0);
    for_brk_cnt(5,1);
    for_brk_cnt(6,0);
    for_brk_cnt(6,1);
    for_brk_cnt(1,0);
    for_brk_cnt(1,1);
    for_brk_cnt(0,0);
    for_brk_cnt(0,1);

    while_brk_cnt_2(4,0,0);
    while_brk_cnt_2(4,0,1);
    while_brk_cnt_2(4,1,0);
    while_brk_cnt_2(4,1,1);

    for_nested_1(7,0);
    for_nested_1(8,0);
    for_nested_1(7,1);
    for_nested_1(8,1);

    for_nested_2(3,0);
    for_nested_2(3,1);

    return 0;
}
