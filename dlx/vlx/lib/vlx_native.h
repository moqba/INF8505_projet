/*
-- File : vlx_native.h
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



#ifndef _vlx_native_h
#define _vlx_native_h

#include "vlx_define.h"
#include "isg/vlx_iss_types.h"



#include "isg/vlx_chess_types.h"
#include "isg/vlx_chess_opns.h"
#include<stack>
extern std::stack<vbool_t> vbs_vbool;
extern std::stack<vint_t> vbs_vint;
extern std::stack<vuint_t> vbs_vuint;
inline vint_t vint_t::operator=(const vint_t& vi) {
  for (int i=0; i<4; i++) {
    if (vbs_vint.top().elem(i))
      val[i] = vi.val[i];
  }
  return *this;
}
inline vuint_t vuint_t::operator=(const vuint_t& vi) {
  for (int i=0; i<4; i++) {
    if (vbs_vuint.top().elem(i))
      val[i] = vi.val[i];
  }
  return *this;
}
inline vbool_t vbool_t::operator=(const vbool_t& vi) {
  for (int i=0; i<4; i++) {
    if (vbs_vbool.top().elem(i))
      val[i] = vi.val[i];
  }
  return *this;
}

namespace vlx_primitive {
inline w32 __promo_vbool_t_on_w32(vbool_t a) {
  unsigned int tmp=0;
  for (int i = 4; i >0;) {
    tmp <<=1;
    tmp |=(toBitType(a.elem(--i))!=0) ? 1 : 0;
  }
  return tmp;
}

inline vbool_t __promo_w32_to_vbool_t(w32 a) {
  vbool_t val;
  unsigned int tmp=toBitType(a).to_unsigned();
  for (int i = 0; i < 4; i++) {
    val.elem(i, (tmp & 1));
    tmp >>=1;
  }
  return val;
}

}

#endif /* _vlx_native_h */
