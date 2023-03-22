/*
-- Copyright (c) 2014 Synopsys Inc.
*/


#define ADDR_A 0x10000
int chess_storage(DMb:ADDR_A) A[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

#ifdef __chess__
inline assembly void test_lw_indep1() clobbers()
{
    asm_begin
        .direct_eval >>,&,(,),+
    asm_text
        nop
        nop
        lhi r6, #(ADDR_A>>16)
        ori r6,r6,#(ADDR_A&0xffff)
        nop
        nop
        lw r4,12(r6)
.chess_report __sint
        nop
        ori r5, r0, #123
        sw r5,12(r6)
        lw r4,12(r6)
.chess_report __sint
        nop
        ori r5, r0, #555
        ori r4, r5, #0
.chess_report __sint
        nop
        nop
    asm_end
}
#else
inline void test_lw_indep1() 
{
    chess_report (4);
    chess_report (123);
    chess_report (555);
}
#endif

#ifdef __chess__
inline assembly void test_lw_indep2() clobbers()
{
    asm_begin
        .direct_eval >>,&,(,),+
    asm_text
        nop
        nop
        lhi r6, #(ADDR_A>>16)
        ori r6,r6,#(ADDR_A&0xffff)
        nop
        nop
        lw r4,16(r6)
.chess_report __sint
        nop
        ori r5, r0, #222
        sw r5,16(r6)
        lw r4,16(r6)
.chess_report __sint
        ori r5, r0, #444
        ori r4, r5, #0
.chess_report __sint
        nop
        nop
        nop
        nop
    asm_end
}
#else
inline void test_lw_indep2() 
{
    chess_report (5);
    chess_report (222);
    chess_report (444);
}
#endif

#ifdef __chess__
inline assembly void test_lw_dep1() clobbers()
{
    asm_begin
        .direct_eval >>,&,(,),+
    asm_text
        nop
        nop
        lhi r6, #(ADDR_A>>16)
        ori r6,r6,#(ADDR_A&0xffff)
        nop
        nop
        lw r4,20(r6)
.chess_report __sint
        nop
        ori r5, r0, #123
        sw r5,20(r6)
        lw r4,20(r6)
.chess_report __sint
        nop
        addi r4,r4,#10    // dependency on lw (no hw_stall)
.chess_report __sint
        nop
        nop
    asm_end
}
#else
inline void test_lw_dep1() 
{
    chess_report (6);
    chess_report (123);
    chess_report (133);
}
#endif

#ifdef __chess__
inline assembly void test_lw_dep2() clobbers()
{
    asm_begin
        .direct_eval >>,&,(,),+
    asm_text
        nop
        nop
        lhi r6, #(ADDR_A>>16)
        ori r6,r6,#(ADDR_A&0xffff)
        nop
        nop
        lw r4,24(r6)
.chess_report __sint
        nop
        ori r5, r0, #222
        sw r5,24(r6)
        lw r4,24(r6)
.chess_report __sint
        addi r4,r4,#40    // dependency on lw (hw_stall)
.chess_report __sint
        nop
        nop
        nop
        nop
    asm_end
}
#else
inline void test_lw_dep2() 
{
    chess_report (7);
    chess_report (222);
    chess_report (262);
}
#endif

int main()
{
    test_lw_indep1();
    test_lw_indep2();
    test_lw_dep1();
    test_lw_dep2();
    return 0;
}
