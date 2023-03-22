/*
-- Multi-threaded example testing the semaphore.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


const int M = 3; // # contexts

volatile int finish = 0;
volatile bool start = 0;

void work() property(isr)
{
#if __chess__
    while(!start) ;
#endif
    mtx_acquire();
    finish++;  // read-modify-write of a global variable is an example
               // of a critical section, requiring mutual exclusion
    mtx_release();
}

#ifdef __chess__
extern char chess_storage(DMb) _sp_start_DMb;
#else
char _sp_start_DMb; // dummy;
#endif

int main()
{
    for (int i=0; i<M; i++) {
        set_flow_void(i+1, work, &_sp_start_DMb+(i+1)*0x2000);
    }
    start = 1;
    while(finish<M) ;
    chess_report(0);
    return 0;
}
