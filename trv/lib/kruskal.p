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

void swapf_hw(w32 uxr, w32 vxr, w32 wxr, w32 uyr, w32 vyr, w32 wyr, w32& uxw, w32& vxw, w32& wxw, w32& uyw, w32& vyw, w32& wyw) {
    uint32_t ux = uxr;
    uint32_t vx = vxr;
    uint32_t wx = wxr;
    uint32_t uy = uyr;
    uint32_t vy = vyr;
    uint32_t wy = wyr;
    uxw = uy;
    vxw = vy;
    wxw = wy;
    uyw = ux;
    vyw = vx;
    wyw = wx;
}