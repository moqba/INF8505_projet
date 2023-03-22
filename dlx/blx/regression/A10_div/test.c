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
inline assembly void test_1() clobbers(R2,R3,R4,R12,R13)
{
    asm_begin
    asm_text
        ori r2, r0, #103
        ori r3, r0, #5
        nop
        nop
        div r2,r3
        or r4,r0, r12
.chess_report __sint
        or r4,r0, r13
.chess_report __sint
        nop
        nop
        nop
    asm_end
}
#else
inline void test_1()
{
    chess_message( "// test_1()" );
    chess_report (20);
    chess_report (3);
}
#endif

#ifdef __chess__
inline assembly void test_div(int chess_storage() a, int chess_storage() b)
                     clobbers(R4,R6,R7,R12,R13)
{
    asm_begin
    asm_text
        ori r6, r0, #a
        ori r7, r0, #b
        nop
        nop
        div r6,r7
        or r4,r0,r12
.chess_report __sint
        or r4,r0,r13
.chess_report __sint
        nop
        nop
        nop
    asm_end
}
#else
inline void test_div(int a, int b)
{
    chess_message( "// test_div(" << a << ',' << b << ')' );
    chess_report (a/b);
    chess_report (a%b);
}
#endif

#ifdef __chess__
inline assembly void test_div_w_conf(int chess_storage(R6) a,
                                     int chess_storage(R7) b)
                                     clobbers(R4,R5,R6,R7,R8,R12,R13)
{
    asm_begin
    asm_text
        nop
        nop
        div r6,r7
        lhi r5,#3
        lhi r6,#5
        lhi r7,#6
        lhi r8,#7
        ori r5,r5,#11
        ori r6,r6,#12
        ori r7,r7,#13
        ori r8,r8,#14
        or r4,r0,r12
.chess_report __sint
        or r4,r0,r13
.chess_report __sint
        or r4,r0,r5
.chess_report __sint
        or r4,r0,r6
.chess_report __sint
        or r4,r0,r7
.chess_report __sint
        or r4,r0,r8
.chess_report __sint
        nop
        nop
        nop
    asm_end
}
#else
inline void test_div_w_conf(int a, int b)
{
    chess_message( "// test_div_w_conf(" << a << ',' << b << ')' );
    chess_report (a/b);
    chess_report (a%b);
    chess_report(0x0003000b);
    chess_report(0x0005000c);
    chess_report(0x0006000d);
    chess_report(0x0007000e);
}
#endif


#ifdef __chess__
inline assembly void test_div_j_ds1(int chess_storage(R6) aa,
                                    int chess_storage(R7) bb)
                                     clobbers(R4,R5,R6,R7,R8,R9,R12,R13)
{
    asm_begin
      .direct_eval >>,&,(,),+
    asm_text
        lhi r9, #(Lc>>16)
        ori r9, r0, #(Lc&0xffff)
        nop
        nop
        div r6,r7
        jr r9
        addi r12, r12, #33  // should not be executed
        nop
        nop
Lc:     nop
        addi r12, r12, #113 // jump target stalls on result
        ori r4,r0,#22
.chess_report __sint
        or r4,r0,r12
.chess_report __sint
        nop
        nop
        nop
    asm_end
}
#else
inline void test_div_j_ds1(int a, int b)
{
    chess_message( "// test_div_j_ds1(" << a << ',' << b << ')' );
    chess_report (22);
    chess_report (113 + a/b);
}
#endif

#ifdef __chess__
inline assembly void test_div_jr_ds2(int chess_storage(R6) aa,
                                     int chess_storage(R7) bb)
                                     clobbers(R4,R6,R7,R12,R13,R15)
{
    asm_begin
      .direct_eval >>,&,(,),+
    asm_text
        lhi r15, #(Lc>>16)
        ori r15, r0, #(Lc&0xffff)
        nop
        nop
        div r6,r7
        jr r15
        addi r13, r13, #33  // should not be executed
        nop
        nop
Lc:     addi r12, r12, #101 // branch target stalls on result
        addi r13, r13, #103 // branch target
        ori r4,r0,#22
.chess_report __sint
        or r4,r0,r12
.chess_report __sint
        or r4,r0,r13
.chess_report __sint
        nop
        nop
        nop
    asm_end
}
#else
inline void test_div_jr_ds2(int a, int b)
{
    chess_message( "// test_div_jr_ds2(" << a << ',' << b << ')' );
    chess_report (22);
    chess_report (101 + a/b);
    chess_report (103 + a%b);
}
#endif

#ifdef __chess__
inline assembly void test_div_jr_ds1(int chess_storage(R6) aa,
                                     int chess_storage(R7) bb)
                                     clobbers(R4,R6,R7,R12,R13,R15)
{
    asm_begin
      .direct_eval >>,&,(,),+
    asm_text
        lhi r15, #(Lc>>16)
        ori r15, r0, #(Lc&0xffff)
        nop
        nop
        div r6,r7
        jr r15
        addi r13, r13, #33  // should not be executed
        nop
        nop
Lc:     addi r12, r12, #101 // branch target stalls on result
        addi r13, r13, #103 // branch target
        ori r4,r0,#22
.chess_report __sint
        or r4,r0,r12
.chess_report __sint
        or r4,r0,r13
.chess_report __sint
        nop
        nop
        nop
    asm_end
}
#else
inline void test_div_jr_ds1(int a, int b)
{
    chess_message( "// test_div_jr_ds1(" << a << ',' << b << ')' );
    chess_report (22);
    chess_report (101 + a/b);
    chess_report (103 + a%b);
}
#endif


#ifdef __chess__
inline assembly void test_div_bnez(int chess_storage(R6) aa,
                                   int chess_storage(R7) bb)
                                     clobbers(R2,R4,R5,R6,R7,R12,R13)
{
    asm_begin
    asm_text
        ori r4,r0,#22
.chess_report __sint
        nop
        nop
        // Test jump not taken
        div r6,r7
        nop
        sltui r2,r6,#100  // a < 100
        beqz r2, #Ld
        slli r5,r12,#1    // was delay slot
        or r4,r0,r5       // was delay slot
.chess_report __sint
        nop
Ld:     addi r4,r12,#25
.chess_report __sint
        nop
        // Test jump taken
        div r6,r7
        nop
        sltui r2,r6,#100  // a < 100
        slli r5,r12,#2    // was delay slot
        or r4,r0,r5       // was delay slot
        bnez r2, #Le
        nop
.chess_report __sint
        nop
Le:     addi r4,r12,#35
.chess_report __sint
        nop
        nop
    asm_end
}
#else
inline void test_div_bnez(int a, int b)
{
    chess_message( "// test_div_bnez(" << a << ',' << b << ')' );
    chess_report(22);
    if (a < 100)
        chess_report ((a/b) << 1);
    chess_report ((a/b) + 25);
    if (!(a < 100))
        chess_report ((a/b) << 2);
    chess_report ((a/b) + 35);
}
#endif




#ifdef __chess__
inline assembly void test_div_loop() clobbers(R2,R3,R4,R5,R6,R12,R13)
{
    asm_begin
    asm_text
        ori r2, r0, #1000
        ori r3, r0, #0    // count
        ori r4, r0, #3    // N nr of iterations
        nop
        nop
        nop
LOOP:   div r3,r4         // count % 3
        addi r3,r3,#1     // count++
        sltui r5,r3,#3    // count < N
        slli r6,r13,#2    //   [was delay slot]
        add r6,r2,r6      // r6 = &a[i % 3]         [was delay slot]
        bnez r5,#LOOP     //
        or r4,r0,r6
.chess_report __sint
        nop
        nop
    asm_end
}
#else
inline void test_div_loop()
{
    chess_message( "// test_div_loop()");

    chess_report (1000 + ((2%3)<<2));
}
#endif


#ifdef __chess__
inline assembly void test_div_div() clobbers(R2,R3,R4,R5,R6,R12,R13)
{
    asm_begin
    asm_text
        ori r2, r0, #129
        ori r3, r0, #5
        ori r5, r0, #89
        ori r6, r0, #4
        nop
        nop
        div r2,r3
        div r5,r6
        or r4,r0, r12
.chess_report __sint
        or r4,r0, r13
.chess_report __sint
        nop
        nop
        nop
    asm_end
}
#else
inline void test_div_div()
{
    chess_message( "// test_div_div()");

    chess_report (89/4);
    chess_report (89%4);
}
#endif

int A[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00 };

int main()
{
    test_1();
    test_div(84,10);
    test_div(20,20);
    test_div(1,1);
    int ii = 0;
    do {
        test_div_w_conf(A[ii],3);
        test_div_j_ds1 (A[ii],3);
        test_div_jr_ds1(A[ii],3);
        test_div_jr_ds2(A[ii],3);
        test_div_bnez  (A[ii],3);
    } while (A[ii++] != 0);
    test_div_loop();
    test_div_div();
    return 0;
}


