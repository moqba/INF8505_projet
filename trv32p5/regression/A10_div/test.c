/*
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifdef __ndl__
inline assembly void test_nodep() clobbers(x3,x4,x5,x10) {
  asm_begin
  asm_text
    ori x3,x0,10
    ori x4,x0,5
    nop
    nop
    div x5,x3,x4
    // 33 nops
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    ori x10,x5,0   // no hazard
.chess_report __sint
    nop
    nop
    nop
  asm_end
}
#else
inline void test_nodep() {
  chess_message( "// test_nodep()" );
  chess_report (10/5);
}
#endif


#ifdef __ndl__
inline assembly void test_raw1a() clobbers(x3,x4,x5,x10) {
  asm_begin
  asm_text
    ori x3,x0,15
    ori x4,x0,5
    nop
    nop
    div x5,x3,x4
    or x10,x5,x0   // raw hazard
.chess_report __sint
    nop
    nop
    nop
  asm_end
}
#else
inline void test_raw1a() {
  chess_message( "// test_raw1a()" );
  chess_report (15/5);
}
#endif
#ifdef __ndl__
inline assembly void test_raw1b() clobbers(x3,x4,x5,x10) {
  asm_begin
  asm_text
    ori x3,x0,15
    ori x4,x0,5
    nop
    nop
    div x5,x3,x4
    or x10,x0,x5   // raw hazard
.chess_report __sint
    nop
    nop
    nop
  asm_end
}
#else
inline void test_raw1b() {
  chess_message( "// test_raw1b()" );
  chess_report (15/5);
}
#endif

#ifdef __ndl__
inline assembly void test_waw() clobbers(x3,x4,x5,x10) {
  asm_begin
  asm_text
    ori x3,x0,15
    ori x4,x0,5
    nop
    nop
    div x10,x6,x7
    nop
    ori x10,x0,123   // overwrite destination register
.chess_report __sint
    nop
    nop
    nop
  asm_end
}
#else
inline void test_waw() {
  chess_message( "// test_waw()" );
  chess_report (123);
}
#endif

#ifdef __ndl__
inline assembly void test_indep() clobbers(x3,x4,x10,x12) {
  asm_begin
  asm_text
    ori x3,x0,10
    ori x4,x0,5
    nop
    nop
    div x12,x3,x4
    addi x4,x4,10  // indep
    addi x4,x4,20  // indep
    ori x10,x12,0   // raw hazard
.chess_report __sint
    nop
    ori x10,x4,0   // report x4
.chess_report __sint
    nop
    nop
  asm_end
}
#else
inline void test_indep() {
  chess_message( "// test_indep()" );
  chess_report (10/5);
  chess_report (5+10+20);
}
#endif

#ifdef __ndl__
inline assembly void test_wport() clobbers(x3,x4,x5,x6,x10) {
  asm_begin
  asm_text
    ori x3,x0,7
    ori x4,x0,2
    ori x6,x0,10
    nop
    nop
    div x5,x3,x4
    addi x6,x6,1
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    div x5,x3,x4
    addi x6,x6,2
    addi x6,x6,3
    addi x6,x6,4
    addi x6,x6,5
    addi x6,x6,6
    addi x6,x6,7
    addi x6,x6,8
    ori x10,x5,0   // dependent instr before chess_report
.chess_report __sint
    ori x10,x6,0
.chess_report __sint
    nop
    nop
    nop
  asm_end
}
#else
inline void test_wport() {
  chess_message( "// test_wport()" );
  chess_report (7/2);
  chess_report (10+1+2+3+4+5+6+7+8);
}
#endif

#ifdef __ndl__
inline assembly void test_raw2(int chess_storage(x12) a, int chess_storage(x13) b)
                     clobbers(x5,x10) {
  asm_begin
  asm_text
    nop
    nop
    nop
    div x5,x12,x13
    ori x10,x5,0   // raw hazard
.chess_report __sint
    nop
    nop
    nop
  asm_end
}
#else
inline void test_raw2(int a, int b) {
  chess_message( "// test_raw2(" << a << ',' << b << ')' );
  if (b == 0) {
    // RISC-V specific
    chess_report(-1);
  } else {
    chess_report (a/b);
  }
}
#endif

#ifdef __ndl__
inline assembly void test_waw2(int chess_storage(x13) a, int chess_storage(x14) b)
    clobbers(x10) {
  asm_begin
  asm_text
    nop
    nop
    nop
    div x10,x13,x14
    or x10,x0,x13 // wait for div to write
.chess_report __sint
    nop
    nop
    nop
    nop
    rem x10,x13,x14
    or x10,x0,x13 // wait for rem to write
.chess_report __sint
    nop
    nop
    nop
  asm_end
}
#else
inline void test_waw2(int a, int b) {
  chess_message( "// test_waw2(" << a << ',' << b << ')' );
  chess_report (a);
  chess_report (a);
}
#endif

#ifdef __ndl__
inline assembly void test_2xdiv(int chess_storage(x13) a,
                                int chess_storage(x14) b,
                                int chess_storage(x15) c)
                     clobbers(x8,x10) {
  asm_begin
  asm_text
    nop
    nop
    nop
    div x10,x13,x14
    div x8,x13,x15 // wait for first div to complete
    ori x10,x10,0
.chess_report __sint
    ori x10,x8,0
.chess_report __sint
    nop
    nop
    nop
    nop
    rem x10,x13,x14
    rem x8,x13,x15 // wait for first div to complete
    ori x10,x10,0
.chess_report __sint
    ori x10,x8,0
.chess_report __sint
    nop
    nop
    nop
  asm_end
}
#else
inline void test_2xdiv(int a, int b, int c) {
  chess_message( "// test_2xdiv(" << a << ',' << b << ',' << c << ')' );
  chess_report (a/b);
  chess_report (a/c);
  chess_report (a%b);
  chess_report (a%c);
}
#endif

#ifdef __ndl__
inline assembly void test_load_div() clobbers(x3,x4,x10) {
  asm_begin
  asm_text
    ori x3,x0,10
    ori x4,x0,5
    nop
    nop
    addi x2, x2, -16
    sw   x3, 0(x2)
    addi x3, x0, 0
    lw   x3, 0(x2)
    div  x3, x3, x4
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    ori x10,x3,0   // no hazard
.chess_report __sint
    nop
    nop
    nop
    addi x2, x2, 16
  asm_end
}
#else
inline void test_load_div() {
  chess_message( "// test_load_div()" );
  chess_report (10/5);
}
#endif


#ifdef __ndl__
inline assembly void test_removed_div() clobbers(x3,x4,x5,x10) {
  asm_begin
  asm_text
    ori x3,x0,10
    ori x4,x0,11
    ori x5,x0,12
    nop
    nop
    beq x0, x0, La
    div x5,x3,x4
    nop
    nop
La:
    ori x10,x5,0
.chess_report __sint
    nop
    nop
    nop
  asm_end
}
#else
inline void test_removed_div()
{
    chess_message( "// test_removed_div()" );
    chess_report (12);
}
#endif


#ifdef __ndl__
  inline assembly void test_raw_removed() clobbers(x3,x4,x5,x6,x10) {
  asm_begin
  asm_text
    ori x3, x0, 15
    ori x4, x0, 5
    ori x5, x0, 20
    ori x6, x0, 0
    nop
    nop
    div x5,x3,x4
    beq x0, x0, La
    addi x6, x5, 13   // raw hazard
  La:
    add x10, x6, x5
  .chess_report __sint
    nop
    nop
  asm_end
  }
#else
inline void test_raw_removed() {
  chess_message( "// test_raw_removed()" );
  chess_report (15/5);
}
#endif

#ifdef __ndl__
inline assembly void test_raw2_removed() clobbers(x3,x4,x5,x6,x10) {
  asm_begin
  asm_text
    ori x3, x0, 15
    ori x4, x0, 5
    ori x5, x0, 20
    ori x6, x0, 0
    nop
    nop
    div x5,x3,x4
    beq x0, x0, La
    div x6,x5,x4
  La:
    add x10, x6, x5
  .chess_report __sint
    nop

    beq x0, x0, Lb
    jal x0, La
  Lb:
    nop
  asm_end
}
#else
inline void test_raw2_removed() {
  chess_message( "// test_raw2_removed()" );
  chess_report (15/5);
}
#endif


#ifdef __ndl__
inline assembly void test_div_jump() clobbers(x3,x4,x5,x6,x10) {
  asm_begin
  asm_text
    ori x3, x0, 15
    ori x4, x0, 5
    ori x5, x0, 20
    ori x6, x0, 0
    nop
    nop
    div x5,x3,x4
    jal x0, La
    div x6,x5,x4
  La:
    add x10, x6, x5
  .chess_report __sint
    nop

    nop
  asm_end
}
#else
inline void test_div_jump() {
  chess_message( "// test_div_jump()" );
  chess_report (15/5);
}
#endif


#ifdef __ndl__
inline assembly void test_div2div_raw() clobbers(x3,x4,x5,x6,x10) {
  asm_begin
  asm_text
    ori x3, x0, 15
    ori x4, x0, 5
    ori x5, x0, 20
    ori x6, x0, 0
    nop
    nop
    div x5,x3,x4
    div x5,x5,x4
    add x10, x6, x5
  .chess_report __sint
    nop

    nop
  asm_end
}
#else
inline void test_div2div_raw() {
  chess_message( "// test_div2div_raw()" );
  chess_report (15/5/5);
}
#endif

#ifdef __ndl__
inline assembly void test_raw_agu(int * chess_storage(x13) a) clobbers(x3,x4,x5,x10) {
  asm_begin
  asm_text
    ori x3,x0,5
    mul x4,x13,x3
    nop
    nop
    nop
    div x5,x4,x3
    lw x10,0(x5)   // raw hazard
.chess_report __sint
    nop
    nop
    nop
  asm_end
}
#else
inline void test_raw_agu(int * a) {
  chess_message( "// test_raw_agu()" );
  chess_report (*a);
}
#endif

int A[] = {0x85, 0x14, 0x09, 0x05, 0x03, 0x01, 0x00 };

int main() {
  test_nodep();
  test_raw1a();
  test_raw1b();
  test_waw();
  test_indep();
  test_load_div();
  test_removed_div();
  test_raw_removed();
  test_raw2_removed();
  test_div_jump();
  test_div2div_raw();
  test_wport();
  test_raw2(10,0);
  test_raw_agu(A);

  int ii = 0;
  do {
    test_raw2(A[ii],10);
    test_waw2(A[ii],10);
    test_2xdiv(A[ii],10,3);
  } while (A[ii++] != 0);

  return 0;
}
