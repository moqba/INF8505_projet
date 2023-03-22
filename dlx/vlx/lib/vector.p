v4w32 vadd(v4w32 a, v4w32 b, v4u1& co)
{
    v4w32 vec_res;
    v4u1 cc_temp;
    for(int32_t i=0;i<4;i++)
    {
        uint1_t cc;
        uint32_t res = add(a[i], b[i], cc);
        vec_res[i] = res;
        cc_temp[i] = cc;
        DEBUG_PRINT("vadd a[i] = 0x%x b[i]=0x%x res= 0x%x cc[i]=0x%x \n",a[i],b[i],res,cc);
    }
    co=cc_temp;
    return vec_res;
}

v4w32 vsub(v4w32 a, v4w32 b, v4u1& co)
{
    v4w32 vec_res;
    v4u1 cc_temp;
    for(int32_t i=0;i<4;i++)
    {
        uint1_t cc;
        uint32_t res = sub(a[i], b[i], cc);
        vec_res[i] = res;
        cc_temp[i] = cc;
        DEBUG_PRINT("vsub a[i] = 0x%x b[i]=0x%x res= 0x%x cc[i]=0x%x \n",a[i],b[i],res,cc);
    }
    co=cc_temp;
    return vec_res;
}

v4w32 vaddx(v4w32 a, v4w32 b, v4u1 ci, v4u1& co)
{
    v4w32 vec_res;
    v4u1 cc_temp;
    for(int32_t i=0;i<4;i++)
    {
        uint1_t cc;
        uint32_t res = addx(a[i], b[i], ci[i], cc);
        vec_res[i] = res;
        cc_temp[i] = cc;
        DEBUG_PRINT("vaddx a[i] = 0x%x b[i]=0x%x res=0x%x ci[i]=0x%x cc[i]=0x%x\n",a[i],b[i], res, ci[i],cc);
    }
    co=cc_temp;
    return vec_res;
}

v4w32 vsubx(v4w32 a, v4w32 b, v4u1 ci, v4u1& co)
{
    v4w32 vec_res;
    v4u1 cc_temp;
    for(int32_t i=0;i<4;i++)
    {
        uint1_t cc;
        uint32_t res = subx(a[i], b[i], ci[i], cc);
        vec_res[i] = res;
        cc_temp[i] = cc;
        DEBUG_PRINT("vsubx a[i] = 0x%x b[i]=0x%x res=0x%x ci[i]=0x%x cc[i]=0x%x\n",a[i],b[i], res, ci[i],cc);
    }
    co=cc_temp;
    return vec_res;
}

v4w32 vband (v4w32 a, v4w32 b) {
    v4w32 r;
    for (int32_t i = 0; i < 4; i++)
        r[i] = band(a[i] , b[i]);
    return r;
}

v4w32 vbor (v4w32 a, v4w32 b) {
    v4w32 r;
    for (int32_t i = 0; i < 4; i++)
        r[i] = bor(a[i] , b[i]);
    return r;
}

v4w32 vbxor (v4w32 a, v4w32 b) {
    v4w32 r;
    for (int32_t i = 0; i < 4; i++)
        r[i] = bxor(a[i] , b[i]);
    return r;
}

w32 vsge(v4w32 a, v4w32 b)
{
    w32 r=0;
    for (int32_t i = 0; i < 4; i++)
        r[i] = a[i] >= b[i];
    return r;

}

w32 vsgt(v4w32 a, v4w32 b)
{
    w32 r=0;
    for (int32_t i = 0; i < 4; i++)
        r[i] = a[i] > b[i];
    return r;
}

w32 vsle(v4w32 a, v4w32 b)
{
    w32 r=0;
    for (int32_t i = 0; i < 4; i++)
        r[i] = a[i] <= b[i];
    return r;
}

w32 vslt(v4w32 a, v4w32 b)
{
    w32 r=0;
    for (int32_t i = 0; i < 4; i++)
        r[i] = a[i] < b[i];
    return r;
}

w32 vseq(v4w32 a, v4w32 b)
{
    w32 r=0;
    for (int32_t i = 0; i < 4; i++)
        r[i] = a[i] == b[i];
    return r;
}

w32 vsne(v4w32 a, v4w32 b)
{
    w32 r=0;
    for (int32_t i = 0; i < 4; i++)
        r[i] = a[i] != b[i];
    return r;
}

v4w32 vselect(w32 sel, v4w32 a, v4w32 b)
{
    v4w32 vec_res;
    for(int32_t i=0;i<4;i++)
    {
        vec_res[i] = sel[i] ? a[i] : b[i];
    }
    return vec_res;
}

w32 vsgeu(v4w32 a, v4w32 b)
{
    w32 r=0;
    for (int32_t i = 0; i < 4; i++)
        r[i] = (uint32_t)a[i] >= (uint32_t)b[i];
    return r;

}

w32 vsgtu(v4w32 a, v4w32 b)
{
    w32 r=0;
    for (int32_t i = 0; i < 4; i++)
        r[i] = (uint32_t)a[i] > (uint32_t)b[i];
    return r;
}

w32 vsleu(v4w32 a, v4w32 b)
{
    w32 r=0;
    for (int32_t i = 0; i < 4; i++)
        r[i] = (uint32_t)a[i] <= (uint32_t)b[i];
    return r;
}

w32 vsltu(v4w32 a, v4w32 b)
{
    w32 r=0;
    for (int32_t i = 0; i < 4; i++)
        r[i] = (uint32_t)a[i] < (uint32_t)b[i];
    return r;
}

v4w32 vinsert(v4w32 lhs,w32 value,w32 index)
{
   v4w32 tmp=lhs;
   tmp[(uint2)index]=value;
   return tmp;
}

w32 vextract(v4w32 lhs,w32 index)
{
    return lhs[(uint2)index];
}
