/*
-- Copyright (c) 2014-2021 Synopsys Inc.
*/


#define ADDR_A 0x2000
int chess_storage(DMb:ADDR_A) A[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,1,2, 3, 4 ,5};

#ifdef __chess__
inline assembly void test_raw() clobbers()
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
        nop
        vsum r4,v0
.chess_report __sint
        nop
        lv v1,16(r6)
        nop
        nop
        nop
        vsum r4,v1
.chess_report __sint
        nop
        lv v2,32(r6)
        nop
        nop
        vsum r4,v2
.chess_report __sint
        nop
        lv v3,48(r6)
        nop
        vsum r4,v3
.chess_report __sint
        nop
        lv v0,64(r6)
        vsum r4,v0
.chess_report __sint
        nop
        nop
        nop
        nop
    asm_end
}
#else
inline void test_raw()
{
    chess_report (10);
    chess_report (26);
    chess_report (42);
    chess_report (43);
    chess_report (14);
}
#endif

#ifdef __chess__
inline assembly void test_waw() clobbers()
{
    asm_begin
    asm_text
        nop
        nop
        ori r5, r0, #11
        ori r6, r0, #ADDR_A
        nop
        nop
        lv v0,0(r6)
        nop           // nops are needed for chess_report
        nop           // but still one hw_stall remains
.chess_report vint_t
        nop
        vbcast v0,r5
.chess_report vint_t
        vsum r4,v0
.chess_report __sint
        nop
        nop
        lv v1,16(r6)   // no nops hence 4 hw_stall cycles
        vbcast v1,r5
.chess_report vint_t
        vsum r4,v1
.chess_report __sint
        nop
        nop
        nop
    asm_end
}
#else
inline void test_waw()
{
    chess_report (vint_t(4,3,2,1));
    chess_report (vint_t(11,11,11,11));
    chess_report (44);
    chess_report (vint_t(11,11,11,11));
    chess_report (44);
}
#endif


#ifdef __chess__
inline assembly void test_lv_lv() clobbers()
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
.chess_report vint_t
        nop
        lv v1,16(r6)
        vmv v0,v1
.chess_report vint_t
        nop
        nop
        nop
        nop
        nop
        lv v3,32(r6)   // no nops hence 4 hw_stall cycles
        lv v0,48(r6)
        nop
        nop
        nop
.chess_report vint_t
        nop
        nop
        vmv v0,v3
.chess_report vint_t
        nop
        nop
        nop
        nop
        nop
    asm_end
}
#else
inline void test_lv_lv()
{
    chess_report (vint_t(4,3,2,1));
    chess_report (vint_t(8,7,6,5));
    chess_report (vint_t(1,15,14,13));
    chess_report (vint_t(12,11,10,9));
}
#endif


#ifdef __chess__
inline assembly void test_lv_sv() clobbers()
{
    asm_begin
    asm_text
        nop
        nop
        ori r6, r0, #ADDR_A
        nop
        nop
        lv v3,0(r6)
        nop
        nop
        nop
        lv v0,32(r6)
        sv v3,16(r6)
.chess_report vint_t
        nop
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
inline void test_lv_sv()
{
    chess_report (vint_t(12,11,10,9));
    chess_report (vint_t(4,3,2,1));
}
#endif


#ifdef __chess__
inline assembly void test_sv_lv() clobbers()
{
    asm_begin
    asm_text
        nop
        nop
        ori r6, r0, #ADDR_A
        nop
        nop
        lv v3,32(r6)
        nop
        nop
        nop
        nop
        sv v3,16(r6)
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
inline void test_sv_lv()
{
    chess_report (vint_t(12,11,10,9));
}
#endif


#ifdef __chess__
inline assembly void test_sv_sv() clobbers()
{
    asm_begin
    asm_text
        nop
        nop
        ori r6, r0, #ADDR_A
        nop
        nop
        lv v2,0(r6)
        lv v3,16(r6)
        nop
        nop
        nop
        nop
        sv v2,32(r6)
        sv v3,48(r6)
        nop
        nop
        nop
        nop
        lv v0,32(r6)
        nop
        nop
        nop
        nop
.chess_report vint_t
        lv v0,48(r6)
        nop
        nop
        nop
        nop
.chess_report vint_t
        nop
        nop
        nop
        nop
        nop
    asm_end
}
#else
inline void test_sv_sv()
{
    chess_report (vint_t(4,3,2,1));
    chess_report (vint_t(12,11,10,9));
}
#endif



int main()
{
    test_raw();
    test_waw();
    test_lv_lv();
    test_lv_sv();
    test_sv_lv();
    test_sv_sv();
    return 0;
}
