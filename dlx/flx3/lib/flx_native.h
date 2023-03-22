/*
-- File : flx_native.h
--
-- Contents :  support for native compilation
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _flx_native_h
#define _flx_native_h

#include "flx_define.h"
#include "isg/flx_iss_types.h"



#include <verilated.h>
#include "verilated_fpu_models/Vspsr24.h"
#include "verilated_fpu_models/Vspdv24.h"
#include "isg/flx_chess_types.h"
inline void fdiv(float24_t a, float24_t b, float24_t& c);
#include "isg/flx_chess_opns.h"
#if __tct_release__ <= 2009 // now automatically generated
// in order to keep using manual definitions, add property(dont_generate_native)
// in order to use the core's definition i.s.o. the front-end's own version, add property(generate_opaque_native)
inline float24_t::float24_t(int a)   {
    flx_primitive::w32 pa = a;
    flx_primitive::w32 t = flx_primitive::i2f(pa);
    *this = flx_primitive::__promo_w32_to_float24_t(t);
}

inline float24_t::operator int() const {
    flx_primitive::w32 pa = flx_primitive::__promo_float24_t_on_w32(*this);
    flx_primitive::w32 t = flx_primitive::f2i(pa);
    return t.value();
}

inline float24_t::operator signed char() const {
    return (int)(*this);
}

inline float24_t::float24_t(signed char a)   {
    *this = (float24_t)(int)a;
}


inline float24_t::operator signed short() const {
    return (int)(*this);
}

inline float24_t::float24_t(signed short a)   {
    *this = (float24_t)(int)a;
}


inline float24_t::float24_t(unsigned a)   {
    if(a>=0x80000000)
    {
        unsigned tmp1 = a-0x80000000U;
        flx_primitive::w32 tmp2 = tmp1;
        flx_primitive::w32 tmp3 = flx_primitive::fadd(tmp2,flx_primitive::__promo_float24_t_on_w32(0x4f0000));
        *this = tmp3.value();
    }
    else
    {
        *this = (float24_t)(int)a;
    }
}

inline float24_t::operator unsigned () const {
    flx_primitive::w32 tmp1 = flx_primitive::__promo_float24_t_on_w32(0x4f0000);
    flx_primitive::w32 tmp2 = flx_primitive::__promo_float24_t_on_w32(*this);
    flx_primitive::w32 tmp3 = flx_primitive::sfle(tmp1,tmp2);

    if(tmp3.value())
    {
        flx_primitive::w32 tmp4 = flx_primitive::fsub(tmp2,tmp1);
        flx_primitive::w32 tmp5 = flx_primitive::f2i(tmp4);
        return tmp5.to_unsigned() + 0x80000000U;
    }
    else
        return (int)(*this);
}

inline float24_t::operator unsigned char() const {
    return (unsigned)(*this);
}

inline float24_t::float24_t(unsigned char a)   {
    *this = (float24_t)(unsigned)a;
}


inline float24_t::operator unsigned short() const {
    return (unsigned)(*this);
}

inline float24_t::float24_t(unsigned short a)   {
    *this = (float24_t)(unsigned)a;
}
#endif

inline float24_t fsqrt(float24_t a) {
    Vspsr24 spsr24_model;
    spsr24_model.spsrAf_in = as_int32(a);
    spsr24_model.eval();
    return as_float24_t(spsr24_model.spsrRf_out);
}

inline void fdiv(float24_t a, float24_t b, float24_t& c) {
    Vspdv24 spdv24_model;
    spdv24_model.spdvAf_in = as_int32(a);
    spdv24_model.spdvBf_in = as_int32(b);
    spdv24_model.eval();
    c = as_float24_t(spdv24_model.spdvRf_out);
}



#endif /* _flx_native_h */
