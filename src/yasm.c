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
        instructions[i] = yas_visit_line(blockAst->children[0]);
    }
    return instructions;
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
    return 0;
}

unsigned yas_visit_jump(Ast* jumpAst) {
    return 0;
}

unsigned yas_visit_label(Ast* labelAst) {
    return 0;
}

unsigned yas_visit_halt(Ast* haltAst) {
    return 0;
}

unsigned yas_create_word(Ast* node, int type) {
    return 0;
}

void yas_write_binary(unsigned* instructions, unsigned int size, char* file_name) {
    return;
}