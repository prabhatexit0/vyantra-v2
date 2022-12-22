#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "token.h"
#include "ast.h"

typedef struct ParserStruct {
    Lexer* lexer;
    Token* current_token;
} Parser;

void parser_eat(Parser* parser, int token_type);

Parser* init_parser(Lexer* lexer);

Ast* parser_parse_line(Parser* parser);

Ast* parser_parse_block(Parser* parser, char* identifier);

Ast* parser_parse_start_end(Parser* parser);

Ast* parser_parse_binary(Parser* parser);

Ast* parser_parse_load(Parser* parser);

Ast* parser_parse_jump(Parser* parser);

Ast* parser_parse_label(Parser* parser);

Ast* parser_parse_show(Parser* parser);

Ast* parser_parse_func(Parser* parser);

Ast* parser_parse_call(Parser* parser);

Ast* parser_parse_end(Parser* parser);

Ast* parser_parse_halt();

Ast* parser_get_function(char* identifier);

int parser_get_register_token(char* value);

#endif
