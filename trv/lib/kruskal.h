/*
-- kruskal.h
--
-- Ce fichier est inclus à la fin de trv32p3.h
--
-- Déclaration des primitives des instructions personnalisées KRUSKAL
*/

#ifndef KRUSKAL_H
#define KRUSKAL_H

namespace trv32p3_primitive {
    void swap_hw(w32 xr, w32 yr, w32& xw, w32& yw);
    void swapf_hw(w32 uxr, w32 vxr, w32 wxr, w32 uyr, w32 vyr, w32 wyr, w32& uxw, w32& vxw, w32& wxw, w32& uyw, w32& vyw, w32& wyw);
}

#endif
