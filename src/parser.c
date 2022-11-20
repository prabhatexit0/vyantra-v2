#include "include/parser.h"
#include "include/lexer.h"
#include "include/ast.h"
#include "include/ast.h"
#include <stdlib.h>
#include <stdio.h>

void parser_eat(Parser* parser, int token_type) {
    if(parser->current_token->type == token_type) {
        parser->current_token = lexer_get_next_token(parser->lexer);
    } else {
        printf("Error: Unexpected Token\n");
        exit(1);
    }
}

Parser* init_parser(Lexer* lexer) {
    Parser* parser = calloc(1, sizeof(Parser));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    return parser;
}

Ast* parser_parse_block(Parser* parser) {
    
}

Ast* parser_parse_start_end(Parser* parser) {

}

Ast* parser_parse_binary(Parser* parser) {

}

Ast* parser_parse_load(Parser* parser) {

}

Ast* parser_parse_jump(Parser* parser) {

}

Ast* parser_parse_label(Parser* parser) {

}

Ast* parser_parse_halt(Parser* parser) {

}