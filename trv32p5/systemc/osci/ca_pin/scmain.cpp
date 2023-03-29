/*
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "trv32p5_define.h"

#include "Mdl_trv32p5.h"
#include "Mdl_trv32p5_uicore.h"
#include "Mdl_trv32p5_convert.h"
#include "Mdl_trv32p5_converter.h"
#ifdef NOGUI
#include "trv32p5_sc_no_gui_systemc.h"
#else
#include "trv32p5_sc_systemc.h"
#endif

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

typedef DataMemory<4,8> dm_t;

int sc_main(int argc, char** argv) {
  // Modules
  dm_t eDM("eDM");
  trv32p5_converter_sc_impl<dm_t> trv32p5_tb(&eDM);

  sc_clock clock;

#ifdef NOGUI
  if (argc < 2 || argc > 3) {
    std::cerr << "Usage: " << argv[0] << " <program> [<chess_report_filename>]" << std::endl;
    return 1;
  }

  trv32p5_load_program_args_sc pl_args(argv[1]);
  pl_args.cycle_count_breakpoints = 1;

  trv32p5_sc iss("iss", &trv32p5_tb, pl_args);

  if (argc == 3) {
    std::string fnm(argv[2]);
    chkapi_l_chess_report_set_file_name(iss.uicore, fnm);
  }

#else
  trv32p5_sc iss("iss", &trv32p5_tb);
#endif

  // Signals
  sc_signal<bool>                reset;

  // DM
  sc_signal<sc_dt::sc_uint<32>>  edm_rd;
  sc_signal<sc_dt::sc_uint<32>>  edm_addr;
  sc_signal<bool>                ld_edm;
  sc_signal<sc_dt::sc_uint<32>>  edm_wr;
  sc_signal<sc_dt::sc_uint<4>>   st_edm;

  // Connections
  iss.clock    (clock   );
  iss.reset    (reset   );

  iss.edm_rd   (edm_rd  );
  iss.edm_addr (edm_addr);
  iss.ld_edm   (ld_edm  );
  iss.edm_wr   (edm_wr  );
  iss.st_edm   (st_edm  );

  eDM.clock    (clock   );
  eDM.q        (edm_rd  );
  eDM.a        (edm_addr);
  eDM.ld       (ld_edm  );
  eDM.d        (edm_wr  );
  eDM.st       (st_edm  );

#ifndef NOGUI
  // wait for the debugger to join before the actual run
  ChkrsOSCIDebugControl::instance()->startAfterDebuggerJoins();
#endif

  // Run
  reset = 0;
  sc_start(sc_time(100, SC_NS));
  reset = 1;
  sc_start();

  return 0;
}
