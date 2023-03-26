/*
-- kruskal.p
--
-- Ce fichier est inclus à la fin de trv32p3.p
--
-- Implémentation en PDG des instructions personnalisées KRUSKAL
*/

void swap_hw(w32 xr, w32 yr, w32& xw, w32& yw) {
    uint32_t x = xr;
    uint32_t y = yr;
    xw = y;
    yw = x;
}