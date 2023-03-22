
#include <math.h>

#ifdef __cplusplus
#error "This file is not intended to be compiled in C++ mode (C99 inline semantics)"
#endif

// Generate out-of-line versions of inline functions in this compilation unit
extern inline float fabsf(float a);
extern inline float copysignf(float x, float y);
extern inline double fabs(double a);
extern inline double copysign(double x, double y);
extern inline float  truncf(float  x);
extern inline double trunc (double x);
extern inline float  frexpf(float  a, int* e);
extern inline double frexp (double a, int* e);
