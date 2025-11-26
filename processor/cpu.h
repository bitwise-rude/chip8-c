#include <stdint.h>
#include <stdlib.h>

#pragma once

typedef uint8_t u8;
typedef uint16_t u16;

typedef union{
    u8 lo;
    u8 hi;
    u16 value;
}REG16;

typedef struct{
    u8 *registers[16]; // 16 registers 0 TO F
    REG16 I; // I register
    REG16 PC; // Program counter
    u8 SP; // Stack Pointer ()
}CPU;