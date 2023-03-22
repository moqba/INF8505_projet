// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vfcp__Syms_H_
#define _Vfcp__Syms_H_

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vfcp.h"

// SYMS CLASS
class Vfcp__Syms : public VerilatedSyms {
  public:

    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;

    // SUBCELL STATE
    Vfcp*                          TOPp;

    // CREATORS
    Vfcp__Syms(Vfcp* topp, const char* namep);
    ~Vfcp__Syms() {}

    // METHODS
    inline const char* name() { return __Vm_namep; }

} VL_ATTR_ALIGNED(64);

#endif // guard
