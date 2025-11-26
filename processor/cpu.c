#include "cpu.h"
#include "../memory/memory.h"
#include <stdio.h>

CPU *make_cpu(struct Memory *mem){
    return &(CPU){
        .memory = mem,
        .PC=(REG16){.value=START}
    };
}

void fill_opcode(Opcode *op_s, u8 *op_v){

}


void step(CPU *cpu){
    // fetch the instruction
    u8 *opcode = at_ram(cpu->memory,cpu->PC.value);

    // create the opcode
    Opcode op = (Opcode){};
    // fill_opcode(&op);
    printf("THE OPCODE IS %x",*opcode);

    


}
