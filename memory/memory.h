#include <stdint.h>
#include <stdlib.h>

#pragma once

#define END 0xFFF
#define START 0x200

typedef uint8_t u8;
typedef uint16_t u16;


typedef struct Memory
{
    size_t len; // length of ram from file
    u8 *ram;   // final ram
}Memory;


Memory *initialize_memory(Memory *);
u8 *at_ram(Memory *ram, u16 addr);