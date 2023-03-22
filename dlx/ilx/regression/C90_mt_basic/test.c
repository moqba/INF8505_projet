/*
-- Multi-threaded example.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


const int N = 5;
const int M = 3; // # contexts

typedef int T;

T in[M*N];
T out[M*N];

volatile bool start = 0;

void work(chess_stack int ctx) property(isr_with_arguments)
{
#if __chess__
    while(!start) ; // optional, only to have 3 slave threads starting around
                    // the same time and so being active concurrently
                    // (actually interleaved).
#endif

    T* p = out+ctx;
    T* q = in+ctx;
    int j = ctx*N;
    for (int i = 0; i < N; i++) {
        *p = (*q) + i + j;
        p += M;
        q += M;
    }
}

#ifdef __chess__
extern char chess_storage(DMb) _sp_start_DMb;
#else
char _sp_start_DMb; // dummy;
#endif

int main()
{
    for (int i=0; i<M; i++) {
        set_flow_int(i+1, work, &_sp_start_DMb+(i+1)*0x2000, i);
    }
    start = 1;               // slave threads actually start processing
    while(get_activity()) ;  // wait untill all slave threads are done
    for (int i = 0; i < M*N; i++) chess_report(out[i]);
    return 0;
}
