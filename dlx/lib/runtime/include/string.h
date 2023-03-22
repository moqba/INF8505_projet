/*
-- File: string.h
--
-- Contents: ISO C99 Standard, 7.21 String handling <string.h>
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



#ifndef _STRING_H
#define	_STRING_H

#include <stddef.h>

#if defined(__cplusplus) || defined(__ndl__)
extern "C" {
#endif

// copying
void *memcpy(void * restrict s1, const void * restrict s2, size_t n); 
void *memmove(void *s1, const void *s2, size_t n);
char *strcpy(char * restrict s1, const char * restrict s2);
char *strncpy(char * restrict s1, const char * restrict s2, size_t n);

// concatenation
char *strcat(char * restrict s1, const char * restrict s2);
char *strncat(char * restrict s1, const char * restrict s2, size_t n);

// comparison
int memcmp(const void *s1, const void *s2, size_t n);
int strcmp(const char *s1, const char *s2);
inline int strcoll(const char *s1, const char *s2) { return strcmp(s1,s2); }
int strncmp(const char *s1, const char *s2, size_t n);
size_t strxfrm(char * restrict s1, const char * restrict s2, size_t n);

// search
void *memchr(const void *s, int c, size_t n);
char *strchr(const char *s, int c);
size_t strcspn(const char *s1, const char *s2); 
char *strpbrk(const char *s1, const char *s2);
char *strrchr(const char *s, int c);
size_t strspn(const char *s1, const char *s2);
char *strstr(const char *s1, const char *s2);
char *strtok(char * restrict s1, const char * restrict s2);

// miscellaneous
void *memset(void *s, int c, size_t n);
char *strerror(int errnum);
size_t strlen(const char *s);

#if defined(__cplusplus) || defined(__ndl__)
} // extern "C"
#endif

#endif /* string.h */
