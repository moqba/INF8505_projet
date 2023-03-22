/*
-- Test hardware zloop instructions.
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include "flx_define.h"

#if defined(__chess__) && defined(FLX_HAS_ZLOOP)
inline assembly void test_zlp1() clobbers_not(LR)
{
    asm_begin
    asm_text
        ori r4, r0, #10
        ori r5, r0, #1
        ori r6, r0, #2
        ori r7, r0, #3
        ori r8, r0, #4
        ori r9, r0, #3
        // loop of size 3 with count of 3
        mv zc, r9
.rela 0 Ls1 0
        mv zs, 0
.rela 0 Le1 0
        mv ze, 0
        add r4,r4,r5    // not in loop
.begin_of_loop
Ls1:
        add r4,r4,r6
.chess_report __sint    // 13, 15, 17
        nop             // avoid .chess_report breakpoint on .eol
.end_of_loop
Le1:    nop
        // loop of size 1 with count of 3
.rela 0 Lse2 0
        mv zs, 0
.rela 0 Lse2 0
        mv ze, 0
        mv zc, r9
        add r4,r4,r8    // not in loop
        add r4,r4,r7    // not in loop
.begin_of_loop
.end_of_loop
Lse2:   add r4,r4,r5    // loop
.chess_report __sint    // 27
        ori r9, r0, #1
        // loop of size 1 with count of 1
.rela 0 Lse3 0
        mv zs, 0
.rela 0 Lse3 0
        mv ze, 0
        mv zc, r9
        nop             //
        add r4,r4,r7    //
.begin_of_loop
.end_of_loop
Lse3:   add r4,r4,r5
.chess_report __sint    // 31
        add r4,r4,r8
.chess_report __sint    // 35
        nop
    asm_end
}
#else
inline void test_zlp1()
{
        chess_message( "// test_zlp1()" );
        chess_report(13);
        chess_report(15);
        chess_report(17);
        chess_report(27);
        chess_report(31);
        chess_report(35);
}
#endif


int main()
{
    test_zlp1();
    return 0;
}
