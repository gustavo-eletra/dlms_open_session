#pragma once
#include <stdint.h>
#include "byte_array.h"

#define BIT_ARRAY_CAPACITY 8

typedef byte_array bit_array;

void bit_array_init(bit_array *arr);
void bit_array_clear(bit_array *arr);
void bit_array_attach(bit_array *arr, uint8_t *value, uint16_t count, uint16_t capacity);
uint8_t bit_array_is_attached(bit_array *arr);
uint8_t *bit_array_to_string(bit_array *arr);
uint16_t bit_array_get_capacity(bit_array *arr);
uint16_t bit_array_byte_count(uint16_t bit_count);
uint16_t bit_array_get_size(bit_array *arr);
int bit_array_set(bit_array *arr, uint8_t item);
int bit_array_set_by_index(bit_array *arr, int index, uint8_t item);
int bit_array_get_by_index(bit_array *arr, int index, uint8_t *value);
int bit_array_get_byte_index(int bit_count);
int bit_array_capacity(bit_array *arr, uint16_t capacity);
int bit_array_copy(bit_array *target, uint8_t *src, uint16_t count);
int bit_array_get(bit_array *arr, uint8_t *value);
int bit_array_to_int(bit_array *arr, uint32_t *value);
