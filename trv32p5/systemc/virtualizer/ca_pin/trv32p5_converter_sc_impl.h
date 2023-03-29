/*
-- Copyright (c) 2020-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P5_CONVERTER_SC_IMPL_H__
#define INCLUDED_TRV32P5_CONVERTER_SC_IMPL_H__

#include "trv32p5_sc_systemc.h"

#include "../ca_pin/pin_memories.h"

template <typename DataMemory>
struct trv32p5_converter_sc_impl : public trv32p5_converter_sc {
  // constructor
  trv32p5_converter_sc_impl(DataMemory* edm)
    : peDM(edm)
  { }

  DataMemory * peDM;

  void dbg_access_eDM(AddressType a, sc_dt::sc_uint<32>& v, bool read) override  {
    if (read) peDM->iss_get(a,v);
    else      peDM->iss_put(a,v);
  }

  void dbg_access_eDM(AddressType a, VectorIndexType e, sc_dt::sc_uint<8>& v, bool read) override  {
    if (read) peDM->iss_get(a,e,v);
    else      peDM->iss_put(a,e,v);
  }
};
#endif
