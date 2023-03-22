/*
-- File: malloc.c
--
-- Contents: C library, Memory management functions <malloc.h>
--
-- Copyright (c) 2017 Synopsys, Inc. This processor model and the associated
-- documentation are proprietary to Synopsys, Inc.  This model may only be
-- used in accordance with the terms and conditions of a written license
-- agreement with Synopsys, Inc.  All other use, reproduction, or distribution
-- of this model are strictly prohibited.
*/


#include <malloc.h>
#include <string.h>
#include <stddef.h>

/*
 *  Memory allocator based on the "Double Linked Free Storage" allocator
 *  described in
 *
 *    "Data Structures and Algorithms with Object-Oriented Design Patterns
 *    in C++" by Bruno R. Preiss.
 *    http://www.brpreiss.com/books/opus4/html/page426.html
 *
 *  The storage pool is an array of fixed size blocks. A block has a size of
 *  16 bytes and has the following structure, depending on whether is it
 *  reserved or free.
 *
 *    Reserved block                  Free block
 *    +-+--------------+              +-+--------------+
 *    |1|    length    |	      |0|    length    |
 *    +-+--------------+	      +-+--------------+
 *    |                |	      |      next      |
 *    +----------------+	      +----------------+
 *    |                |	      |      prev      |
 *    +----------------+	      +----------------+
 *    |                |	      |                |
 *    +----------------+	      +----------------+
 *
 *  In case a memory chunk of more than 12 bytes is requested, multiple
 *  blocks are coalesced.
 *
 *  All free blocks are collected in a doubly linked list.  The malloc function
 *  uses a first fit allocation strategy. As a side ellect malloc coalesces
 *  adjacent free blocks.
 */

#ifndef __clang__
#define bitsizeof(T) chess_bitsof(T)
#else
#define bitsizeof(T) (__CHAR_BIT__*sizeof(T))
#endif

#define BLOCK_WORDS 4

typedef struct MBlock_
{
    unsigned head;
    union
    {
	struct {
	    struct MBlock_* next;
	    struct MBlock_* prev;
	} link;
	unsigned user_part[BLOCK_WORDS-1]; // block size = BLOCK_WORDS * sizeof(unsigned) (e.g. 4 * 4 = 16 bytes)
    } u;
} MBlock_;

#define HDR_LENGTH   (~(1<<(bitsizeof(unsigned)-1)))
#define HDR_RESERVED (1<<(bitsizeof(unsigned)-1))

#ifdef __clang__
#define INLINE __attribute__((always_inline)) inline
#else
#define INLINE inline
#endif

const int nr_of_blocks = 1024; // heap of 1024 blocks (e.g. 16K in case of 16 byte blocks)
static MBlock_ pool[nr_of_blocks+1];
static MBlock_* sentinel = 0;

INLINE int length(MBlock_* b) { return b->head & HDR_LENGTH; }

INLINE int is_reserved(MBlock_* b) { return b->head & HDR_RESERVED; }

INLINE void set_reserved(MBlock_* b)   { b->head |= HDR_RESERVED; }
INLINE void clear_reserved(MBlock_* b) { b->head &= ~HDR_RESERVED; }

INLINE void set_head(MBlock_* b, int res, int len) {
    b->head = res << (bitsizeof(int)-1) | len;
}

INLINE void add_length(MBlock_* b, int len) {
    b->head = b->head & HDR_RESERVED | (length(b) + len);
}

INLINE void insert_after(MBlock_* a, MBlock_* b)
{
    a->u.link.next->u.link.prev = b;
    b->u.link.next = a->u.link.next;
    b->u.link.prev = a;
    a->u.link.next = b;
}

INLINE void unlink(MBlock_* a)
{
    a->u.link.prev->u.link.next = a->u.link.next;
    a->u.link.next->u.link.prev = a->u.link.prev;
}

static void init()
{
    sentinel = &pool[nr_of_blocks];
    set_head(sentinel,1,0);
    sentinel->u.link.next = sentinel;
    sentinel->u.link.prev = sentinel;

    MBlock_* first = &pool[0];
    set_head(first,0,nr_of_blocks);
    insert_after(sentinel,first);
}

void free(void* p)
{
    if (p) {
        MBlock_* block = (MBlock_*)((char*)p - offsetof(MBlock_,u));
        clear_reserved(block);
        insert_after(sentinel,block);
    }
}

void* malloc(size_t bytes)
{

    if (!sentinel)
	init();

    // note: no guard against excessive values of `bytes'
    int blocks =
	(bytes + sizeof (unsigned) + sizeof (MBlock_) - 1U) / sizeof (MBlock_);

    MBlock_* ptr = sentinel;
    int len;
    do {
        ptr = ptr->u.link.next;
        if (ptr == sentinel)
            return 0;

        len = length(ptr);

        // merge candidate block with unreserved successors
	for (;;) {
	    MBlock_* successor = ptr + len;
	    if (is_reserved(successor))
		break;
            len += length(successor);
	    unlink(successor);
            set_head(ptr,0,len);
	}
    } while (len < blocks);

    // split off new block if candidate too large
    if (len > blocks) {
	MBlock_* new_block = ptr + blocks;
	set_head(new_block,0,len-blocks);
	insert_after(sentinel,new_block);
    }
    set_head(ptr,1,blocks);
    unlink(ptr);
    return ptr->u.user_part;
}

INLINE int block_size(void* p)
{
    MBlock_* block = (MBlock_*)((char*)p - offsetof(MBlock_,u));
    return (length(block)) * sizeof(MBlock_) - sizeof(unsigned);
}

void *calloc(size_t nmemb, size_t size)
{
    void* p;
    p = malloc(nmemb * size);
    if (p)
        memset(p,0,nmemb*size);
    return p;
}

void *realloc(void *ptr, size_t size)
{
    if (ptr) {
	if (size == 0)  {
	    free(ptr);
	    return 0;
	}
        void* p = malloc(size);
	if (p) {
	    unsigned old_size = block_size(ptr);
	    memcpy(p, ptr, old_size < size ? old_size : size);
	    free(ptr);
	}
	return p;
    }
    else
        return malloc(size);
}
