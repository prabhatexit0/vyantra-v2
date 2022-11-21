#include "include/ast.h"
#include <stdlib.h>

Ast* init_ast(int type) {
    Ast* astNode = calloc(1, sizeof(Ast));
    astNode->type = type;
    astNode->children = (void*)0;
    astNode->instr_type = instr_none;
    astNode->load_reg = reg_none;
    astNode->oper_reg_one = reg_none;
    astNode->oper_reg_two = reg_none;
    astNode->scalerIntValue = 0;
    return astNode;
}
