#ifndef YASM_H
#define YASM_H
#include "ast.h" 

void yas_parse_source_to_binary(char* source);

Ast* yas_visit_block(Ast* blockAst);

Ast* yas_visit_line(Ast* lineAst);

Ast* yas_visit_binary(Ast* binaryAst);

Ast* yas_visit_load(Ast* loadAst);

Ast* yas_visit_jump(Ast* jumpAst);

Ast* yas_visit_label(Ast* labelAst);

Ast* yas_visit_halt(Ast* haltAst);

void yas_write_binary(unsigned* instructions, unsigned int size, char* file_name);

#endif
