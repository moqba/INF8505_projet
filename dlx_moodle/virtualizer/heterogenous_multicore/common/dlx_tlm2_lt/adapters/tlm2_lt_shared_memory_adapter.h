#ifndef _SIMPLE_MEMORY_TLM2_ADAPTER_H_
#define _SIMPLE_MEMORY_TLM2_ADAPTER_H_

#include <systemc>
#ifdef __VZER_PARALLEL_MODE__
#include "guarded_initiator_socket.h"
#else
#include <snps_vp_sc_version.h>
#if defined(SNPS_VP_SC_VERSION) && (SNPS_VP_SC_VERSION  >= 20180902)
#define SNPS_SCML2_INITIATOR_SOCKET_EXTENDED_API
#include <scml2/initiator_socket.h>
#else
// ---- pre-including headers from initiator_socket.h (for the private->public hack below)
#include <scml2/mappable_if.h>
#include <scml2/dmi_handler.h>
#include <scml2/utils.h>
#include <scml2/quantumkeeper_if.h>
#include <scml2/quantumkeeper_wrapper.h>
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
// ----
#define private public
#include <scml2/initiator_socket.h>
#undef private
#endif
#endif // __VZER_PARALLEL_MODE__

#include <scml.h>
#include <scml2.h>
#include <tlm.h>
#include "AddressType.h"

#include "checkers_nml_memory_if.h"
#include "checkers_sc_wrapper_base.h"

#define DEBUG 0
#define dout if (DEBUG && mUiCore->debug_initiator_sockets()) std::cout

template <int data_width>
class TLM2_LT_Shared_Memory_Adapter : public sc_core::sc_module,
                                       public nCheckers::NMLMemoryIF<data_width> {
   public:
    unsigned int shared_memory_offset; 
    static const int word_size = data_width / 8;
#ifdef __VZER_PARALLEL_MODE__
    nCheckers::guarded_initiator_socket<data_width>* mSocket;
#else
    scml2::initiator_socket<data_width>* mSocket;
#endif
   public:
    SC_HAS_PROCESS(TLM2_LT_Shared_Memory_Adapter);
    TLM2_LT_Shared_Memory_Adapter(const sc_module_name& name,
#ifdef __VZER_PARALLEL_MODE__
                                   nCheckers::guarded_initiator_socket<data_width>* s,
#else
                                   scml2::initiator_socket<data_width>* s,
#endif
                                   nCheckers::SCWrapperBase* scptr,
                                   int r_int_latency = 1,
                                   int w_int_latency = 1)
        : sc_core::sc_module(name),
          mSocket(s),
          mSCWrapper(scptr),
          mRIntLatency(r_int_latency),
          mWIntLatency(w_int_latency),
          mQuantumKeeper(nullptr) 
    {
        mUiCore   = mSCWrapper->ui_core();
        mCoreName = mSCWrapper->core_name();
        // mSocket->set_endianness(tlm::TLM_BIG_ENDIAN);
        mPortName = mSocket->name();
        auto pos = mPortName.find_last_of('.');
        if (pos != std::string::npos) {
            mPortName = mPortName.substr(pos+1);
        }
        char* tmp = ::getenv("SNPS_DLX_SHARED_MEMORY_OFFSET");
        if (tmp) {
            std::string tmpstr = tmp;
            shared_memory_offset = stoul(tmpstr, 0, 16);
            std::cout << "DLX: shared memory offset set to 0x" << std::hex << shared_memory_offset << std::endl;
        } else {
            std::cerr << "Error: environment variable: SNPS_DLX_SHARED_MEMORY_OFFSET not set, exiting!" << std::endl;
            exit(-1);
        }
    }

    void end_of_elaboration() {
        mClockPeriod = mSCWrapper->clock_period();
        mQuantumKeeper = mSCWrapper->get_quantumkeeper();
#ifdef __VZER_PARALLEL_MODE__
        mSocket->set_quantumkeeper(mQuantumKeeper);
#endif
    }

    std::string bufToHexStr(const unsigned char* buf, int bytes)
    {
        std::ostringstream os;
        // assuming big endian for now
        // for (int i = 0; i < bytes; i++) {
        for (int i = bytes-1; i >=0 ; i--) {
            os << std::hex << setw(2) << setfill('0') << ((int) buf[i] & 0xff);
        }
        return os.str();
    }

    void updateTime(int latency)
    {
        mConsumedCycles = ((mLocalTime + mClockPeriod).value() - 1) / mClockPeriod.value();
        if (mQuantumKeeper) {
            mQuantumKeeper->inc(mLocalTime);
        } else {
            mSCWrapper->vp_add_consumed_cycles(mConsumedCycles);
        }
        if (mConsumedCycles > latency) {
            // std::cerr << "Warning: latency of the external memory is greater than the one specified in the model!\n";
        }
    }

    void logRequest(AddressType addr, unsigned char* data, int nbytes, bool isDebug, bool isWrite)
    {
        if (DEBUG && mUiCore->debug_initiator_sockets()) {
            std::lock_guard<std::mutex> lock(checkers_globalsp->globals_mutex);
            std::string reqkind = isWrite ? "write" : "read";
            if (isDebug) reqkind += "_debug";
            std::ostringstream os;
            os << mCoreName << ": " << mSocket->name() << '.' << reqkind
               << '<' << nbytes << "> addr=0x" << std::hex << addr
               << ", val=0x" << bufToHexStr(data, nbytes);
            std::cout << os.str() << std::endl;
            checkers_globalsp->debug_log_file << os.str() << std::endl;
        }
    }

    nCheckers::MemTrnStatus beginRead(AddressType addr, int nwords, unsigned char* data, const VBitWrapper& enable) {
        dout << "beginRead recieved for address = 0x" << std::hex << addr << ", nwords = " << nwords << std::endl;
        auto nelements = enable.getBitSize();
        if (nelements > 0) dout << mSocket->name() << ": word enable: 0x" << enable.toHex() << std::endl;
        const int total_bytes = nwords * word_size;
        auto tr_addr = addr * word_size + shared_memory_offset;
        mLocalTime = sc_core::SC_ZERO_TIME;
        mSCWrapper->notify_begin_read_access(mPortName, tr_addr, total_bytes);

        if (!mSocket->template read<word_size>(tr_addr, data, nwords, mLocalTime)) {
            std::ostringstream os;
            os << "Error: " << mSocket->name() << ".read failed for address: 0x" << std::hex << tr_addr
               << ", returning 0";
            std::cerr << os.str() << '\n';
            mErrorOccured = true;
            return nCheckers::TRANS_ERROR;
        }
        if (nelements > 0) {
            dout << "read before: " <<  std::hex << bufToHexStr(data, total_bytes) << std::endl;
            auto ele_size = total_bytes / nelements;
            for (auto i = 0; i < nelements; i++) {
                if (!(enable.getBit(i))) {
                    memset(data + i*ele_size, 0, ele_size);
                }
            }
            dout << "read after: " <<  std::hex << bufToHexStr(data, total_bytes) << std::endl;
        }
        if (mLocalTime != SC_ZERO_TIME) {
            updateTime(mRIntLatency);
        } else {
            mConsumedCycles = 0;
        }
        mSCWrapper->notify_end_read_access(mPortName, tr_addr, data, total_bytes, mConsumedCycles);
        logRequest(tr_addr, data, total_bytes, false, false);
        return nCheckers::TRANS_DONE;
    }

    nCheckers::MemTrnStatus endRead(unsigned char* data, int nwords)
    {
        return nCheckers::TRANS_OK;
    }

    nCheckers::MemTrnStatus beginWrite(AddressType addr, const unsigned char* data, int nwords, const VBitWrapper& enable)
    {
        const int total_bytes = nwords * word_size;
        auto nelements = enable.getBitSize();
        dout << "beginWrite recieved for address = 0x" << std::hex << addr << ", nwords = " << nwords
             << ", data = 0x" << bufToHexStr(data, total_bytes) << std::endl;
        if (nelements > 0) dout << mSocket->name() << ": word enable: 0x" << enable.toHex() << std::endl;
        auto tr_addr = addr * word_size + shared_memory_offset;
        mLocalTime = sc_core::SC_ZERO_TIME;
        if (nelements > 0) {
            dout << "write before: " <<  std::hex << bufToHexStr(data, total_bytes) << std::endl;
            auto* tmpdata = new unsigned char[total_bytes];
            mSocket->template read_debug<word_size>(tr_addr, tmpdata, nwords);
            auto ele_size = total_bytes/nelements;
            for (auto i = 0; i < nelements; i++) {
                if (enable.getBit(i)) {
                    memcpy(tmpdata + i*ele_size, data + i*ele_size, ele_size);
                }
            }
            data = tmpdata;
            dout << "write after: " <<  std::hex << bufToHexStr(data, total_bytes) << std::endl;
        }
        mSCWrapper->notify_begin_write_access(mPortName, tr_addr, (unsigned char*) data, total_bytes);
        if (!mSocket->template write<word_size>(tr_addr, data, nwords, mLocalTime)) {
            std::ostringstream os;
            os << "Error: " << mSocket->name() << ".write failed for address: 0x" << std::hex << tr_addr;
            std::cerr << os.str() << '\n';
            mErrorOccured = true;
            return nCheckers::TRANS_ERROR;
        }
        if (mLocalTime != SC_ZERO_TIME) {
            updateTime(mWIntLatency);
        } else {
            mConsumedCycles = 0;
        }
        mSCWrapper->notify_end_write_access(mPortName, tr_addr, (unsigned char*) data, total_bytes, mConsumedCycles);
        logRequest(tr_addr, (unsigned char*) data, total_bytes, false, true);
        if (nelements > 0) {
            delete[] data;
        }
        return nCheckers::TRANS_DONE;
    }

    nCheckers::MemTrnStatus endWrite(const unsigned char* data, int nwords)
    {
        return nCheckers::TRANS_OK;
    }

    void dbg_access(AddressType addr, unsigned char* data, int nwords, bool read) {
        const int total_bytes = nwords * word_size;
        auto tr_addr = addr * word_size + shared_memory_offset;
        if (read) {
            if (!mSocket->template read_debug<word_size>(tr_addr, data, nwords)) {
                std::ostringstream os;
                os << "Error: " << mSocket->name() << ".read_debug failed for address: 0x"
                   << std::hex << addr << ", returning 0";
                std::cerr << os.str() << '\n';
                data = nullptr;
                return;
            }
            logRequest(tr_addr, data, total_bytes, true, false);
        } else {
            if (!mSocket->template write_debug<word_size>(tr_addr, data, nwords)) {
                std::ostringstream os;
                os << "Error: " << mSocket->name() << ".write_debug failed for address: 0x"
                   << std::hex << addr;
                std::cerr << os.str() << '\n';
                return;
            }
            logRequest(tr_addr, data, total_bytes, true, true);
        }
    }

   private:
    nCheckers::SCWrapperBase* mSCWrapper;
    Checkers_uicore* mUiCore;
    std::string mCoreName, mPortName;
    unsigned long long mRIntLatency, mWIntLatency;
    sc_core::sc_time mLocalTime;
    sc_core::sc_time mClockPeriod;
    unsigned long long mConsumedCycles;
    nCheckers::QuantumKeeperBase* mQuantumKeeper;
    bool mErrorOccured = false;
};

#endif
