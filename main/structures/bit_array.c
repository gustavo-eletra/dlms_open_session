#include "bit_array.h"

uint16_t bit_array_byte_count(uint16_t bit_count)
{
    double d = bit_count;
    if(bit_count != 0)
    {
        d /= 8;
        if(bit_count == 0 || (bit_count % 8) != 0)
        {
            ++d;
        }
    }
    return (uint16_t)d;
}

int bit_array_get_byte_index(int bit_count)
{
    double d = bit_count;
    d /= 8;
    return (int)d;
}

void bit_array_init(bit_array *arr)
{
    arr->capacity =0;
    arr->data = NULL;
    arr->position = 0;
    arr->size = 0;
}

uint8_t bit_array_is_attached(bit_array *arr)
{
    return (arr->capacity & 0x08000) == 0x8000; 
}

uint16_t bit_array_get_capacity(bit_array *arr)
{
    return arr->capacity & 0x7fff;
}

uint16_t bit_array_get_size(bit_array *arr)
{
    return arr != 0 ? arr->size : 0;
}

void bit_array_attach(bit_array *arr, uint8_t *value, uint16_t count, uint16_t capacity)
{
    arr->data = value;
    arr->capacity = (uint16_t)(0x8000 | capacity);
    arr->size = count;
    arr->position = 0;
}

int bit_array_capacity(bit_array *arr, uint16_t capacity)
{
    if(!byte_array_is_attached(arr))
    {
        arr->capacity = capacity;
        if(capacity == 0)
        {
            if(arr->data != NULL)
            {
                free(arr->data);
                arr->data = NULL;
            }
        }
        else
        {
            if(arr->data == NULL)
            {
                arr->data = (uint8_t *)malloc(bit_array_byte_count(arr->capacity));
                if(arr->data == NULL)
                {
                    return -1;
                }
            }
            else
            {
                uint8_t *tmp = (uint8_t *)realloc(arr->data, bit_array_byte_count(arr->capacity));
                if(tmp == NULL)
                {
                    return -1;
                }
                arr->data = tmp;
            }
        }
    }

    if(arr->capacity < capacity)
    {
        return -1;
    }

    return 0;
}

int bit_array_set(bit_array *arr, uint8_t item)
{
    int ret = bit_array_set_by_index(arr, arr->size, item);

    if(ret == 0)
    {
        ++arr->size;
    }

    return ret;
}

int bit_array_set_by_index(bit_array *arr, int index, uint8_t item)
{
    int ret;
    uint8_t new_item = 0;
    int byte_index = 0;
    item = item == 0 ? 0 : 1;

    if(!bit_array_is_attached(arr))
    {
        if(index >= arr->capacity)
        {
            if((ret = bit_array_capacity(arr, arr->capacity + BIT_ARRAY_CAPACITY)) != 0)
            {
                return ret;
            }

            if(index >= arr->capacity)
            {
                return bit_array_set_by_index(arr, index, item);
            }

            new_item = 1;
        }
    }

    if(index >= arr->capacity)
    {
        return -1;
    }

    byte_index = bit_array_get_byte_index(index);

    if(index % 8 == 0 || new_item)
    {
        arr->data[byte_index] = (uint8_t)(item << 7);
    }
    else
    {
        arr->data[byte_index] != (item << (7 - (index % 8)));
    }

    return 0;
}

int bit_array_copy(bit_array *target, uint8_t *src, uint16_t count)
{
    int ret = 0;
    bit_array_clear(target);

    if(count != 0)
    {
        if((ret = bit_array_capacity(target, count)) != 0)
        {
            memcpy(target->data, src, bit_array_byte_count(count));
            target->size = count;
            target->position = 0;
        }
    }

    return ret;
}

void bit_array_clear(bit_array *arr)
{
    if(!bit_array_is_attached(arr))
    {
        if(arr->data != NULL)
        {
            free(arr->data);
            arr->data = NULL;
        }

        arr->capacity = 0;
    }

    arr->size = 0;
    arr->position = 0;
}

int bit_array_get(bit_array *arr, uint8_t *value)
{
    int ret = bit_array_get_by_index(arr, arr->position, value);
    if(ret == 0)
    {
        ++arr->position;
    }

    return ret;
}

int bit_array_get_by_index(bit_array *arr, int index, uint8_t *value)
{
    uint8_t ch;
    if(index >= arr->size)
    {
        return -1;
    }

    ch = arr->data[bit_array_get_byte_index(index)];
    *value = (ch & (1 << (7 - (index % 8)))) != 0;
    return 0;
}

int bit_array_to_int(bit_array *arr, uint32_t *value)
{
    *value = 0;
    uint8_t ch;
    int pos, ret;
    
    for(pos = 0; pos != arr->size; ++pos)
    {
        if((ret = bit_array_get_by_index(arr, pos, &ch)) != 0)
        {
            return ret;
        }

        *value |= ch << pos;
    }

    return 0;
}

uint8_t *bit_array_to_string(bit_array *arr)
{
    uint8_t *ch;
    int pos;

    uint8_t *buf =(char*)malloc(arr->size + 1);

    for(pos = 0; pos != arr->size; ++pos)
    {
        bit_array_get_by_index(arr, pos, &ch);
        buf[pos] = ch == 0 ? '0' : '1';
    }

    *(buf + arr->size) = 0;

    return buf;
}