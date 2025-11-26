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
    // TODO; some redundant values will be removed later
    op_s->msb = *op_v;
    op_s->lsb = *(op_v+1);

    op_s->opcode = combine_bytes(op_s->msb,op_s->lsb);
    op_s->nnn = op_s->opcode & (0x0FFF);
    op_s->n = op_s->lsb & 0x0F;
    op_s->x = op_s->msb & 0x0F;
    op_s->y = op_s->lsb >> 4 ;
    op_s->kk = op_s->lsb;


}

u16 combine_bytes(u8 msb, u8 lsb){
    return  (((u16)msb<<8 )| (u16)lsb);
}


void step(CPU *cpu){
    // fetch the instruction
    u8 *opcode = at_ram(cpu->memory,cpu->PC.value);

    // create the opcode
    Opcode op = (Opcode){};
    fill_opcode(&op,opcode);

    printf("THE OPCODE IS %x",*opcode);

    


}
