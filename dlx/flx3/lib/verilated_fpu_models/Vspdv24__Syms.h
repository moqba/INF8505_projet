// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vspdv24__Syms_H_
#define _Vspdv24__Syms_H_

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vspdv24.h"

// SYMS CLASS
class Vspdv24__Syms : public VerilatedSyms {
  public:

    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;

    // SUBCELL STATE
    Vspdv24*                       TOPp;

    // CREATORS
    Vspdv24__Syms(Vspdv24* topp, const char* namep);
    ~Vspdv24__Syms() {}

    // METHODS
    inline const char* name() { return __Vm_namep; }

} VL_ATTR_ALIGNED(64);

#endif // guard
