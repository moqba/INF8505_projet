/*
-- File: malloc.c
--
-- Contents: C library, Memory management functions <malloc.h>
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#include <malloc.h>
#include <string.h>
#include <errno.h>

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
 */

#define bitsizeof(T) (8*sizeof(T))

struct MBlock_
{
    unsigned head;
    union
    {
        struct {
            MBlock_* next;
            MBlock_* prev;
        } link;
        char user_part[16 - sizeof(unsigned)]; // block size = 16
    } u;
};

#define HDR_LENGTH   0x7fffffff
#define HDR_FREE     0x7fffffff
#define HDR_RESERVED 0x80000000

const int nr_of_blocks = 1024;
static char chess_storage(DMb%4) pool[(nr_of_blocks+1) * sizeof(MBlock_)];
static MBlock_* sentinel=0;

inline int length(MBlock_* b) { return b->head & HDR_LENGTH; }

inline int is_reserved(MBlock_* b) { return b->head & HDR_RESERVED; }

inline void set_reserved(MBlock_* b) { b->head |= HDR_RESERVED; }

inline void set_head(MBlock_* b, int res, int len) {
    b->head = res << 31 | (len & HDR_LENGTH);
}

inline void add_length(MBlock_* b, int len) {
    b->head = b->head & HDR_RESERVED | (length(b) + len);
}

static inline void insert_after(MBlock_* a, MBlock_* b)
{
    if (a->u.link.next) a->u.link.next->u.link.prev = b;
    b->u.link.next = a->u.link.next;
    b->u.link.prev = a;
    a->u.link.next = b;
}

static inline void unlink(MBlock_* a)
{
    if (a->u.link.prev) a->u.link.prev->u.link.next = a->u.link.next;
    if (a->u.link.next) a->u.link.next->u.link.prev = a->u.link.prev;
}

static void init()
{
    sentinel = (MBlock_*)pool + nr_of_blocks;
    set_head(sentinel,1,0);
    sentinel->u.link.next = sentinel;
    sentinel->u.link.prev = sentinel;

    MBlock_* first = (MBlock_*)pool;
    set_head(first,0,nr_of_blocks);
    insert_after(sentinel,first);
}

void free(void* p)
{
    if (p) {
        MBlock_* block = (MBlock_*)((unsigned*)p-1);
        set_head(block,0,length(block));
        insert_after(sentinel,block);
    }
}

void* malloc(size_t bytes)
{

    if (!sentinel)
        init();

    unsigned int const blocks =
        (bytes + sizeof (unsigned) + sizeof (MBlock_) - 1U) / sizeof (MBlock_);

    MBlock_* ptr;
    for (ptr = sentinel->u.link.next; ptr != sentinel; ptr = ptr->u.link.next) {
        for (;;) {
            MBlock_* successor = &ptr[length(ptr)];
            if (is_reserved(successor))
                break;
            unlink(successor);
            add_length(ptr,length(successor));
        }
        if (length(ptr) >= blocks)
            break;
    }
    if (ptr == sentinel)
        return 0;
    if (length(ptr) > blocks) {
        MBlock_* new_block = &ptr[blocks];
        set_head(new_block,0,length(ptr)-blocks);
        set_head(ptr,1,blocks);
        insert_after(sentinel,new_block);
    }
    unlink(ptr);
    set_reserved(ptr);
    return ptr->u.user_part;
}

int block_size(void* p)
{
    MBlock_* block = (MBlock_*)((unsigned*)p-1);
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

