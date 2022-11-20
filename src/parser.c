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

Ast* parser_parse(Parser* parser) {
    return parser_parse_statement(parser);
}

Ast* parser_parse_statement(Parser* parser) {
    Ast* statement = init_ast(ast_statement);
    statement->children = calloc(1, sizeof(Ast*));
    // statement->children->size will be 0 here
    while(parser->current_token->type != token_nline) { // curr token = load
        Ast* astToken = (void*)0;
        switch(parser->current_token->type) {
            case token_identifier:
                astToken = parser_parse_identifier(parser);
                break;
            case token_reg:
                astToken = parser_parse_register(parser);
                break;
            break;
            case token_scaler:
                astToken = parser_parse_scaler(parser);
                break;
            break;
            case token_add:
            case token_sub:
            case token_mult:
            case token_div:
                astToken = parser_parse_math(parser);
                break;
            break;
            case token_and:
            case token_or:
            case token_xor:
                astToken = parser_parse_logical(parser);
                break;

            case token_load:
                astToken = parser_parse_instruction(parser);
            break;
        }

        if(astToken == (void*)0) {
            printf("Error: Unexpected Token! Program Terminated\n");
            exit(1);
        }

        statement->children[statement->children_size-1] = astToken;
        statement->children = 
            realloc(statement->children, sizeof(Ast*) * ++statement->children_size);
    }
}

Ast* parser_parse_block(Parser* parser) {
    Ast* block = init_ast(ast_block);
}

Ast* parser_parse_instruction(Parser* parser) {
    Ast* instruction = init_ast(ast_instruction);
}

Ast* parser_parse_register(Parser* parser) {}

Ast* parser_parse_scaler(Parser* parser) {}

Ast* parser_parse_identifier(Parser* parser) {}

Ast* parser_parse_math(Parser* parser) {}

Ast* parser_parse_logical(Parser* parser) {}