#ifndef YASM_H
#define YASM_H
#include "ast.h" 

void yas_parse_source_to_binary(char* source);

unsigned* yas_visit_block(Ast* blockAst);

unsigned yas_visit_line(Ast* lineAst);

unsigned yas_visit_binary(Ast* binaryAst);

unsigned yas_visit_load(Ast* loadAst);

unsigned yas_visit_jump(Ast* jumpAst);

unsigned yas_visit_label(Ast* labelAst);

unsigned yas_visit_halt(Ast* haltAst);

unsigned yas_visit_start_end(Ast* haltAst);

void yas_write_binary(unsigned* instructions, unsigned int size, char* file_name);

#endif
