 /*
-- Test executing of reporting function.
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



#ifdef __chess__
inline assembly void asm_report() clobbers(R2,R3,R4)
{
    asm_begin
    asm_text
	ori r2, r0, #10 
	ori r3, r0, #20 
	nop
	nop
	nop
	add  r4,r2,r3
.chess_report __sint
	nop
	nop
	nop
    asm_end
}
#else
inline void asm_report() 
{
    chess_report (30);
}
#endif

int main()
{
    chess_message( "// First test message" );
    chess_report(101);
    asm_report();
    return 0;
}
