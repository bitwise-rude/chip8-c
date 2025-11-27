#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stdlib.h>



#define END 0xFFF
#define START 0x200

typedef uint8_t u8;
typedef uint16_t u16;


typedef struct Memory
{
    size_t len; // length of ram from file
    u8 *ram;   // final ram
}Memory;


void initialize_memory(Memory *);
u8 *get_from_ram(Memory *ram, u16 addr);
void set_to_ram(Memory *ram, u16 addr, u8 data);
#endif