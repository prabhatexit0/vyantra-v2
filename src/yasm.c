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

#define BINARY "./test.yex"
unsigned* Instr_Buffer;

void yas_parse_source_to_binary(char* source) {
    Lexer* lexer = init_lexer(source);
    Parser* parser = init_parser(lexer);
    Ast* globalAstRoot = parser_parse_block(parser);
    yas_visit_block(globalAstRoot);
}

unsigned* yas_visit_block(Ast* blockAst) {
    int i = 0;
    unsigned* instructions = calloc(blockAst->children_size, sizeof(unsigned));
    for(i = 0; i < blockAst->children_size; i++) {
        instructions[i] = yas_visit_line(blockAst->children[i]);
    }
    return instructions;
}

unsigned yas_visit_line(Ast* lineAst) {
    switch(lineAst->type) {
        case ast_start:
        case ast_end:
            return yas_visit_start_end(lineAst);
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
    }
    return 0;
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

void yas_write_binary(unsigned* instructions, unsigned int size, char* file_name) {
    return;
}

