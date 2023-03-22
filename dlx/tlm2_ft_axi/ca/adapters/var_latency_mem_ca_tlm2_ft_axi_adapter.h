#ifndef _VAR_LATENCY_CA_TLM2_FT_AXI_ADAPTER_H_
#define _VAR_LATENCY_CA_TLM2_FT_AXI_ADAPTER_H__

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

#undef DEBUG
#undef dout

#define dout if (mUiCore->debug_initiator_sockets()) std::cout

template <int data_width>
class VarLatency_CA_TLM2_FT_AXI_Adapter : public sc_core::sc_module,
                                          public nCheckers::NMLMemoryIF<data_width> {
   private:
    bool mInWaitStateLastCycle = false;
    nCheckers::SCWrapperBase* mSCWrapper;
    Checkers_uicore* mUiCore;
    sc_core::sc_time mClockPeriod;
    dlx* mModel;
    tlm_utils::peq_with_cb_and_phase<VarLatency_CA_TLM2_FT_AXI_Adapter<data_width>> mInPEQ;
    struct TimedTrnState
    {
        scml2::axi_protocol_state_enum state;
        sc_time t;
        TimedTrnState(scml2::axi_protocol_state_enum s, sc_time tt) : state(s), t(tt) { }
    };
    struct TimedTrnStateCompare
    {
        bool operator () (const TimedTrnState& ob1, const TimedTrnState& ob2) const {
            if (ob1.t > ob2.t) return true;
            return false;
        }
    };
    std::priority_queue<TimedTrnState, std::vector<TimedTrnState>, TimedTrnStateCompare> mTrnStateInPEQ;

    // states corresponding to the write data channel are absent because write-data and address
    // are coming at the same time from the model
    enum TrnStatus {
        TRN_ARRIVED = 0,
        TRN_SENT,
        TRN_ACKED,
        DATA_RECVD,
        WRESP_RECVD,
        TRN_FINISHED
    };
    struct DataPacket {
        AddressType address;
        unsigned char* data;
        bool is_write;
        int nbytes;
        TrnStatus status;
        sc_time trntime;
    };
    std::queue<DataPacket*> mReadAddressQ, mReadDataQ;
    // No queue for write-data, as we are sending both address and data together
    std::queue<DataPacket*> mWriteAddressQ, mWriteRespQ;

   public:
    scml2::ft_initiator_socket<data_width>* mSocket;
    scml2::initiator_port_adaptor* mSocketAdapter;

   public:
    SC_HAS_PROCESS(VarLatency_CA_TLM2_FT_AXI_Adapter);
    VarLatency_CA_TLM2_FT_AXI_Adapter(const sc_module_name& name,
                                      scml2::ft_initiator_socket<data_width>* s,
                                      nCheckers::SCWrapperBase* scptr, dlx* mdl)
        : sc_core::sc_module(name),
          mSocket(s),
          mSCWrapper(scptr),
          mModel(mdl),
          mInPEQ(this, &VarLatency_CA_TLM2_FT_AXI_Adapter<data_width>::in_peq_cb) {
        mSocketAdapter = scml2::initiator_port_adaptor::create("mSocketAdapter", s);
        mUiCore   = mSCWrapper->ui_core();

        SCML2_REGISTER_TIMING_CBK(mSocketAdapter, scml2::RD_ADDR_END, this,
                                  VarLatency_CA_TLM2_FT_AXI_Adapter<data_width>::on_rd_addr_end);
        if (mSocketAdapter->has_data_phase()) {
            SCML2_REGISTER_TIMING_CBK_WITH_ARG(
                mSocketAdapter, scml2::RD_DATA_START, this,
                VarLatency_CA_TLM2_FT_AXI_Adapter<data_width>::on_rd_data_start, false);
            SCML2_REGISTER_TIMING_CBK_WITH_ARG(
                mSocketAdapter, scml2::RD_DATA_LAST_START, this,
                VarLatency_CA_TLM2_FT_AXI_Adapter<data_width>::on_rd_data_start, true);
        }
        SCML2_REGISTER_TIMING_CBK(mSocketAdapter, scml2::WR_ADDR_END, this,
                                  VarLatency_CA_TLM2_FT_AXI_Adapter<data_width>::on_wr_addr_end);
        SCML2_REGISTER_TIMING_CBK_WITH_ARG(
            mSocketAdapter, scml2::WR_DATA_END, this,
            VarLatency_CA_TLM2_FT_AXI_Adapter<data_width>::on_wr_data_end, false);
        SCML2_REGISTER_TIMING_CBK_WITH_ARG(
            mSocketAdapter, scml2::WR_DATA_LAST_END, this,
            VarLatency_CA_TLM2_FT_AXI_Adapter<data_width>::on_wr_data_end, true);
        if (mSocketAdapter->has_wr_rsp()) {
            SCML2_REGISTER_TIMING_CBK(
                mSocketAdapter, scml2::WR_RSP_START, this,
                VarLatency_CA_TLM2_FT_AXI_Adapter<data_width>::on_wr_rsp_start);
        }
    }

    void end_of_elaboration() { mClockPeriod = mSCWrapper->clock_period(); }

    void in_peq_cb(tlm::tlm_generic_payload& trans, const tlm::tlm_phase& /*phase*/)
    {
        scml2::axi_protocol_state_enum proto_state = mTrnStateInPEQ.top().state;
        mTrnStateInPEQ.pop();
        switch (proto_state)
        {
            case scml2::ARREADY:
            {
                dout << sc_time_stamp() << ": ARREADY recieved!!" << std::endl;
                mReadAddressQ.front()->status = TRN_ACKED;
                break;
            }
            case scml2::RVALID_LAST:
            {
                dout << sc_time_stamp() << ": RVALID_LAST recieved!!" << std::endl;
                unsigned char* pData = trans.get_data_ptr();
                DataPacket* dp;
                if (mReadDataQ.size() > 0) {
                    dp = mReadDataQ.front();
                } else {
                    dp = mReadAddressQ.front();
                }
                dp->status = DATA_RECVD;
                assert(dp->data == pData);
                dout << "data read: 0x";
                for(int i=0; i < dp->nbytes; i++) {
                    dout << std::hex << (int)(dp->data)[i];
                }
                dout << std::endl;
                trans.set_data_ptr(0);
                sc_time delay(0, SC_NS);
                mSocketAdapter->update_transaction(trans, delay, scml2::RD_DATA_LAST_END);
                break;
            }
            case scml2::AWREADY:
            {
                dout << sc_time_stamp() << ": AWREADY recieved!!" << std::endl;
                mWriteAddressQ.front()->status = TRN_ACKED;
                sc_time delay(0, SC_NS);
                mSocketAdapter->update_transaction(trans, delay, scml2::WR_DATA_START);
                break;
            }
            case scml2::BVALID:
            {
                dout << sc_time_stamp() << ": BVALID recieved!!" << std::endl;
                trans.set_data_ptr(0);
                DataPacket* dp;
                if (mWriteRespQ.size() > 0) {
                    dp = mWriteRespQ.front();
                } else {
                    dp = mWriteAddressQ.front();
                }
                dp->status = WRESP_RECVD;
                sc_time delay(0, SC_NS);
                mSocketAdapter->update_transaction(trans, delay, scml2::WR_RSP_END);
                break;
            }
            default:
                std::cerr << "###### Error: in_peq_cb called with invalid AXI state: " << proto_state << endl;
        }
    }

    void update_status() {
        mInWaitStateLastCycle = mModel->in_wait_state();
        if (mReadAddressQ.size() > 0) {
            DataPacket* dp = mReadAddressQ.front();
            if (dp->status == TRN_ARRIVED) {
                unsigned char* buf = new unsigned char[dp->nbytes];
                start_transaction(tlm::TLM_READ_COMMAND, dp->address, buf, dp->nbytes);
                dp->data = buf;
                dp->status = TRN_SENT;
            } else if (dp->status >= TRN_ACKED) {
                mReadAddressQ.pop();
                mReadDataQ.push(dp);
                if (mReadAddressQ.size() > 0) {
                    DataPacket* dp = mReadAddressQ.front();
                    unsigned char* buf = new unsigned char[dp->nbytes];
                    start_transaction(tlm::TLM_READ_COMMAND, dp->address, buf, dp->nbytes);
                    dp->data = buf;
                    dp->status = TRN_SENT;
                }
            }
        }
        if (mReadDataQ.size() > 0) {
            DataPacket* dp = mReadDataQ.front();
            if (dp->status == TRN_FINISHED) {
                mReadDataQ.pop();
                delete dp->data;
                delete dp;
            }
        }
        if (mWriteAddressQ.size() > 0) {
            DataPacket* dp = mWriteAddressQ.front();
            if (dp->status == TRN_ARRIVED) {
                start_transaction(tlm::TLM_WRITE_COMMAND, dp->address, dp->data, dp->nbytes);
                dp->status = TRN_SENT;
            } else if (dp->status >= TRN_ACKED) {
                mWriteAddressQ.pop();
                mWriteRespQ.push(dp);
                if (mWriteAddressQ.size() > 0) {
                    DataPacket* dp = mWriteAddressQ.front();
                    start_transaction(tlm::TLM_WRITE_COMMAND, dp->address, dp->data, dp->nbytes);
                    dp->status = TRN_SENT;
                }
            }
        }
        if (mWriteRespQ.size() > 0) {
            DataPacket* dp = mWriteRespQ.front();
            if (dp->status == TRN_FINISHED) {
                mWriteRespQ.pop();
                delete dp->data;
                delete dp;
            }
        }
    }

    nCheckers::MemTrnStatus beginRead(AddressType addr, int nwords, const VBitWrapper&) {
        if (mInWaitStateLastCycle) return nCheckers::TRANS_OK;
        dout << "Read request recieved, address = 0x" << std::hex << addr << ", nwords = " << nwords
             << std::endl;
        const int bytes_per_word = (data_width / 8);
        const int total_bytes = nwords * bytes_per_word;
        auto tr_addr = addr * bytes_per_word;
        DataPacket* dp;
        if (mReadAddressQ.size() > 0 &&
            mReadAddressQ.back()->status == TRN_ARRIVED) {  // later delta-cycles
            dp = mReadAddressQ.back();
        } else {
            dp = new DataPacket();  // first delta cycle
            mReadAddressQ.push(dp);
        }
        dp->address = tr_addr;
        dp->nbytes = total_bytes;
        dp->is_write = false;
        dp->status = TRN_ARRIVED;
        dp->trntime = sc_time_stamp();
        // call to notify begin_read
        mSCWrapper->notify_begin_read_access("p_DMb_ft", dp->address, dp->nbytes);
        return nCheckers::TRANS_OK;
    }

    nCheckers::MemTrnStatus endRead(unsigned char* data, int nwords) {
        dout << "End Read request recieved!\n";
        DataPacket* dp;
        if (mReadDataQ.size() > 0) {
            dp = mReadDataQ.front();
        } else {
            dp = mReadAddressQ.front();
        }
        if (dp->status == DATA_RECVD) {
            memcpy(data, dp->data, dp->nbytes);
            dp->status = TRN_FINISHED;
            // call to notify end read
            auto consumed_time = sc_time_stamp().value() - (dp->trntime).value();
            auto cycles = (unsigned long long) ((consumed_time + mClockPeriod.value() - 1) / mClockPeriod.value());
            mSCWrapper->notify_end_read_access("p_DMb_ft", dp->address, dp->data, dp->nbytes, cycles);
        } else {
            mModel->insert_wait_this_cycle();  // gate the status updates this cycle
            dout << "Read: inserting wait request!!\n";
        }
        return nCheckers::TRANS_OK;
    }

    nCheckers::MemTrnStatus beginWrite(AddressType addr, const unsigned char* data, int nwords, const VBitWrapper&) {
        if (mInWaitStateLastCycle) return nCheckers::TRANS_OK;
        dout << "Write request recieved, address = 0x" << std::hex << addr
             << ", nwords = " << nwords 
             << ", data = 0x";
        dout << std::dec << std::endl;
        const int bytes_per_word = (data_width / 8);
        const int total_bytes = nwords * bytes_per_word;
        auto tr_addr = addr * bytes_per_word;
        DataPacket* dp;
        if (mWriteAddressQ.size() > 0 && mWriteAddressQ.back()->status == TRN_ARRIVED) {
            dp = mWriteAddressQ.back();
            memcpy (dp->data, data, total_bytes);
        } else {
            dp = new DataPacket();
            mWriteAddressQ.push(dp);
            unsigned char* buf = new unsigned char[total_bytes];
            memcpy (buf, data, total_bytes);
            dp->data = buf;
        }
        for(int i=0; i < total_bytes; i++) {
            dout << std::hex << (int)(dp->data)[i];
        }
        dp->address = tr_addr;
        dp->nbytes = total_bytes;
        dp->is_write = true;
        dp->status = TRN_ARRIVED;
        dp->trntime = sc_time_stamp();
        // call to notify begin write
        mSCWrapper->notify_begin_write_access("p_DMb_ft", dp->address, dp->data, dp->nbytes);
        return nCheckers::TRANS_OK;
    }

    nCheckers::MemTrnStatus endWrite(const unsigned char* data, int nwords) {
        dout << "End Write request recieved!\n";
        DataPacket* dp;
        if (mWriteRespQ.size() > 0) {
            dp = mWriteRespQ.front();
        } else {
            dp = mWriteAddressQ.front();
        }
        if (dp->status == WRESP_RECVD) {
            dp->status = TRN_FINISHED;
            // call to notify end write
            auto consumed_time = sc_time_stamp().value() - (dp->trntime).value();
            auto cycles = (unsigned long long) ((consumed_time + mClockPeriod.value() - 1) / mClockPeriod.value());
            mSCWrapper->notify_end_write_access("p_DMb_ft", dp->address, dp->data, dp->nbytes, cycles);
        } else {
            mModel->insert_wait_this_cycle();  // gate the status updates this cycle
            dout << "Write: inserting wait request!!\n";
        }
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

    void start_transaction(tlm::tlm_command cmd, AddressType addr, unsigned char* buf, int nbytes) {
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
        sc_time delay(0, SC_NS);
        mSocketAdapter->send_transaction(payload, delay);
    }

    tlm::tlm_sync_enum on_rd_addr_end(tlm::tlm_generic_payload& trans, sc_time& delay) {
        dout << "@" << sc_time_stamp() << " + " << delay << ": Read address END for address: 0x"
             << std::hex << trans.get_address() << std::endl
             << std::dec;
        tlm::tlm_phase phase = scml2::FT_TIMING;
        mInPEQ.notify(trans, phase, delay);
        mTrnStateInPEQ.emplace(scml2::ARREADY, sc_time_stamp() + delay);
        return tlm::TLM_ACCEPTED;
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
            tlm::tlm_phase phase = scml2::FT_TIMING;
            mInPEQ.notify(trans, phase, delay);
            mTrnStateInPEQ.emplace(scml2::RVALID_LAST, sc_time_stamp() + delay);
            return tlm::TLM_ACCEPTED;
        } else {
            return tlm::TLM_UPDATED;
        }
    }

    tlm::tlm_sync_enum on_wr_addr_end(tlm::tlm_generic_payload& trans, sc_time& delay) {
        dout << "@" << sc_time_stamp() << " + " << delay << ": Write address end for address: 0x"
             << std::hex << trans.get_address() << std::endl
             << std::dec;
        tlm::tlm_phase phase = scml2::FT_TIMING;
        mInPEQ.notify(trans, phase, delay);
        mTrnStateInPEQ.emplace(scml2::AWREADY, sc_time_stamp() + delay);
        return tlm::TLM_ACCEPTED;
    }

    tlm::tlm_sync_enum on_wr_data_end(tlm::tlm_generic_payload& trans, sc_time& delay, bool isLast)
    {
        dout << "@" << sc_time_stamp() << " + " << delay << ": Write data end for address: 0x" << std::hex << trans.get_address() << std::endl << std::dec;
        /*
        if (isLast) {
            tlm::tlm_phase phase = scml2::FT_TIMING;
            mInPEQ.notify(trans, phase, delay);
            mTrnStateInPEQ.emplace(scml2::WREADY_LAST, sc_time_stamp() + delay);
        }*/
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
        tlm::tlm_phase phase = scml2::FT_TIMING;
        mInPEQ.notify(trans, phase, delay);
        mTrnStateInPEQ.emplace(scml2::BVALID, sc_time_stamp() + delay);
        return tlm::TLM_ACCEPTED;
    }
};

#endif
