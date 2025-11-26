#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "memory/memory.h"
#include "processor/cpu.h"

typedef uint8_t u8;
typedef uint16_t u16;



void show_err(const char *err){
    fprintf(stderr,
            "CHIP-8 Emulator\nError: %s\n",
            err
    );  
    exit(EXIT_FAILURE);
}

void *data_from_file(const char *file_name,Memory *mem){
    
    FILE *fp = fopen(file_name,"rb");

    if(fp == NULL)show_err("ROM File couldn't be found or accessed.");

    fseek(fp,0,SEEK_END);
    size_t len = ftell(fp);
    fseek(fp,0,SEEK_SET);

    u8 *buffer = (u8 *) malloc(len);

    //check if allocation fails
    if (buffer == NULL)show_err("Memory Allocation Failed.");
    fread(buffer,1,len,fp);

    mem->ram = buffer;
    mem->len = len;

}


int main(int argc, char *argv[]){
    srand(time(NULL)); // random number

    if (argc < 2) show_err("Provide ROM File location");

    // read file data
    Memory *memory = &(Memory){};
    data_from_file(argv[1],memory);

    if (memory == NULL) show_err("Memory Allocation Failed");

    // create ram from the file data
    initialize_memory(memory);

    // make cpu
    CPU *cpu = &(CPU){};
    make_cpu(cpu,(struct Memory*)memory);
    
    //step
    for(int i =0;i<=600000;i++){    step(cpu);}
    
    return 0;
}