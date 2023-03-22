/*
-- Test executing of straight line code.
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifdef __chess__
inline assembly void test_br_taken()
{
    asm_begin
    asm_text
        ori r4, r0, #100
	ori r5, r0, #1
	ori r6, r0, #2
	ori r7, r0, #3
	ori r8, r0, #4
	ori r9, r0, #5
	ori r10, r0, #6
        nop
	add r4,r4,r5
	seq r13, r0, r0
        add r4,r4,r6
        add r4,r4,r7
	bnez r13, #La
	add r4,r4,r8
La: 	add r4,r4,r9
	add r4,r4,r10
.chess_report __sint
	nop
	nop
    asm_end
}
#else
inline void test_br_taken()
{
    chess_message(" // test_br_taken");
    chess_report (117);
}
#endif

#ifdef __chess__
inline assembly void test_br_untaken()
{
    asm_begin
    asm_text
        ori r4, r0, #200
	ori r5, r0, #1
	ori r6, r0, #2
	ori r7, r0, #3
	ori r8, r0, #4
	ori r9, r0, #5
	ori r10, r0, #6
        nop
	add r4,r4,r5
	sne r13, r0, r0
        add r4,r4,r6
        add r4,r4,r7
	bnez r13, #Lb
	add r4,r4,r8
Lb: 	add r4,r4,r9
	add r4,r4,r10
.chess_report __sint
	nop
	nop
    asm_end
}
#else
inline void test_br_untaken()
{
    chess_message(" // test_br_untaken");
    chess_report (221);
}
#endif

int main()
{
    test_br_taken();
    test_br_untaken();
    return 0;
}
