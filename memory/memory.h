#include <stdint.h>
#include <stdlib.h>

typedef uint8_t u8;
typedef uint16_t u16;


typedef struct RAM
{
    size_t len; // length of ram from file
    u8 *ram;   // ram from file
}RAM;
