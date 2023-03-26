/*
-- kruskal.p
--
-- Ce fichier est inclus à la fin de trv32p3.p
--
-- Implémentation en PDG des instructions personnalisées KRUSKAL
*/

void swap_hw(w32& xu, w32& xv, w32& xw, w32& yu, w32& yv, w32& yw) {
    uint32_t x1 = xu;
    uint32_t x2 = xv;
    uint32_t x3 = xw;
    
    uint32_t y1 = yu;
    uint32_t y2 = yv;
    uint32_t y3 = yw;
    
    uint32_t t1 = x1;
    uint32_t t2 = x2;
    uint32_t t3 = x3;
    
    x1 = y1;
    x2 = y2;
    x3 = y3;
    
    y1 = t1;
    y2 = t2;
    y3 = t3;
}