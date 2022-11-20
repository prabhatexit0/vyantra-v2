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
        ast_halt
    } type;

    // AST Start / End Props (eat?)
    // AST Block Props
    struct AstStruct** children;
    unsigned int children_size; 

    // AST Binary Props
    enum {
        math_none,
        math_add,
        math_sub,
        math_mult,
        math_div
    } math_type;

    enum {
        logical_none,
        logical_and,
        logical_or,
        logical_xor
    } logical_type ;

    enum {
        reg_none,
        reg_one,
        reg_two,
        reg_three
    } reg_place_one, reg_place_two, reg_place_three;

    int scalerIntValue;

    
    // AST Load Props
    // * use reg_place_one for register
    // and use scalerIntValue for scaler value


    // AST Jump Props
    struct AstStruct* labelNode;

    // AST Label Props
    struct AstStruct* branchRef;

    // AST Halt Props
    // just type is enough
} Ast;

Ast* init_ast(int type);

#endif
