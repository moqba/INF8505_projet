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
inline assembly void test_j() clobbers()
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
	add r4,r4,r5
        add r4,r4,r6
	j #La
	add r4,r4,r7
	add r4,r4,r8
La: 	add r4,r4,r9
	add r4,r4,r10
.chess_report __sint
	nop
	nop
    asm_end
}
#else
inline void test_j()
{
    chess_message(" // test_j");
    chess_report (114);
}
#endif

#ifdef __chess__
inline assembly void test_jr() clobbers()
{
    asm_begin
      .direct_eval >>,&,(,),+
    asm_text
        ori r4, r0, #200
	lhi r13, #(Lb>>16)
	ori r13, r0, #(Lb&0xffff)
	nop
	ori r5, r0, #1
	ori r6, r0, #2
	ori r7, r0, #3
	ori r8, r0, #4
	ori r9, r0, #5
	ori r10, r0, #6
	add r4,r4,r5
        add r4,r4,r6
        add r4,r4,r7
	jr r13
	add r4,r4,r8
Lb: 	add r4,r4,r9
	add r4,r4,r10
.chess_report __sint
	nop
	nop
    asm_end
}
#else
inline void test_jr()
{
    chess_message(" // test_jr");
    chess_report (217);
}
#endif

int main()
{
    test_j();
    test_jr();
    return 0;
}
