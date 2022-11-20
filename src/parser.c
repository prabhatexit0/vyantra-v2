#include "include/parser.h"
#include "include/lexer.h"
#include "include/ast.h"
#include "include/ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

Ast* parser_parse_line(Parser* parser) {
    switch(parser->current_token->type) {
        case token_add:
        case token_sub:
        case token_mult:
        case token_div:
        case token_and:
        case token_or:
        case token_xor:
            return parser_parse_binary(parser);
        case token_load:
            return parser_parse_load(parser);
        case token_halt:
            return parser_parse_halt(parser);
        case token_start:
        case token_end:
            return parser_parse_start_end(parser);
        default:
            printf("Error: Unexpected token while parsing statement Type: %d\n", parser->current_token->type);
            exit(1);
    }
    
    return (void*)0;
}

Ast* parser_parse_block(Parser* parser) {
    Ast* blockAst = init_ast(ast_block);
    Ast* temp = init_ast(ast_block);
    int i = 0;
    blockAst->children = calloc(++blockAst->children_size, sizeof(Ast*));
    blockAst->children[blockAst->children_size-1] = parser_parse_line(parser);
    parser->current_token = lexer_get_next_token(parser->lexer);

    while(parser->current_token->type == token_nline) {
        parser_eat(parser, token_nline);
        if(parser->current_token->type == token_eof)
            break;

        blockAst->children = realloc(
            blockAst->children,
            (blockAst->children_size++) * sizeof(struct AstStruct*)
        );
        temp = parser_parse_line(parser);
        blockAst->children[i++] = temp;
        parser->current_token = lexer_get_next_token(parser->lexer);
    }

    return blockAst;
}

Ast* parser_parse_start_end(Parser* parser) {
    if(parser->current_token->type == token_start) {
        return init_ast(ast_start);
    } 
    else if(parser->current_token->type == token_end) {
        return init_ast(ast_end);
    }
    else {
        printf("Error: Unexpected token!! Should be start or end\n");
        exit(1);
    }
}


// will be used for parsing binary math and logical instructions
// [ instr reg1 reg2 reg3 ]
Ast* parser_parse_binary(Parser* parser) {
    Ast* binaryAst = init_ast(ast_binary);
    int operation = parser->current_token->type;
    int temp_reg[3] = {reg_none, reg_none, reg_none};
    int i = 0;

    for(i = 0; i < 3; i++) {
        parser->current_token = lexer_get_next_token(parser->lexer);
        temp_reg[i] = parser_get_register_token(parser->current_token->value);
        if(temp_reg[i] == reg_none) {
            printf("Error: Unexpected Token, expected Register\n");
        }
    }

    switch(operation) {
        case token_add:
            binaryAst->math_type = math_add;
            break;
        case token_sub:
            binaryAst->math_type = math_sub;
            break;
        case token_mult:
            binaryAst->math_type = math_mult;
            break;
        case token_div:
            binaryAst->math_type = math_div;
            break;
        case token_and:
            binaryAst->logical_type = logical_and;
            break;
        case token_or:
            binaryAst->logical_type = logical_or;
            break;
        case token_xor:
            binaryAst->logical_type = logical_or;
            break;
        default:
            printf("Error: Unexpected Token\n");
            exit(1);
    }


    binaryAst->reg_place_one = temp_reg[0];
    binaryAst->reg_place_two = temp_reg[1];
    binaryAst->reg_place_three = temp_reg[2];

    return binaryAst;
}


Ast* parser_parse_load(Parser* parser) {
    Ast* loadAst = init_ast(ast_load);
    parser->current_token = lexer_get_next_token(parser->lexer);
    if(parser->current_token->type != token_reg) {
        printf("Error: Expected register token\n");
        exit(1);
    } 

    if(!strcmp(parser->current_token->value, "A")) 
        loadAst->reg_place_one = reg_one;
    else if(!strcmp(parser->current_token->value, "B")) 
        loadAst->reg_place_one = reg_two;
    else if(!strcmp(parser->current_token->value, "C")) 
        loadAst->reg_place_one = reg_three;
    else {
        printf("Error: Unexpected Error in parsing\n");
        printf("- Token type: %d | Token value: %s", parser->current_token->type, parser->current_token->value);
        exit(1);
    }


    parser->current_token = lexer_get_next_token(parser->lexer);
    if(parser->current_token->type != token_scaler) {
        printf("Error: Unexpected Error in parsing, Expected a scaler token\n");
        exit(1);
    }
    loadAst->scalerIntValue = atoi(parser->current_token->value);

    return loadAst;
}

Ast* parser_parse_jump(Parser* parser) {
    // Todo: creating the jump parser
}

Ast* parser_parse_label(Parser* parser) {
    // Todo: creating the label parser
}

Ast* parser_parse_halt(Parser* parser) {
    return init_ast(ast_halt);
}

int parser_get_register_token(char* value) {
    if(!strcmp(value, "A")) return reg_one;
    if(!strcmp(value, "B")) return reg_two;
    if(!strcmp(value, "C")) return reg_three;
    return reg_none;
}