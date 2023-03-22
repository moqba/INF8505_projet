/*
-- Test switch statement transformations.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



int switch_tail_break(int k)
{
    chess_message( "// switch_tail_break(" << k << ')' );

    int z = 0;
    switch (k) {
    case 2 :
        z+=2;   break;
    case 3 :
        z+=3;   break;
    case 4 :
        z+=4;   break;
    default:
        z+=9;   break;
    }
    return z;
}


int switch_fall_through(int k)
{
    chess_message( "// switch_fall_through(" << k << ')' );

    int z = 0;
    switch (k) {
    case 2 :
        z+=2;
    case 3 :
        z+=3;
    case 4 :
        z+=4;
    default:
        z+=9;
    }
    return z;
}


int switch_mixed(int k)
{
    chess_message( "// switch_mixed(" << k << ')' );

    int z = 0;
    switch (k) {
    case 2 :
        z+=2;
    case 3 :
        z+=3;   break;
    case 4 :
        z+=4;
    default:
        z+=9;
    }
    return z;
}


int switch_if_break(int k, int c)
{
    chess_message( "// switch_if_break(" << k << ',' << c << ')' );

    int z = 0;
    switch (k) {
    case 2 :
        z+=2;   if (c) break;
    case 3 :
        z+=3;   break;
    case 4 :
        z+=4;
    default:
        z+=9;
    }
    z+=0;
    return z;
}


int switch_nested_if(int k, int c)
{
    chess_message( "// switch_nested_if(" << k << ',' << c << ')' );

    int z = 0;
    switch (k) {
    case 2 :
        z+=2;
        if (c) {
            z+=30;
        case 3 :
            z+=31;
        }
    case 4 :
        z+=4;
    default:
        z+=9;
    }
    return z;
}


int switch_nested_switch(int k, int l)
{
    chess_message( "// switch_nested_switch(" << k << ',' << l << ')' );

    int z = 0;
    switch (k) {
    case 2 :
        z+=4;
    case 4 :
        z+=4;
        switch (l) {
        case 1 : z += 100; break;
        case 2 : z += 200;
        case 3 : z += 300; break;
        default: z -= 1000;
        }
    default:
        z+=9;
    }
    return z;
}


int switch_default_not_last(int k)
{
    chess_message( "// switch_default_not_last(" << k << ')' );

    int z = 0;
    switch (k) {
    case 2 :
        z+=2;   break;
    case 3 :
        z+=3;   break;
    default:
        z+=9;   break;
    case 4 :
        z+=4;   break;
    }
    return z;
}


enum color { red, gold, green, paleturquoise };


int switch_color(color c, int k)
{
    chess_message( "// switch_color(" << (int)c << ',' << k << ')' );

    int x = 0;
    int y = 0;

    switch (c) {
    case red :
        x += 1;
    case gold :
        x += 2;
    case green :
        x += 3;
    default:
        x += 4;
    }
    chess_report(x);

    switch (c) {
    case gold :
        x += 10;
    default:
        x += 40;
    case green :
        x += 20;
    case red :
        x += 30;
    }
    chess_report(x);

    switch (c) {
    case red :
        x += 100; break;
    case gold :
        x += 200; break;
    default:
        x += 300;
    }
    chess_report(x);

    switch (c) {
    default:
        x += 1000; break;
    case green :
        x += 2000;
    }
    chess_report(x);

    switch (c) {
    case red :
        y += 1;
        if (k) break;
    case gold :
        y += 2;
        if (k) break;
    default:
        y += 3;
    }
    chess_report(y);

    switch (c) {
    default:
        y += 100;
        if (k) break;
    case gold :
        y += 200;
    }
    chess_report(y);

    return x + y;
}


int main()
{
    chess_report( switch_tail_break(0) );
    chess_report( switch_tail_break(3) );

    chess_report( switch_fall_through(0) );
    chess_report( switch_fall_through(3) );

    chess_report( switch_mixed(0) );
    chess_report( switch_mixed(2) );
    chess_report( switch_mixed(3) );
    chess_report( switch_mixed(4) );

    chess_report( switch_if_break(2,0) );
    chess_report( switch_if_break(2,1) );
    chess_report( switch_if_break(3,0) );
    chess_report( switch_if_break(3,1) );

    chess_report( switch_nested_if(2,0) );
    chess_report( switch_nested_if(2,1) );

    chess_report( switch_nested_switch(0,0) );
    chess_report( switch_nested_switch(2,1) );
    chess_report( switch_nested_switch(4,0) );
    chess_report( switch_nested_switch(4,1) );
    chess_report( switch_nested_switch(4,2) );
    chess_report( switch_nested_switch(4,3) );

    chess_report( switch_default_not_last(0) );
    chess_report( switch_default_not_last(2) );
    chess_report( switch_default_not_last(4) );

    chess_report( switch_color(red,0) );
    chess_report( switch_color(red,1) );
    chess_report( switch_color(gold,0) );
    chess_report( switch_color(gold,1) );
    chess_report( switch_color(green,0) );
    chess_report( switch_color(green,1) );
    chess_report( switch_color(paleturquoise,0) );
    chess_report( switch_color(paleturquoise,1) );

    return 0;
}
