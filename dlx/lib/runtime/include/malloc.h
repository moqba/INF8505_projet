/*
-- File: malloc.h
--
-- Contents : ISO C99 Standard, Memory management functions <malloc.h>
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



#ifndef _MALLOC_H
#define _MALLOC_H

#include <stddef.h>

#if defined(__cplusplus) || defined(__ndl__)
extern "C" {
#endif

// 7.20.3 Memory management functions

void *malloc(size_t size);

void free(void *ptr);

void *calloc(size_t nmemb, size_t size);

void *realloc(void *ptr, size_t size);

#if defined(__cplusplus) || defined(__ndl__)
} // extern "C"
#endif


#endif
