/*
-- File : c_array.h
--
-- Contents : Bjarne Stroustrups c_array.
--            The C++ programming language, Third Edition, $17.5.4
*/

#ifndef _c_array_h
#define _c_array_h

#include <cstddef>

template<class T, int max> struct c_array {
    typedef T value_type;

    typedef T* iterator;
    typedef const T* const_iterator;

    typedef T& reference;
    typedef const T& const_reference;

    T v[max];

    // operator T*() { return v; }

    reference operator[](std::size_t i) { return v[i]; }
    const_reference operator[](std::size_t i) const { return v[i]; }

    iterator begin() { return v; }
    const_iterator begin() const { return v; }

    iterator end() { return v+max; }
    const_iterator end() const { return v+max; }

    std::ptrdiff_t size() { return max; }
};

#endif
