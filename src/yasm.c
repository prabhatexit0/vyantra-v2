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

Ast* yas_visit_block(Ast* blockAst) {
    int i = 0;
    for(i = 0; i < blockAst->children_size; i++) {
        yas_visit_line(blockAst->children[0]);
    }
    return (void*)0;
}

Ast* yas_visit_line(Ast* lineAst) {
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
    return (void*)0;
}

Ast* yas_visit_binary(Ast* binaryAst) {}

Ast* yas_visit_load(Ast* loadAst) {}

Ast* yas_visit_jump(Ast* jumpAst) {}

Ast* yas_visit_label(Ast* labelAst) {}

Ast* yas_visit_halt(Ast* haltAst) {}

Ast* yas_create_word(Ast* node, int type) {}

void yas_write_binary(unsigned* instructions, unsigned int size, char* file_name) {}