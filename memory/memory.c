#include "memory.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const u8 chip8_fontset[16 * 5] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


void initialize_memory(Memory *memory){
    // TODO: make digits later
    u8 *ram = malloc(0x1000);
    if (!ram) {
        ram= NULL;
        return;
    }

    memset(ram,0,0x1000);

    // fill the interpreter area with nonsense value 
    // for (int i=0; i<START;i++){
    //     ram[i] = 0x0;
    // }

    memcpy(ram,chip8_fontset, sizeof(chip8_fontset));

    // filling the rest with our rom
    for (int i = 0; i < (int)memory->len; i++) {
        ram[START + i] = memory->ram[i];
    }
    
    // free the original ram
    free(memory->ram);

    // now created ram will be the ram
    // we don't have to free this, cuz this won't be in the heap
    memory->ram = ram;
    memory->len = 0x1000;
}

u8 *get_from_ram(Memory *ram, u16 addr){
    // when fetching opcode, this might cause an issue but whatever

    if (addr >END) {printf("ILLEGAL INSTRUCTION\n");return NULL;}
    else return &ram->ram[addr];
}

void set_to_ram(Memory *ram, u16 addr, u8 data){
    if (addr >END) printf("ILLEGAL INSTRUCTION\n"); 
    else ram->ram[addr] = data;
}