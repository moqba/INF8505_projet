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

#endif
