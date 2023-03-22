#ifndef _DMB_ADAPTER_H_
#define _DMB_ADAPTER_H_
#define private public
#include <scml2/initiator_socket.h>
#undef private

// ---- pre-including headers from initiator_socket.h (for the private->public hack below)
#include <scml2/mappable_if.h>
#include <scml2/dmi_handler.h>
#include <scml2/utils.h>
#include <scml2/tlm2_gp_mm_ifs.h>
#include <scml2/tlm2_gp_mm_dispatcher.h>
#include <scml2_logging/stream.h>
#include <scml2_logging/severity.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm.h>
#include <systemc>
#include <string>
#include <set>
#include <vector>
#include <cassert>

#include <scml.h>
#include <scml2.h>
#include <tlm.h>
#include "AddressType.h"

#include "checkers_nml_memory_if.h"
#include "checkers_osci_wrapper_base.h"

#define DEBUG 0
#define dout if (DEBUG) std::cout

template <int data_width>
class DMb_adapter : public sc_core::sc_module,
                                       public nCheckers::NMLMemoryIF<data_width> {
   public:
    static const int word_size = data_width / 8;
    scml2::initiator_socket<data_width>* mSockets[4];
   public:
    SC_HAS_PROCESS(DMb_adapter);
    DMb_adapter(const sc_module_name& name,
                scml2::initiator_socket<data_width>* s0,
                scml2::initiator_socket<data_width>* s1,
                scml2::initiator_socket<data_width>* s2,
                scml2::initiator_socket<data_width>* s3,
                nCheckers::OSCIWrapperBase* scptr,
                int r_int_latency = 1,
                int w_int_latency = 1)
        : sc_core::sc_module(name),
          mSCWrapper(scptr),
          mRIntLatency(r_int_latency),
          mWIntLatency(w_int_latency)
    {
        mSockets[0] = s0;
        mSockets[1] = s1;
        mSockets[2] = s2;
        mSockets[3] = s3;
        mUiCore   = mSCWrapper->ui_core();
        mCoreName = mSCWrapper->core_name();
        // mSocket->set_endianness(tlm::TLM_BIG_ENDIAN);
    }

    void end_of_elaboration() {
        mClockPeriod = mSCWrapper->clock_period();
    }

    std::string bufToHexStr(const unsigned char* buf, int bytes)
    {
        std::ostringstream os;
        // assuming big endian for now
        // for (int i = 0; i < bytes; i++) {
        for (int i = bytes-1; i >=0 ; i--) {
            os << std::hex << std::setw(2) << std::setfill('0') << ((int) buf[i] & 0xff);
        }
        return os.str();
    }

    void updateTime(int latency)
    {
        mConsumedCycles = ((mLocalTime + mClockPeriod).value() - 1) / mClockPeriod.value();
//        mSCWrapper->vp_add_consumed_cycles(mConsumedCycles);
        if (mConsumedCycles > latency) {
            // std::cerr << "Warning: latency of the external memory is greater than the one specified in the model!\n";
        }
    }

    nCheckers::MemTrnStatus beginRead(AddressType addr, int nwords, unsigned char* data, const VBitWrapper& enable) {
        dout << "beginRead recieved for address = 0x" << std::hex << addr << ", nwords = " << nwords << std::endl;
        const int total_bytes = nwords * word_size;
        auto tr_addr = addr * word_size;
        auto pdata = data;
        mLocalTime = sc_core::SC_ZERO_TIME;
        for(int i = 0; i < nwords; i++) {
            auto socketp = mSockets[(addr + i) % 4];
            dout << "i=" << i << " socket=" << socketp->name() << " tr_addr=0x" << std::hex << tr_addr << std::dec << std::endl;
            if (!socketp->template read<word_size>(tr_addr, pdata, 1, mLocalTime)) {
                std::ostringstream os;
                os << "Error: " << socketp->name() << ".read failed for address: 0x" << std::hex << tr_addr
                   << ", returning 0";
                std::cerr << os.str() << '\n';
                mErrorOccured = true;
                return nCheckers::TRANS_ERROR;
            }
            pdata += word_size;
            tr_addr += word_size;
        }
        return nCheckers::TRANS_DONE;
    }

    nCheckers::MemTrnStatus endRead(unsigned char* data, int nwords)
    {
        return nCheckers::TRANS_OK;
    }

    nCheckers::MemTrnStatus beginWrite(AddressType addr, const unsigned char* data, int nwords, const VBitWrapper& enable)
    {
        const int total_bytes = nwords * word_size;
        dout << "beginWrite recieved for address = 0x" << std::hex << addr << ", nwords = " << nwords
             << ", data = 0x" << bufToHexStr(data, total_bytes) << std::endl;
        auto tr_addr = addr * word_size;
        mLocalTime = sc_core::SC_ZERO_TIME;
        for(int i = 0; i < nwords; i++) {
            auto socketp = mSockets[(addr + i) % 4];
            dout << "i=" << i << " socket=" << socketp->name() << " tr_addr=0x" << std::hex << tr_addr << std::dec << std::endl;
            if (!socketp->template write<word_size>(tr_addr, data, 1, mLocalTime)) {
                std::ostringstream os;
                os << "Error: " << socketp->name() << ".write failed for address: 0x" << std::hex << tr_addr;
                std::cerr << os.str() << '\n';
                mErrorOccured = true;
                return nCheckers::TRANS_ERROR;
            }
            data += word_size;
            tr_addr += word_size;
        }
        return nCheckers::TRANS_DONE;
    }

    nCheckers::MemTrnStatus endWrite(const unsigned char* data, int nwords)
    {
        return nCheckers::TRANS_OK;
    }

    void dbg_access(AddressType addr, unsigned char* data, int nwords, bool read) {
        const int total_bytes = nwords * word_size;
        auto tr_addr = addr * word_size;
        for(int i = 0; i < nwords; i++) {
            auto socketp = mSockets[(addr + i) % 4];
            if (read) {
                if (!socketp->template read_debug<word_size>(tr_addr, data, 1)) {
                    std::ostringstream os;
                    os << "Error: " << socketp->name() << ".read_debug failed for address: 0x"
                       << std::hex << addr << ", returning 0";
                    std::cerr << os.str() << '\n';
                    data = nullptr;
                    return;
                }
            } else {
                if (!socketp->template write_debug<word_size>(tr_addr, data, 1)) {
                    std::ostringstream os;
                    os << "Error: " << socketp->name() << ".write_debug failed for address: 0x"
                       << std::hex << addr;
                    std::cerr << os.str() << '\n';
                    return;
                }
            }
            data += word_size;
            tr_addr += word_size;
        }
    }

   private:
    nCheckers::OSCIWrapperBase* mSCWrapper;
    Checkers_uicore* mUiCore;
    std::string mCoreName;
    unsigned long long mRIntLatency, mWIntLatency;
    sc_core::sc_time mLocalTime;
    sc_core::sc_time mClockPeriod;
    unsigned long long mConsumedCycles;
    bool mErrorOccured = false;
};

#undef DEBUG
#undef dout

#endif
