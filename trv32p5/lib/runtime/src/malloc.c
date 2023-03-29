/*
-- File: malloc.c
--
-- Contents: C library, Memory management functions <malloc.h>
--
-- Copyright (c) 2017-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include <malloc.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus) || defined(__ndl__)
extern "C" {
#endif

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
 *    |1|    length    |              |0|    length    |
 *    +-+--------------+              +-+--------------+
 *    |                |              |      next      |
 *    +----------------+              +----------------+
 *    |                |              |      prev      |
 *    +----------------+              +----------------+
 *    |                |              |                |
 *    +----------------+              +----------------+
 *
 *  In case a memory chunk of more than 12 bytes is requested, multiple
 *  blocks are coalesced.
 *
 *  All free blocks are collected in a doubly linked list.  The malloc function
 *  uses a first fit allocation strategy. As a side ellect malloc coalesces
 *  adjacent free blocks.
 *
 *  ASSUMPTIONS
 *  1) The size of the struct MBlock_ should be equal to BLOCK_WORDS times the
 *     size of the word type (unsigned or unsigned long).
 *  2) The word type should be a type of maximal alignment, since malloc needs
 *     to return maximally aligned pointers.
 */

#define BLOCK_WORDS 4
typedef unsigned long word_type;

typedef struct MBlock_
{
    word_type head;
    union
    {
        struct {
            struct MBlock_* next;
            struct MBlock_* prev;
        } link;
        word_type user_part[BLOCK_WORDS-1]; // block size = BLOCK_WORDS * sizeof(word_type) (e.g. 4 * 4 = 16 bytes)
    } u;
} MBlock_;

#define HDR_LENGTH   (~(1UL<<(chess_bitsof(word_type)-1)))
#define HDR_RESERVED (1UL<<(chess_bitsof(word_type)-1))

#ifdef __clang__
#define INLINE __attribute__((always_inline)) inline
#else
#define INLINE inline
#endif

const size_t nr_of_blocks = 16384; // heap of 16384 blocks * 16 bytes = 262144
static MBlock_ pool[nr_of_blocks+1];
static MBlock_* sentinel = 0;

INLINE word_type length(MBlock_* b) { return b->head & HDR_LENGTH; }

INLINE word_type is_reserved(MBlock_* b) { return b->head & HDR_RESERVED; }

INLINE void set_reserved(MBlock_* b)   { b->head |= HDR_RESERVED; }
INLINE void clear_reserved(MBlock_* b) { b->head &= ~HDR_RESERVED; }

INLINE void set_head(MBlock_* b, word_type res, word_type len) {
    b->head = res << (chess_bitsof(word_type)-1) | len;
}

INLINE void add_length(MBlock_* b, word_type len) {
    b->head = (b->head & HDR_RESERVED) | (length(b) + len);
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
#ifndef NDEBUG
    chess_assert(sizeof(MBlock_) == (BLOCK_WORDS * sizeof(word_type)));
#endif
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
    word_type blocks =
        (bytes + sizeof (word_type) + sizeof (MBlock_) - 1U) / sizeof (MBlock_);

    MBlock_* ptr = sentinel;
    word_type len;
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
#ifndef NDEBUG
    intptr_t r = (intptr_t)(void*)ptr->u.user_part;
    chess_assert((r % 4) == 0);
#endif
    return ptr->u.user_part;
}

INLINE word_type block_size(void* p)
{
    MBlock_* block = (MBlock_*)((char*)p - offsetof(MBlock_,u));
    return (length(block)) * sizeof(MBlock_) - sizeof(word_type);
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
            size_t old_size = block_size(ptr);
            memcpy(p, ptr, old_size < size ? old_size : size);
            free(ptr);
        }
        return p;
    }
    else
        return malloc(size);
}

#if defined(__cplusplus) || defined(__ndl__)
} // extern "C"
#endif
