
#include "stdio.h"

#ifdef __clang__
# define NOINLINE __attribute__((noinline))
# define ALIGNED(x) __attribute__((align_value(x)))
# define ALIGNED_VARIABLE(x) __attribute__((aligned(x)))
#else
# define NOINLINE
# define ALIGNED(x)
# define ALIGNED_VARIABLE(x) chess_storage(%x)
# define __restrict restrict
#endif

#define VSIZEBYTES 16
#define VSIZE 4

unsigned ALIGNED_VARIABLE(VSIZEBYTES) A[VSIZE] = {0xffffffff,0x34,0x56,0x78};
unsigned ALIGNED_VARIABLE(VSIZEBYTES) B[VSIZE] = {0xab,0xcd,0xef,0x12};
unsigned ALIGNED_VARIABLE(VSIZEBYTES) C[VSIZE] ;


#define LARGE_VECTOR 1024
int ALIGNED_VARIABLE(VSIZEBYTES) largeA[LARGE_VECTOR]={0};
int ALIGNED_VARIABLE(VSIZEBYTES) largeB[LARGE_VECTOR]={0};
int ALIGNED_VARIABLE(VSIZEBYTES) largeC[LARGE_VECTOR]={0};

#if defined(__clang__)
// llvm allows vector access
void print_vint(const char* msg, vint_t rhs)
{
  printf("%s: {", msg);
  for (int i=0; i<4; ++i) {
    printf(" 0x%08x", rhs[i]);
  }
  printf(" }\n");
}

// in llvm, vint_t comparisons return a vint_t
// Redefine vbool_t (as it already exists, but is not usable in llvm)
#define vbool_t vint_t
void print_vbool(const char* msg, vbool_t rhs) 
{
  print_vint(msg, rhs);
}
#else
void print_vint(const char* msg, vint_t rhs)
{
    *(vint_t*)C=rhs;
  printf("%s: {", msg);
  for (int i=0; i<4; ++i) {
    printf(" 0x%08x", C[i]);
  }
  printf(" }\n");
}

// in plain noodle, a comparison returns a vbool_t
void print_vbool(const char* msg, vbool_t rhs)
{
  printf("%s: {0x%0x}\n", msg, (int)rhs);
}
#endif

// Functionality that works in both noodle and llvm
vint_t vadd(vint_t* a, vint_t* b)
{
    return *a + *b;
}

vint_t vsub(vint_t* a, vint_t* b)
{
    return *a - *b;
}

vint_t vband(vint_t* a, vint_t* b)
{
    return *a & *b;
}

vint_t vbor(vint_t* a, vint_t* b)
{
    return *a | *b;
}

vint_t vbxor(vint_t* a, vint_t* b)
{
    return *a ^ *b;
}


vint_t vmax(vint_t* a, vint_t* b)
{
#if defined(__clang__)
  vint_t mask=*a > *b;
  return (*a & mask) | (*b & ~mask);
#else
    return vselect(*a > *b,*a , *b);
#endif
}

vbool_t vslt(vint_t* a, vint_t* b)
{
    return *a < *b;
}

vbool_t vsle(vint_t* a, vint_t* b)
{
    return *a <= *b;
}

vbool_t vsgt(vint_t* a, vint_t* b)
{
    return *a > *b;
}

vbool_t vsge(vint_t* a, vint_t* b)
{
    return *a >= *b;
}

vbool_t vseq(vint_t* a, vint_t* b)
{
    return *a == *b;
}

vbool_t vsne(vint_t* a, vint_t* b)
{
    return *a != *b;
}

vbool_t vsltu(vuint_t* a, vuint_t* b)
{
    return *a < *b;
}

vbool_t vsleu(vuint_t* a, vuint_t* b)
{
    return *a <= *b;
}

vbool_t vsgtu(vuint_t* a, vuint_t* b)
{
    return *a > *b;
}

vbool_t vsgeu(vuint_t* a, vuint_t* b)
{
    return *a >= *b;
}

// Functionality that can be vectorized in llvm
void initUpwards(int* dst ALIGNED(16)) NOINLINE
{
  for (int i=0; i<LARGE_VECTOR; ++i) {
    dst[i]=i;
  }
}

void initDownwards(int* dst ALIGNED(16)) NOINLINE
{
  for (int i=0; i<LARGE_VECTOR; ++i) {
    dst[i]=LARGE_VECTOR-i;
  }
}

void initZero(int* dst ALIGNED(16)) NOINLINE
{
  for (int i=0; i<LARGE_VECTOR; ++i) {
    dst[i]=0;
  }
}

void print_large_array(const char* msg, int* dst ALIGNED(16)) NOINLINE
{
  // compute summary
  int summary=0;
  for (int i=0; i<LARGE_VECTOR;++i) {
      summary +=dst[i];
  }
  printf("\n%s: summary: %d\n", msg, summary);

#if 0 // print large array
  printf("\n%s:", msg);
  for (int i=0; i<LARGE_VECTOR; ++i) {
    if ((i%16)==0) {
      printf("\n%4d:", i);
    }
    printf(" %08x", dst[i]);
  }
  printf("\n");
#endif
}

void do_add(int* __restrict dst ALIGNED(16), 
            int* __restrict lhs ALIGNED(16),
            int* __restrict rhs ALIGNED(16)) NOINLINE
{
    for (int i=0; i<LARGE_VECTOR; ++i) {
        dst[i]=lhs[i]+rhs[i];
    }
}

void do_max(int* __restrict dst ALIGNED(16), 
            int* __restrict lhs ALIGNED(16),
            int* __restrict rhs ALIGNED(16)) NOINLINE
{
    for (int i=0; i<LARGE_VECTOR; ++i) {
        dst[i]=lhs[i] < rhs[i] ? lhs[i] : rhs[i];
    }
}

vuint_t buildIt(unsigned a, unsigned b)
{
    vuint_t tmp={a,a,b,b};
    return tmp;
}



int main() {
    vint_t* vec1 = (vint_t*)A;
    vint_t* vec2 = (vint_t*)B;
    
    vuint_t* vec1u = (vuint_t*)A;
    vuint_t* vec2u = (vuint_t*)B;
    vbool_t res;

    print_vint("A", *vec1);
    print_vint("B", *vec2);
    print_vint("vadd", vadd(vec1, vec2));
    print_vint("vsub", vsub(vec1, vec2));
    print_vint("vband", vband(vec1, vec2));
    print_vint("vbor", vbor(vec1, vec2));
    print_vint("vbxor", vbxor(vec1, vec2));

    print_vint("vselect, vsgtmax", vmax(vec1, vec2));

    print_vbool("vseq", vseq(vec1, vec2));
    print_vbool("vsne", vsne(vec1, vec2));
    print_vbool("vslt", vslt(vec1, vec2));
    print_vbool("vsle", vsle(vec1, vec2));
    print_vbool("vsgt", vsgt(vec1, vec2));
    print_vbool("vsge", vsge(vec1, vec2));
    print_vbool("vsltu", vsltu(vec1u, vec2u));
    print_vbool("vsleu", vsleu(vec1u, vec2u));
    print_vbool("vsgtu", vsgtu(vec1u, vec2u));
    print_vbool("vsgue", vsgeu(vec1u, vec2u));

    initUpwards(largeA);
    initDownwards(largeB);
    initZero(largeC);
    print_large_array("largeA:", largeA);
    print_large_array("largeB:", largeB);
    print_large_array("largeC:", largeC);

    do_add(largeC, largeA, largeB);
    print_large_array("do_add:", largeC);
    
    do_max(largeC, largeA, largeB);
    print_large_array("do_max:", largeC);

    return 1;
}


