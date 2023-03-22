// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vfif__Syms_H_
#define _Vfif__Syms_H_

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vfif.h"

// SYMS CLASS
class Vfif__Syms : public VerilatedSyms {
  public:

    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;

    // SUBCELL STATE
    Vfif*                          TOPp;

    // CREATORS
    Vfif__Syms(Vfif* topp, const char* namep);
    ~Vfif__Syms() {}

    // METHODS
    inline const char* name() { return __Vm_namep; }

} VL_ATTR_ALIGNED(64);

#endif // guard
