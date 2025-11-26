#include "cpu.h"
#include "../memory/memory.h"
#include <stdio.h>

void make_cpu(CPU *cpu,struct Memory *mem){
        cpu->memory = mem;
        cpu->PC=(REG16){.value=START};
   
}

u16 combine_bytes(u8 msb, u8 lsb){
    return  (((u16)msb<<8 )| (u16)lsb);
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
    op_s->a = (u8)((op_s->msb & 0xF0)>>4);


}


void step(CPU *cpu){
    // fetch the instruction
    u8 *opcode = at_ram(cpu->memory,cpu->PC.value);

    // create the opcode
    Opcode op = (Opcode){};
    fill_opcode(&op,opcode);

    printf("CURRENTLY EXECUTING: %.4x at PC:%.4x\n",op.opcode,cpu->PC.value);

    //increment PC
    cpu->PC.value +=2;


    // execute the opcode
    switch(op.a){
        case 0x01:
            // Jump to location nnn.
            cpu->PC.value = op.nnn;
            break;
        case 0x06:
            // Set Vx = kk
            cpu->registers[op.x] = op.kk;
            break;
        case 0x0a:
            //The value of register I is set to nnn.
            cpu->I.value = op.nnn;
            break;
        case 0x0d:
            //Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
            break;
        case 0x03:
            //Skip next instruction if Vx = kk.
            if (cpu->registers[op.x] == op.kk ) cpu->PC.value +=2;
            break;
        case 0x04:
            //Skip next instruction if Vx != kk.
            if (cpu->registers[op.x] != op.kk ) cpu->PC.value +=2;
            break;
        case 0x05:
            //Skip next instruction if Vx = Vy.
            if (cpu->registers[op.x] == cpu->registers[op.y]) cpu->PC.value +=2;
            break;
        

        default:
            printf("NOT IMPLEMENTED\n");
            exit(0);
    }

}
