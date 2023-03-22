/*
-- Test jump instructions at the end of a hardware loop.
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifdef __chess__
inline assembly void test_cl_doi() clobbers_not(LR)
{
    asm_begin
    asm_text
        ori r4, r0, #40
        ori r5, r0, #1
        ori r6, r0, #2
        ori r7, r0, #3
        // loop of size 2 with count of 3
        doi 3,La
        ori r8, r0, #4  // delay slot 0
        ori r9, r15, #0 // delay slot 1      // save PR
        ori r10, r0, #Fa
        jalr r10
        add r4,r4,r6
        nop
.eol
La:     nop
.chess_report __sint    // 52
        ori r10, r0, #Done
        jr r10
        add r4,r4,r7
        nop

Fa:     add r4,r4,r5
.chess_report __sint    // 43, 47, 51
        jr r15          // r15=lr
        add r4,r4,r5
        nop
        add r4,r4,r5

Done:   nop
        ori r15, r9, #0        // restore LR
        nop
    asm_end
}
#else
inline void test_cl_doi()
{
        chess_message( "// test_cl_doi()" );
        chess_report(43);
        chess_report(47);
        chess_report(51);
        chess_report(52);
}
#endif

int main()
{
    test_cl_doi();
    return 0;
}
