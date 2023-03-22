/*
-- Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "Mdl_trv32p3_systemc.h"

#include "Mdl_trv32p3.h"
#include "Mdl_trv32p3_uicore.h"
#include "Mdl_trv32p3_convert.h"
#include "Mdl_trv32p3_testbench.h"
#include "checkers_sc_time_gater.h"

#include "trv32p3_define.h"

#include <ScatteredArray.h>
#include <inttypes.h>


#define PM_SIZE (1ULL<<(PM_SIZE_NBIT)) /* in byte  */
#define DM_SIZE (1ULL<<(DM_SIZE_NBIT)) /* in byte */


// PM: aligned addresses only
template<  unsigned addr_bits, size_t mem_size >
SC_MODULE(ProgramMemory)
{
public:
  typedef sc_uint<32>           D;
  typedef sc_uint<addr_bits>    A;

private:
  ScatteredArray<uint32_t, mem_size-1, false> ram;
public:
  sc_in_clk           clock;
  sc_in<bool>         ld, st;
  sc_in<A>            a;
  sc_in<D>            d;
  sc_out<D>           q;

  void prc_memory() {
    AddressType ar = a.read();
    if (ld.read() && ar < mem_size) {
      q.write(ram[ar]);
    } else if (st.read() && ar < mem_size) {
      ram[ar] = d.read();
    }
  }

  SC_CTOR(ProgramMemory)
    : clock("clock"),ld("ld"),st("st"),a("a"),d("d"),q("q")
  {
    SC_METHOD(prc_memory);
    sensitive << clock.pos();
  }

  void iss_put(AddressType a, D val) {
    if (a < mem_size) ram[a] = val;
  }

  void iss_put(AddressType a, VectorIndexType e, sc_uint<8> val) {
    if (a < mem_size) {
      D mem = ram[a];
      mem.range(8*(e+1)-1,8*e) = val; // little endian
      ram[a] = mem;
    }
  }

  D iss_get(AddressType a) {
    return (a < mem_size) ? (D)ram[a] : (D)0;
  }

  sc_uint<8> iss_get(AddressType a, VectorIndexType e) {
    if (a < mem_size) {
      return D(ram[a]).range(8*(e+1)-1,8*e); // little endian
    } else
      return 0;
  }
};



// memory with byte write enable, aligned accesses only
template < unsigned addr_bits, size_t mem_size >
SC_MODULE(DataMemoryBank)
{
public:
  typedef sc_uint<32>           D;
  typedef sc_uint<addr_bits>    A;

private:
  ScatteredArray<uint32_t, mem_size-1, false> ram;
public:

  sc_in_clk             clock;
  sc_in<bool>           ld;
  sc_in<sc_uint<4> >    st;
  sc_in<A>              a;
  sc_in<D>              d;
  sc_out<D>             q;

  void prc_memory() {
    AddressType ar = a.read();
    sc_uint<4>  wen = st.read();
    if (ld.read() && ar < mem_size) {
      q.write(ram[ar]);
    } else if (wen != 0 && ar < mem_size) {
      D mem = ram[ar];
      D inp = d.read();
      for (int i = 0; i < 4; ++i) {
        if (wen[i] != 0) {
          mem.range(8*(i+1)-1,8*i) =
            inp.range(8*(i+1)-1,8*i);  // little endian
        }
      }
      ram[ar] = mem;
    }
  }

  SC_CTOR(DataMemoryBank)
    : clock("clock"),ld("ld"),st("st"),a("a"),d("d"),q("q")
  {
    SC_METHOD(prc_memory);
    sensitive << clock.pos();
  }

  void iss_put(AddressType a, D val) {
    if (a < mem_size) ram[a] = val;
  }

  void iss_put(AddressType a, VectorIndexType e, sc_uint<8> val) {
    if (a < mem_size) {
      D mem = ram[a];
      mem.range(8*(e+1)-1,8*e) = val; // little endian
      ram[a] = mem;
    }
  }

  D iss_get(AddressType a) {
    return (a < mem_size) ? (D)ram[a] : (D)0;
  }

  sc_uint<8> iss_get(AddressType a, VectorIndexType e) {
    if (a < mem_size) {
      return D(ram[a]).range(8*(e+1)-1,8*e); // little endian
    } else
      return 0;
  }
};


typedef ProgramMemory<32,PM_SIZE/4>     PMtype;
typedef DataMemoryBank<32,DM_SIZE/4 >   DMBankType;


struct trv32p3_testbench_systemc : public trv32p3_testbench_sc
{
  // constructor
  trv32p3_testbench_systemc(PMtype* epm, DMBankType* edm)
    : pePM(epm), peDM(edm)  { }

  PMtype     * pePM;
  DMBankType * peDM;

  virtual void dbg_access_ePM(AddressType a, sc_dt::sc_uint<32>& v, bool read) {
    if (read) v=pePM->iss_get(a);
    else        pePM->iss_put(a,v);
  }
  virtual void dbg_access_ePM(AddressType a, VectorIndexType e, sc_dt::sc_uint<8>& v, bool read) {
    if (read) v=pePM->iss_get(a,e);
    else        pePM->iss_put(a,e,v);
  }
  virtual void dbg_access_eDM(AddressType a, sc_dt::sc_uint<32>& v, bool read) {
    if (read) v=peDM->iss_get(a);
    else        peDM->iss_put(a,v);
  }
  virtual void dbg_access_eDM(AddressType a, VectorIndexType e, sc_dt::sc_uint<8>& v, bool read) {
    if (read) v=peDM->iss_get(a,e);
    else        peDM->iss_put(a,e,v);
  }
};



SC_MODULE(trv32p3_top_sc)
{
public:
  sc_in_clk                        clock;
  sc_in<bool>                      reset;

  // ------------------------------------------
  // Internal connections
  // ------------------------------------------

  // PM
  PMtype                                epm;
  sc_signal<sc_dt::sc_uint<32> >        epm_rd;
  sc_signal<sc_dt::sc_uint<32> >        epm_addr;
  sc_signal<bool >                      ld_epm;
  sc_signal<sc_dt::sc_uint<32> >        epm_wr;
  sc_signal<bool >                      istore;

  // DM
  DMBankType                            edm;
  sc_signal<sc_dt::sc_uint<32> >        edm_rd;
  sc_signal<sc_dt::sc_uint<32> >        edm_addr;
  sc_signal<bool >                      ld_edm;
  sc_signal<sc_dt::sc_uint<32> >        edm_wr;
  sc_signal<sc_dt::sc_uint<4> >         st_edm;

  // time gater (connection to GUI)
  checkers_time_gater                   gclock;
  sc_signal<bool>                       scbreak_req;

  // testbenches
  trv32p3_testbench_systemc             trv32p3_tb;

  // TRV32P3 core
  trv32p3_sc                            trv32p3;

  // ------------------------------------------
  // Constructor
  // ------------------------------------------
public:
  SC_CTOR(trv32p3_top_sc)
    : clock             ("clock"        )
    , reset             ("reset"        )
    , epm               ("epm"           )
    , edm               ("edm"          )
    , trv32p3_tb        (&epm, &edm)            // testbenches
    , trv32p3("TRV32P3", &trv32p3_tb)           // Core
    , gclock("gclock")                          // time gater (connection to GUI)
  {
    // TRV32P3 connections
    trv32p3.clock           (clock          );
    trv32p3.reset           (reset          );

    trv32p3.scbreak_req     (scbreak_req    );


    // TRV32P3 - PM
    trv32p3.epm_rd          (epm_rd         );
    trv32p3.epm_addr        (epm_addr       );
    trv32p3.ld_epm          (ld_epm         );
    epm_wr = 0;
    istore = false;

    // TRV32P3 - eDM
    trv32p3.edm_rd          (edm_rd         );
    trv32p3.edm_addr        (edm_addr       );
    trv32p3.ld_edm          (ld_edm         );
    trv32p3.edm_wr          (edm_wr         );
    trv32p3.st_edm          (st_edm         );

    // PM connections
    epm.clock               (clock          );
    epm.q                   (epm_rd         );
    epm.a                   (epm_addr       );
    epm.ld                  (ld_epm         );
    epm.d                   (epm_wr         );
    epm.st                  (istore         );

    // eDM connections
    edm.clock               (clock          );
    edm.q                   (edm_rd         );
    edm.a                   (edm_addr       );
    edm.ld                  (ld_edm         );
    edm.d                   (edm_wr         );
    edm.st                  (st_edm         );

    // time gater (connection to GUI)
    gclock.clock        (clock          );
    gclock.break_req    (scbreak_req    );

  } // c'tor

}; // trv32p3_top_sc



Tcl_Interp* sc_interp = 0;

int sc_main(int, char*[])
{
  // Top module
  trv32p3_top_sc trv32p3_top("trv32p3_top");

  // signals
  sc_clock                       clock;
  sc_signal<bool>                reset;

  // Connections
  trv32p3_top.clock                 (clock          );
  trv32p3_top.reset                 (reset          );

  // Run
  reset = true;
  sc_start(sc_time(100, SC_NS));
  reset = false;
  sc_start();

  return 0;
}

