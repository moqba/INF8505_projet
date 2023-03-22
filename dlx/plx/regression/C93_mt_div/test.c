/*
-- Multi-threaded example where 2 threads access same div unit.
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
There is a resource hazard: 2 threads have concurrent division but only one
divider is present. There is a data hazard: the divider takes multiple cylces
to write quotient/remainder result in registers r12/r13. The PCU kills the
instruction in the ID stage, in case of either hazard situation. There a new
opportunity for the instruction 4 cylces later.
*/

volatile bool start = 0;

void work(chess_stack unsigned& a, chess_stack unsigned& b) property(isr_with_arguments)
{
#if __chess__
    while(!start) ;
#endif
    int x = a/b;
    int y = a+b;
    a = x; b = y;
}

#ifdef __chess__
extern char chess_storage(DMb) _sp_start_DMb;
#else
char _sp_start_DMb; // dummy;
#endif


void test_waw(unsigned a, unsigned b, int& c, int& chess_storage(R13) d) {
  c = a/b;
  d = 42;
}


int main() {
    unsigned a, b, c, d;

    a = 300; b = 4;
    set_flow_uintR_uintR(1, work, &_sp_start_DMb+0x2000, a, b);
    c = 53; d = 5;
    set_flow_uintR_uintR(2, work, &_sp_start_DMb+0x4000, c, d);

    start = 1;

    while(get_activity());

#if __chess__
    a = *((volatile unsigned*)(&_sp_start_DMb+0x2000)-1);
    b = *((volatile unsigned*)(&_sp_start_DMb+0x2000)-2);
    c = *((volatile unsigned*)(&_sp_start_DMb+0x4000)-1);
    d = *((volatile unsigned*)(&_sp_start_DMb+0x4000)-2);
#endif

    chess_report(a);
    chess_report(b);
    chess_report(c);
    chess_report(d);

    // test WAW when remainder is produced in r13 but not further used
    {
        int c,d;
        test_waw(0x80000001,0x80000000,c,d);
        chess_report(d);
    }

    return 0;
}
