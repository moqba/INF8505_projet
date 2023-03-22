
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#ifdef __cplusplus
#error "This file is not intended to be compiled in C++ mode (C99 inline semantics)"
#endif

// Generate out-of-line versions of inline functions in this compilation unit

extern inline int strcoll(const char *s1, const char *s2);

extern inline int atoi(const char *nptr);
extern inline long atol(const char *nptr);
extern inline void exit(int status);
extern inline void abort();
extern inline void _Exit(int status);
extern inline int atexit( void (*func)() );

extern inline int vprintf(const char* format, va_list ap);
extern inline int vscanf(const char* format, va_list ap);
extern inline int putc(int c, FILE* stream);
extern inline int putchar(int c);
extern inline int puts(const char* s);
extern inline int getc(FILE* stream);
extern inline int getchar();
extern inline void rewind(FILE* stream);

extern inline int isalnum(int c);
extern inline int isalpha(int c);
extern inline int isblank(int c);
extern inline int iscntrl(int c);
extern inline int isdigit(int c);
extern inline int isgraph(int c);
extern inline int islower(int c);
extern inline int isprint(int c);
extern inline int ispunct(int c);
extern inline int isspace(int c);
extern inline int isupper(int c);
extern inline int isxdigit(int c);
extern inline int tolower(int c);
extern inline int toupper(int c);
