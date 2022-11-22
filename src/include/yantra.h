#ifndef YANTRA_H
#define YANTRA_H

typedef struct InstructionStruct {
    int instr_type;
    int load_reg;
    int oper_reg_one;
    int oper_reg_two;
    int scaler_value;
} Instruction;

Instruction* init_instruction(unsigned instr);

Instruction* yantra_fetch();

void yantra_eval(Instruction* instr);

void yantra_show_registers();

void yantra_run(unsigned* instructions, int length_of_ins);


#endif