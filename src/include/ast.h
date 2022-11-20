#ifndef AST_H
#define AST_H

typedef struct AstStruct {
    enum {
        ast_function_decl,
        ast_function_call,
        ast_statement,
        ast_instruction,
        ast_register,
        ast_scaler,
        ast_identifier,
        ast_compound_node
    } type;


    // ast_statement,
    struct AstStruct** children;

    // ast_instruction,
    enum {
        math_none,
        math_add,
        math_sub,
        math_mult,
        math_div,
    } math_instr;

    enum {
        logical_none,
        logical_and,
        logical_or,
        logical_xor
    } logical_instr;

    // ast_register,
    enum {
        reg_none,
        reg_one,
        reg_two,
        reg_three
    } reg;


    // ast_scaler,
    int scalerValue;

    // ast_identifier,
    char* identifierString;
} Ast;

Ast* init_ast(int type);

#endif AST_H
