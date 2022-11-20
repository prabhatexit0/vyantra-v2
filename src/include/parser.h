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

Ast* parser_parse_block(Parser* parser);

Ast* parser_parse_start_end(Parser* parser);

Ast* parser_parse_binary(Parser* parser);

Ast* parser_parse_load(Parser* parser);

Ast* parser_parse_jump(Parser* parser);

Ast* parser_parse_label(Parser* parser);

Ast* parser_parse_halt(Parser* parser);

int parser_get_register_token(char* value);

#endif