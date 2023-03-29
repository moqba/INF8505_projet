/*
-- trv32p3_kruskal.h
--
-- Ce fichier est inclus à la fin de trv32p3_chess.h
--
-- Traduction des appels en C vers les primitives des instructions personnalisées KRUSKAL pour le compilateur
*/

#ifndef TRV32P3_KRUSKAL_H
#define TRV32P3_KRUSKAL_H

promotion void swap_hw(signed x, signed y, signed& xw, signed& yw)
        = void swap_hw(w32 x, w32 y, w32& xw, w32& yw);
promotion void swapf_hw(signed uxr, signed vxr, signed wxr, signed uyr, signed vyr, signed wyr, signed& uxw, signed& vxw, signed& wxw, signed& uyw, signed& vyw, signed& wyw)
        = void swapf_hw(w32 uxr, w32 vxr, w32 wxr, w32 uyr, w32 vyr, w32 wyr, w32& uxw, w32& vxw, w32& wxw, w32& uyw, w32& vyw, w32& wyw);
#endif
