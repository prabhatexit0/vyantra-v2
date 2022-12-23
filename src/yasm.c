/*
 * yasm.c
 *
 * This is the yantra assembler
 *
 */

#include "include/yasm.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned* Instr_Buffer;
Ast** Call_Stack = NULL;
int Stack_Size = 0;

void yas_parse_source_to_binary(char* source) {
    Lexer* lexer = init_lexer(source);
    Parser* parser = init_parser(lexer);
    Ast* globalAstRoot = parser_parse_block(parser);
    yas_visit_block(globalAstRoot);
}

InstrContainer* init_instr_cont() {
    InstrContainer* instr_cont = calloc(1, sizeof(InstrContainer));
    instr_cont->instructions = NULL;
    instr_cont->size = 0;
    return instr_cont;
}

InstrContainer* yas_visit_block(Ast* blockAst) {
    // Todo fix Issue: No instructions are returned after function call
    int i = 0, j = 0, c = 0;
    InstrContainer* instr_cont = init_instr_cont();
    InstrContainer* fn_instr_cont = init_instr_cont();

    if(blockAst == NULL) {
        return instr_cont;
    }

    for(i = 0; i < blockAst->children_size; i++) {
        printf("number of total children : %d\n", blockAst->children_size);
        instr_cont->instructions = realloc(instr_cont->instructions, sizeof(unsigned) * (instr_cont->size+1));
        instr_cont->size++;
        instr_cont->instructions[c++] = yas_visit_line(blockAst->children[i]);
        printf("here %d\n", instr_cont->instructions[c]);

        if(blockAst->children[i]->type == ast_call) {
            if(Stack_Size <=  0) {
                printf("Error: No functions found in Call Stack\n");
                exit(1);
            }

            fn_instr_cont = yas_visit_block(blockAst->children[i]->func_node->block);
            for(j = 0; j < fn_instr_cont->size; j++) {
                instr_cont->instructions = 
                    realloc(instr_cont->instructions, sizeof(unsigned) * (instr_cont->size+1));
                instr_cont->instructions[c++] = fn_instr_cont->instructions[j];
                instr_cont->size++;
            }
        }

        if(blockAst->children[i]->type == ast_end) {
            if(
                Stack_Size <= 0 ||
                Call_Stack[Stack_Size-1]->identifier != blockAst->children[i]->identifier
                ) {
                printf("Error: %s is not defined for current scope!\n", blockAst->children[i]->identifier);
                exit(1);
            }
            free(Call_Stack[Stack_Size-1]);
            Stack_Size--;
        }
    }
    return instr_cont;
}

unsigned yas_visit_line(Ast* lineAst) {
    switch(lineAst->type) {
        case ast_binary: 
            return yas_visit_binary(lineAst);
        case ast_load: 
            return yas_visit_load(lineAst);
        case ast_jump: 
            return yas_visit_jump(lineAst);
        case ast_label: 
            return yas_visit_label(lineAst);
        case ast_halt: 
            return yas_visit_halt(lineAst);
        case ast_show:
            return yas_visit_show(lineAst);
        case ast_call:
            return yas_visit_call(lineAst);
        case ast_block:
        case ast_func:
        default:
            return 0;
    }
}

unsigned yas_visit_binary(Ast* astNode) {
    unsigned binaryInstruction = 0;
    binaryInstruction = astNode->instr_type << 24;
    binaryInstruction += astNode->load_reg << 20;
    binaryInstruction += astNode->oper_reg_one << 16;
    binaryInstruction += astNode->oper_reg_two << 12;
    return binaryInstruction;
}

unsigned yas_visit_load(Ast* astNode) {
    unsigned loadInstruction = 0;
    loadInstruction = astNode->instr_type << 24;
    loadInstruction += astNode->load_reg << 20;
    loadInstruction += astNode-> scalerIntValue;
    return loadInstruction;
}

unsigned yas_visit_jump(Ast* astNode) {
    unsigned jumpInstruction = 0;
    jumpInstruction = astNode->instr_type << 24;
    jumpInstruction += astNode-> scalerIntValue;
    return jumpInstruction;
}

unsigned yas_visit_label(Ast* astNode) {
    unsigned labelInstruction = 0;
    labelInstruction = astNode->instr_type << 24;
    labelInstruction += astNode->scalerIntValue;
    return labelInstruction;
}

unsigned yas_visit_show(Ast* showNode) {
    unsigned showInstruction = 0;
    showInstruction = showNode->instr_type << 24;
    showInstruction += showNode->load_reg << 20;
    return showInstruction;
}

unsigned yas_visit_halt(Ast* astNode) {
    unsigned haltInstruction = 0;
    haltInstruction = astNode->instr_type << 24;
    return haltInstruction;
}

unsigned yas_visit_start_end(Ast* astNode) {
    unsigned instruction = 0;
    instruction = astNode->instr_type << 24;
    return instruction;
} 

unsigned yas_visit_call(Ast* astNode) {
    unsigned instruction = astNode->instr_type << 24;
    Call_Stack = realloc(Call_Stack, sizeof(Ast*) * ++Stack_Size);
    Call_Stack[Stack_Size-1] = astNode->func_node;
    return instruction;
}

