/*
-- File : trv32p5.h
--
-- Contents : Processor header file for the trv32p5 processor.
--
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P5_H_
#define INCLUDED_TRV32P5_H_

#include "trv32p5_define.h"

namespace trv32p5_primitive {

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Declaration of primitive data types
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Main Data Types (Data & Instruction Words)

  class w08        property(  8 bit signed);
  class w16        property( 16 bit signed);
  class w32        property( 32 bit signed);
  class u08        property(  8 bit unsigned);

  class addr       property( 32 bit unsigned);
  class iword      property( 32 bit unsigned);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Types for Transitories, Immediates, ...

  // unsigned
  class t1u        property(  1 bit unsigned);
  class t2u        property(  2 bit unsigned);
  class t5u        property(  5 bit unsigned);
  class t6u        property(  6 bit unsigned);
  class t8u        property(  8 bit unsigned);

  // signed
  class t12s       property( 12 bit signed);

  // irregular
  //  - nz              non-zero
  //  - s<N>            step of N
  //  - rp<N>           right-padded with N zeros (see conversions)

  // unsigned, irregular
  class t5unz      property(  5 bit unsigned min=1 max=31);

  // signed, irregular
  class t13s_s2    property( 13 bit signed step=2);
  class t20s_rp12  property( 20 bit signed);
  class t21s_s2    property( 21 bit signed step=2);
  class t31s_rp1   property( 31 bit signed);


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Declaration of Primitive Functions
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Integer Arithmetic

  w32 add    (w32,w32)       property(commutative);
  w32 sub    (w32,w32);
  w32 slt    (w32,w32);
  w32 sltu   (w32,w32);
  w32 seq0   (w32)           property(programmers_view);
  w32 sne0   (w32)           property(programmers_view);

  w32 band   (w32,w32)       property(commutative);
  w32 bor    (w32,w32)       property(commutative);
  w32 bxor   (w32,w32)       property(commutative);

  w32 sll    (w32,w32);
  w32 srl    (w32,w32);
  w32 sra    (w32,w32);

  w32 mul    (w32,w32)       property(programmers_view commutative);
  w32 mulh   (w32,w32)       property(programmers_view commutative);
  w32 mulhsu (w32,w32)       property(programmers_view);
  w32 mulhu  (w32,w32)       property(programmers_view commutative);

  // RTL optimized primitives
  void  mul_hw (w32,w32,t2u,w32&,w32&);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Integer Comparisons

  bool eq    (w32,w32)       property(commutative);
  bool lt    (w32,w32);
  bool ltu   (w32,w32);
  bool ne    (w32,w32)       property(commutative);
  bool ge    (w32,w32);
  bool geu   (w32,w32);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~ Bit Extension Primitives for Loads

  w32 sext   (w08)           property(promotion_conversion_alternate);
  w32 zext   (w08)           property(promotion_conversion_alternate);
  w32 sext   (w16)           property(promotion_conversion_alternate);
  w32 zext   (w16)           property(promotion_conversion_alternate);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Division & Remainder

  w32 divs   (w32,w32)       property(multicycle_32);
  w32 rems   (w32,w32)       property(multicycle_32);
  w32 divu   (w32,w32)       property(multicycle_32);
  w32 remu   (w32,w32)       property(multicycle_32);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Control Primitives (ujump, cjump, call)

  w32 jal    (t21s_s2)       property(relative call);
  w32 jalr   (w32)           property(absolute call);

  void j     (t21s_s2)       property(relative jump     programmers_view);
  void jr    (w32)           property(absolute jump ret programmers_view);

  void br    (bool,t13s_s2)  property(relative jump);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Primitives Needed Only for OCD Interface

#ifdef __go__
  addr incr1(addr); // OCD addr + 1
  addr incr4(addr); // OCD addr + 4
#endif


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Miscellaneous

  void nop ()                property(nop programmers_view);

  // single-instr sign/zero extension
  w32 zext_08 (w32)          property(programmers_view); // bit-and 0xff


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Definition of Conversions Between Primitive Data Types
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  class w32 {
    w32(t5u);
    w32(t12s);
    w32(t20s_rp12)  property (right_padding_12); // lui
    w32(addr);
#ifndef __programmers_view__
    w32(t21s_s2);  // jal
    w32(t13s_s2);  // br
    w32(t31s_rp1) property (right_padding_1);
#endif
  };

#ifndef __programmers_view__
  class t31s_rp1 { t31s_rp1(w32) property (right_truncate_1); };
#endif

  // store
  class w08  { w08 (w32); };
  class w16  { w16 (w32); };

  class addr { addr(w32); };

#ifdef __go__
  // for div.p write address
  class t5u { t5u(t5unz); };
#endif
}

#include "trv32p5_p_userext.h"

#endif // INCLUDED_TRV32P5_H_
