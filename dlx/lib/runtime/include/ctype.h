/*
-- File: ctype.h
--
-- Contents: ISO C99 Standard, 7.4 Character handling <ctype.h>
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



#ifndef _CTYPE_H
#define _CTYPE_H

#include <limits.h>

// Table base implementation of ctype.h functions.

enum {
    _ct_L = 0x01,  // lower case letter
    _ct_U = 0x02,  // upper case letter
    _ct_D = 0x04,  // digit
    _ct_X = 0x08,  // hexadecimal digit
    _ct_P = 0x10,  // punctuation
    _ct_C = 0x20,  // control character
    _ct_S = 0x40,  // white space character
    _ct_B = 0x80   // blank character
};

extern const unsigned char _ct_code[];

#ifdef __clang__
__attribute__((always_inline))
#endif
inline int _ct_test(unsigned char c, unsigned int code) {
    if (UCHAR_MAX <= 256)
        return _ct_code[c] & code;
    else if (c < 256)
        return _ct_code[c] & code;
    else 
        return 0;
}

#if defined(__cplusplus) || defined(__ndl__)
extern "C" {
#endif

inline int isalnum(int c) { return _ct_test(c,_ct_L|_ct_U|_ct_D); }
inline int isalpha(int c) { return _ct_test(c,_ct_L|_ct_U); }
inline int isblank(int c) { return _ct_test(c,_ct_B); }
inline int iscntrl(int c) { return _ct_test(c,_ct_C); }
inline int isdigit(int c) { return _ct_test(c,_ct_D); }
inline int isgraph(int c) { return _ct_test(c,_ct_L|_ct_U|_ct_D|_ct_P); }
inline int islower(int c) { return _ct_test(c,_ct_L); } 
inline int isprint(int c) { return _ct_test(c,_ct_L|_ct_U|_ct_D|_ct_P|_ct_B) && c != '\t'; }
inline int ispunct(int c) { return _ct_test(c,_ct_P); }
inline int isspace(int c) { return _ct_test(c,_ct_S); }
inline int isupper(int c) { return _ct_test(c,_ct_U); }
inline int isxdigit(int c) { return _ct_test(c,_ct_X); }

inline int tolower(int c)  { return isupper(c) ? (c - 'A' + 'a') : c; }
inline int toupper(int c)  { return islower(c) ? (c - 'a' + 'A') : c; }

#if defined(__cplusplus) || defined(__ndl__)
} // extern "C"
#endif

#endif /* ctype.h */
