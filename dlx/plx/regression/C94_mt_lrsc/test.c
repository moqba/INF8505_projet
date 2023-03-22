/*
-- Multi-threaded example.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

const int M = 3; // # contexts

volatile int count = 42;

volatile bool start = 0;

void work() property(isr)
{
#if __chess__
    while(!start) ; // optional, only to have 3 slave threads starting around
                    // the same time and so being active concurrently
                    // (actually interleaved).
#endif

    bool success;
    do {
        int i = load_rsvd(&count);
        i++;
        success = store_cond(&count,i);
    } while (!success);
}

#ifdef __chess__
extern char chess_storage(DMb) _sp_start_DMb;
#else
char _sp_start_DMb; // dummy;
#endif

int main() {
    for (int i=0; i<M; i++) {
        set_flow_void(i+1, work, &_sp_start_DMb+(i+1)*0x2000);
    }
    start = 1;               // slave threads actually start processing
    while(get_activity()) ;  // wait untill all slave threads are done
    chess_report(count);
    return 0;
}
