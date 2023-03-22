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
inline assembly void test_1() clobbers(R2,R3,R4)
{
    asm_begin
    asm_text
        ori r3, r0, #10
	ori r2, r0, #20
	nop
	nop
	add r4,r3,r2
	nop
	nop
	add r4,r4,r3
	nop
	nop
	add r4,r4,r3
	nop
	nop
	add r4,r4,r3
	nop
	nop
	add r4,r4,r3
.chess_report __sint
	nop
	nop
	nop
	sub r4,r2,r4
.chess_report __sint
	nop
	nop
    asm_end
}
#else
inline void test_1() 
{
    chess_message(" // test_1");
    chess_report (70);
    chess_report (-50);
}
#endif

#ifdef __chess__
inline assembly void test_2() clobbers(R2,R3,R4)
{
    asm_begin
    asm_text
        ori r3, r0, #10
	ori r2, r0, #20
	nop
	add r4,r3,r2
	nop
	add r4,r4,r3
	nop
	add r4,r4,r3
	nop
	add r4,r4,r3
	nop
	add r4,r4,r3
.chess_report __sint
	nop
	nop
	nop
	sub r4,r2,r4
.chess_report __sint
	nop
	nop
    asm_end
}
#else
inline void test_2() 
{
    chess_message(" // test_2");
    chess_report (70);
    chess_report (-50);
}
#endif

#ifdef __chess__
inline assembly void test_3() clobbers(R2,R3,R4)
{
    asm_begin
    asm_text
        ori r3, r0, #10
	ori r2, r0, #20
	add r4,r3,r2
	add r4,r4,r3
	add r4,r4,r3
	add r4,r4,r3
	add r4,r4,r3
.chess_report __sint
	sub r4,r2,r4
.chess_report __sint
	nop
	nop
	nop
    asm_end
}
#else
inline void test_3() 
{
    chess_message(" // test_3");
    chess_report (70);
    chess_report (-50);
}
#endif

int main()
{
    test_1();
    test_2();
    test_3();
    return 0;
}
