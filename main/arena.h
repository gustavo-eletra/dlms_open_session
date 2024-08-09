#pragma once
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    void *(*alloc)(size_t size, void *context);
    void (*free)(size_t size, void *ptr, void *context);

    void *context;
}allocator;

#define make(T, n, a) ((T *)((a).alloc(sizeof(T) * n, (a).context)))
#define release(s, p, a) ((a).free(s, p, (a).context))
#define DEFAULT_ALIGNMENT (2 * sizeof(void *))

typedef struct
{
    void *base;
    size_t size;
    size_t offset;
    size_t commited;
}arena;

#define arena_alloc_init(a) (allocator){arena_alloc, arena_free, a}
#define is_power_of_two(x) ((x != 0) && ((x & (x - 1)) == 0))

uintptr_t align_forward(uintptr_t ptr, size_t aligment);
void *arena_alloc_aligned(arena *a, size_t size, size_t aligment);
void *arena_alloc(size_t size, void *context);
void arena_free(size_t size, void *ptr, void *context);
arena arena_init(void *buffer, size_t size);