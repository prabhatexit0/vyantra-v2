/*
 * yasm.c
 *
 * This is the yantra assembler
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/yasm.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/ast.h"

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
    printf("type of line ast %d\n", lineAst->type);
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
    }
    return 0;
}

unsigned yas_visit_binary(Ast* binaryAst) {
    unsigned binaryInstruction = 0;
    binaryInstruction = binaryAst->instr_type << 24;
    binaryInstruction += binaryAst->load_reg << 20;
    binaryInstruction += binaryAst->oper_reg_one << 16;
    binaryInstruction += binaryAst->oper_reg_two << 12;
    return binaryInstruction;
}

unsigned yas_visit_load(Ast* loadAst) {
    unsigned loadInstruction = 0;
    loadInstruction = loadAst->instr_type << 24;
    loadInstruction += loadAst->load_reg << 20;
    loadInstruction += loadAst-> scalerIntValue;
}

unsigned yas_visit_jump(Ast* jumpAst) {
    unsigned jumpInstruction = 0;
    jumpInstruction = jumpAst->instr_type << 24;
    jumpInstruction += jumpAst-> scalerIntValue;
    return jumpInstruction;
}

unsigned yas_visit_label(Ast* labelAst) {
    unsigned labelInstruction = 0;
    labelInstruction = labelAst->instr_type << 24;
    labelInstruction += labelAst->scalerIntValue;
    return labelInstruction;
}

unsigned yas_visit_halt(Ast* haltAst) {
    unsigned haltInstruction = 0;
    haltInstruction = haltAst->instr_type << 24;
    return haltInstruction;
}

void yas_write_binary(unsigned* instructions, unsigned int size, char* file_name) {
    return;
}