// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vffi__Syms_H_
#define _Vffi__Syms_H_

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vffi.h"

// SYMS CLASS
class Vffi__Syms : public VerilatedSyms {
  public:

    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;

    // SUBCELL STATE
    Vffi*                          TOPp;

    // CREATORS
    Vffi__Syms(Vffi* topp, const char* namep);
    ~Vffi__Syms() {}

    // METHODS
    inline const char* name() { return __Vm_namep; }

} VL_ATTR_ALIGNED(64);

#endif // guard
