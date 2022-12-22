#ifndef YASM_H
#define YASM_H
#include "ast.h" 

typedef struct InstructionContainerStruct {
    unsigned* instructions;
    unsigned size;
} InstrContainer;


void yas_parse_source_to_binary(char* source);

InstrContainer* init_instr_cont();

InstrContainer* yas_visit_block(Ast* blockAst);

unsigned yas_visit_line(Ast* lineAst);

unsigned yas_visit_binary(Ast* binaryAst);

unsigned yas_visit_load(Ast* loadAst);

unsigned yas_visit_jump(Ast* jumpAst);

unsigned yas_visit_label(Ast* labelAst);

unsigned yas_visit_show(Ast* showAst);

unsigned yas_visit_halt(Ast* haltAst);

unsigned yas_visit_start_end(Ast* haltAst);

unsigned yas_visit_func(Ast* funcAst);

unsigned yas_visit_call(Ast* callAst);

#endif
