/*
-- File : dw_fpu_primitives.cpp
--
-- Contents : C++ implementation of float primitives 
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- stricfly prohibited. 
*/

#ifndef _dw_fpu_primitives_h
#define _dw_fpu_primitives_h
#include <math.h>
#include <iostream>

#include "flx_define.h"

#include "Mdl_flx.h"
namespace flx_primitive {
    
typedef union { float f; unsigned u; } f2u;  // float to unsigned reinterpretation

inline float as_float(w32 x) {
    f2u xx;
    xx.u = x.to_unsigned();
    return xx.f;
}

inline unsigned as_uns(float x) {
    f2u xx;
    xx.f = x;
    return xx.u;
}
    
#ifdef __checkers_ia__
void fdivide(w32 a, w32 b, w32 &result){
    
    float answer = as_float(a) /as_float(b); 
    result =    as_uns(answer);       
}

void fsqrt(w32 a, w32 &b) {
    float c = as_float(a);
    b = as_uns(sqrtf(c));
} 
#endif

static inline float  hw_nan(float x)  {  return (isnanf(x)) ? as_float(0x7F800001) : x;}
    
w32 faddsub(uint1 op, w32 a, w32 b)
{
    if (op.value())
        return as_uns(hw_nan(as_float(a) - as_float(b)));
    else
        return as_uns(hw_nan(as_float(a) + as_float(b)));
}

w32 fmul(w32 a, w32 b)
{
    return as_uns(hw_nan(as_float(a) * as_float(b)));
}

w32 sfle(w32 a, w32 b)
{
    return as_float(a) <= as_float(b);
}

w32 sflt(w32 a, w32 b)
{
    return as_float(a) < as_float(b);

}

w32 sfeq(w32 a, w32 b)
{
    return as_float(a) == as_float(b);
}

w32 i2f(w32 a)
{
    float ff = a.to_signed();
    return as_uns(ff);
}

w32 f2i(w32 a)
{
    return (int)as_float(a);
}
} // end namespace  flx_primitive
#endif  // _dw_fpu_primitives_h


