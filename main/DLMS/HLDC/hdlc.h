#pragma once
#include <stdio.h>
#include <stdint.h>

#define DLMS_FRAME_FLAG 0x7e

#define MY_ID 0x1314

typedef struct
{
    uint8_t *section1;
    uint8_t *section2;
    uint8_t *section3;
    uint8_t *section4;
    size_t size;   
} dlms_mem_arena;

typedef struct
{

} hdlc_t;


