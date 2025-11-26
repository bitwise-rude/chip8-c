#include "memory.h"

Memory *initialize_memory(Memory *memory){
    // TODO: make digits later
    u8 ram[0x1000] = {0};

    // fill the interpreter area with nonsense value 
    // TODO: change this to fill it with digits
    for (int i=0; i<START;i++){
        ram[i] = 0x0;
    }

    // filling the rest with our rom
    for (int i = START; i< (START + memory->len); i++){
        ram[i] = memory->ram[i];
    }
    
    // free the original ram
    free(memory->ram);

    // now created ram will be the ram
    // we don't have to free this, cuz this won't be in the heap
    memory->ram = ram;
}