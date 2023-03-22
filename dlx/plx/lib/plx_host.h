 /*
-- File : plx_host.h
--
-- Contents : Host emulation for the PLX core.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



chess_properties {
    reserved: host_CTX, host_CMD, host_SP, host_PC;
}

namespace plx_primitive {
    volatile int   chess_storage(host_SP)  sp_;
    volatile int   chess_storage(host_PC)  pc_;
    volatile ctxt  chess_storage(host_CTX) ctx_;
    volatile uint1 chess_storage(host_CMD) cmd_;

    promotion ctxt  int_to_ctxt  (int  ) = ctxt(w32);
    promotion uint1 bool_to_uint1(bool ) = uint1(w32);
    promotion bool  uint1_to_bool(uint1) = w32(uint1);

    promotion int get_sr() property(dont_generate) = w32 get_sr_cv();
}

inline void set_flow(int ctx, int pc, int sp) property(dont_generate_native)
{
    while (plx_primitive::uint1_to_bool(plx_primitive::cmd_)) ;

    plx_primitive::pc_  = pc;
    plx_primitive::sp_  = sp;
    plx_primitive::ctx_ = plx_primitive::int_to_ctxt(ctx);
    plx_primitive::cmd_ = plx_primitive::bool_to_uint1(1);
}

inline bool get_cmd_flag() property(dont_generate_native)
{
    return plx_primitive::uint1_to_bool(plx_primitive::cmd_);
}

#define CSIZE_TRUE        ((1<<CSIZE)-1)

inline bool get_activity() property(dont_generate_native)
{
    int e = plx_primitive::get_sr(); // MC | TK | EN15 | ... | EN3 | EN2 | EN1 | EN0
    return (e & (CSIZE_TRUE-1));     // mask 0b001111111111111110 as first thread is emulating host
}

// example parameter bindings

inline void set_flow_void(
    int ctx,
    void (*pc)() property(isr),
    void* sp)                                           property(dont_generate_native)
{
    set_flow(ctx, (int)pc, (int)sp);
}

inline void set_flow_int(
    int ctx,
    void (*pc)(auto int) property(isr_with_arguments),
    void* sp,
    int arg)                                            property(dont_generate_native)
{
    *((volatile int*)sp-1) = arg;
    set_flow(ctx, (int)pc, (int)sp);
}

inline void set_flow_uintR_uintR(
    int ctx,
    void (*pc)(auto unsigned&, auto unsigned&) property(isr_with_arguments),
    void* sp,
    unsigned& arg1, unsigned& arg2)                     property(dont_generate_native)
{
    *((volatile unsigned*)sp-1) = arg1;
    *((volatile unsigned*)sp-2) = arg2;
    set_flow(ctx, (int)pc, (int)sp);
}