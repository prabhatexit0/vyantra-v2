#include "include/yantra.h"
#include "include/ast.h"
#include <stdlib.h>
#include <stdio.h>

#define NUM_REGS 4
#define INSTR_BUFFER_SIZE 1024
unsigned registers[4] = {0};
char register_tags[NUM_REGS] = {'R', 'A', 'B', 'C'};
Instruction** instr_buffer;
unsigned labels[1024];
int program_counter = 0;
int is_running = 1;


Instruction* init_instruction(unsigned instr_encoded) {
    Instruction* instr  = calloc(1, sizeof(Instruction));
    instr->instr_type   = (instr_encoded & 0xFF000000) >> 24;
    instr->load_reg     = (instr_encoded & 0x00F00000) >> 20;
    instr->oper_reg_one = (instr_encoded & 0x000F0000) >> 16;   // For operating on regs
    instr->oper_reg_two = (instr_encoded & 0x0000F000) >> 12;   // Same as above
    instr->scaler_value = (instr_encoded & 0x000000FF);         // Immediate values for loads
    return instr;
}

Instruction* yantra_fetch(int length_of_ins) {
    program_counter = (program_counter + 1) % length_of_ins;
    return instr_buffer[program_counter];
}

void yantra_eval(Instruction* instr) {
    switch(instr->instr_type) {
        case instr_math_add:
            registers[instr->load_reg] = registers[instr->oper_reg_one] + registers[instr->oper_reg_two];
            break;
        case instr_math_sub:
            registers[instr->load_reg] = registers[instr->oper_reg_one] - registers[instr->oper_reg_two];
            break;
        case instr_math_mult:
            registers[instr->load_reg] = registers[instr->oper_reg_one] * registers[instr->oper_reg_two];
            break;
        case instr_math_div:
            registers[instr->load_reg] = registers[instr->oper_reg_one] / registers[instr->oper_reg_two];
            break;
        case instr_logical_and:
            registers[instr->load_reg] = registers[instr->oper_reg_one] & registers[instr->oper_reg_two];
            break;
        case instr_logical_or:
            registers[instr->load_reg] = registers[instr->oper_reg_one] | registers[instr->oper_reg_two];
            break;
        case instr_logical_xor:
            registers[instr->load_reg] = registers[instr->oper_reg_one] ^ registers[instr->oper_reg_two];
            break;
        case instr_load:
            registers[instr->load_reg] = instr->scaler_value;
            break;
        case instr_jump:
            program_counter = labels[instr->scaler_value];
            break;
        case instr_start:
            break;
        case instr_end:
            is_running = 0;
            break;
        case instr_halt:
            is_running = 0;
            break;
        case instr_show:
            printf("Register '%c': %d\n", register_tags[instr->load_reg] , registers[instr->load_reg]);
        default:
            break;
    }
}


void yantra_run(unsigned* instructions, int length_of_ins) {
    Instruction* instr = NULL;
    instr_buffer = calloc(length_of_ins, sizeof(Instruction*));
    int i = 0;
    printf("Length of instructions in yantra: %d\n", length_of_ins);

    for(i = 0; i < length_of_ins; i++) {
        instr_buffer[i] = init_instruction(instructions[i]);
        if(instr_buffer[i]->instr_type == instr_label) {
            labels[instr_buffer[i]->scaler_value] = i;
        }
        printf("instr_type: %d idx: %d\n", instr_buffer[i]->instr_type, i);
    }

    while(is_running) {
        instr = yantra_fetch(length_of_ins+1);
        yantra_eval(instr);
    }
}
