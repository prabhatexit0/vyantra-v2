#include "include/ast.h"
#include <stdlib.h>
#include <stdio.h>

Ast* init_ast(int type) {
    Ast* astNode = calloc(1, sizeof(Ast));
    astNode->type = type;
    astNode->children = NULL;
    astNode->instr_type = instr_none;
    astNode->load_reg = reg_none;
    astNode->oper_reg_one = reg_none;
    astNode->oper_reg_two = reg_none;
    astNode->scalerIntValue = 0;
    astNode->identifier = NULL;
    astNode->func_node = NULL;
    return astNode;
}

AstFuncStack* init_ast_func_stack() {
    AstFuncStack* func_stack = calloc(1, sizeof(AstFuncStack));
    func_stack->stack = NULL;
    func_stack->size = 0;
    return func_stack;
}

void push(AstFuncStack* func_stack, Ast* node) {
    func_stack = realloc(func_stack, ++func_stack->size * sizeof(AstFuncStack*));
    func_stack->stack[func_stack->size - 1] = node;
}

Ast* pop(AstFuncStack* func_stack) {
    Ast* temp = NULL;
    if(func_stack->size == 0) {
        printf("Error: No functions in AST FUNC STACK\n");
        exit(1);
    }
    temp = func_stack->stack[func_stack->size-1];
    func_stack = realloc(func_stack, --func_stack->size * sizeof(AstFuncStack*));
    return temp;
}

Ast* peek(AstFuncStack* func_stack) {
    Ast* temp = NULL;
    if(func_stack->size == 0) {
        printf("Error: No functions in AST FUNC STACK\n");
        exit(1);
    }
    temp = func_stack->stack[func_stack->size-1];
    return temp;
}
