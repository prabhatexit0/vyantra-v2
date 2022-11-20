#include "include/ast.h"
#include <stdlib.h>

Ast* init_ast(int type) {
    Ast* astNode = calloc(1, sizeof(Ast));
    astNode->type = type;
    astNode->children = (void*)0;
    astNode->math_type = math_none;
    astNode->logical_type = logical_none;
    astNode->reg_place_one = reg_none;
    astNode->reg_place_two = reg_none;
    astNode->reg_place_three = reg_none;
    astNode->scalerIntValue = 0;
    astNode->labelNode = (void*)0;
    astNode->branchRef = (void*)0;
    return astNode;
}
