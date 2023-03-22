/*
-- File: stdio_native.c
--
-- Contents: C library, Input/output (only the subset related to file I/O).
--           Native implementation of fread_word and fwrite_word.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



#include <stdio.h>

size_t fwrite_word(const void* ptr, size_t size, size_t nword, int lsb_first, FILE* fp)
{
    size_t i = 0;
    for (; i < nword; i++) {
	unsigned w = ((unsigned*)ptr)[i];
	if (lsb_first) 
	    for (size_t j = 0; j < size; j++) {
		unsigned char c = w & 0xff;
		if (fwrite(&c,1,1,fp))
		    w >>= 8;
		else
		    return i;
	    }
	else
	    for (int j = size - 1; j >= 0; j--) {
		unsigned char c = w >> (j*8) & 0xff;
		if (!fwrite(&c,1,1,fp))
		    return i;
	    }
    }
    return i;
}

size_t fread_word(void* ptr, size_t size, size_t nword, int lsb_first, FILE* fp)
{
    size_t i = 0;
    for (; i < nword; i++) {
	unsigned w = 0;
	if (lsb_first) 
	    for (size_t j = 0; j < size; j++) {
		unsigned char c;
		if (fread(&c,1,1,fp))
		    w |= (unsigned)c << (j * 8);
		else
		    return i;
	    }
	else
	    for (size_t j = 0; j < size; j++) {
		unsigned char c;
		if (fread(&c,1,1,fp))
		    w = (w << 8) | c;
		else
		    return i;
	    }
	((unsigned*)ptr)[i] = w;
    }
    return i;
}
