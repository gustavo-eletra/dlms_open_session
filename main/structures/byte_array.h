#pragma once
#include <stdint.h>
#include <structures/arena.h>

//TODO: Make functions that allocate and dealocate in the arena

typedef struct
{
    uint8_t *data;
    uint16_t capacity;
    uint16_t size;
    uint16_t position;
} byte_array;

//Byte array/buffer
uint8_t byte_array_is_attached(byte_array *arr);
uint16_t byte_array_available(byte_array *arr);
int byte_array_init(byte_array *arr);
int byte_array_zero(byte_array *arr);
int byte_array_insert_byte(byte_array *arr, uint16_t index, uint8_t item);
int byte_array_alloc(byte_array *arr, uint16_t index, uint16_t data_size);
int byte_array_arena_alloc(byte_array *arr, uint16_t index, uint16_t data_size, allocator *alloc);
int byte_array_set_byte(byte_array *arr, uint8_t item);
int byte_array_set_byte_by_index(byte_array *arr, uint16_t index, uint8_t item);
int byte_array_set_uint16(byte_array *arr, uint16_t item);
int byte_array_set_uint16_by_index(byte_array *arr, uint16_t index, uint16_t item);
int byte_array_set_uint32(byte_array *arr, uint32_t item);
int byte_array_set_uint32_by_index(byte_array *arr, uint16_t index, uint32_t item);
int byte_array_attach(byte_array *arr, uint8_t *value, uint16_t count, uint16_t capacity);
int byte_array_is_empty(byte_array *arr);
int byte_array_clear(byte_array *arr);
int byte_array_get(byte_array *arr, uint8_t *value, uint16_t count);