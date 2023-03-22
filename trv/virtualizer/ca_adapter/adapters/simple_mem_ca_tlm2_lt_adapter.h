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
#include "checkers_uicore.h"

#define dout std::cout

template <int data_width>
class SimpleMem_CA_TLM2LT_Adapter : public sc_core::sc_module,
                                    public nCheckers::NMLMemoryIF<data_width> {
   public:
    static const int word_size = data_width / 8;
#ifdef __VZER_PARALLEL_MODE__
    nCheckers::guarded_initiator_socket<data_width>* mSocket;
#else
    scml2::initiator_socket<data_width>* mSocket;
#endif
    enum TrnStatus {
        TRN_ARRIVED = 0,
        TRN_SENT,
        TRN_FINISHED,
        TRN_ERROR
    };
    struct Request {
        AddressType address;
        unsigned char* data;
        bool isWrite;
        unsigned int nbytes;
        bool isDebug;
        TrnStatus status;
        VBitWrapper word_enable;
        unsigned long long cycles;
        int element_size;

        Request (AddressType a, const unsigned char* d, int n, bool isw, bool isd, TrnStatus s, const VBitWrapper& we) {
            init(a, d, n, isw, isd, s, we);
        }
        void init (AddressType a, const unsigned char* d, int n, bool isw, bool isd, TrnStatus s, const VBitWrapper& we) {
            address = a; nbytes = n; isWrite = isw; isDebug = isd;
            data = new unsigned char[nbytes];
            word_enable = we;
            if (isw) memcpy(data, d, nbytes);
            status = s;
            element_size = nbytes;
            if (we.getBitSize() > 0) {
                element_size /= we.getBitSize();
            }
        }
    };

   public:
    SC_HAS_PROCESS(SimpleMem_CA_TLM2LT_Adapter);
    SimpleMem_CA_TLM2LT_Adapter(const sc_module_name& name,
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
        //for (int i = 0; i < bytes; i++) {
        for (int i = bytes-1; i >=0 ; i--) {
            os << std::hex << setw(2) << setfill('0') << ((int) buf[i] & 0xff);
        }
        return os.str();
    }

    void updateTime(Request* req, const sc_time& last_current_time, const sc_time& local_time, int latency)
    {
        if (mQuantumKeeper) {
            mQuantumKeeper->set(local_time);
            auto consumed_time = mQuantumKeeper->get_current_time().value() - last_current_time.value();
            req->cycles = (consumed_time + mClockPeriod.value() - 1) / mClockPeriod.value();
        } else {
            auto consumed_time = sc_time_stamp().value() + local_time.value() - last_current_time.value();
            req->cycles = (consumed_time + mClockPeriod.value() - 1) / mClockPeriod.value();
            mSCWrapper->vp_add_consumed_cycles(req->cycles);
        }
        if (req->cycles > latency) {
            // std::cerr << "Warning: latency of the external memory is greater than the one specified in the model!\n";
        }
    }

    void logRequest(Request* req)
    {
        if (true || mUiCore->debug_initiator_sockets()) {
            std::lock_guard<std::mutex> lock(checkers_globalsp->globals_mutex);
            std::string reqkind = req->isWrite ? "write" : "read";
            if (req->isDebug) reqkind += "_debug";
            std::ostringstream os;
            os << mCoreName << ": " << mSocket->name() << '.' << reqkind
               << '<' << req->nbytes << "> addr=0x" << std::hex << req->address
               << ", val=0x" << bufToHexStr(req->data, req->nbytes);
            std::cout << os.str() << std::endl;
            checkers_globalsp->debug_log_file << os.str() << std::endl;
        }
    }

    void update_status()
    {
        if (mWReqQ.size() > 0) {
            Request* req = mWReqQ.front();
            logRequest(req);
            sc_time local_time, current_time;
            if (mQuantumKeeper) {
                local_time = mQuantumKeeper->get_local_time();
                current_time = mQuantumKeeper->get_current_time();
            } else {
                local_time = sc_core::SC_ZERO_TIME;
                current_time = sc_time_stamp();
            }
            if (req->isWrite) {
                auto nelements = req->word_enable.getBitSize();
                if (nelements > 0) {
                    dout << "write before: " <<  std::hex << bufToHexStr(req->data, req->nbytes) << std::endl;
                    auto* tmpdata = new unsigned char[req->nbytes];
                    dbg_access(req->address/word_size, tmpdata, (req->nbytes)/word_size, true);
                    auto ele_size = req->element_size;
                    for (auto i = 0; i < nelements; i++) {
                        if (!(req->word_enable.getBit(i))) {
                            memcpy(req->data + i*ele_size, tmpdata + i*ele_size, ele_size);
                        }
                    }
                    dout << "write after: " <<  std::hex << bufToHexStr(req->data, req->nbytes) << std::endl;
                    delete[] tmpdata;
                }
                if (!mSocket->template write<word_size>(req->address, req->data, (req->nbytes)/word_size, local_time)) {
                    std::ostringstream os;
                    os << "Error: " << mSocket->name() << ".write failed for address: 0x" << std::hex << req->address;
                    std::cerr << os.str() << '\n';
                    req->status = TRN_ERROR;
                } else {
                    req->status = TRN_SENT;
                }
                updateTime(req, current_time, local_time, mWIntLatency);
            } else {
                assert(false);
            }
            mWReqQ.pop();
            mWFinQ.push(req);
        }
        if (mRReqQ.size() > 0) {
            Request* req = mRReqQ.front();
            logRequest(req);
            sc_time local_time, current_time;
            if (mQuantumKeeper) {
                local_time = mQuantumKeeper->get_local_time();
                current_time = mQuantumKeeper->get_current_time();
            } else {
                local_time = sc_core::SC_ZERO_TIME;
                current_time = sc_time_stamp();
            }
            if (req->isWrite) {
                assert(false);
            } else {
                if (!mSocket->template read<word_size>(req->address, req->data, (req->nbytes)/word_size, local_time)) {
                    std::ostringstream os;
                    os << "Error: " << mSocket->name() << ".read failed for address: 0x" << std::hex << req->address
                       << ", returning 0";
                    std::cerr << os.str() << '\n';
                    req->status = TRN_ERROR;
                } else {
                    req->status = TRN_SENT;
                }
                auto nelements = req->word_enable.getBitSize();
                if (nelements > 0) {
                    dout << "read before: " <<  std::hex << bufToHexStr(req->data, req->nbytes) << std::endl;
                    auto ele_size = req->element_size;
                    for (auto i = 0; i < nelements; i++) {
                        if (!(req->word_enable.getBit(i))) {
                            memset(req->data + i*ele_size, 0, ele_size);
                        }
                    }
                    dout << "read after: " <<  std::hex << bufToHexStr(req->data, req->nbytes) << std::endl;
                }
                updateTime(req, current_time, local_time, mRIntLatency);
            }
            mRReqQ.pop();
            mRFinQ.push(req);
        }
        if (mWFinQ.size()) {
            Request* req = mWFinQ.front();
            if (req->status == TRN_FINISHED) {
                mWFinQ.pop();
                delete req->data;
                delete req;
            }
        }
        if (mRFinQ.size()) {
            Request* req = mRFinQ.front();
            if (req->status == TRN_FINISHED) {
                mRFinQ.pop();
                delete req->data;
                delete req;
            }
        }
    }

    nCheckers::MemTrnStatus beginRead(AddressType addr, int nwords, unsigned char*, const VBitWrapper& we) {
        dout << mSocket->name() << ": beginRead recieved for address = 0x" << std::hex << addr << ", nwords = " << nwords << std::endl;
        if (we.getBitSize() > 0) dout << mSocket->name() << ": word enable: 0x" << we.toHex() << std::endl;
        const int total_bytes = nwords * word_size;
        auto tr_addr = addr * word_size;
        Request* req;
        if (mRReqQ.size() > 0 && mRReqQ.back()->status == TRN_ARRIVED) { // later delta-cycles
            req = mRReqQ.back();
            req->init(tr_addr, nullptr, total_bytes, false, false, TRN_ARRIVED, we);
        } else {
            req = new Request(tr_addr, nullptr, total_bytes, false, false, TRN_ARRIVED, we);
            mRReqQ.push(req);
        }
        mSCWrapper->notify_begin_read_access(mPortName, tr_addr, total_bytes);
        return nCheckers::TRANS_OK;
    }

    nCheckers::MemTrnStatus endRead(unsigned char* data, int nwords)
    {
        if (mRFinQ.size() == 0) return nCheckers::TRANS_IN_PROGRESS;
        Request* req = mRFinQ.front();
        if (req->status == TRN_ERROR) {
            req->status = TRN_FINISHED;
            data = nullptr;
            return nCheckers::TRANS_ERROR;
        }
        req->status = TRN_FINISHED;
        const int total_bytes = nwords * word_size;
        memcpy(data, req->data, total_bytes);
        logRequest(req);
        mSCWrapper->notify_end_read_access(mPortName, req->address, req->data, req->nbytes, req->cycles);
        dout << mSocket->name() << ": Finished End Read request!\n";
        return nCheckers::TRANS_OK;
    }

    nCheckers::MemTrnStatus beginWrite(AddressType addr, const unsigned char* data, int nwords, const VBitWrapper& we)
    {
        const int total_bytes = nwords * word_size;
        dout << mSocket->name() << ": beginWrite recieved for address = 0x" << std::hex << addr << ", nwords = " << nwords
             << ", data = 0x" << bufToHexStr(data, total_bytes) << std::endl;
        if (we.getBitSize() > 0) dout << mSocket->name() << ": word enable: 0x" << we.toHex() << std::endl;
        auto tr_addr = addr * word_size;
        Request* req;
        if (mWReqQ.size() > 0 && mWReqQ.back()->status == TRN_ARRIVED) { // later delta-cycles
            req = mWReqQ.back();
            req->init(tr_addr, data, total_bytes, true, false, TRN_ARRIVED, we);
        } else {
            req = new Request(tr_addr, data, total_bytes, true, false, TRN_ARRIVED, we);
            mWReqQ.push(req);
        }
        mSCWrapper->notify_begin_write_access(mPortName, tr_addr, req->data, total_bytes);
        return nCheckers::TRANS_OK;
    }

    nCheckers::MemTrnStatus endWrite(const unsigned char* data, int nwords)
    {
        if (mWFinQ.size() == 0) return nCheckers::TRANS_IN_PROGRESS;
        Request* req = mWFinQ.front();
        if (req->status == TRN_ERROR) {
            req->status = TRN_FINISHED;
            return nCheckers::TRANS_ERROR;
        }
        req->status = TRN_FINISHED;
        logRequest(req);
        mSCWrapper->notify_end_write_access(mPortName, req->address, req->data, req->nbytes, req->cycles);
        dout << mSocket->name() << ": Finished End Write request!\n";
        return nCheckers::TRANS_OK;
    }

    void dbg_access(AddressType addr, unsigned char* data, int nwords, bool read) {
        const int total_bytes = nwords * word_size;
        auto tr_addr = addr * word_size;
        Request* req = new Request(tr_addr, data, total_bytes, !read, true, TRN_ARRIVED, VBitWrapper());
        if (read) {
            if (!mSocket->template read_debug<word_size>(tr_addr, req->data, nwords)) {
                std::ostringstream os;
                os << "Error: " << mSocket->name() << ".read_debug failed for address: 0x"
                   << std::hex << addr << ", returning 0";
                std::cerr << os.str() << '\n';
                data = nullptr;
                delete req->data;
                delete req;
                return;
            }
            memcpy(data, req->data, total_bytes);
            logRequest(req);
        } else {
            if (!mSocket->template write_debug<word_size>(tr_addr, req->data, nwords)) {
                std::ostringstream os;
                os << "Error: " << mSocket->name() << ".write_debug failed for address: 0x"
                   << std::hex << addr;
                std::cerr << os.str() << '\n';
                delete req->data;
                delete req;
                return;
            }
            logRequest(req);
        }
        delete req->data;
        delete req;
    }

   private:
    nCheckers::SCWrapperBase* mSCWrapper;
    Checkers_uicore* mUiCore;
    std::string mCoreName, mPortName;
    unsigned long long mRIntLatency, mWIntLatency;
    sc_core::sc_time mClockPeriod;
    nCheckers::QuantumKeeperBase* mQuantumKeeper;
    bool mErrorOccured = false;
    std::queue<Request*> mWReqQ;
    std::queue<Request*> mWFinQ;
    std::queue<Request*> mRReqQ;
    std::queue<Request*> mRFinQ;
};

#endif
