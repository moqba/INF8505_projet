/*
-- File : dlx_io.p
--
-- Contents : Definition of IO interface that targets 32 bit external memory.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/




/*
   This IO interface maps the 8, 16 and 32 bit memory accesses of DLX onto a 32
   bit wide external memory XDM.

   Load operations:

   - w32 load operations are passed directly to XDM.

   - For w08 and w16 load operations, the w32 value in XDM that contains the
     requested w08 or w16 address is loaded and the requested w08 or w16 part
     is extracted.

   - Note that when a sequence of w08 values from successive addresses is
     loaded, the w32 values that are loaded from XDM could be buffered and
     reused, so that only one w32 load is needed for every four w08 loads. This
     optimization reduces XDM traffic but costs decoding logic. It is not
     implemented in this memory interface.

   Store operations:

   - In order to store a w08 or w16 value, a read-merge-write operation must be
     executed:
       + the w32 value located at the store address must be loaded from XDM,
       + the w08 or w16 store value must be merged with the loaded w32 value,
       + the resulting w32 value must be stored back to XDM.
     While this basic scheme is easy to implement in an IO interface, it is not
     efficient; especially when a sequence of stores to successive addresses is
     executed (as is a memcpy() of strcpy() function).

   - In this IO interface, a store buffer is used. The buffer consists of a w32
     data register, sb_data, to which w08, w16 and w32 values are added. The
     address of the most recent store is saved in register sb_addr. The 4 bits
     of the sb_valid register indicate which parts of sb_data have been
     updated.

   - Because the IO interface can introduce wait cycles, the result of a load
     that may have been initiated in the cycle before a wait cycle has to be
     buffered. The wait buffer is formed by the ld_data register and is
     controlled by ld_req_ff.
   
   - Note that a memory to memory path exists in this IO interface. When
     sb_merge_ff is set, the xdm_rd value is merged with sb_data and the result
     is assigned to xdm_wr. Since there is only multiplexing on this path, this
     is considered as acceptable.
   
*/


#include "memsize.h"

io_interface banks (DMb)
{
    mem XDM [XDM_SIZE]<w32,addr> access {
    xdm_ld: xdm_rd `1` = XDM[xdm_addr `0`] `1`;
    xdm_st: XDM[xdm_addr `0`] `1` = xdm_wr `0`;
    };

    reg ld_offset<uint2_t>;

    // load wait buffer
    reg ld_data<w32>;
    reg ld_req_ff<uint1>;      // set in data stage of load 

    // store buffer sb_
    reg sb_valid<uint4_t>;     // 4 valid bits, one per byte
    reg sb_addr<addr>;
    reg sb_data<w32>;

    reg sb_merge_ff<uint1_t>;  // set when store requres a merge
    reg sb_load_ff<uint1_t>;   // set when ld requires a merge 
    reg sb_bypass_ff<uint1_t>; // set when st-ld bypass is active

    process process_result() {
        DEBUG_PRINT("RESULT:  sb_bypass_ff=%d, sb_load_ff=%d, ld_req_ff=%d, sb_valid=%x, ld_offset=%d",sb_bypass_ff,sb_load_ff,ld_req_ff,sb_valid,ld_offset);
        DEBUG_PRINT("         sb_addr=%d, sb_data=%x, ld_data=%x, xdm_rd=%x",sb_addr,sb_data,ld_data,xdm_rd);
        if (ld_req_ff && in_wait_cycle()) // capture result of previous load
            ld_data = xdm_rd;
        w32 td = 0;
        if (sb_bypass_ff)
            td = sb_data;
        else if (sb_load_ff) {  // merge loaded and buffered parts
            td[31:24] = sb_valid[3] ? sb_data[31:24] : xdm_rd[31:24];
            td[23:16] = sb_valid[2] ? sb_data[23:16] : xdm_rd[23:16];
            td[15: 8] = sb_valid[1] ? sb_data[15: 8] : xdm_rd[15: 8];
            td[ 7: 0] = sb_valid[0] ? sb_data[ 7: 0] : xdm_rd[ 7: 0];
        }
        else if (ld_req_ff)
            td = xdm_rd;
        else // after wait cycle 
            td = ld_data;
        switch (ld_offset) { // extract requested w08 or w16 field
        case 0: dmw_rd=td; dmh_rd=td[31:16]; dmb_rd=td[31:24]; break;
        case 1: dmw_rd=td; dmh_rd=td[31:16]; dmb_rd=td[23:16]; break;
        case 2: dmw_rd=td; dmh_rd=td[15: 0]; dmb_rd=td[15: 8]; break;
        case 3: dmw_rd=td; dmh_rd=td[15: 0]; dmb_rd=td[ 7: 0]; break;
        }
    }

    process process_request() {

        if (ld_dmw) DEBUG_PRINT("REQUEST: lw %d",dm_addr);
        if (ld_dmh) DEBUG_PRINT("REQUEST: lh %d",dm_addr);
        if (ld_dmb) DEBUG_PRINT("REQUEST: lb %d",dm_addr);
        if (st_dmw) DEBUG_PRINT("REQUEST: sw %d %x",dm_addr,dmw_wr);
        if (st_dmh) DEBUG_PRINT("REQUEST: sh %d %x",dm_addr,dmh_wr);
        if (st_dmb) DEBUG_PRINT("REQUEST: sb %d %x",dm_addr,dmb_wr);

        addr taddr    = dm_addr[18:2];
        uint2_t toffs = dm_addr[1:0];
        xdm_addr = taddr;

        uint1_t same_address = taddr==sb_addr; 
        uint1_t partial_pending_write =
            sb_valid[0] | sb_valid[1] | sb_valid[2] | sb_valid[3];
        uint1_t full_pending_write    =
            sb_valid[0] & sb_valid[1] & sb_valid[2] & sb_valid[3];
        uint1_t buffer_empty = !partial_pending_write;

        // process load request
        uint1_t tld = ld_dmb | ld_dmh | ld_dmw; // temp XDM load enable
        uint1_t fld = 0; // force load in stall cycle
        sb_bypass_ff = 0;
        sb_load_ff = 0;
        ld_offset = toffs;
        DEBUG_PRINT("         tld=%d, taddr;%d, toffs=%d, same_address=%d",tld,taddr,toffs,same_address);
        DEBUG_PRINT("         partial_pending_write=%d, full_pending_write=%d",partial_pending_write,full_pending_write);
        if (tld && same_address & partial_pending_write) { 
            // the store buffer potentially contains relevant bytes
            // -1- test if requested load is fully present in store buffer
            uint1_t buffer_overlap =
                ld_dmw & full_pending_write
              | ld_dmh & (toffs == 0 & sb_valid[3:2] == "11" |
                          toffs == 2 & sb_valid[1:0] == "11")
              | ld_dmb & (toffs == 0 & sb_valid[3] |
                          toffs == 1 & sb_valid[2] |
                          toffs == 2 & sb_valid[1] |
                          toffs == 3 & sb_valid[0] );
            // -2- test if requested load and store buffer are fully disjoint
            uint1_t no_buffer_overlap =
                ld_dmh & (toffs == 0 & sb_valid[3:2] == "00" |
                          toffs == 2 & sb_valid[1:0] == "00")
              | ld_dmb & (toffs == 0 & !sb_valid[3] |
                          toffs == 1 & !sb_valid[2] |
                          toffs == 2 & !sb_valid[1] |
                          toffs == 3 & !sb_valid[0] );
            DEBUG_PRINT("          ld - buffer_overlap=%d, no_buffer_overlap=%d",buffer_overlap,no_buffer_overlap);
            if (buffer_overlap) { // activate bypass from store buffer to load
                tld = 0;
                sb_bypass_ff = 1;
            }
            else if (no_buffer_overlap) // proceed as if normal load
                ;
            else if (sb_load_ff)   // nothing to be done 
                tld = 0;
            else  {  // partial overlap, requires merge of store buffer and XDM 
                DEBUG_PRINT("         ld - partial overlap requires merge");
                xdm_addr = sb_addr;
                fld = 1;
                insert_wait_this_cycle();
                sb_load_ff = 1;
            }
        }

        // process store request
        uint1_t tst = st_dmb | st_dmh | st_dmw; // temp XDM store enable
        uint1_t add_to_buffer = 0;
        sb_merge_ff = 0;
        uint4_t tvalid = sb_valid;
        if (tst) {
            if (buffer_empty) {
                DEBUG_PRINT("         st - buffer empty");
                sb_addr = taddr;
                add_to_buffer = 1;
                tst = 0;
            }
            else if (same_address) {
                DEBUG_PRINT("         st - same address -> add to buffer");
                tst = 0;
                add_to_buffer = 1;
            }
            else if (sb_merge_ff) {
                DEBUG_PRINT("         st - sb_merge_ff set -> merge load and buffer");
                // merge buffer to loaded word 
                w32 tmerge;
                tmerge[31:24] = sb_valid[3] ? sb_data[31:24] : xdm_rd[31:24];
                tmerge[23:16] = sb_valid[2] ? sb_data[23:16] : xdm_rd[23:16];
                tmerge[15: 8] = sb_valid[1] ? sb_data[15: 8] : xdm_rd[15: 8];
                tmerge[ 7: 0] = sb_valid[0] ? sb_data[ 7: 0] : xdm_rd[ 7: 0];
                // store merged value
                xdm_addr = sb_addr;
                xdm_wr   = tmerge;    // beware of xdm_rd to xdm_wr path
                // initiate buffer with new store
                tvalid = "0000";
                sb_addr = taddr;
                add_to_buffer = 1;
                    
            }
            else if (full_pending_write) {
                DEBUG_PRINT("         st - full pending write -> store buffer");
                // store current buffer 
                xdm_addr = sb_addr;
                xdm_wr   = sb_data;
                // initiate buffer with new store
                tvalid = "0000";
                sb_addr = taddr;
                add_to_buffer = 1;
            }
            else if (partial_pending_write) {  // initiate load 
                DEBUG_PRINT("         st - partial pending write -> initiate merge");
                tst = 0;
                fld  = 1;
                xdm_addr = sb_addr;
                insert_wait_this_cycle();
                sb_merge_ff = 1;
            }
        }

        xdm_st = tst && !in_wait_cycle();
        xdm_ld = tld && !in_wait_cycle() || fld;
        ld_req_ff = tld && !in_wait_cycle();
        
        if (add_to_buffer) {  
            DEBUG_PRINT("         add to buffer");
            w32 tdata = sb_data;
            if (st_dmw | ld_dmw) {
                tdata = dmw_wr;
                tvalid |= "1111";
            }
            else if (st_dmh | ld_dmh) {
                if (toffs == 0) {
                    tdata[31:16] = dmh_wr;
                    tvalid |=  "1100";
                } else {
                    tdata[15:0] = dmh_wr;
                    tvalid |=  "0011";
                }
            }
            else if (st_dmb | ld_dmb) {
                if (toffs == 0) {
                    tdata[31:24] = dmb_wr;
                    tvalid |= "1000";
                }
                else if (toffs == 1) {
                    tdata[23:16] = dmb_wr;
                    tvalid |= "0100";
                }
                else if (toffs == 2) {
                    tdata[15:8] = dmb_wr;
                    tvalid |= "0010";
                }
                else if (toffs == 3) {
                    tdata[7:0] = dmb_wr;
                    tvalid |= "0001";
                }
            }
            sb_data = tdata;
            sb_valid = tvalid;
        }
    }

    void dbg_access_DMb(unsigned a, w08& v, bool read)
    {
        unsigned aa = a >> 2;
        w32 w;
        if (read) {
            dbg_access_XDM(aa, w, 1); 
            switch (a[1:0]) {
            case 0 : v = w[31:24]; break; // big endian
            case 1 : v = w[23:16]; break;
            case 2 : v = w[15:8];  break;
            case 3 : v = w[7:0];   break;
            }
        } else {
            dbg_access_XDM(aa, w, 1); // read
            switch (a[1:0]) {
            case 0 : w[31:24] = v; break;
            case 1 : w[23:16] = v; break;
            case 2 : w[15:8]  = v; break;
            case 3 : w[7:0]   = v; break;
            }
            dbg_access_XDM(aa, w, 0); // write
        }
    }
}

