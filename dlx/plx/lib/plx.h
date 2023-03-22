/*
-- File : plx.h
--
-- Contents : Processor header-file for the PLX processor.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/




#ifndef _plx_h
#define _plx_h

#include "common.h"

namespace plx_primitive {

// declaration of primitive data types

    // main data types
    class w08     property( 8 bit signed);
    class w16     property(16 bit signed);
    class w32     property(32 bit signed);

    class addr    property(32 bit unsigned);
    class iword   property(32 bit unsigned);

    // types for immediates
    class uint1   property( 1 bit unsigned);
    class uint3   property( 3 bit unsigned);
    class uint4   property( 4 bit unsigned);
    class uint5   property( 5 bit unsigned);
    class uint16  property(16 bit unsigned);

    class int5    property( 5 bit signed);
    class int16   property(16 bit signed);
    class int16p  property(16 bit signed /*padded*/);
    class int26   property(26 bit signed);

    class ctxt    property(bit=actual_CSIZE_NBIT unsigned); //  3
    class state   property(bit=CSIZE             unsigned); // 16
    class status  property(bit=CSIZE+6           unsigned); // 19

// integer primitives

    w32 add(w32,w32,uint1&)              property(commutative);
    w32 add(w32,w32)                     property(commutative);
    w32 sub(w32,w32,uint1&);

    w32 addx(w32,w32,uint1,uint1&)       property(commutative);
    w32 subx(w32,w32,uint1,uint1&);

    w32 band(w32,w32)                    property(commutative);
    w32 bor (w32,w32)                    property(commutative);
    w32 bxor(w32,w32)                    property(commutative);
    w32 xtd (w32,w32);

    w32 mul(w32,w32)                     property(commutative);

    void lmulss(w32,w32,w32& l, w32& h)  property(commutative);
    void lmulsu(w32,w32,w32& l, w32& h);
    void lmuluu(w32,w32,w32& l, w32& h)  property(commutative);

    w32 sll(w32,w32);
    w32 srl(w32,w32);
    w32 sra(w32,w32);
    w32 clb(w32);

    w32 sge (w32,w32);
    w32 sgt (w32,w32);
    w32 sle (w32,w32);
    w32 slt (w32,w32);
    w32 sgeu(w32,w32);
    w32 sgtu(w32,w32);
    w32 sleu(w32,w32);
    w32 sltu(w32,w32);
    w32 seq (w32,w32)  property(commutative);
    w32 sne (w32,w32)  property(commutative);

    w32 lhi(int16p) property(right_padding_16 promotion_conversion_alternate);

    w32 extend_sign(w08)  property(promotion_conversion_alternate);
    w32 extend_zero(w08)  property(promotion_conversion_alternate);
    w32 extend_sign(w16)  property(promotion_conversion_alternate);
    w32 extend_zero(w16)  property(promotion_conversion_alternate);
    w08 extract_w08(w32)  property(promotion_conversion_alternate);
    w16 extract_w16(w32)  property(promotion_conversion_alternate);

// iterative division primitive
    void divide(w32 a, w32 b, w32& l, w32& h) property(multicycle_8); // = 32/4

// control primitives

    bool eqz(w32);
    bool nez(w32) property(copy_jump);
    w32 seq0(w32) property(chess_view);
    w32 sne0(w32) property(chess_view);

    void br(bool,int16)   property(relative jump);
    void j(int26)         property(relative jump);
    void jr(w32)          property(absolute jump ret);
    void nop()            property(nop);
    void rti()            property(rti);
    void jti(w32)         property(absolute jti);

    w32  get_sr_cv()     property(programmers_view volatile);

    state set_bit(state, ctxt, uint1);

#if defined(__programmers_view__)
    w32 jal(int26)        property(relative call);
    w32 jalr(w32)         property(absolute call);
#else
    void jal(int26)       property(relative call);
    void jalr(w32)        property(absolute call);
#endif

    w32 sign_extend_08(w32)  property(chess_view);
    w32 zero_extend_08(w32)  property(chess_view);
    w32 sign_extend_16(w32)  property(chess_view);
    w32 zero_extend_16(w32)  property(chess_view);

    w32  load_rsvd(addr    ) property(programmers_view volatile);
    w32 store_cond(addr,w32) property(programmers_view volatile);

#if defined(__go__)
    addr incr4(addr); // OCD addr + 4
#endif

// definition of primitive data types

    class w32 {
        w32(int16);          // for immediates
        w32(uint16);         // for immediates
        w32(int5);
        w32(status);
        w32(uint1);
        w32(ctxt);
    };
    class uint1 {
        uint1(w32);
    };
    class ctxt {
        ctxt(w32);
    };
    class status {
        status(w32);
    };
    class addr {
        addr(w32);
    };
}

#ifndef __programmers_view__
#include "plx_hw.h"
#endif

#endif // _plx_h
