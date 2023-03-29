/*
-- Test reducing of if-stmts on manifest condition, with complications.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "regression.h"

int manifest_ret() // no warning, nor error
{
    chess_message("// manifest_ret");
    chess_report(10);
    if (true) return 10;
}

int following_ret() // syntax level warning!
{
    chess_message("// following_ret");
    chess_report(20); return 20;
    chess_report(29); return 29; // dead
}

int following_manifest_ret() // no warning!
{
    chess_message("// following_manifest_ret");
    if (true) { chess_report(30); return 30; }
    chess_report(39); return 39; // dead
}

int following_if_both_ret(int c) // syntax level warning!
{
    chess_message("// following_if_both_ret");
    UNKNOWN(c);
    if (c) { chess_report(41); return 41; }
    else   { chess_report(42); return 42; }
    chess_report(49); return 49; // dead
}

int following_if_manifest_ret(int c) // no warning!
{
    chess_message("// following_if_manifest_ret");
    if (c) { if (true) { chess_report(51); return 51; } }
    else   { chess_report(52); return 52; }
    chess_report(59); return 59; //dead
}

int do_ret(int c) // syntax level warning!
{
    chess_message("// do_ret");
    UNKNOWN(c);
    do {
        chess_report(60); return 60;
    } while (--c); // dead
    chess_report(69); return 69; // dead
}

int do_manifest_ret(int c) // optimiser warning!
{
    chess_message("// do_manifest_ret");
    UNKNOWN(c);
    do {
        if (true) { chess_report(70); return 70; }
    } while (--c); // dead
    chess_report(79); return 79; // dead
}

int while_ret(int c) // syntax level warning!
{
    chess_message("// while_ret");
    UNKNOWN(c);
    while (--c) { // while --> if
        chess_report(80); return 80;
    }
    chess_report(89); return 89; // NOT dead
}

int while_manifest_ret(int c) // optimiser warning!
{
    chess_message("// while_manifest_ret");
    UNKNOWN(c);
    while (--c) { // while --> if
        if (true) { chess_report(90); return 90; }
    }
    chess_report(99); return 99; // NOT dead
}


// involving labels

int broken_if(int c) // syntax level warning!
{
    chess_message("// broken_if");
    UNKNOWN(c);
    int xx;
    if (c) goto Lt; else goto Le;
    if (c) { // dead heading
Lt:    xx = 101;
    } else {
Le:    xx = 102;
    }
    chess_report(xx); return xx;
}

int manifest_broken_if(int c) // optimiser warning!
{
    chess_message("// manifest_broken_if");
    UNKNOWN(c);
    int xx;
    if (true) goto L;
    if (c) { // dead heading
L:    xx = 111;
    } else {
        xx = 119; // dead
    }
    chess_report(xx); return xx;
}


int main()
{
    chess_report(manifest_ret());                //  10
    chess_report(following_ret());               //  20
    chess_report(following_manifest_ret());      //  30
    chess_report(following_if_both_ret(1));      //  41
    chess_report(following_if_both_ret(0));      //  42
    chess_report(following_if_manifest_ret(1));  //  51
    chess_report(following_if_manifest_ret(0));  //  52

    chess_report(do_ret(1));                     //  60
    chess_report(do_ret(3));                     //  60
    chess_report(do_manifest_ret(1));            //  70
    chess_report(do_manifest_ret(3));            //  70
    chess_report(while_ret(1));                  //  89
    chess_report(while_ret(3));                  //  80
    chess_report(while_manifest_ret(1));         //  99
    chess_report(while_manifest_ret(3));         //  90

    chess_report(broken_if(1));                  // 101
    chess_report(broken_if(0));                  // 102
    chess_report(manifest_broken_if(1));         // 111
    chess_report(manifest_broken_if(0));         // 111
    return 0;
}
