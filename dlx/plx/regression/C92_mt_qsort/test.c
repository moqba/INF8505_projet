/*
-- Multi-threaded example where 3 threads have different program flow.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include <stdlib.h>

volatile bool start = 0;


int cmp(const void* a, const void* b) { return *(int*)a > *(int*)b;}
inline void qsort(int* a, int n) { qsort(a, n, sizeof(int), cmp); }

const int N = 5;
const int M = 3; // # contexts

int a[M][N] = { { 0,2,7,0,4 }, { 1,2,7,0,4 }, { 2,442,7,-13,4 } };

void work(chess_stack int ctx) property(isr_with_arguments)
{
#if __chess__
    while(!start) ;
#endif

    qsort(a[ctx],N);
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
    start = 1;
    while(get_activity()) ;
    for (int ctx=0; ctx<M; ctx++) {
        chess_message("sorted array:");
        for(int i=0; i<N; i++) {
            chess_report(a[ctx][i]);
        }
    }
    return 0;
}
