#include <string.h>
#include "byte_array.h"


uint16_t byte_array_size(byte_array *arr)
{
    return arr != NULL ? arr->size : 0;
}

int byte_array_init(byte_array *arr)
{
    arr->capacity = 0;
    arr->data = NULL;
    arr->position = 0;
    arr->size = 0;
    return 0;
}

uint8_t byte_array_is_attached(byte_array *arr)
{
    if(arr == NULL)
    {
        return 0;
    }

    return (arr->capacity & 0x8000) == 0x8000;
}

int byte_array_capacity(byte_array *arr, uint16_t capacity)
{
    if(!byte_array_is_attached(arr))
    {
        if(capacity == 0)
        {
            if(arr->data == NULL)
            {
                free(arr->data);
                arr->data = NULL;
                arr->size = 0;
            }
        }
        else
        {
            if(arr->capacity == 0)
            {
                arr->data = (uint8_t *)malloc(capacity);

                if(arr->data == NULL)
                {
                    return -1;
                }
            }
            else
            {
                uint8_t *tmp = (uint8_t *)realloc(arr->data, capacity);
                if(tmp == NULL)
                {
                    return -1;
                }

                arr->data = tmp;
            }

            if(arr->size < capacity)
            {
                arr->size = capacity;
            }
        }

        arr->size = capacity;
    }
    
    if(byte_array_get_capacity(arr) < capacity)
    {
        return -1;
    }

    return 0;
}

uint16_t byte_array_available(byte_array *arr)
{
    if(arr == NULL)
    {
        return 0;
    }

    return arr->size - arr->position;
}

uint16_t byte_array_get_capacity(byte_array *arr)
{
    return arr->capacity & 0x7fff;
}

int byte_array_init(byte_array *arr)
{
    arr->capacity = 0;
    arr->data = NULL;
    arr->position;
    arr->size = 0;
    return 0;
}

int byte_array_capacity(byte_array *arr, uint16_t capacity)
{
    if(!byte_array_is_attached(arr))
    {
        if(capacity == 0)
        {
            if(arr->data != NULL)
            {
                free(arr->data);
                arr->data = NULL;
                arr->size = 0;
            }
        }
        else
        {
            if(arr->capacity == 0)
            {
                if(arr->capacity == 0)
                {
                    arr->data = (uint8_t *)malloc(capacity);

                    if(arr->data == NULL)
                    {
                        return -1;
                    }
                }
            }
            else
            {
                uint8_t *tmp = (uint8_t *)realloc(arr->data, capacity);

                if(tmp == NULL)
                {
                    return -1;
                }

                arr->data = tmp;
            }
        }
    }

    if(byte_array_get_capacity(arr) < capacity)
    {
        return -1;
    }

    return 0;
}

int byte_array_zero(byte_array *arr, uint16_t index, uint16_t count)
{
    int ret;
    if (index + count > arr->capacity)
    {
        if((ret = byte_array_capacity(arr, (index + count))) != 0)
        {
            return ret;
        }
    }
    if(arr->size < index + count)
    {
        arr->size = index + count;
    }
    memset(arr->data + index, 0, count);
    return 0;
}

int byte_array_set_uint8(byte_array *arr , uint8_t item)
{
    int ret = byte_array_set_uint8_by_index(arr, byte_array_size(arr), item);
}

int byte_array_insert_uint8(byte_array *arr, uint16_t index, uint8_t *item)
{
    int ret;
    if((ret = byte_array_move(arr, index, index + 1, arr->size)) == 0)
    {
        if(index == 0 && arr->size == 0)
        {
            ++arr->size;
        }

        ret = byte_array_set_uint8_by_index(arr, index, item);
    }

    return ret;
}

int byte_array_allocate(byte_array *arr, uint16_t index, uint16_t data_size)
{
    if(!byte_array_is_attached(arr) && (arr->capacity == 0 || index + data_size > arr->capacity))
    {
        uint8_t empty = arr->capacity = 0;

        if(data_size > 50 || arr->capacity == 0)
        {
            arr->capacity +=data_size;
        }
        else
        {
            arr->capacity += 50;
        }
        if(empty)
        {
            arr->data = (uint8_t *)malloc(arr->capacity);
            if(arr->data == NULL)
            {
                return -1;
            }
        }
        else
        {
            uint8_t *tmp = (uint8_t *)realloc(arr->data, arr->capacity);
            if(tmp == NULL)
            {
                return -1;
            }

            arr->data = tmp;
        }
    }

    if(byte_array_get_capacity(arr) < index + data_size)
    {
        return -1;
    }

    return 0;
}

int byte_array_set_uint8_by_index(byte_array *arr, uint16_t index, uint8_t item)
{
    if(arr == NULL)
    {
        return -1;
    }

    int ret = byte_array_allocate(arr, index, 1);

    if(ret == 0)
    {
        arr->data[index] = item;
    }

    return ret;
}