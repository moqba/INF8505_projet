// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vspsr24__Syms.h"
#include "Vspsr24.h"

// FUNCTIONS
Vspsr24__Syms::Vspsr24__Syms(Vspsr24* topp, const char* namep)
        // Setup locals
        : __Vm_namep(namep)
        , __Vm_didInit(false)
        // Setup submodule names
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
}
