#include <stdint.h>
#include <stdlib.h>
#include <time.h>


#pragma once

typedef uint8_t u8;
typedef uint16_t u16;

struct Memory;


typedef union{
    u8 lo;
    u8 hi;
    u16 value;
}REG16;

typedef struct{
    u8 registers[16]; // 16 registers 0 TO F

    REG16 I; // I register
    REG16 PC; // Program counter

    u8 SP; // Stack Pointer ()
    u16 STACK[16]; // the actual stack

    struct Memory *memory;

    u8 DT; // DElay timer
    u8 ST;  // Sound timer
    clock_t dt_start ; // delay timer start time
    clock_t st_start; // sound timer start time


    struct Screen *screen;

    u8 is_halted;

}CPU;

typedef struct 
{
  u8 msb;
  u8 lsb;
  u16 opcode;

  u16 nnn; //A 12-bit value, the lowest 12 bits of the instruction

  u8 n; //A 4-bit value, the lowest 4 bits of the instruction
  u8 x;// A 4-bit value, the lower 4 bits of the high byte of the instruction
  u8 y; //A 4-bit value, the upper 4 bits of the low byte of the instruction

  u8 kk; //An 8-bit value, the lowest 8 bits of the instruction

  u8 a; // high nibble of the high byte
}Opcode;

void make_cpu(CPU*, struct Memory*,struct Screen*);
void step(CPU*);