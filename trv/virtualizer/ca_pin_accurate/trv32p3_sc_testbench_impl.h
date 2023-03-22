#ifndef _TRV_TB_SC_IMPL_
#define _TRV_TB_SC_IMPL_

#include "trv32p3_sc_systemc.h"
#include "PinMemories.h"
#include <iostream>



struct trv32p3_testbench_sc_impl : public trv32p3_testbench_sc {

    DMBankType* peDM;
    PMType* pePM;

    trv32p3_testbench_sc_impl(DMBankType* idmp, PMType* ipmp) : peDM(idmp), pePM(ipmp) {
    }

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

struct trv32p3_testbench_sc_no_io_impl : public trv32p3_testbench_sc {

    Memory* peDM;
    Memory* pePM;

    trv32p3_testbench_sc_no_io_impl(Memory* idmp, Memory* ipmp) : peDM(idmp), pePM(ipmp) {
    }

    virtual void dbg_access_PMb(AddressType a, sc_dt::sc_uint<8>& v, bool read) {
        if (read) v=pePM->iss_get(a);
        else        pePM->iss_put(a,v);
    }

    virtual void dbg_access_DMb(AddressType a, sc_dt::sc_uint<8>& v, bool read) {
        if (read) v=peDM->iss_get(a);
        else        peDM->iss_put(a,v);
    }

};

#endif
