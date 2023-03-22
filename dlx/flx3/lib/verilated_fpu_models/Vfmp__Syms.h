// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vfmp__Syms_H_
#define _Vfmp__Syms_H_

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vfmp.h"

// SYMS CLASS
class Vfmp__Syms : public VerilatedSyms {
  public:

    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;

    // SUBCELL STATE
    Vfmp*                          TOPp;

    // CREATORS
    Vfmp__Syms(Vfmp* topp, const char* namep);
    ~Vfmp__Syms() {}

    // METHODS
    inline const char* name() { return __Vm_namep; }

} VL_ATTR_ALIGNED(64);

#endif // guard
