
#include <math.h>

#ifdef __cplusplus
#error "This file is not intended to be compiled in C++ mode (C99 inline semantics)"
#endif

// Generate out-of-line versions of inline functions in this compilation unit
extern inline float fabsf(float a);
extern inline float copysignf(float x, float y);
extern inline double fabs(double a);
extern inline double copysign(double x, double y);
extern inline float  ldexpf(float  x, int i);
extern inline double ldexp (double x, int i);
extern inline float  ceilf (float  x);
extern inline double ceil  (double x);
extern inline float  floorf(float  x);
extern inline double floor (double x);
extern inline float  roundf(float  x);
extern inline double round (double x);
extern inline float  cosf  (float  x);
extern inline double cos   (double x);
extern inline float  sinf  (float  x);
extern inline double sin   (double x);
extern inline float  expf  (float  x);
extern inline double exp   (double x);
extern inline float  logf  (float  x);
extern inline double log   (double x);
extern inline float  log10f(float  x);
extern inline double log10 (double x);
extern inline float  sqrtf (float  x);
extern inline double sqrt  (double x);
extern inline float  powf  (float  x, float  y);
extern inline double pow   (double x, double y);
extern inline double fmod  (double x, double y);
extern inline float  acosf (float  x);
extern inline double acos  (double x);
extern inline float  asinf (float  x);
extern inline double asin  (double x);
extern inline double atan  (double x);
extern inline float  atan2f(float y,  float x);
extern inline double atan2 (double y, double x);
extern inline float  truncf(float  x);
extern inline double trunc (double x);
extern inline float  frexpf(float  a, int* e);
extern inline double frexp (double a, int* e);
