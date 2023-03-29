/*
-- File : pdc_caches.h
--
-- Contents : declaration of caches used in Checkers_pdc_interface class.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
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
#include <array>
#include <AddressType.h>

class pdc_commands;

namespace pdc_caches {

//  sizes
    enum { line_sz = 64,
           vline_addr_sz = 8, vline_elem_sz = 8,
           vline_sz = vline_addr_sz * vline_elem_sz
    };

//  cache for scalar memory
    using cache_line = std::array<DataType,line_sz>;

//  cache for vector memory (combination of consecutive addresses and elements)
    using vcache_line = std::array<DataType,vline_sz>;

//  single address vector element cache (for registers and write merge buffer)
    using sa_vcache_line = std::array<DataType,vline_elem_sz>;

//  range class ([first,last], where length() works up to INT_MAX)

    template<typename T>
    struct Range {
        T first;
        T last;

        Range()                 { clear(); }
        Range(T f)              { first = f; last = f; }
        Range(T f, T l)         { first = f; last = l; }
        int length() const      { return static_cast<int>(last - first + 1); }
        bool empty() const      { return first > last; }
        bool covers(T a) const  { return first <= a && a <= last; }
        void clear()            { first = 1; last = 0; }
    };

    template<typename T>
    inline bool operator==(const Range<T>& a, const Range<T>& b)
    {
        return a.first == b.first && a.last == b.last;
    }
    template<typename T>
    inline bool overlaps(const Range<T>& a, const Range<T>& b)
    {
        return a.first <= b.last && b.first <= a.last;
    }
    template<typename T>
    inline Range<T> operator*(const Range<T>& a, unsigned i)
    {
        return Range<T>(a.first*i,a.last*i);
    }

    using range = Range<unsigned>;
    using arange = Range<AddressType>;

//  access of scalar caches

    inline AddressType cache_index(AddressType addr) { return addr / line_sz; }

    inline unsigned cache_offset(AddressType addr) { return addr % line_sz; }

    inline arange line_address_range(AddressType addr)
    {
        AddressType beg = addr - addr % line_sz;
        return arange(beg, beg + line_sz-1);
    }

//  access of vector caches

    inline AddressType vcache_index(AddressType addr, unsigned elem, unsigned vec_sz)
    {
        int lines_per_vector = (vec_sz + vline_elem_sz - 1) / vline_elem_sz;
        return (addr / vline_addr_sz) * lines_per_vector
             + (elem / vline_elem_sz);
    }

    inline unsigned vcache_offset(AddressType addr, unsigned elem)
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

    inline arange vline_address_range(AddressType addr)
    {
        AddressType beg = addr - addr % vline_addr_sz;
        return arange(beg,beg + vline_addr_sz-1);
    }

//  vector write-merge-line, to buffer consecutive writes

    class write_merge_vline {
        bool for_reg = false;
        AddressType addr = -1;
        range elems;
        std::array<DataType,vline_elem_sz> values;
        std::array<bool,vline_elem_sz> set;

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
        bool same_line(AddressType a, range r) const {
            return addr == a && elems == r;
        }
        bool same_line(range r) const {
            return elems == r;
        }
        bool covered(arange ar, range er) const {
            return ar.covers(addr) && elems == er;
        }
        void assign(range r, const DataType* p) {
            elems = r;
            for (int i = 0; i < r.length(); i++) {
                set[i] = true;
                values[i] = *p++;
            }
        }
        void add(AddressType a, range r, unsigned e, const DataType& val) {
            for_reg = false;
            addr = a;
            elems = r;
            values[e-r.first] = val;
            set[e-r.first] = true;
        }
        void add(range r, unsigned e, const DataType& val) {
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
        void flush(pdc_commands*, std::string name);
    };

//  read-once vector line, storing the load result of a protected vector address

    class read_once_vline {
        std::string name;
        AddressType addr = -1;
        range elems;
        std::array<DataType,vline_elem_sz> values;
        std::array<bool,vline_elem_sz> read;
    public:
        read_once_vline() { clear(); }

        template <class I>
        read_once_vline(std::string s, AddressType a, range r, I vp)
            : name(s), addr(a), elems(r) {
            for (int i = 0; i < r.length(); i++) {
                read[i] = false;
                values[i] = *vp++;
            }
        }
        bool same_line(std::string s, AddressType a, range r) const {
            return name == s && addr == a && elems == r;
        }
        bool get(unsigned e, DataType& val) {
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
