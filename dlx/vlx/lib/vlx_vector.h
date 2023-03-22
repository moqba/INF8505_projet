/*
-- File : vlx_vector.h
--
-- Contents : Vector application layer for the VLX processor.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _vlx_vector_h
#define _vlx_vector_h

class  vint_t property( vector      int[4] llvm_vector);
class vuint_t property( vector unsigned[4] llvm_vector);
class vbool_t property( vector     bool[4] llvm_vector);
chess_property{
    representation  vint_t : v4w32;
    representation vuint_t : v4w32;
    promotion      vbool_t : strong { w08, w32 }
                             transitory { addr };
}
class vint_t {
    inline vint_t(int, int, int, int);
    vint_t(int);
    vint_t(vuint_t);
    inline vint_t(vbool_t);
};

class vuint_t {
    inline vuint_t(unsigned, unsigned, unsigned, unsigned);
    vuint_t(unsigned);
    vuint_t(vint_t);
    inline vuint_t(vbool_t);
};

class vbool_t {
    inline vbool_t(vint_t);
    inline vbool_t(vuint_t);
    operator int() const;
};

promotion vint_t(int) = v4w32(w32);
promotion vuint_t(unsigned) = v4w32(w32);

promotion vint_t(vuint_t) = nil;
promotion vuint_t(vint_t) = nil;

promotion vbool_t::operator int() const = nil;


promotion int      vextract(vint_t, int)         property(extract_vector_elt) = w32  vextract(v4w32, w32);
promotion unsigned vextract(vuint_t,int)         property(extract_vector_elt) = w32  vextract(v4w32, w32);
promotion vint_t   vinsert(vint_t, int,     int) property( insert_vector_elt) = v4w32 vinsert(v4w32, w32, w32);
promotion vuint_t  vinsert(vuint_t,unsigned,int) property( insert_vector_elt) = v4w32 vinsert(v4w32, w32, w32);
inline vbool_t::vbool_t(vint_t a)  { *this = a != 0; }
inline vbool_t::vbool_t(vuint_t a) { *this = a != 0; }

inline vuint_t::vuint_t(unsigned a0, unsigned a1, unsigned a2, unsigned a3) property(build_vector)
{
    if (chess_manifest(a1 == a2) || chess_manifest(a1 == a3)) {
        // prefer a1
        vuint_t tmp=a1;
        if (!chess_manifest(a1 == a0)) {
            tmp=vinsert(tmp, a0, 0);
        }
        if (!chess_manifest(a1 == a2)) {
            tmp=vinsert(tmp, a2, 2);
        }
        if (!chess_manifest(a1 == a3)) {
            tmp=vinsert(tmp, a3, 3);
        }
        *this = tmp;
    } else if (chess_manifest(a2 == a3)) {
        // prefer a3
        vuint_t tmp=a3;
        if (!chess_manifest(a2 == a0)) {
            tmp=vinsert(tmp, a0, 0);
        }
        if (!chess_manifest(a2 == a1)) {
            tmp=vinsert(tmp, a1, 1);
        }
        if (!chess_manifest(a2 == a3)) {
            tmp=vinsert(tmp, a3, 3);
        }
        *this = tmp;
    } else {
        vuint_t tmp=a0;
        if (!chess_manifest(a0 == a1)) {
            tmp=vinsert(tmp, a1, 1);
        }
        if (!chess_manifest(a0 == a2)) {
            tmp=vinsert(tmp, a2, 2);
        }
        if (!chess_manifest(a0 == a3)) {
            tmp=vinsert(tmp, a3, 3);
        }
        *this = tmp;
    }
}

inline vint_t::vint_t(int a0, int a1, int a2, int a3) property(build_vector) {
    vuint_t tmp=vuint_t(a0,a1,a2,a3);
    *this=tmp;
}

promotion  vint_t operator+(vint_t,vint_t)   = v4w32 vadd (v4w32,v4w32,v4u1&) property(duplicate_at_using_opn2);
promotion  vint_t operator-(vint_t,vint_t)   = v4w32 vsub (v4w32,v4w32,v4u1&) property(duplicate_at_using_opn2);
promotion  vint_t operator&(vint_t,vint_t)   = v4w32 vband(v4w32,v4w32);
promotion  vint_t operator|(vint_t,vint_t)   = v4w32 vbor (v4w32,v4w32);
promotion  vint_t operator^(vint_t,vint_t)   = v4w32 vbxor(v4w32,v4w32);

promotion  vuint_t operator+(vuint_t,vuint_t)   = v4w32 vadd (v4w32,v4w32,v4u1&) property(duplicate_at_using_opn2);
promotion  vuint_t operator-(vuint_t,vuint_t)   = v4w32 vsub (v4w32,v4w32,v4u1&) property(duplicate_at_using_opn2);
promotion  vuint_t operator&(vuint_t,vuint_t)   = v4w32 vband(v4w32,v4w32);
promotion  vuint_t operator|(vuint_t,vuint_t)   = v4w32 vbor (v4w32,v4w32);
promotion  vuint_t operator^(vuint_t,vuint_t)   = v4w32 vbxor(v4w32,v4w32);

promotion vbool_t operator< ( vint_t, vint_t) = w32 vslt(v4w32,v4w32);
promotion vbool_t operator<=( vint_t, vint_t) = w32 vsle(v4w32,v4w32);
promotion vbool_t operator> ( vint_t, vint_t) = w32 vsgt(v4w32,v4w32);
promotion vbool_t operator>=( vint_t, vint_t) = w32 vsge(v4w32,v4w32);
promotion vbool_t operator< (vuint_t,vuint_t) = w32 vsltu(v4w32,v4w32);
promotion vbool_t operator<=(vuint_t,vuint_t) = w32 vsleu(v4w32,v4w32);
promotion vbool_t operator> (vuint_t,vuint_t) = w32 vsgtu(v4w32,v4w32);
promotion vbool_t operator>=(vuint_t,vuint_t) = w32 vsgeu(v4w32,v4w32);
promotion vbool_t operator==( vint_t, vint_t) = w32 vseq(v4w32,v4w32);
promotion vbool_t operator!=( vint_t, vint_t) = w32 vsne(v4w32,v4w32);

promotion vint_t vselect(vbool_t,vint_t,vint_t) property(select) = v4w32 vselect(w32,v4w32,v4w32);

inline vint_t::vint_t(vbool_t c)  { *this = vselect(c,vint_t(-1),vint_t(0)); }
inline vuint_t::vuint_t(vbool_t c) { *this = vselect(c,vint_t(1),vint_t(0)); }

#endif // _vlx_vector_h

