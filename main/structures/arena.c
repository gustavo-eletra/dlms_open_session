#include "arena.h"

uintptr_t align_forward(uintptr_t ptr, size_t aligment)
{
    uintptr_t p, a, modulo;
    if(!is_power_of_two(aligment))
    {
        return 0;
    }

    p = ptr;

    a = (uintptr_t)aligment;
    modulo = p & (a - 1);

    if(modulo)
    {
        p += a - modulo;
    }

    return p;
}

void *arena_alloc_aligned(arena *a, size_t size, size_t aligment)
{
    uintptr_t curr_ptr = (uintptr_t)a->base + (uintptr_t)a->offset;
    uintptr_t offset = align_forward(curr_ptr, aligment);
    offset -= (uintptr_t)a->base;

    if(offset + size > a->size)
    {
        return 0;
    }

    a->commited += size;
    void *ptr = (uint8_t *)a->base + offset;
    a->offset = offset + size;

    return ptr;
}

void *arena_alloc(size_t size, void *context)
{
    if(!size)
    {
        return 0;
    }

    return arena_alloc_aligned((arena *) context, size, DEFAULT_ALIGNMENT);
}

void arena_free(size_t size, void *ptr, void *context)
{
    (void)ptr; (void)size; (void)context;
}

void arena_free_all(void *context)
{
    arena *a = context;
    a->offset = 0;
    a->commited = 0;   
}

arena arena_init(void *buffer, size_t size)
{
    return (arena){.base = buffer, .size = size};
}