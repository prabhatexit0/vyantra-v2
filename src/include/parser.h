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

Ast* parser_parse(Parser* parser);

Ast* parser_parse_statement(Parser* parser);

Ast* parser_parse_block(Parser* parser);

Ast* parser_parse_instruction(Parser* parser);

Ast* parser_parse_register(Parser* parser);

Ast* parser_parse_scaler(Parser* parser);

Ast* parser_parse_identifier(Parser* parser);

Ast* parser_parse_math(Parser* parser);

Ast* parser_parse_logical(Parser* parser);


#endif