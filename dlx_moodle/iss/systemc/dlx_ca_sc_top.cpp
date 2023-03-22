
// File generated by checkers version P-2019.09#3993eff943#190321
// Copyright 2014-2021 Synopsys, Inc. All rights reserved.
// checkers -B -v -M -cwork/dlx_ca_sc/LNa64/dlx_ca_sc.ccf dlx

// Processor: dlx

#include "Mdl_dlx_systemc.h"

#include "Mdl_dlx.h"
#include "Mdl_dlx_uicore.h"
#include "Mdl_dlx_convert.h"
#include "Mdl_dlx_testbench.h"
#include "checkers_sc_time_gater.h"




#define PM_SIZE (1ULL<<20) /* in byte  */
#define DM_SIZE (1ULL<<24) /* in byte */

#define MEMJITLIMIT (32 * 1024 * 1024)

template<class D, class A, int mem_size, int addr_shift=0>
SC_MODULE(RamMemory)
{
private:
  //ScatteredArray<D, mem_size, false, MEMJITLIMIT> ram;
  D * ram = new D[mem_size];
public:
  sc_in_clk           clock;
  sc_in<bool>         ld, st;
  sc_in<A>            a;
  sc_in<D>            d;
  sc_out<D>           q;


  void prc_memory() {
    unsigned ar = a.read() >> addr_shift;
    if (ld.read() && ar < mem_size)
      q.write(ram[ar]);
    else if (st.read() && ar < mem_size)
      ram[ar] = d.read();
  }

  SC_CTOR(RamMemory)
    : clock("clock"),ld("ld"),st("st"),a("a"),d("d"),q("q")
  {
    SC_METHOD(prc_memory);
    sensitive << clock.pos();
  }

  void iss_put(AddressType addr, D val) {
    unsigned a = addr >> addr_shift;
    if (a < mem_size) ram[a] = val;
  }
  D iss_get(AddressType addr) {
    unsigned a = addr >> addr_shift;
    return (a < mem_size) ? ram[a] : (D)0;
  }
};


typedef RamMemory<sc_uint<32>,sc_uint<32>,PM_SIZE,  2> PMemory;
typedef RamMemory<sc_uint<8>, sc_uint<32>,DM_SIZE/4  > DMemBank;



struct dlx_testbench_systemc : public dlx_testbench_sc
{
  // constructor
  dlx_testbench_systemc(PMemory* pm, DMemBank* dm0, DMemBank* dm1,
                        DMemBank* dm2, DMemBank* dm3)
  : pPMb(pm), pDM0(dm0), pDM1(dm1), pDM2(dm2), pDM3(dm3)
  {  }

  PMemory *pPMb;
  DMemBank *pDM0;
  DMemBank *pDM1;
  DMemBank *pDM2;
  DMemBank *pDM3;


  void dbg_access_PMb(AddressType a, sc_dt::sc_uint<8>& v, bool read) {
    sc_uint<32> word = pPMb->iss_get(a);
    unsigned col = a & 3;
    unsigned byte = word.range(8*(4-col)-1,8*(3-col));
    word.range(8*(4-col)-1,8*(3-col)) = v;
    if (read) v=byte;
    else        pPMb->iss_put(a,word);
  }
  void dbg_access_DM0(AddressType a, sc_dt::sc_uint<8>& v, bool read) {
    if (read) v=pDM0->iss_get(a);
    else        pDM0->iss_put(a,v);
  }
  void dbg_access_DM1(AddressType a, sc_dt::sc_uint<8>& v, bool read) {
    if (read) v=pDM1->iss_get(a);
    else        pDM1->iss_put(a,v);
  }
  void dbg_access_DM2(AddressType a, sc_dt::sc_uint<8>& v, bool read) {
    if (read) v=pDM2->iss_get(a);
    else        pDM2->iss_put(a,v);
  }
  void dbg_access_DM3(AddressType a, sc_dt::sc_uint<8>& v, bool read) {
    if (read) v=pDM3->iss_get(a);
    else        pDM3->iss_put(a,v);
  }
};



SC_MODULE(dlx_top_sc)
{
public:
  sc_in_clk                        clock;
  sc_in<bool>                      reset;

  // ------------------------------------------
  // Internal connections
  // ------------------------------------------

  // PM
  PMemory                               pm;
  sc_signal<sc_dt::sc_uint<32> >        pm_rd;
  sc_signal<sc_dt::sc_uint<32> >        pm_addr;
  sc_signal<bool >                      ifetch;
  sc_signal<sc_dt::sc_uint<32> >        pm_wr;
  sc_signal<bool >                      istore;

  // DM banks

  DMemBank                              dm0;
  sc_signal<sc_dt::sc_uint<8> >         dm0_rd;
  sc_signal<sc_dt::sc_uint<32> >        dm0_addr;
  sc_signal<bool >                      ld0;
  sc_signal<sc_dt::sc_uint<8> >         dm0_wr;
  sc_signal<bool >                      st0;

  DMemBank                              dm1;
  sc_signal<sc_dt::sc_uint<8> >         dm1_rd;
  sc_signal<sc_dt::sc_uint<32> >        dm1_addr;
  sc_signal<bool >                      ld1;
  sc_signal<sc_dt::sc_uint<8> >         dm1_wr;
  sc_signal<bool >                      st1;

  DMemBank                              dm2;
  sc_signal<sc_dt::sc_uint<8> >         dm2_rd;
  sc_signal<sc_dt::sc_uint<32> >        dm2_addr;
  sc_signal<bool >                      ld2;
  sc_signal<sc_dt::sc_uint<8> >         dm2_wr;
  sc_signal<bool >                      st2;

  DMemBank                              dm3;
  sc_signal<sc_dt::sc_uint<8> >         dm3_rd;
  sc_signal<sc_dt::sc_uint<32> >        dm3_addr;
  sc_signal<bool >                      ld3;
  sc_signal<sc_dt::sc_uint<8> >         dm3_wr;
  sc_signal<bool >                      st3;

  // time gater (connection to GUI)
  checkers_time_gater                   gclock;
  sc_signal<bool>                       scbreak_req;

  // testbenches
  dlx_testbench_systemc                 dlx_tb;

  // DLX core
  dlx_sc                                dlx;

  // ------------------------------------------
  // Constructor
  // ------------------------------------------
public:
  SC_CTOR(dlx_top_sc)
    : clock             ("clock"        )
    , reset             ("reset"        )
    , pm                ("pm"           )
    , dm0               ("dm0"          )
    , dm1               ("dm1"          )
    , dm2               ("dm2"          )
    , dm3               ("dm3"          )
    , dlx_tb (&pm, &dm0, &dm1, &dm2, &dm3)      // testbenches
    , dlx("DLX", &dlx_tb)                       // Core
    , gclock("gclock")                          // time gater (connection to GUI)
  {
    // DLX connections
    dlx.clock           (clock          );
    dlx.reset           (reset          );

    dlx.scbreak_req     (scbreak_req    );


    // DLX - PM
    dlx.pm_rd           (pm_rd          );
    dlx.pm_addr         (pm_addr        );
    dlx.ifetch          (ifetch         );
    dlx.pm_wr           (pm_wr          );
    dlx.istore          (istore         );

    // DLX - DM0
    dlx.dm0_rd          (dm0_rd         );
    dlx.dm0_addr        (dm0_addr       );
    dlx.ld0             (ld0            );
    dlx.dm0_wr          (dm0_wr         );
    dlx.st0             (st0            );

    // DLX - DM1
    dlx.dm1_rd          (dm1_rd         );
    dlx.dm1_addr        (dm1_addr       );
    dlx.ld1             (ld1            );
    dlx.dm1_wr          (dm1_wr         );
    dlx.st1             (st1            );

    // DLX - DM2
    dlx.dm2_rd          (dm2_rd         );
    dlx.dm2_addr        (dm2_addr       );
    dlx.ld2             (ld2            );
    dlx.dm2_wr          (dm2_wr         );
    dlx.st2             (st2            );

    // DLX - DM3
    dlx.dm3_rd          (dm3_rd         );
    dlx.dm3_addr        (dm3_addr       );
    dlx.ld3             (ld3            );
    dlx.dm3_wr          (dm3_wr         );
    dlx.st3             (st3            );

    // PM connections
    pm.clock            (clock          );
    pm.q                (pm_rd          );
    pm.a                (pm_addr        );
    pm.ld               (ifetch         );
    pm.d                (pm_wr          );
    pm.st               (istore         );

    // DM0 connections
    dm0.clock           (clock          );
    dm0.q               (dm0_rd         );
    dm0.a               (dm0_addr       );
    dm0.ld              (ld0            );
    dm0.d               (dm0_wr         );
    dm0.st              (st0            );

    // DM1 connections
    dm1.clock           (clock          );
    dm1.q               (dm1_rd         );
    dm1.a               (dm1_addr       );
    dm1.ld              (ld1            );
    dm1.d               (dm1_wr         );
    dm1.st              (st1            );

    // DM2 connections
    dm2.clock           (clock          );
    dm2.q               (dm2_rd         );
    dm2.a               (dm2_addr       );
    dm2.ld              (ld2            );
    dm2.d               (dm2_wr         );
    dm2.st              (st2            );

    // DM3 connections
    dm3.clock           (clock          );
    dm3.q               (dm3_rd         );
    dm3.a               (dm3_addr       );
    dm3.ld              (ld3            );
    dm3.d               (dm3_wr         );
    dm3.st              (st3            );

    // time gater (connection to GUI)
    gclock.clock        (clock          );
    gclock.break_req    (scbreak_req    );

  } // c'tor

}; // dlx_top_sc



Tcl_Interp* sc_interp = 0;

int sc_main(int, char*[])
{
  // Top module
  dlx_top_sc dlx_top("dlx_top");

  // signals
  sc_clock                       clock;
  sc_signal<bool>                reset;

  // Connections
  dlx_top.clock                 (clock          );
  dlx_top.reset                 (reset          );

  // Run
  reset = true;
  sc_start(sc_time(100, SC_NS));
  reset = false;
  sc_start();

  return 0;
}
