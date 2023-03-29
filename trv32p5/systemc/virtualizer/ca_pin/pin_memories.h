/*
-- Copyright (c) 2020-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_PIN_MEMORIES_H__
#define INCLUDED_PIN_MEMORIES_H__

#include <ScatteredArray.h>
#include <vbit.h>

// memory with byte write enable, aligned accesses only
template < int lanes, int lane_nbits = 8, int addr_nbits = 32, int data_nbits = lanes * lane_nbits >
SC_MODULE(DataMemory) {
public:

  typedef sc_uint<data_nbits>  D;
  typedef sc_uint<addr_nbits>  A;
  typedef sc_uint<lanes>       WE;

public:
  sc_in_clk    clock;
  sc_in<bool>  ld;
  sc_in<WE>    st;
  sc_in<A>     a;
  sc_in<D>     d;
  sc_out<D>    q;

  void prc_memory() {
    AddressType ar = a.read();
    auto wen = st.read();
    if (ld.read()) {
      q.write(D(ram[ar].value()));
    } else if (wen != 0) {
      auto inp = d.read();
      for (int i = 0; i < lanes; ++i) {
        if (wen[i] != 0) {
          auto val = inp.range(lane_nbits*(i+1)-1, lane_nbits*i).value();
          ram[ar].deposit(val, lane_nbits*(i+1)-1, lane_nbits*i);
        }
      }
    }
  }

  SC_CTOR(DataMemory)
    : clock("clock"), ld("ld"), st("st"), a("a"), d("d"), q("q")
  {
    SC_METHOD(prc_memory);
    sensitive << clock.pos();
  }

  void iss_put(AddressType a, D val) {
    ram[a] = val.value();
  }

  void iss_put(AddressType a, VectorIndexType e, sc_uint<lane_nbits> val) {
    ram[a].deposit(val.value(), lane_nbits*(e+1)-1, lane_nbits*e);
  }

  void iss_get(AddressType a, D& v) {
    v = ram[a].value();
  }

  void iss_get(AddressType a, VectorIndexType e, sc_uint<lane_nbits>& v) {
    v = ram[a].extract(lane_nbits*(e+1)-1, lane_nbits*e).value();
  }

private:
  VariableScatteredArray<VBit<data_nbits,false>, /*init=*/false> ram;
};

#endif
