// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vspsr24__Syms_H_
#define _Vspsr24__Syms_H_

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vspsr24.h"

// SYMS CLASS
class Vspsr24__Syms : public VerilatedSyms {
  public:

    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;

    // SUBCELL STATE
    Vspsr24*                       TOPp;

    // CREATORS
    Vspsr24__Syms(Vspsr24* topp, const char* namep);
    ~Vspsr24__Syms() {}

    // METHODS
    inline const char* name() { return __Vm_namep; }

} VL_ATTR_ALIGNED(64);

#endif // guard
