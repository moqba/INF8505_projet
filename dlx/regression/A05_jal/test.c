/*
-- Test executing of straight line code.
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



#ifdef __chess__
inline assembly void test_jal()
{
    asm_begin
    asm_text
        ori r4, r0, #100
	ori r5, r0, #1
	ori r6, r0, #2
	ori r7, r0, #3
	ori r8, r0, #4
	add r4,r4,r5
	jal #Fa
	add r4,r4,r6
	add r4,r4,r7
.chess_report __sint
	nop
	j #Da
	nop
	nop
Fa: 	add r4,r4,r8
.chess_report __sint
	nop
.rts
        jr r15
	add r4,r4,r5
	nop
Da:
	lhi r15, #0    // clear LR
	nop
    asm_end
}
#else
inline void test_jal() 
{
    chess_message(" // test_jal");
    chess_report (107);
    chess_report (111);
}
#endif

#ifdef __chess__
inline assembly void test_jalr()
{
    asm_begin
      .direct_eval >>,&,(,),+
    asm_text
        ori r4, r0, #200
	lhi r13, #(La>>16)
	ori r13, r0, #(La & 0xffff)
	nop
	ori r5, r0, #1
	ori r6, r0, #2
	ori r7, r0, #3
	ori r8, r0, #4
	ori r9, r0, #5
	ori r10, r0, #6
	add r4,r4,r5
	jalr r13
	add r4,r4,r6
	add r4,r4,r7
	add r4,r4,r8
.chess_report __sint
	nop
	j #Db
        nop
La: 	add r4,r4,r9
	add r4,r4,r10
.chess_report __sint
	nop
.rts
        jr r15
	nop
	nop
Db:
	nop
	lhi r15, #0    // clear LR
    asm_end
}
#else
inline void test_jalr() 
{
    chess_message(" // test_jalr");
    chess_report (217);
    chess_report (221);
}
#endif

int main()
{
    test_jal();
    test_jalr();
    return 0;
}
