#pragma once
#include "../structures/byte_array.h"

#define MESSAGE_CAPACITY 2

typedef struct 
{
    byte_array **data;
    uint8_t capacity;
    uint8_t size;
    uint8_t attached;
}message;

void messsage_init(message *msg);
void message_attach(message *msg,  byte_array **data, uint8_t capacity);
void message_clear(message *msg);
int message_push(message *msg, byte_array *item);