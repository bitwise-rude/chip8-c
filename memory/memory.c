#include "memory.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Memory *initialize_memory(Memory *memory){
    // TODO: make digits later
    u8 *ram = malloc(0x1000);
    if (!ram) {
        return NULL;
    }

    memset(ram,0,0x1000);

    // fill the interpreter area with nonsense value 
    // TODO: change this to fill it with digits
    // for (int i=0; i<START;i++){
    //     ram[i] = 0x0;
    // }

    // filling the rest with our rom
    for (int i = 0; i < memory->len; i++) {
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

    if (addr >END) printf("ILLEGAL INSTRUCTION\n"); 
    else return &ram->ram[addr];
}

void set_to_ram(Memory *ram, u16 addr, u8 data){
    if (addr >END) printf("ILLEGAL INSTRUCTION\n"); 
    else ram->ram[addr] = data;
}