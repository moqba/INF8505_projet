#ifndef _vlx_llvm_h
#define _vlx_llvm_h

#include "vlx_define.h"

#include "isg/vlx_chess_llvm.h"

// The vector compare instructions return a "vint_t" and not a "vbool_t" because of the enabled LLVM support with the property(llvm_vector).
// For easier programming we define the vbool_t to vint_t.
#define vbool_t vint_t
inline vint_t vselect(vint_t c, vint_t a, vint_t b) { return (a & c) | (b & ~c); }

#endif
