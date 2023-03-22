/*
-- Copyright (c) 2014-2021 Synopsys Inc.
*/


#define ADDR_A 0x2000
int chess_storage(DMb:ADDR_A) A[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

#ifdef __chess__
inline assembly void test_lv() clobbers()
{
    asm_begin
    asm_text
        nop
        nop
        ori r6, r0, #ADDR_A
        nop
        nop
        lv v0,0(r6)
        nop
        nop
        nop
        lv v1,0(r5)
        vsum r4,v0
.chess_report __sint
        nop
        nop
        nop
        nop
        nop
    asm_end
}
#else
inline void test_lv()
{
    chess_report (10);
}
#endif

#ifdef __chess__
inline assembly void test_sv() clobbers()
{
    asm_begin
    asm_text
        nop
        nop
        ori r6, r0, #ADDR_A
        nop
        nop
        lv v1,0(r6)
        nop
        nop
        nop
        nop
        sv v1,16(r6)
        nop
        nop
        nop
        nop
        lv v0,16(r6)
        nop
        nop
        nop
        nop
.chess_report vint_t
        nop
    asm_end
}
#else
inline void test_sv()
{
    chess_report (vint_t(4,3,2,1));
}
#endif


int main()
{
    test_lv();
    test_sv();
    return 0;
}
