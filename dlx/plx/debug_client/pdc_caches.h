/*
-- File : pdc_caches.h
--
-- Contents : declaration of caches used in Checkers_pdc_interface class.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _pdc_caches_h
#define _pdc_caches_h

#include <string>
#include "c_array.h"

class Checkers_pdc_interface;
class pdc_commands;

namespace pdc_caches {

//  sizes
    enum { line_sz = 64,
           vline_addr_sz = 8, vline_elem_sz = 8,
           vline_sz = vline_addr_sz * vline_elem_sz
    };

//  cache for scalar memory
    typedef c_array<long long,line_sz> cache_line;

//  cache for vector memory (combination of consecutive addresses and elements)
    typedef c_array<long long,vline_sz> vcache_line;

//  single address vector element cache (for registers and write merge buffer)
    typedef c_array<long long,vline_elem_sz> sa_vcache_line;

//  range class ([first,last] assuming that length < INT_MAX)

    struct range {
        unsigned first;
        unsigned last;

        range()                         { clear(); }
        range(unsigned f)               { first = f; last = f; }
        range(unsigned f, unsigned l)   { first = f; last = l; }
        int length() const              { return last - first + 1; }
        bool empty() const              { return length() <= 0; }
        bool covers(unsigned a) const   { return first <= a && a <= last; }
        void clear()                    { first = 1; last = 0; }
    };

    inline bool operator==(const range& a, const range& b)
    {
        return a.first == b.first && a.last == b.last;
    }
    inline bool overlaps(const range& a, const range& b)
    {
        return a.first <= b.last && b.first <= a.last;
    }

//  access of scalar caches

    inline unsigned cache_index(unsigned addr) { return addr / line_sz; }

    inline unsigned cache_offset(unsigned addr) { return addr % line_sz; }

    inline range line_address_range(unsigned addr)
    {
        unsigned beg = addr - addr % line_sz;
        return range(beg, beg + line_sz-1);
    }

//  access of vector caches

    inline unsigned vcache_index(unsigned addr, unsigned elem, unsigned vec_sz)
    {
        int lines_per_vector = (vec_sz + vline_elem_sz - 1) / vline_elem_sz;
        return (addr / vline_addr_sz) * lines_per_vector
             + (elem / vline_elem_sz);
    }

    inline unsigned vcache_offset(unsigned addr, unsigned elem)
    {
        return (addr % vline_addr_sz) * vline_elem_sz + (elem % vline_elem_sz);
    }

    inline unsigned sa_vcache_index(unsigned elem)
    {
        return elem / vline_elem_sz;
    }

    inline unsigned sa_vcache_offset(unsigned elem)
    {
        return elem % vline_elem_sz;
    }

    inline range vline_elem_range(unsigned elem, unsigned vec_sz)
    {
        unsigned beg = elem - elem % vline_elem_sz;
        unsigned end = beg + vline_elem_sz-1;
        return range(beg,(vec_sz-1 < end) ? vec_sz-1 : end);
    }

    inline range vline_address_range(unsigned addr)
    {
        unsigned beg = addr - addr % vline_addr_sz;
        return range(beg,beg + vline_addr_sz-1);
    }

//  vector write-merge-line, to buffer consecutive writes

    class write_merge_vline {
        bool for_reg;
        unsigned addr;
        range elems;
        c_array<long long,vline_elem_sz> values;
        c_array<bool,vline_elem_sz> set;

    public:
        write_merge_vline() { clear(); }

        void clear() {
            elems.clear();
            for (int i = 0; i < vline_elem_sz; i++) set[i] = false;
        }

        bool empty() const          { return elems.length() == 0; }

        bool complete() const {
            bool r = true;
            for (int i = 0; i < elems.length(); i++) r = r & set[i];
            return r;
        }
        bool same_line(unsigned a, range r) const {
            return addr == a && elems == r;
        }
        bool same_line(range r) const {
            return elems == r;
        }
        bool covered(range ar, range er) const {
            return ar.covers(addr) && elems == er;
        }
        void assign(range r, long long* p) {
            elems = r;
            for (int i = 0; i < r.length(); i++) {
                set[i] = true;
                values[i] = *p++;
            }
        }
        void add(unsigned a, range r, unsigned e, long long val) {
            for_reg = false;
            addr = a;
            elems = r;
            values[e-r.first] = val;
            set[e-r.first] = true;
        }
        void add(range r, unsigned e, long long val) {
            for_reg = true;
            addr = 0;
            elems = r;
            values[e-r.first] = val;
            set[e-r.first] = true;
        }
        template <class I>
        void copy_to(I vp) const {
            for (int i = 0; i < elems.length(); i++) {
                if (set[i]) *vp = values[i];
                vp++;
            }
        }
        void flush(Checkers_pdc_interface*, pdc_commands*, std::string name);
    };

//  read-once vector line, storing the load result of a protected vector address

    class read_once_vline {
        std::string name;
        unsigned addr;
        range elems;
        c_array<long long,vline_elem_sz> values;
        c_array<bool,vline_elem_sz> read;
    public:
        read_once_vline() { clear(); }

        template <class I>
        read_once_vline(std::string s, unsigned a, range r, I vp)
            : name(s), addr(a), elems(r) {
            for (int i = 0; i < r.length(); i++) {
                read[i] = false;
                values[i] = *vp++;
            }
        }
        bool same_line(std::string s, unsigned a, range r) const {
            return name == s && addr == a && elems == r;
        }
        bool get(unsigned e, long long& val) {
            if (!read[e-elems.first]) {
                val = values[e-elems.first];
                read[e-elems.first] = true;
                return true;
            }
            return false;
        }
        void clear() {
            elems.clear();
        }
    };
}

#endif
