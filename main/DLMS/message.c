#include "message.h"

void messsage_init(message *msg)
{
    msg->capacity = MESSAGE_CAPACITY;
    msg->data = (byte_array**)malloc(msg->capacity * sizeof(byte_array*));
    msg->size = 0;
    msg->attached = 0;
}

void message_attach(message *msg,  byte_array **data, uint8_t capacity)
{
    msg->capacity = 0;
    msg->data = data;
    msg->capacity = 0;
    msg->attached = 1;
}

void message_clear(message *msg)
{
    int pos = 0;
    if (!msg->attached)
    {
        if (msg->size != 0)
        {
            for (pos = 0; pos != msg->size; ++pos)
            {
                free(msg->data[pos]->data);
                free(msg->data[pos]);
            }
        }
        if (msg->data != NULL)
        {
            free(msg->data);
            msg->data = NULL;
        }
        msg->capacity = 0;
    }
    msg->size = 0;
}

int message_push(message *msg, byte_array *item)
{
    if(msg->size == msg->capacity)
    {
        if(msg->attached)
        {
            return -1;
        }

        msg->capacity += MESSAGE_CAPACITY;

        if(msg->data == NULL)
        {
            msg->data = (byte_array**)realloc(msg->data, msg->capacity * sizeof(byte_array));
            if(msg->data == NULL)
            {
                return -1;
            }
        }
    }

    msg->data[msg->size] = item;
    ++msg->size;
    return 0;
}