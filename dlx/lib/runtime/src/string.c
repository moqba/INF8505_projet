/*
-- File string.c
--
-- Contents: C library, implementation of ISO C99 <string.h> functions.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/


#include <string.h>

// copying

void* memcpy(void * restrict s1, const void * restrict s2, size_t n)
{
    char* ll = (char*)s1;
    char* rr = (char*)s2;
    for (size_t i = 0; i < n; i++) ll[i] = rr[i];
    return s1;
}

void* memmove(void *s1, const void *s2, size_t n)
//  s1 and s2 can overlap    
{
    char* ll = (char*)s1;
    char* rr = (char*)s2;
    if (ll <= rr)
	for (size_t i = 0; i < n; i++) ll[i] = rr[i];
    else
	for (int i = n-1; i >= 0; i--) ll[i] = rr[i];
    return s1;
}

char* strcpy(char * restrict s1, const char * restrict s2)
{
    char* result = s1;
    while (*s1++ = *s2++);
    return result;
}

char* strncpy(char * restrict s1, const char * restrict s2, size_t n)
//  copy exact n characters, add zeros if s2 is shorter than n    
{
    char* result = s1;
    ptrdiff_t ns = n;
    while (ns-- && (*s1++ = *s2++));
    while (ns-- > 0)  // "ns" must be signed when s2 is not shorter than n
	*s1++ = 0;
    return result;
}

// concatenation

char* strcat(char * restrict s1, const char * restrict s2)
{
    char* result = s1;
    while (*s1++); s1--;
    while (*s1++ = *s2++);
    return result;
}

char* strncat(char * restrict s1, const char * restrict s2, size_t n)
//  at most n characters from s2 excluding zero, then still add one zero,
//  implying that n+1 positions can be written.    
{
    char* result = s1;
    while (*s1++); s1--;
    char c;
    while (n-- && (c = *s2++)) *s1++ = c;
    *s1 = 0;
    return result;
}

// comparison (based on unsigned chars)

int memcmp(const void *s1, const void *s2, size_t n)
{
    char *r1 = (char*) s1;
    char *r2 = (char*) s2;
    while (n--) {
	char c1 = *r1++;
	char c2 = *r2++;
	if (c1 != c2)
	    return (unsigned char)c1 - (unsigned char)c2;
    }
    return 0;
}

int strcmp(const char *s1, const char *s2)
{
    while (1) {
	char c1 = *s1++;
	char c2 = *s2++;
	if (c1 != c2 || c1 == 0)
	    return (unsigned char)c1 - (unsigned char)c2;
    }
}

int strncmp(const char *s1, const char *s2, size_t n)
//  compare at most n characters    
{
    while (n--) {
	char c1 = *s1++;
	char c2 = *s2++;
	if (c1 != c2 || c1 == 0)
	    return (unsigned char)c1 - (unsigned char)c2;
    }
    return 0;
}

size_t strxfrm(char * restrict s1, const char * restrict s2, size_t n)
//  just copy s2 as strcoll == strcmp in C locale
{
    size_t result = strlen(s2);
    if (result < n)
	for (size_t i = 0; i <= result; i++) chess_loop_range(1,)
	    s1[i] = s2[i];
    return result;
}

// search

void* memchr(const void *s, int c, size_t n)
//  look for (unsigned char)c including zero
{
    unsigned char* r = (unsigned char*)s;
    while (n--) {
	unsigned char d = *r++;
	if (d == (unsigned char)c)
	    return r-1;
    }
    return 0;
}

char* strchr(const char *s, int c)
//  look for (char)c including zero
{
    char d;
    do {
	d = *s++;
	if (d == (char)c)
	    return (char*)(s-1);
    } while (d);
    return 0;
}

size_t strcspn(const char *s1, const char *s2)
//  length of s1 segment excluding any s2 char    
{
    const char* r1 = s1;
    while (1) {
	char c = *r1++;
	const char* r2 = s2;
	char d;
	do {
	    d = *r2++;
	    if (c == d)
		return (r1-1) - s1;
	} while (d);
    }
}

char* strpbrk(const char *s1, const char *s2)
//  pointer to first char in s1 also belonging to s2    
{
    char c;
    while (c = *s1++) {
	const char* r2 = s2;
	char d;
	do {
	    d = *r2++;
	    if (c == d)
		return (char*)(s1-1);
	} while (d);
    }
    return 0;
}

char* strrchr(const char *s, int c)
//  last occurrence of (char)c in s, including zero char.    
{
    char* result = 0;
    char d;
    do {
	d = *s++;
	if (d == (char)c)
	    result = (char*)(s-1);
    } while (d);
    return result;
}

size_t strspn(const char *s1, const char *s2)
// length of s1 segment, consisting of s2 chars
{
    const char* r1 = s1;
    char c;
    while (c = *r1++) {
	const char* r2 = s2;
	char d;
	do {
	    d = *r2++;
	    if (c == d) break;
	} while (d);
	if (!d)
	    break;
    }
    return (r1-1) - s1;    
}

char* strstr(const char *s1, const char *s2)
// first occurrence of s2 in s1 (when s2 == "", return s1).
{
    do {
	const char* r1 = s1;
	const char* r2 = s2;
	while (1) {
	    char c1 = *r1++;
	    char c2 = *r2++;
	    if (c2 == 0)
		return (char*)s1;
	    if (c1 != c2)
		break;
	}
    } while (*s1++);
    return 0;
}

char* strtok(char * restrict s1, const char * restrict s2)
{
    static char* last;

    if (!s1 && !(s1 = last))
	return 0;
    
    // skip initial s2 chars (cf. strspn):

    char c;
    while (c = *s1++) {
	const char* r2 = s2;
	char d;
	do {
	    d = *r2++;
	    if (c == d) break;
	} while (d);
	if (!d)
	    break;
    }
    if (c == 0) {
	last = 0;
	return 0;
    }
    char* start = s1-1;

    // scan token (cf. strcspn) :

    char* r1 = s1;
    while (1) {
	char c = *r1++;
	const char* r2 = s2;
	char d;
	do {
	    d = *r2++;
	    if (c == d) {
		if (c == 0)
		    last = 0;
		else {
		    *(r1-1) = 0;
		    last = r1;
		}
		return start;
	    }
	} while (d);
    }
}
/*
char* strtok(char * restrict s1, const char * restrict s2)
//  by calling strspn() and strcspn(), but not much less instructions.
{
    static char* last;

    if (!s1 && !(s1 = last))
	return 0;
    
    // skip initial s2 chars (cf. strspn):

    s1 += strspn(s1,s2);
    if (*s1 == 0) {
	last = 0;
	return 0;
    }
    char* start = s1;

    // scan token (cf. strcspn) :

    s1 += strcspn(s1,s2);
    if (*s1)
	last = 0;
    else {
	*s1 = 0;
	last = s1+1;
    }
    return start;
}
*/

// miscellaneous

void *memset(void *s, int c, size_t n)
{
    unsigned char* ll = (unsigned char*)s;
    for (size_t i = 0; i < n; i++)
	ll[i] = (unsigned char)c;
    return s;
}

char *strerror(int errnum)
{
    return (char*)"";
}

size_t strlen(const char *s)
{
    const char* r = s;
    while (*r++);
    return (r - 1) - s;
}
