/*
-- Copyright (c) 2020-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_VAR_LATENCY_IA_TLM2_FT_AXI_ADAPTER_H__
#define INCLUDED_VAR_LATENCY_IA_TLM2_FT_AXI_ADAPTER_H__

#include <systemc>
#include <scml.h>
#include <scml2.h>
#include <tlm.h>
#include <tlm_utils/peq_with_cb_and_phase.h>
#include "AddressType.h"

#include "checkers_nml_memory_if.h"
#include "checkers_sc_wrapper_base.h"
#include "checkers_uicore.h"

#include <stdlib.h>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

namespace {
  template <typename T>
  T round_multiple(T val, T multiple) {
    return (val + multiple - 1) / multiple;
  }
};

template <int data_width>
class VarLatency_IA_TLM2_FT_AXI_Adapter : public sc_core::sc_module,
                                          public nCheckers::NMLMemoryIF<data_width> {
public:
  scml2::ft_initiator_socket<data_width>&         mSocket;
  std::unique_ptr<scml2::initiator_port_adaptor>  mSocketAdapter;

public:
  SC_HAS_PROCESS(VarLatency_IA_TLM2_FT_AXI_Adapter);

  typedef VarLatency_IA_TLM2_FT_AXI_Adapter<data_width> adapter_t;

  // Constructor
  VarLatency_IA_TLM2_FT_AXI_Adapter(const sc_module_name& name,
                                    scml2::ft_initiator_socket<data_width>& s,
                                    nCheckers::SCWrapperBase& scptr)
    : sc_core::sc_module(name),
      mSocket(s),
      mSocketAdapter(scml2::initiator_port_adaptor::create("mSocketAdapter",&s)),
      mSCWrapper(scptr),
      mPortName(get_port_name(mSocket.name())) {

    // RD_ADDR
    SCML2_REGISTER_TIMING_CBK(
        mSocketAdapter, scml2::RD_ADDR_END, this, adapter_t::on_rd_addr_end);

    // RD_DATA
    if (mSocketAdapter->has_data_phase()) {
      SCML2_REGISTER_TIMING_CBK_WITH_ARG(
          mSocketAdapter, scml2::RD_DATA_START, this,
          adapter_t::on_rd_data_start, false);
      SCML2_REGISTER_TIMING_CBK_WITH_ARG(
          mSocketAdapter, scml2::RD_DATA_LAST_START, this,
          adapter_t::on_rd_data_start, true);
    }

    // WR_ADDR
    SCML2_REGISTER_TIMING_CBK(
        mSocketAdapter, scml2::WR_ADDR_END, this,
        adapter_t::on_wr_addr_end);

    // WR_DATA
    SCML2_REGISTER_TIMING_CBK_WITH_ARG(
        mSocketAdapter, scml2::WR_DATA_END, this,
        adapter_t::on_wr_data_end, false);
    SCML2_REGISTER_TIMING_CBK_WITH_ARG(
        mSocketAdapter, scml2::WR_DATA_LAST_END, this,
        adapter_t::on_wr_data_end, true);

    // WR_RSP
    if (mSocketAdapter->has_wr_rsp()) {
      SCML2_REGISTER_TIMING_CBK(
          mSocketAdapter, scml2::WR_RSP_START, this,
          adapter_t::on_wr_rsp_start);
    }
  }

  // sc_core::sc_module
  void end_of_elaboration() {
    mClockPeriod = mSCWrapper.clock_period();
    mQuantumKeeper = mSCWrapper.get_quantumkeeper();
  }

public:

  // nCheckers::NMLMemoryIF
  nCheckers::MemTrnStatus beginRead(AddressType addr, int nwords,
                                    unsigned char*, const VBitWrapper&) {

    if (isDebug()) log_beginRead(addr,nwords);
    assert(mQuantumKeeper);

    auto total_bytes = to_bytes(nwords);
    auto tr_addr = to_byte_addr(addr);

    mActiveReq.address = tr_addr;
    mActiveReq.data.resize(total_bytes);
    mActiveReq.nbytes = total_bytes;
    mActiveReq.trntime = mQuantumKeeper->get_current_time();

    mSCWrapper.notify_begin_read_access(mPortName, tr_addr, total_bytes);

    sc_time local_time = mQuantumKeeper->get_local_time();
    start_transaction(tlm::TLM_READ_COMMAND, tr_addr, mActiveReq.data.data(),
                      total_bytes, local_time);

    return nCheckers::TRANS_OK;
  }

  // nCheckers::NMLMemoryIF
  nCheckers::MemTrnStatus endRead(unsigned char* data, int nwords) {

    if (isDebug()) log_endRead(data,nwords);
    assert(mQuantumKeeper);

    auto total_bytes = to_bytes(nwords);

    // wait for event
    wait(mDataRecvd);

    memcpy(data, mActiveReq.data.data(), total_bytes);

    auto consumed_time = mQuantumKeeper->get_current_time().value() -
                         mActiveReq.trntime.value();
    auto cycles = round_multiple(consumed_time, mClockPeriod.value());

    mSCWrapper.notify_end_read_access(mPortName, mActiveReq.address,
                                      mActiveReq.data.data(),
                                      mActiveReq.nbytes, cycles);

    return nCheckers::TRANS_OK;
  }

  // nCheckers::NMLMemoryIF
  nCheckers::MemTrnStatus beginWrite(AddressType addr,
                                     unsigned char const* data, int nwords,
                                     const VBitWrapper&) {

    if (isDebug()) log_beginWrite(addr,data,nwords);
    assert(mQuantumKeeper);

    auto total_bytes = to_bytes(nwords);
    auto tr_addr = to_byte_addr(addr);

    mActiveReq.address = tr_addr;
    mActiveReq.data.resize(total_bytes);
    mActiveReq.nbytes = total_bytes;
    mActiveReq.trntime = mQuantumKeeper->get_current_time();
    memcpy(mActiveReq.data.data(), data, total_bytes);

    mSCWrapper.notify_begin_write_access(mPortName, tr_addr,
                                         mActiveReq.data.data(), total_bytes);

    sc_time local_time = mQuantumKeeper->get_local_time();
    start_transaction(tlm::TLM_WRITE_COMMAND, tr_addr, mActiveReq.data.data(),
                      total_bytes, local_time);

    return nCheckers::TRANS_OK;
  }

  // nCheckers::NMLMemoryIF
  nCheckers::MemTrnStatus endWrite(unsigned char const* data, int nwords) {

    if (isDebug()) log_endWrite(data,nwords);
    assert(mQuantumKeeper);

    // wait for event
    wait(mDataWritten);

    auto consumed_time = mQuantumKeeper->get_current_time().value() -
                         mActiveReq.trntime.value();
    auto cycles = round_multiple(consumed_time, mClockPeriod.value());

    mSCWrapper.notify_end_write_access(mPortName, mActiveReq.address,
                                       mActiveReq.data.data(),
                                       mActiveReq.nbytes, cycles);

    return nCheckers::TRANS_OK;
  }

  // nCheckers::NMLMemoryIF
  void dbg_access(AddressType addr, unsigned char* data, int nwords,
                  bool read) {

    if (isDebug()) log_dbg_access(addr,data,nwords,read);

    auto total_bytes = to_bytes(nwords);
    auto tr_addr = to_byte_addr(addr);

    if (read) {
      mSocketAdapter->read_debug(tr_addr, data, total_bytes);
    } else {
      mSocketAdapter->write_debug(tr_addr, data, total_bytes);
    }
  }

private:

  void start_transaction(tlm::tlm_command cmd, AddressType addr,
                         unsigned char* buf, int nbytes, sc_time& delay) {

    if (isDebug()) log_start_transaction(cmd,addr,buf,nbytes,delay);

    tlm::tlm_generic_payload& payload =
        mSocketAdapter->alloc_and_init_trans(cmd);
    payload.set_address(addr);
    // set allocated data pointer to transaction payload
    payload.set_data_ptr(buf);
    payload.set_data_length(nbytes);
    payload.set_streaming_width(nbytes);
    payload.set_byte_enable_ptr(nullptr);
    payload.set_byte_enable_length(0);

    // send transaction through port adaptor
    mSocketAdapter->send_transaction(payload, delay);
  }

  tlm::tlm_sync_enum on_rd_addr_end(tlm::tlm_generic_payload& trans,
                                    sc_time& delay) {

    if (isDebug()) log_on_rd_addr_end(trans,delay);
    return tlm::TLM_UPDATED;
  }

  tlm::tlm_sync_enum on_rd_data_start(tlm::tlm_generic_payload& trans,
                                      sc_time& delay, bool isLast) {

    if (isDebug()) log_on_rd_data_start(trans,delay,isLast);
    assert(mQuantumKeeper);

    if (isLast) {
      if (!trans.is_response_ok()) {
        std::cerr << fmterr_rd_data_start(trans) << std::endl;
      }
      assert(mActiveReq.data.data() == trans.get_data_ptr());

      trans.set_data_ptr(nullptr);
      mQuantumKeeper->set(delay);
      mDataRecvd.notify();
    }
    return tlm::TLM_UPDATED;
  }

  tlm::tlm_sync_enum on_wr_addr_end(tlm::tlm_generic_payload& trans,
                                    sc_time& delay) {

    if (isDebug()) log_on_wr_addr_end(trans,delay);
    return tlm::TLM_UPDATED;
  }

  tlm::tlm_sync_enum on_wr_data_end(tlm::tlm_generic_payload& trans,
                                    sc_time& delay, bool isLast) {

    if (isDebug()) log_on_wr_data_end(trans,delay,isLast);
    return tlm::TLM_UPDATED;
  }

  tlm::tlm_sync_enum on_wr_rsp_start(tlm::tlm_generic_payload& trans,
                                     sc_time& delay) {

    if (isDebug()) log_on_wr_rsp_start(trans,delay);
    assert(mQuantumKeeper);

    if (!trans.is_response_ok()) {
      std::cerr << fmterr_wr_rsp_start(trans) << std::endl;
    }

    trans.set_data_ptr(nullptr);
    mQuantumKeeper->set(delay);
    mDataWritten.notify();

    return tlm::TLM_UPDATED;
  }

  AddressType to_byte_addr(AddressType addr) const {
    return addr * bytes_per_word;
  }

  int to_bytes(int nwords) const {
    return nwords * bytes_per_word;
  }

private:

  bool isDebug() {
    return mSCWrapper.ui_core()->debug_initiator_sockets();
  }

  std::string fmterr_rd_data_start(tlm::tlm_generic_payload const& trans) const {
    std::stringstream os;
    os << "Error: During read data start: "
       << trans.get_response_string()
       << "for address: " << std::hex << trans.get_address();
    return os.str();
  }

  std::string fmterr_wr_rsp_start(tlm::tlm_generic_payload const& trans) const {
    std::stringstream os;
    os << "Error: During write response start: "
       << trans.get_response_string()
       << "for address: " << std::hex << trans.get_address();
    return os.str();
  }

  void log_beginRead(AddressType addr, int nwords) const {
    std::stringstream os;
    os << "Read request received, address = 0x" << std::hex << addr
       << ", nwords = " << nwords;
    std::cout << os.str() << std::endl;
  }

  void log_endRead(unsigned char* data, int nwords) const {
    std::stringstream os;
    os << "End Read request received!";
    std::cout << os.str() << std::endl;
  }

  void log_beginWrite(AddressType addr, unsigned char const* data, int nwords) const {
    std::stringstream os;
    os << "Write request received, address = 0x" << std::hex << addr
       << ", nwords = " << nwords
       << ", data =";
    for(int i=0; i < nwords * (data_width / 8); i++) {
      os << " 0x" << std::hex << (int)data[i];
    }
    std::cout << os.str() << std::endl;
  }

  void log_endWrite(unsigned char const* data, int nwords) const {
    std::stringstream os;
    os << "End Write request received!";
    std::cout << os.str() << std::endl;
  }

  void log_dbg_access(AddressType addr, unsigned char* data, int nwords,
                      bool read) const {
    std::stringstream os;
    os << "Debug request received, address = 0x" << std::hex << addr
       << ", nwords = " << nwords << "is_read: " << read;
    std::cout << os.str() << std::endl;
  }

  void log_start_transaction(tlm::tlm_command cmd, AddressType addr,
                             unsigned char* buf, int nbytes, sc_time& delay) const {
    std::stringstream os;
    os << "Create " << cmd << " Transaction @" << sc_time_stamp()
       << ", address: " << std::hex << addr;
    std::cout << os.str() << std::endl;
  }

  void log_on_rd_addr_end(tlm::tlm_generic_payload& trans, sc_time& delay) const {
    std::stringstream os;
    os << "@" << sc_time_stamp() << " + " << delay
       << ": Read address END for address: 0x"
       << std::hex << trans.get_address();
    std::cout << os.str() << std::endl;
  }

  void log_on_rd_data_start(tlm::tlm_generic_payload& trans, sc_time& delay,
                            bool isLast) const {
    std::stringstream os;
    os << "@" << sc_time_stamp() << " + " << delay << ": data read";
    std::cout << os.str() << std::endl;
  }

  void log_on_wr_addr_end(tlm::tlm_generic_payload& trans, sc_time& delay) const {
    std::stringstream os;
    os << "@" << sc_time_stamp() << " + " << delay
       << ": Write address end for address: 0x"
       << std::hex << trans.get_address();
    std::cout << os.str() << std::endl;
  }

  void log_on_wr_data_end(tlm::tlm_generic_payload& trans, sc_time& delay,
                          bool isLast) const {
    std::stringstream os;
    os << "@" << sc_time_stamp() << " + " << delay
       << ": Write data end for address: 0x"
       << std::hex << trans.get_address();
    std::cout << os.str() << std::endl;
  }

  void log_on_wr_rsp_start(tlm::tlm_generic_payload& trans, sc_time& delay) {
    std::stringstream os;
    os << "@" << sc_time_stamp() << " + " << delay
       << ": Write response start for address: 0x"
       << std::hex << trans.get_address();
    std::cout << os.str() << std::endl;
  }

  std::string get_port_name(std::string portname) const {
    auto pos = portname.find_last_of('.');
    if (pos != std::string::npos) {
      portname = portname.substr(pos + 1);
    }
    return portname;
  }

private:

  static int const bytes_per_word = (data_width / 8);

  struct DataPacket {
    AddressType                 address;
    std::vector<unsigned char>  data;
    unsigned                    nbytes;
    sc_time                     trntime;
  };


  nCheckers::SCWrapperBase&     mSCWrapper;
  std::string                   mPortName;
  sc_core::sc_time              mClockPeriod;
  nCheckers::QuantumKeeperBase* mQuantumKeeper = nullptr;

  DataPacket    mActiveReq;

  sc_event      mDataRecvd;
  sc_event      mDataWritten;
};

#endif // INCLUDED_VAR_LATENCY_IA_TLM2_FT_AXI_ADAPTER_H__
