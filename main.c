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

Memory  *data_from_file(const char *file_name){
    
    FILE *fp = fopen(file_name,"rb");

    if(fp == NULL)show_err("ROM File couldn't be found or accessed.");

    fseek(fp,0,SEEK_END);
    size_t len = ftell(fp);
    fseek(fp,0,SEEK_SET);

    u8 *buffer = (u8 *) malloc(len);

    //check if allocation fails
    if (buffer == NULL)show_err("Memory Allocation Failed.");
    fread(buffer,1,len,fp);

    return &(Memory){len,buffer};

}


int main(int argc, char *argv[]){

    if (argc < 2) show_err("Provide ROM File location");

    // read file data
    Memory *memory = data_from_file(argv[1]);

    // create ram from the file data
    initialize_memory(memory);

    // make cpu
    CPU *cpu = make_cpu((struct Memory*)memory);
    
    //step
    step(cpu);
    
    return 0;
}