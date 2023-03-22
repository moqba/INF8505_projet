#define VSIZE 16
unsigned chess_storage(DMb%VSIZE) A[VSIZE] = {0x12121212,0x34343434,0x56565656,0x78787878,0x90909090,0xabababab,0xcdcdcdcd,0xefefefef};
unsigned chess_storage(DMb%VSIZE) B[VSIZE] = {0x12121212,0x34343435,0x55565656,0x78787878,0x90909090,0xabababab,0xcdcdcdcd,0xefefefef};
unsigned chess_storage(DMb%VSIZE) D[VSIZE] = {0x34343434,0x56565656,0x78787878,0x90909090,0xabababab,0xcdcdcdcd,0xefefefef,0x12121212};
unsigned chess_storage(DMb%VSIZE) C[VSIZE] ;

char   chess_storage(DMb%VSIZE) F[VSIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15, 16 };
short  chess_storage(DMb%VSIZE) G[VSIZE/2] = { 1, 2, 3, 4, 5, 6, 7, 8 };
int    chess_storage(DMb%VSIZE) H[4*VSIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
                                           21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
                                           41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,
                                           61,62,63,64,65,66,67,68,69,70,71,72,73,74,75 };
#ifdef __clang__
vint_t chess_storage(DMb%VSIZE) I =       { 0x01020304, 0x05060708, 0x090a0b0c, 0x0d0e0f10 };
vint_t chess_storage(DMb%VSIZE) J =       { 0x01020304, 0x05060708, 0x090a0b0c, 0x0d0e0f10 };
#else
vint_t chess_storage(DMb%VSIZE) I = vint_t( 0x01020304, 0x05060708, 0x090a0b0c, 0x0d0e0f10 );
vint_t chess_storage(DMb%VSIZE) J =       { 0x01020304, 0x05060708, 0x090a0b0c, 0x0d0e0f10 };
#endif

vint_t vadd(vint_t a, vint_t b)
{
    return a + b;
}

vint_t vsub(vint_t a, vint_t b)
{
    return a - b;
}

vint_t vband(vint_t a, vint_t b)
{
    return a & b;
}

vint_t vbor(vint_t a, vint_t b)
{
    return a | b;
}

vint_t vbxor(vint_t a, vint_t b)
{
    return a ^ b;
}

vint_t vselect_test(vbool_t c,vint_t a, vint_t b)
{
    return vselect(c,a , b);
}

vbool_t vslt(vint_t a, vint_t b)
{
    return a < b;
}

vbool_t vsle(vint_t a, vint_t b)
{
    return a <= b;
}

vbool_t vsgt(vint_t a, vint_t b)
{
    return a > b;
}

vbool_t vsge(vint_t a, vint_t b)
{
    return a >= b;
}

vbool_t vseq(vint_t a, vint_t b)
{
    return a == b;
}

vbool_t vsne(vint_t a, vint_t b)
{
    return a != b;
}

vbool_t vsltu(vuint_t a, vuint_t b)
{
    return a < b;
}

vbool_t vsleu(vuint_t a, vuint_t b)
{
    return a <= b;
}

vbool_t vsgtu(vuint_t a, vuint_t b)
{
    return a > b;
}

vbool_t vsgeu(vuint_t a, vuint_t b)
{
    return a >= b;
}

vint_t vloop(vint_t* p)
{
    vint_t x = 0;
    for (int i=0; i < 4; i++) 
        x = x + p[i];
    return x;
}

int main() {
    
    vint_t v1 = *(vint_t *)A;
    vint_t v2 = *(vint_t *)B;
    
    vuint_t v1u = *(vuint_t *)A;
    vuint_t v2u = *(vuint_t *)B;
    
    chess_report(*(vint_t*)F); // char
    chess_report(*(vint_t*)G); // short
    chess_report(*(vint_t*)H); // int
    chess_report(I);
    chess_report(J);
    chess_report(v1);
    chess_report(v2);

    vint_t c;
    c = vadd(v1,v2);
    chess_report(c);
    
    c = vsub(v1,v2);
    chess_report(c);
    
    c = vband(v1,v2);
    chess_report(c);
    
    c = vbor(v1,v2);
    chess_report(c);
    
    c = vbxor(v1,v2);
    chess_report(c);
    
    vbool_t res;

    res = vslt(v1,v2);
    chess_report(res);
    
    c = vselect_test(res,v1,v2);
    chess_report(c);
    
    res = vsle(v1,v2);
    chess_report(res);
    
    res = vsgt(v1,v2);
    chess_report(res);
    
    res = vsge(v1,v2);
    chess_report(res);
    
    res = vseq(v1,v2);
    chess_report(res);
    
    res = vsne(v1,v2);
    chess_report(res);
    
    res = vsltu(v1u,v2u);
    chess_report(res);
    
    res = vsleu(v1u,v2u);
    chess_report(res);
    
    res = vsgtu(v1u,v2u);
    chess_report(res);
    
    res = vsgeu(v1u,v2u);
    chess_report(res);

    c = vloop((vint_t*)H);
    chess_report(c);
    
    return 1;
}



