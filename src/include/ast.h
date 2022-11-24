#ifndef AST_H
#define AST_H

typedef struct AstStruct {
    enum {
        ast_start,
        ast_end,
        ast_block,
        ast_binary,
        ast_load,
        ast_jump,
        ast_label,
        ast_show,
        ast_halt
    } type;

    // AST Start / End Props (eat?)
    // AST Block Props
    struct AstStruct** children;
    unsigned int children_size;

    // Instructions:
    enum {
        instr_none,
        instr_math_add,
        instr_math_sub,
        instr_math_mult,
        instr_math_div,
        instr_logical_and,
        instr_logical_or,
        instr_logical_xor,
        instr_load,
        instr_jump,
        instr_label,
        instr_show,
        instr_start,
        instr_end,
        instr_halt,
    } instr_type;

    enum {
        reg_none,
        reg_one,
        reg_two,
        reg_three
    } load_reg, oper_reg_one, oper_reg_two;

    int scalerIntValue;

    // AST Load Props
    // * use reg_place_one for register
    // and use scalerIntValue for scaler value

    // AST Jump Props
    // store_label id in scalerIntValue

    // AST Label Props
    // store_label id in scalerIntValue

    // AST Halt Props
    // just type is enough

    // Ast Show Props
    // use load_reg for the specified register
} Ast;

Ast* init_ast(int type);

#endif
