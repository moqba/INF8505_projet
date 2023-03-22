#include "flx_define.h"
#include "isg/flx_iss_types.h"



#include <verilated.h>
#include "verilated_fpu_models/Vspsr24.h"
#include "verilated_fpu_models/Vspdv24.h"

namespace flx_primitive {

void fdivide(w32 a, w32 b, w32& r) 
{
    Vspdv24 spdv24_model;
    spdv24_model.spdvAf_in = a.to_unsigned();
    spdv24_model.spdvBf_in = b.to_unsigned();
    spdv24_model.eval();
    r = spdv24_model.spdvRf_out;

}
void fsqrt(w32 a, w32& r) 
{
    Vspsr24 spsr24_model;
    spsr24_model.spsrAf_in = a.to_unsigned();
    spsr24_model.eval();
    r = spsr24_model.spsrRf_out;
}
}

