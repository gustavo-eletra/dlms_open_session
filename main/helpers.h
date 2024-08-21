#include <stdint.h>

//Set Int32 as Big Endian value.
#define PUT32(ct, st) { (ct)[0] = (unsigned char)((st) >> 24); \
                    (ct)[1] = (unsigned char)((st) >> 16); \
                    (ct)[2] = (unsigned char)((st) >>  8); \
                    (ct)[3] = (unsigned char)(st); }

static const uint8_t *EMPTY_KEY[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };