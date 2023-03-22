#ifndef _VAR_LATENCY_IA_TLM2_FT_AXI_ADAPTER_H_
#define _VAR_LATENCY_IA_TLM2_FT_AXI_ADAPTER_H_

#include <systemc>
#include <scml.h>
#include <scml2.h>
#include <tlm.h>
#include <tlm_utils/peq_with_cb_and_phase.h>
#include "AddressType.h"

#include "checkers_nml_memory_if.h"
#include "checkers_sc_wrapper_base.h"

#include "Mdl_dlx.h"

#include <stdlib.h>

#undef dout

#define dout if (mUiCore->debug_initiator_sockets()) std::cout

template <int data_width>
class VarLatency_IA_TLM2_FT_AXI_Adapter : public sc_core::sc_module,
                                          public nCheckers::NMLMemoryIF<data_width> {
   private:
    nCheckers::SCWrapperBase* mSCWrapper;
    Checkers_uicore* mUiCore;
    sc_core::sc_time mClockPeriod;
    dlx* mModel;
    nCheckers::QuantumKeeperBase *mQuantumKeeper = nullptr;
    struct DataPacket {
        AddressType address;
        unsigned char* data;
        int nbytes;
        sc_time trntime;
    };
    DataPacket mActiveReq;
    /*
    enum TrnStatus {
        TRN_ARRIVED = 0,
        TRN_SENT,
        TRN_ACKED,
        DATA_RECVD,
        WRESP_RECVD,
        TRN_FINISHED
    };
    std::queue<DataPacket*> mIncomingQ;
    */
    sc_event mDataRecvd, mDataWritten;

   public:
    scml2::ft_initiator_socket<data_width>* mSocket;
    scml2::initiator_port_adaptor* mSocketAdapter;

   public:
    SC_HAS_PROCESS(VarLatency_IA_TLM2_FT_AXI_Adapter);
    VarLatency_IA_TLM2_FT_AXI_Adapter(const sc_module_name& name,
                                      scml2::ft_initiator_socket<data_width>* s,
                                      nCheckers::SCWrapperBase* scptr, dlx* mdl)
        : sc_core::sc_module(name),
          mSocket(s),
          mSCWrapper(scptr),
          mModel(mdl) {
        mSocketAdapter = scml2::initiator_port_adaptor::create("mSocketAdapter", s);
        mUiCore   = mSCWrapper->ui_core();

        SCML2_REGISTER_TIMING_CBK(mSocketAdapter, scml2::RD_ADDR_END, this,
                                  VarLatency_IA_TLM2_FT_AXI_Adapter<data_width>::on_rd_addr_end);
        if (mSocketAdapter->has_data_phase()) {
            SCML2_REGISTER_TIMING_CBK_WITH_ARG(
                mSocketAdapter, scml2::RD_DATA_START, this,
                VarLatency_IA_TLM2_FT_AXI_Adapter<data_width>::on_rd_data_start, false);
            SCML2_REGISTER_TIMING_CBK_WITH_ARG(
                mSocketAdapter, scml2::RD_DATA_LAST_START, this,
                VarLatency_IA_TLM2_FT_AXI_Adapter<data_width>::on_rd_data_start, true);
        }
        SCML2_REGISTER_TIMING_CBK(mSocketAdapter, scml2::WR_ADDR_END, this,
                                  VarLatency_IA_TLM2_FT_AXI_Adapter<data_width>::on_wr_addr_end);
        SCML2_REGISTER_TIMING_CBK_WITH_ARG(
            mSocketAdapter, scml2::WR_DATA_END, this,
            VarLatency_IA_TLM2_FT_AXI_Adapter<data_width>::on_wr_data_end, false);
        SCML2_REGISTER_TIMING_CBK_WITH_ARG(
            mSocketAdapter, scml2::WR_DATA_LAST_END, this,
            VarLatency_IA_TLM2_FT_AXI_Adapter<data_width>::on_wr_data_end, true);
        if (mSocketAdapter->has_wr_rsp()) {
            SCML2_REGISTER_TIMING_CBK(
                mSocketAdapter, scml2::WR_RSP_START, this,
                VarLatency_IA_TLM2_FT_AXI_Adapter<data_width>::on_wr_rsp_start);
        }
    }

    void end_of_elaboration() {
        mClockPeriod = mSCWrapper->clock_period();
        mQuantumKeeper = mSCWrapper->get_quantumkeeper();
    }

    nCheckers::MemTrnStatus beginRead(AddressType addr, int nwords, unsigned char*, const VBitWrapper&) {
        dout << "Read request recieved, address = 0x" << std::hex << addr << ", nwords = " << nwords
             << std::endl;
        const int bytes_per_word = (data_width / 8);
        const int total_bytes = nwords * bytes_per_word;
        auto tr_addr = addr * bytes_per_word;
        sc_time local_time = mQuantumKeeper->get_local_time();
        mActiveReq.address = tr_addr;
        mActiveReq.data = new unsigned char[total_bytes];
        mActiveReq.nbytes = total_bytes;
        mActiveReq.trntime = mQuantumKeeper->get_current_time();
        mSCWrapper->notify_begin_read_access("p_DMb_ft", tr_addr, total_bytes);
        start_transaction(tlm::TLM_READ_COMMAND, tr_addr, mActiveReq.data, total_bytes, local_time);
        return nCheckers::TRANS_OK;
    }

    nCheckers::MemTrnStatus endRead(unsigned char* data, int nwords) {
        dout << "End Read request recieved!\n";
        const int bytes_per_word = (data_width / 8);
        const int total_bytes = nwords * bytes_per_word;
        // wait for event
        wait(mDataRecvd);
        memcpy(data, mActiveReq.data, total_bytes);
        auto consumed_time = mQuantumKeeper->get_current_time().value() - mActiveReq.trntime.value();
        auto cycles = (unsigned long long) ((consumed_time + mClockPeriod.value() - 1) / mClockPeriod.value());
        mSCWrapper->notify_end_read_access("p_DMb_ft", mActiveReq.address, mActiveReq.data, mActiveReq.nbytes, cycles);
        delete mActiveReq.data;
        return nCheckers::TRANS_OK;
    }

    nCheckers::MemTrnStatus beginWrite(AddressType addr, const unsigned char* data, int nwords, const VBitWrapper&) {
        dout << "Write request recieved, address = 0x" << std::hex << addr
             << ", nwords = " << nwords 
             << ", data = 0x";
        dout << std::dec << std::endl;
        const int bytes_per_word = (data_width / 8);
        const int total_bytes = nwords * bytes_per_word;
        auto tr_addr = addr * bytes_per_word;
        unsigned char tmp;
        mActiveReq.address = tr_addr;
        mActiveReq.data = new unsigned char[total_bytes];
        mActiveReq.nbytes = total_bytes;
        mActiveReq.trntime = mQuantumKeeper->get_current_time();
        memcpy(mActiveReq.data, data, total_bytes);
        for(int i=0; i < total_bytes; i++) {
            dout << std::hex << (int)data[i];
        }
        sc_time local_time = mQuantumKeeper->get_local_time();
        mSCWrapper->notify_begin_write_access("p_DMb_ft", tr_addr, mActiveReq.data, total_bytes);
        start_transaction(tlm::TLM_WRITE_COMMAND, tr_addr, mActiveReq.data, total_bytes, local_time);
        return nCheckers::TRANS_OK;
    }

    nCheckers::MemTrnStatus endWrite(const unsigned char* data, int nwords) {
        dout << "End Write request recieved!\n";
        wait(mDataWritten);
        auto consumed_time = mQuantumKeeper->get_current_time().value() - mActiveReq.trntime.value();
        auto cycles = (unsigned long long) ((consumed_time + mClockPeriod.value() - 1) / mClockPeriod.value());
        mSCWrapper->notify_end_write_access("p_DMb_ft", mActiveReq.address, mActiveReq.data, mActiveReq.nbytes, cycles);
        delete mActiveReq.data;
        return nCheckers::TRANS_OK;
    }

    void dbg_access(AddressType addr, unsigned char* data, int nwords, bool read) {
        //dout << "Debug request recieved, address = 0x" << std::hex << addr << ", nwords = " << nwords
        //     << "is_read: " << read << std::endl;
        const int bytes_per_word = (data_width / 8);
        const int total_bytes = nwords * bytes_per_word;
        auto tr_addr = addr * bytes_per_word;
        if (read) {
            mSocketAdapter->read_debug(tr_addr, data, total_bytes);
        } else {
            mSocketAdapter->write_debug(tr_addr, data, total_bytes);
        }
    }

    void start_transaction(tlm::tlm_command cmd, AddressType addr, unsigned char* buf, int nbytes, sc_time& delay) {
        dout << "Create " << cmd << " Transaction @" << sc_time_stamp() << ", address: " << std::hex
             << addr << std::dec << std::endl;

        tlm::tlm_generic_payload& payload = mSocketAdapter->alloc_and_init_trans(cmd);
        payload.set_address(addr);
        // set allocated data pointter to transaction payload
        payload.set_data_ptr(buf);
        payload.set_data_length(nbytes);
        payload.set_streaming_width(nbytes);
        payload.set_byte_enable_ptr(0);
        payload.set_byte_enable_length(0);

        // send transaaction through port adaptor
        mSocketAdapter->send_transaction(payload, delay);
    }

    tlm::tlm_sync_enum on_rd_addr_end(tlm::tlm_generic_payload& trans, sc_time& delay) {
        dout << "@" << sc_time_stamp() << " + " << delay << ": Read address END for address: 0x"
             << std::hex << trans.get_address() << std::endl
             << std::dec;
        return tlm::TLM_UPDATED;
    }

    tlm::tlm_sync_enum on_rd_data_start(tlm::tlm_generic_payload& trans, sc_time& delay,
                                        bool isLast) {
        if (isLast) {
            bool trans_status = trans.is_response_ok();
            if (!trans_status) {
                std::cerr << "########### Error during read data start!: "<< trans.get_response_string()
                          << "for address: " << std::hex << trans.get_address() << std::endl << std::dec;
            }
            dout << "@" << sc_time_stamp() << " + " << delay << ": data read " << std::endl;
            assert(mActiveReq.data == trans.get_data_ptr());
            trans.set_data_ptr(0);
            mQuantumKeeper->set(delay);
            mDataRecvd.notify();
            return tlm::TLM_UPDATED;
        } else {
            return tlm::TLM_UPDATED;
        }
    }

    tlm::tlm_sync_enum on_wr_addr_end(tlm::tlm_generic_payload& trans, sc_time& delay) {
        dout << "@" << sc_time_stamp() << " + " << delay << ": Write address end for address: 0x"
             << std::hex << trans.get_address() << std::endl
             << std::dec;
        return tlm::TLM_UPDATED;
    }

    tlm::tlm_sync_enum on_wr_data_end(tlm::tlm_generic_payload& trans, sc_time& delay, bool isLast)
    {
        dout << "@" << sc_time_stamp() << " + " << delay << ": Write data end for address: 0x" << std::hex << trans.get_address() << std::endl << std::dec;
        return tlm::TLM_UPDATED;
    }

    tlm::tlm_sync_enum on_wr_rsp_start(tlm::tlm_generic_payload& trans, sc_time& delay) {
        dout << "@" << sc_time_stamp() << " + " << delay << ": Write response start for address: 0x"
             << std::hex << trans.get_address() << std::endl
             << std::dec;
        bool trans_status = trans.is_response_ok();
        if (!trans_status) {
            std::cerr << "########## Error during write response start!: " << trans.get_response_string()
                      << "for address: " << std::hex << trans.get_address() << std::endl << std::dec;
        }
        trans.set_data_ptr(0);
        mQuantumKeeper->set(delay);
        mDataWritten.notify();
        return tlm::TLM_UPDATED;
    }
};

#endif
