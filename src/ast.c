#include "include/ast.h"
#include <stdlib.h>

Ast* init_ast(int type) {
    Ast* astNode = calloc(1, sizeof(Ast));
    astNode->type = type;
    astNode->math_instr = math_none;
    astNode->logical_instr = logical_none;
    astNode->reg = reg_none;
    astNode->children = (void*)0;
    astNode->identifierString = (void*)0;
    astNode->scalerValue = (void*)0;
    return astNode;
}
