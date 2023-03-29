/*
-- Copyright (c) 2020-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_SIMPLE_MEM_CA_TLM2_LT_ADAPTER_H__
#define INCLUDED_SIMPLE_MEM_CA_TLM2_LT_ADAPTER_H__

#include <systemc>
#include <snps_vp_sc_version.h>
#if defined(SNPS_VP_SC_VERSION) && (SNPS_VP_SC_VERSION >= 20180902)
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

#include <scml.h>
#include <scml2.h>
#include <tlm.h>
#include "AddressType.h"

#include "checkers_nml_memory_if.h"
#include "checkers_sc_wrapper_base.h"
#include "checkers_uicore.h"

#include <stl.h>
#include <queue>

namespace {
  template <typename T>
  T round_multiple(T val, T multiple) {
    return (val + multiple - 1) / multiple;
  }
};

template <int data_width>
class SimpleMem_CA_TLM2LT_Adapter : public sc_core::sc_module,
                                    public nCheckers::NMLMemoryIF<data_width> {
public:
  scml2::initiator_socket<data_width> & mSocket;

public:
  SC_HAS_PROCESS(SimpleMem_CA_TLM2LT_Adapter);

  // Constructor
  SimpleMem_CA_TLM2LT_Adapter(
      sc_module_name const& name,
      scml2::initiator_socket<data_width>& s,
      nCheckers::SCWrapperBase& scptr, int r_int_latency = 1,
      int w_int_latency = 1)

      : sc_core::sc_module(name), mSocket(s), mSCWrapper(scptr),
        mPortName(get_port_name(mSocket.name())),
        mRIntLatency(r_int_latency), mWIntLatency(w_int_latency)
  {
  }

  // sc_core::sc_module
  void end_of_elaboration() {
    mClockPeriod = mSCWrapper.clock_period();
    mQuantumKeeper = mSCWrapper.get_quantumkeeper();
  }

public:

  // nCheckers::NMLMemoryIF
  void update_status() {
    if (mWFinQ.size())
      handle_WFinQ();

    if (mRFinQ.size())
      handle_RFinQ();

    if (mWReqQ.size())
      handle_WReqQ();

    if (mRReqQ.size())
      handle_RReqQ();
  }

  // nCheckers::NMLMemoryIF
  nCheckers::MemTrnStatus beginRead(AddressType addr, int nwords,
                                    unsigned char *, VBitWrapper const& we) {

    auto total_bytes = to_bytes(nwords);
    auto tr_addr = to_byte_addr(addr);
    if (mRReqQ.size() > 0 && mRReqQ.back()->status == TRN_ARRIVED) {
      // later delta cycles
      mRReqQ.back()->update(tr_addr, nullptr, total_bytes, we);
    } else {
      mRReqQ.push(stl::make_unique<Request>(tr_addr, nullptr, total_bytes,
                                            false, TRN_ARRIVED, we));
    }

    mSCWrapper.notify_begin_read_access(mPortName, tr_addr, total_bytes);

    return nCheckers::TRANS_OK;
  }

  // nCheckers::NMLMemoryIF
  nCheckers::MemTrnStatus endRead(unsigned char *data, int nwords) {
    if (mRFinQ.size() == 0)
      return nCheckers::TRANS_IN_PROGRESS;

    auto& req = *mRFinQ.front();
    if (req.status == TRN_ERROR) {
      req.status = TRN_FINISHED;
      return nCheckers::TRANS_ERROR;
    }

    req.status = TRN_FINISHED;

    auto total_bytes = to_bytes(nwords);
    assert(req.data.size() == total_bytes);
    memcpy(data, req.data.data(), total_bytes);

    if (isDebug()) logRequest(req);

    mSCWrapper.notify_end_read_access(mPortName, req.address, req.data.data(),
                                      req.nbytes, req.cycles);

    return nCheckers::TRANS_OK;
  }

  // nCheckers::NMLMemoryIF
  nCheckers::MemTrnStatus beginWrite(AddressType addr,
                                     unsigned char const *data, int nwords,
                                     VBitWrapper const& we) {

    auto total_bytes = to_bytes(nwords);
    auto tr_addr = to_byte_addr(addr);
    if (mWReqQ.size() > 0 && mWReqQ.back()->status == TRN_ARRIVED) {
      // later delta cycles
      mWReqQ.back()->update(tr_addr, data, total_bytes, we);
    } else {
      mWReqQ.push(stl::make_unique<Request>(tr_addr, data, total_bytes, true,
                                            TRN_ARRIVED, we));
    }

    mSCWrapper.notify_begin_write_access(mPortName, tr_addr,
                                         const_cast<unsigned char*>(data),
                                         total_bytes);

    return nCheckers::TRANS_OK;
  }

  // nCheckers::NMLMemoryIF
  nCheckers::MemTrnStatus endWrite(unsigned char const *data, int nwords) {
    if (mWFinQ.size() == 0)
      return nCheckers::TRANS_IN_PROGRESS;

    auto& req = *mWFinQ.front();
    if (req.status == TRN_ERROR) {
      req.status = TRN_FINISHED;
      return nCheckers::TRANS_ERROR;
    }

    req.status = TRN_FINISHED;

    if (isDebug()) logRequest(req);

    mSCWrapper.notify_end_write_access(
        mPortName, req.address, req.data.data(), req.nbytes, req.cycles);

    return nCheckers::TRANS_OK;
  }

  // nCheckers::NMLMemoryIF
  void dbg_access(AddressType addr, unsigned char *data, int nwords,
                  bool read) {

    Request req(to_byte_addr(addr), data, to_bytes(nwords), !read, TRN_ARRIVED,
                VBitWrapper());

    if (read) {
      auto status = mSocket.template read_debug<bytes_per_word>(
          req.address, req.data.data(), nwords);

      if (!status) {
        std::cerr << format_dbgread_error(req) << '\n';
        return;
      }

      assert(req.data.size() == req.nbytes);
      memcpy(data, req.data.data(), req.nbytes);
    } else {
      auto status = mSocket.template write_debug<bytes_per_word>(
          req.address, req.data.data(), nwords);

      if (!status) {
        std::cerr << format_dbgwrite_error(req) << '\n';
        return;
      }
    }

    if (isDebug()) logRequest(req, true);
  }


private:

  enum TrnStatus { TRN_ARRIVED = 0, TRN_SENT, TRN_FINISHED, TRN_ERROR };

  struct Request {
    AddressType                 address;
    std::vector<unsigned char>  data;
    bool                        isWrite;
    unsigned                    nbytes;
    TrnStatus                   status;
    VBitWrapper                 word_enable;
    unsigned long long          cycles;
    int                         element_size;

    Request(AddressType a, unsigned char const *d, int n, bool isw,
            TrnStatus s, VBitWrapper const& we)
      : address(a), data(n), isWrite(isw), nbytes(n), status(s),
        word_enable(we), cycles(0),
        element_size((we.getBitSize() > 0) ? n / we.getBitSize() : n)
    {
      if (isWrite) {
        assert(d != nullptr);
        memcpy(data.data(), d, n);
      }
    }

    void update(AddressType a, unsigned char const *d, int n,
                VBitWrapper const& we) {
      address = a;
      nbytes = n;
      if (n != nbytes)
        data.resize(n);
      word_enable = we;
      if (isWrite) {
        assert(d != nullptr);
        memcpy(data.data(), d, n);
      }
      element_size = (we.getBitSize() > 0) ? n / we.getBitSize() : n;
    }
  }; // struct Request

  std::string get_port_name(std::string portname) {
    auto pos = portname.find_last_of('.');
    if (pos != std::string::npos) {
      portname = portname.substr(pos + 1);
    }
    return portname;
  }

  bool isDebug() {
    return mSCWrapper.ui_core()->debug_initiator_sockets();
  }

  AddressType to_word_addr(AddressType addr) const {
    return addr / bytes_per_word;
  }

  int to_words(int nbytes) const {
    return nbytes / bytes_per_word;
  }

  AddressType to_byte_addr(AddressType addr) const {
    return addr * bytes_per_word;
  }

  int to_bytes(int nwords) const {
    return nwords * bytes_per_word;
  }

  std::string bufToHexStr(unsigned char const *buf, int bytes) {
    std::ostringstream os;
    for (int i = bytes - 1; i >= 0; i--) { // little endian
      os << std::hex << std::setw(2) << std::setfill('0')
         << ((int)buf[i] & 0xff);
    }
    return os.str();
  }

  void logRequest(Request const& req, bool is_debug = false) {
    std::lock_guard<std::mutex> lock(checkers_globalsp->globals_mutex);
    std::string reqkind = req.isWrite ? "write" : "read";
    if (is_debug)
      reqkind += "_debug";
    std::ostringstream os;
    os << mSCWrapper.core_name() << ": " << mSocket.name() << '.' << reqkind
       << '<' << req.nbytes << "> addr=0x" << std::hex << req.address
       << ", val=0x" << bufToHexStr(req.data.data(), req.nbytes);
    std::cout << os.str() << std::endl;
    checkers_globalsp->debug_log_file << os.str() << std::endl;
  }

  void updateTime(Request& req, sc_time const& last_current_time,
                  sc_time const& local_time, int latency) {

    if (mQuantumKeeper) {
      mQuantumKeeper->set(local_time);
      auto consumed_time = mQuantumKeeper->get_current_time().value() -
                           last_current_time.value();
      req.cycles = round_multiple(consumed_time,  mClockPeriod.value());
    } else {
      auto consumed_time = sc_time_stamp().value() + local_time.value() -
                           last_current_time.value();
      req.cycles = round_multiple(consumed_time,  mClockPeriod.value());
      mSCWrapper.vp_add_consumed_cycles(req.cycles);
    }
  }

  void handle_RReqQ() {
    assert(mRReqQ.size());
    handle_read_req(*mRReqQ.front());
    mRFinQ.push(std::move(mRReqQ.front()));
    mRReqQ.pop();
  }

  void handle_RFinQ() {
    assert(mRFinQ.size());
    if (mRFinQ.front()->status == TRN_FINISHED) {
      mRFinQ.pop();
    }
  }

  void handle_WReqQ() {
    assert(mWReqQ.size());
    handle_write_req(*mWReqQ.front());
    mWFinQ.push(std::move(mWReqQ.front()));
    mWReqQ.pop();
  }

  void handle_WFinQ() {
    assert(mWFinQ.size());
    if (mWFinQ.front()->status == TRN_FINISHED) {
      mWFinQ.pop();
    }
  }

  void handle_read_req(Request& req) {
    if (isDebug()) logRequest(req);
    assert(!req.isWrite);

    sc_time local_time, current_time;
    if (mQuantumKeeper) {
      local_time = mQuantumKeeper->get_local_time();
      current_time = mQuantumKeeper->get_current_time();
    } else {
      local_time = sc_core::SC_ZERO_TIME;
      current_time = sc_time_stamp();
    }

    auto status = mSocket.template read<bytes_per_word>(
        req.address, req.data.data(), to_words(req.nbytes),
        local_time);

    if (status) {
      req.status = TRN_SENT;
    } else {
      std::cerr << format_read_error(req) << '\n';
      req.status = TRN_ERROR;
    }

    auto nelements = req.word_enable.getBitSize();
    if (nelements > 0) {
      // for read-enable == 0, use zero
      auto elem_size = req.element_size;
      assert((nelements * req.element_size) <= req.data.size());
      for (auto i = 0; i < nelements; i++) {
        if (!(req.word_enable.getBit(i))) {
          memset(req.data.data() + i * elem_size, 0, elem_size);
        }
      }
    }

    updateTime(req, current_time, local_time, mRIntLatency);
  }

  void handle_write_req(Request& req) {
    if (isDebug()) logRequest(req);
    assert(req.isWrite);

    sc_time local_time, current_time;
    if (mQuantumKeeper) {
      local_time = mQuantumKeeper->get_local_time();
      current_time = mQuantumKeeper->get_current_time();
    } else {
      local_time = sc_core::SC_ZERO_TIME;
      current_time = sc_time_stamp();
    }

    auto nelements = req.word_enable.getBitSize();
    if (nelements > 0) {
      // for write-enable == 0, use data from dbg_access
      std::vector<unsigned char> tmpdata(req.nbytes);
      dbg_access(to_word_addr(req.address), tmpdata.data(),
                 to_words(req.nbytes), true);
      auto elem_size = req.element_size;
      assert((nelements * req.element_size) <= req.data.size());
      for (auto i = 0; i < nelements; i++) {
        if (!(req.word_enable.getBit(i))) {
          memcpy(req.data.data() + i * elem_size,
                 tmpdata.data() + i * elem_size, elem_size);
        }
      }
    }

    auto status = mSocket.template write<bytes_per_word>(
        req.address, req.data.data(), to_words(req.nbytes),
        local_time);

    if (status) {
      req.status = TRN_SENT;
    } else {
      std::cerr << format_write_error(req) << '\n';
      req.status = TRN_ERROR;
    }

    updateTime(req, current_time, local_time, mWIntLatency);
  }

  std::string format_read_error(Request const& req) {
    std::ostringstream os;
    os << "Error: " << mSocket.name() << ".read failed for address: 0x"
       << std::hex << req.address << ", returning 0";
    return os.str();
  }

  std::string format_write_error(Request const& req) {
    std::ostringstream os;
    os << "Error: " << mSocket.name() << ".write failed for address: 0x"
       << std::hex << req.address;
    return os.str();
  }

  std::string format_dbgread_error(Request const& req) {
    std::ostringstream os;
    os << "Error: " << mSocket.name()
       << ".read_debug failed for address: 0x" << std::hex << req.address
       << ", returning 0";
    return os.str();
  }

  std::string format_dbgwrite_error(Request const& req) {
    std::ostringstream os;
    os << "Error: " << mSocket.name()
       << ".write_debug failed for address: 0x" << std::hex << req.address
       << ", returning 0";
    return os.str();
  }


private:

  static int const bytes_per_word = data_width / 8;

  typedef std::unique_ptr<Request> request_ptr_t;

  nCheckers::SCWrapperBase&     mSCWrapper;
  std::string                   mPortName;
  unsigned long long            mRIntLatency;
  unsigned long long            mWIntLatency;
  sc_core::sc_time              mClockPeriod;
  nCheckers::QuantumKeeperBase *mQuantumKeeper = nullptr;
  std::queue<request_ptr_t>     mWReqQ;
  std::queue<request_ptr_t>     mWFinQ;
  std::queue<request_ptr_t>     mRReqQ;
  std::queue<request_ptr_t>     mRFinQ;
};

#endif // INCLUDED_SIMPLE_MEM_CA_TLM2_LT_ADAPTER_H__
