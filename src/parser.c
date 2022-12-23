#include "include/parser.h"
#include "include/lexer.h"
#include "include/ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AstFuncStack* func_stack = NULL;

void parser_eat(Parser* parser, int token_type) {
    if(parser->current_token->type == token_type) {
        parser->current_token = lexer_get_next_token(parser->lexer);
    } else {
        printf("Error: Unexpected Token Type: %d, Expected: %d\n", parser->current_token->type, token_type);
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
        case token_jmp:
            return parser_parse_jump(parser);
        case token_label:
            return parser_parse_label(parser);
        case token_show:
            return parser_parse_show(parser);
        case token_func:
            return parser_parse_func(parser);
        case token_call:
            return parser_parse_call(parser);
        default:
            printf(
                "Error: Unexpected token while parsing statement, Token Type: %d\n",
                parser->current_token->type);
            exit(1);
    }
    
    return NULL;
}

Ast* parser_parse_block(Parser* parser) {
    Ast* block_ast = init_ast(ast_block);

    // Initialization of func_stack
    if(func_stack == NULL) {
        func_stack = init_ast_func_stack();
        ast_func_stack_push(func_stack, block_ast);
    } 


    while(parser->current_token->type != token_eof) {
        // skip all new line tokens
        while(parser->current_token->type == token_nline) {
            parser_eat(parser, token_nline);
        }

        // if current token is token_end, pop function from the func_stack
        if(parser->current_token->type == token_end) {
            if(func_stack == NULL) {
                printf("Error: Unexpectedly encountered end token. No function present in AST FUNC STACK while parsing\n");
                exit(1);
            }
            parser_eat(parser, token_end);

            if(parser->current_token->type != token_func) {
                printf("Error: Expected func token after end token to specify func has been ended\n");
                exit(1);
            }

            ast_func_stack_pop(func_stack);
            parser_eat(parser, token_func);
            return block_ast;
        } 

        block_ast->children = realloc(block_ast->children, sizeof(Ast*) * ++block_ast->children_size);
        block_ast->children[block_ast->children_size-1] = parser_parse_line(parser);
        parser->current_token = lexer_get_next_token(parser->lexer);

        while(parser->current_token->type == token_nline) {
            parser_eat(parser, token_nline);
        }
    }

    return block_ast; 
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
            binaryAst->instr_type = instr_math_add;
            break;
        case token_sub:
            binaryAst->instr_type = instr_math_sub;
            break;
        case token_mult:
            binaryAst->instr_type = instr_math_mult;
            break;
        case token_div:
            binaryAst->instr_type = instr_math_div;
            break;
        case token_and:
            binaryAst->instr_type = instr_logical_and;
            break;
        case token_or:
            binaryAst->instr_type = instr_logical_or;
            break;
        case token_xor:
            binaryAst->instr_type = instr_logical_xor;
            break;
        default:
            printf("Error: Unexpected Token\n");
            exit(1);
    }


    binaryAst->load_reg = temp_reg[0];
    binaryAst->oper_reg_one = temp_reg[1];
    binaryAst->oper_reg_two = temp_reg[2];

    return binaryAst;
}


Ast* parser_parse_load(Parser* parser) {
    Ast* loadAst = init_ast(ast_load);

    loadAst->instr_type = instr_load;

    parser->current_token = lexer_get_next_token(parser->lexer);
    if(parser->current_token->type != token_reg) {
        printf("Error: Expected register token\n");
        exit(1);
    } 

    if(!strcmp(parser->current_token->value, "A")) 
        loadAst->load_reg = reg_one;
    else if(!strcmp(parser->current_token->value, "B")) 
        loadAst->load_reg = reg_two;
    else if(!strcmp(parser->current_token->value, "C")) 
        loadAst->load_reg = reg_three;
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

    char* tokenValue = parser->current_token->value;
    tokenValue[sizeof(tokenValue)] = '\0';
    loadAst->scalerIntValue = atoi(tokenValue);
    return loadAst;
}

Ast* parser_parse_jump(Parser* parser) {
    Ast* jumpAst = init_ast(ast_jump);    
    jumpAst->instr_type = instr_jump;
    parser->current_token = lexer_get_next_token(parser->lexer);
    char* tokenValue = parser->current_token->value;
    jumpAst->scalerIntValue = atoi(tokenValue);
    return jumpAst;
}

Ast* parser_parse_label(Parser* parser) {
    Ast* labelAst = init_ast(ast_label);
    labelAst->instr_type = instr_label;
    char* tokenValue = parser->current_token->value;
    labelAst->scalerIntValue = atoi(tokenValue);
    return labelAst;
}

Ast* parser_parse_show(Parser* parser) {
    Ast* showAst = init_ast(ast_show);
    showAst->instr_type = instr_show;
    parser->current_token = lexer_get_next_token(parser->lexer);
    
    // Current token should be a reigster token.
    if(parser->current_token->type != token_reg) {
        printf("Error: Unexpected Token, Expected a register token after print\n");
        exit(1);
    }

    showAst->load_reg = parser_get_register_token(parser->current_token->value);    
    return showAst;
}


Ast* parser_parse_func(Parser* parser) {
    Ast* func_ast = init_ast(ast_func);
    parser_eat(parser, token_func);
    func_ast->identifier = parser->current_token->value;
    parser_eat(parser, token_identifier);
    ast_func_stack_push(func_stack, func_ast);
    func_ast->block = parser_parse_block(parser);
    return func_ast;
}

Ast* parser_parse_call(Parser* parser) {
    Ast* callAst = init_ast(ast_call);
    callAst->instr_type = instr_call;
    callAst->identifier = parser->current_token->value;
    return callAst;
}

Ast* parser_parse_halt() {
    Ast* haltAst = init_ast(ast_halt);
    haltAst->instr_type = instr_halt;
    return haltAst;
}


int parser_get_register_token(char* value) {
    if(!strcmp(value, "A")) return reg_one;
    if(!strcmp(value, "B")) return reg_two;
    if(!strcmp(value, "C")) return reg_three;
    return reg_none;
}
