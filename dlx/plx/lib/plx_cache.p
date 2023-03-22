/*
-- File : plx_cache.p
--
-- Contents : Definition of the PLX IO interface.
--
-- Copyright (c) 2014-2017 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

//#define     PRINT_CACHE
#ifdef        PRINT_CACHE
#define DEBUG_PRINT_CACHE(FMT,ARGS...) DEBUG_PRINT("cache: "FMT, ##ARGS)
#else
#define DEBUG_PRINT_CACHE(FMT,ARGS...)
#endif

// mimic cache timing:
// - cache hit/miss on output bit 'miss'
// - temporarily leave scheduling threads on output bit vector 'suspend'

// cache line size = 16 bytes
// tag map size = 4 (lines)
// move queue size = 1 (requests)

const uint16_t c_move_time = 64;

// addr
uint28_t  get_tag(addr a) { return a[31:4]; }
//uint4_t get_ofs(addr a) { return a[ 3:0]; }

// tag
uint28_t get_tag(tag a) { return a[28: 1]; }
uint1_t  get_val(tag a) { return a[    0]; }
uint16_t get_age(tag a) { return a[44:29]; }
tag set_tag(tag a, uint28_t v) { tag r = a; r[28: 1] = v; return r; }
tag set_val(tag a, uint1_t  v) { tag r = a; r[    0] = v; return r; }
tag set_age(tag a, uint16_t v) { tag r = a; r[44:29] = v; return r; }

// move
uint28_t get_tag(w64 a) { return a[27: 0]; }
uint16_t get_age(w64 a) { return a[44:29]; }
uint2_t  get_idx(w64 a) { return a[46:45]; }
w64 set_tag(w64 a, uint28_t v) { w64 r = a; r[27: 0] = v; return r; }
w64 set_age(w64 a, uint16_t v) { w64 r = a; r[44:29] = v; return r; }
w64 set_idx(w64 a, uint2_t  v) { w64 r = a; r[46:45] = v; return r; }

uint3_t lookup(uint28_t t, v4tag tags) {
    uint3_t r = 7; // -1
    if      ((t == get_tag(tags[0])) && get_val(tags[0])) r = 0;
    else if ((t == get_tag(tags[1])) && get_val(tags[1])) r = 1;
    else if ((t == get_tag(tags[2])) && get_val(tags[2])) r = 2;
    else if ((t == get_tag(tags[3])) && get_val(tags[3])) r = 3;
    return r;
}


#ifdef PAGE0
    // first entry is not a flush candidate
    const uint32_t t0 = 1;
#else
    const uint32_t t0 = 0;
#endif

uint3_t select_dst(v4tag tags) {
    uint3_t r = 7; // -1
    // look for free entry
    bool found = false;
    for (uint32_t i=t0; i<4; i++) {
        if (!found && !get_val(tags[i])) {
            r = i;
            found = true;
        }
    }
    if (!found) { // look for oldest entry
        uint16_t ref_age = 0;
        for (uint32_t i=t0; i<4; i++) {
            uint16_t age = get_age(tags[i]);
            if (age > ref_age) { // strict positive, so at least one access done
                r = i;
                ref_age = age;
            }
        }
    }
    return r;
}

io_interface cache(suspend)
{
    outport miss<uint1_t>;

    reg r_susp<state>;

    reg r_tags<v4tag>; // val || tag || age
    reg r_move<w64>;   // tag || idx || age

#ifdef PAGE0
    reg r_boot<uint1_t>; hw_init r_boot = 1;
#endif

    process process_result() {
        suspend = r_susp;
    }
    process process_request() {
#if 1
        w64   l_move = r_move;
        v4tag l_tags = r_tags;
        state l_susp = r_susp;
        bool  l_ack = 0;

#ifdef PAGE0
        if (r_boot) {
            r_boot = 0;
            l_tags = (uint256_t)1; // first entry is fixed and contains tag 0: i.e. DM[0:15] stays loaded
        }
#endif

        bool transition = false;

        // handle outstanding move
        uint16_t l_age = get_age(l_move);
        if (l_age == 1) {
            uint2_t j = get_idx(l_move);
            uint28_t l_tag = get_tag(l_move);
            DEBUG_PRINT_CACHE("load: leave suspend state=%d, answer (tag=%d,line=%d)",l_susp,l_tag,j);
            // validate entry
            l_tags[j] = set_val(l_tags[j],1);
            l_tags[j] = set_tag(l_tags[j],l_tag);
            l_tags[j] = set_age(l_tags[j],(uint16_t)0);
            // clear suspends
            l_susp = 0;
        }
        if (l_age) {
            transition = true;
            l_move = set_age(l_move,l_age-1);
        }

        // handle DM access
        bool ldst = (st_edmw|st_edmh|st_edmb|ld_edmw|ld_edmh|ld_edmb);
        if (ldst) {
            transition = true;
            uint28_t l_tag = get_tag(edm_addr);
            uint3_t i = lookup(l_tag,l_tags);
            if (i != 7) {
                DEBUG_PRINT_CACHE("hit : (tag=%d,line=%d)",l_tag,i);
                uint16_t age = get_age(l_tags[i]);
                if (age != 0xffff) age += 1;
                l_tags[i] = set_age(l_tags[i],age);
                // acknowledge
                l_ack = 1;
            }
            else {
                // cache miss
                if (get_age(l_move)) {
                    // oustanding move
                    if (l_tag != get_tag(l_move)) {
                        DEBUG_PRINT_CACHE("miss: retry cntxt=%d, no free request",ctx_id);
                    }
                    else {
                        DEBUG_PRINT_CACHE("miss: enter suspend cntxt=%d, requesting already (tag=%d,line=%d)",
                                    ctx_id,l_tag,get_idx(l_move));
                        // suspend (as well)
                        l_susp = set_bit(l_susp,ctx_id,1);
                    }
                }
                else {
                    uint3_t j = select_dst(l_tags);
                    if (j == 7) {
                        DEBUG_PRINT_CACHE("miss: retry cntxt=%d, no free line",ctx_id);
                    }
                    else {
                        DEBUG_PRINT_CACHE("miss: enter suspend cntxt=%d, request (tag=%d,line=%d)",
                                    ctx_id,l_tag,j);
                        // suspend context
                        l_susp = set_bit(l_susp,ctx_id,1);
                        // invalidate entry
                        l_tags[j] = set_val(l_tags[j],0);
                        // request move
                        l_move = set_age(l_move,c_move_time);
                        l_move = set_tag(l_move,l_tag);
                        l_move = set_idx(l_move,j);
                    }
                }
            }
        } // ldst

#if 1
        if (transition) {
            for (uint32_t i=0; i<4; i++) {
                if (get_val(l_tags[i]))
                    DEBUG_PRINT_CACHE("tags: idx=%d, tag=%d, age=%d",i,get_tag(l_tags[i]),get_age(l_tags[i]));
            }
            if (get_age(l_move))
                DEBUG_PRINT_CACHE("move: idx=%d, tag=%d, age=%d, state=0x%x",
                            get_idx(l_move),get_tag(l_move),get_age(l_move),l_susp);
        }
#endif

        r_move = l_move;
        r_tags = l_tags;
        r_susp = l_susp;
        miss = !l_ack;

#else
        r_susp = 0;
        miss = 0;
#endif
    }
}

