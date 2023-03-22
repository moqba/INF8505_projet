/*
-- Test hardware loop instructions.
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#ifdef __chess__
inline assembly void test_doi() clobbers_not(LR)
{
    asm_begin
    asm_text
        ori r4, r0, #10
        ori r5, r0, #1
        ori r6, r0, #2
        // loop of size 3 with count of 3
        doi 3,La
        ori r7, r0, #3  // delay slot 0
        ori r8, r0, #4  // delay slot 1
        add r4,r4,r5
        add r4,r4,r6
.chess_report __sint    // 13, 16, 19
        nop             // avoid .chess_report breakpoint on .eol
.eol
La:     nop
        // loop of size 1 with count of 3
        doi 3,Lb
        add r4,r4,r8    // delay slot 0
        nop             // delay slot 1
.eol
Lb:     add r4,r4,r5
.chess_report __sint    // 26
        // loop of size 1 with count of 1
        doi 1,Lc
        add r4,r4,r8    // delay slot 0
        nop             // delay slot 1
.eol
Lc:     add r4,r4,r5
.chess_report __sint    // 31
        add r4,r4,r8
.chess_report __sint    // 35
        nop
    asm_end
}
#else
inline void test_doi()
{
        chess_message( "// test_doi()" );
        chess_report(13);
        chess_report(16);
        chess_report(19);
        chess_report(26);
        chess_report(31);
        chess_report(35);
}
#endif

#ifdef __chess__
inline assembly void test_do() clobbers_not(LR)
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
        do r9,La
        nop             // delay slot 0
        add r4,r4,r5    // delay slot 1
        add r4,r4,r6
.chess_report __sint    // 13, 15, 17
        nop             // avoid .chess_report breakpoint on .eol
.eol
La:     nop
        // loop of size 1 with count of 3
        do r9,Lb
        add r4,r4,r8    // delay slot 0
        add r4,r4,r7    // delay slot 1
.eol
Lb:     add r4,r4,r5
.chess_report __sint    // 27
        ori r9, r0, #1
        // loop of size 1 with count of 1
        do r9,Lc
        nop             // delay slot 0
        add r4,r4,r7    // delay slot 1
.eol
Lc:     add r4,r4,r5
.chess_report __sint    // 31
        add r4,r4,r8
.chess_report __sint    // 35
        nop
    asm_end
}
#else
inline void test_do()
{
        chess_message( "// test_do()" );
        chess_report(13);
        chess_report(15);
        chess_report(17);
        chess_report(27);
        chess_report(31);
        chess_report(35);
}
#endif

#ifdef __chess__
inline assembly void test_nested_doi() clobbers_not(LR)
{
    asm_begin
    asm_text
        ori r4, r0, #10
        ori r5, r0, #1
        ori r6, r0, #2
        // outer loop with count of 3
        doi 3,Laa
        ori r7, r0, #3  // delay slot 0
        ori r8, r0, #4  // delay slot 1
        // inner loop with count of 1
        doi 2,Lab
        add r4,r4,r5    // delay slot 0
        nop             // delay slot 1
        add r4,r4,r5
        add r4,r4,r6
.chess_report __sint    // 14,17, 25,28, 36,39
        nop             // avoid .chess_report breakpoint on .eol
.eol
Lab:    nop
        add r4,r4,r8
.chess_report __sint    // 21, 32, 43
        nop             // avoid .chess_report breakpoint on .eol
.eol
Laa:    nop
        // outer loop with count of 1
        doi 1,Lba
        add r4,r4,r8    // delay slot 0
        ori r4, r0, #100// delay slot 1
        // inner loop with count of 1
        doi 1,Lbb
        nop
        nop
.eol
Lbb:    add r4,r4,r8
.eol
Lba:    add r4,r4,r5
.chess_report __sint    // 105
        add r4,r4,r8
.chess_report __sint    // 109
        nop
    asm_end
}
#else
inline void test_nested_doi()
{
        chess_message( "// test_nested_doi()" );
        chess_report(14);
        chess_report(17);
        chess_report(21);
        chess_report(25);
        chess_report(28);
        chess_report(32);
        chess_report(36);
        chess_report(39);
        chess_report(43);
        chess_report(105);
        chess_report(109);
}
#endif

#ifdef __chess__
inline assembly void test_nested_do() clobbers_not(LR)
{
    asm_begin
    asm_text
        ori r4, r0, #10
        ori r5, r0, #1
        ori r6, r0, #2
        ori r7, r0, #3
        ori r8, r0, #4
        ori r9, r0, #2
        // outer loop with count of 2
        do r9,Laa
        ori r10, r0, #3 // delay slot 0
        add r4,r4,r5    // delay slot 1
        // inner loop with count of 3
        do r10,Lab
        nop             // delay slot 0
        add r4,r4,r5    // delay slot 1
        add r4,r4,r6
.chess_report __sint    // 14,16,18 25,27,29
        nop             // avoid .chess_report breakpoint on .eol
.eol
Lab:    nop
        add r4,r4,r8
.chess_report __sint    // 22, 33
        nop             // avoid .chess_report breakpoint on .eol
.eol
Laa:    nop
        add r4,r4,r8
.chess_report __sint    // 37
        ori r9, r0, #1
        ori r10, r0, #1
        // outer loop with count of 1
        do r9,Lba
        ori r4, r0, #100 // delay slot 0
        add r4,r4,r8     // delay slot 1
        // inner loop with count of 1
        do r10,Lbb
        nop
        add r4,r4,r8    // delay slot
.eol
Lbb:    add r4,r4,r5
.eol
Lba:    add r4,r4,r5
.chess_report __sint    // 110
        add r4,r4,r8
.chess_report __sint    // 114
        nop
    asm_end
}
#else
inline void test_nested_do()
{
        chess_message( "// test_nested_do()" );
        chess_report(14);
        chess_report(16);
        chess_report(18);
        chess_report(22);
        chess_report(25);
        chess_report(27);
        chess_report(29);
        chess_report(33);
        chess_report(37);
        chess_report(110);
        chess_report(114);
}
#endif

int main()
{
    test_doi();
    test_do();
    test_nested_doi();
    test_nested_do();
    return 0;
}

