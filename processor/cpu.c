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
    u8 *opcode = get_from_ram(cpu->memory,cpu->PC.value);

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

        case 0x07:
            //Adds the value kk to the value of register Vx, then stores the result in Vx.
            cpu->registers[op.x] += op.kk;
            break;

        case 0x09:
            //Skip next instruction if Vx != Vy.
            if (cpu->registers[op.x] != cpu->registers[op.y]) cpu->PC.value +=2;
            break;

        case 0x02:
            //Call subroutine at nnn.
            cpu->STACK[cpu->SP] = cpu->PC.value;
            cpu->SP ++;
            cpu-> PC.value = op.nnn;
            break;
        
        case 0x0:
            // two cases
            if(op.kk == 0xEE){
                //Return from a subroutine.
                cpu->SP--;
                cpu->PC.value = cpu->STACK[cpu->SP];
                break;
            }
        
        case 0x8:
            // many cases
            if(op.n == 0){
                // Set Vx = Vy.
                cpu->registers[op.x] = cpu->registers[op.y];
                break;
            }
            else if(op.n == 1){
                // Set Vx =Vx | Vy.
                cpu->registers[op.x] |= cpu->registers[op.y];
                break;
            }
            else if(op.n == 2){
                // Set Vx = VX &Vy.
                cpu->registers[op.x] &= cpu->registers[op.y];
                break;
            }
            else if(op.n == 3){
                // Set Vx = VX  XOR Vy.
                cpu->registers[op.x] ^= cpu->registers[op.y];
                break;
            }
            else if(op.n == 4){
                // Set Vx = VX + Vy.
                u16 sum = cpu->registers[op.x] + cpu->registers[op.y];
                cpu->registers[0xF] = (sum > 0xFF) ? 1 : 0;
                cpu->registers[op.x] = (uint8_t)sum;
                break;
            }
            else if(op.n == 5){
                // set Vx = Vx - Vy
                u8 vx = cpu->registers[op.x];
                u8 vy = cpu->registers[op.y];
                cpu->registers[0xF] = (vx >= vy) ? 1 : 0;
                cpu->registers[op.x] = (uint8_t)(vx - vy);
                break;
            }
            else if(op.n == 6){
                // Set Vx = Vx SHR 1.
                u8 vx = cpu->registers[op.x];
                cpu->registers[0xF] = vx & 0x01;
                cpu->registers[op.x] = vx >> 1;
                break;
            }
            else if(op.n == 7){
                // set Vx = Vy - Vx
                u8 vx = cpu->registers[op.x];
                u8 vy = cpu->registers[op.y];
                cpu->registers[0xF] = (vy >= vx) ? 1 : 0;
                cpu->registers[op.x] = (uint8_t)(vy - vx);
                break;
            }
            else if(op.n == 0xE){
                // Set Vx = Vx SHL 1.
                u8 vx = cpu->registers[op.x];
                cpu->registers[0xF] = (vx >> 7) & 1;
                cpu->registers[op.x] = vx << 1;
                break;
            }
        
        case 0xF:
            // many of F too
            if(op.kk == 0x55){
                //Store registers V0 through Vx in memory starting at location I.
                for(int i=0;i<=op.x;i++){
                    set_to_ram(cpu->memory,cpu->I.value + i, cpu->registers[i]);
                }
                break;
            }
            else if(op.kk == 0x65){
                //Read registers V0 through Vx from memory starting at location I.
                for(int i=0;i<=op.x;i++){
                    cpu->registers[i] = *get_from_ram(cpu->memory,cpu->I.value + i);
                }
                break;
            }
            else if(op.kk == 0x33){
                //Store BCD representation of Vx in memory locations I, I+1, and I+2.

                u8 val = cpu->registers[op.x];

                set_to_ram(cpu->memory, cpu->I.value + 0, val / 100);   
                set_to_ram(cpu->memory, cpu->I.value + 1, (val/ 10) % 10);
                set_to_ram(cpu->memory, cpu->I.value + 2, val % 10);  
                break;
            }
            


        
        default:
            printf("NOT IMPLEMENTED\n");
            exit(0);
    }

}
