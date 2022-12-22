#include "include/lexer.h"
#include "include/token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


Lexer* init_lexer(char* source_code) {
    Lexer* lex = calloc(1, sizeof(Lexer));
    lex->i = 0;
    lex->source_code = source_code;
    lex->c = source_code[lex->i];
    return lex;
}

void lexer_move(Lexer* lexer) {
    if(lexer->c != '\0' && lexer->i < strlen(lexer->source_code)) {
        lexer->i++;
        lexer->c = lexer->source_code[lexer->i];
    }
}

void lexer_skip_ws(Lexer* lexer) {
    if(lexer->c == ' ' || lexer->c == '\t') {
        lexer_move(lexer);
    }
}

Token* lexer_get_next_token(Lexer* lexer) {
    while(lexer->c != '\0' && lexer->i < strlen(lexer->source_code)) {
        if(lexer->c == ' ' || lexer->c == '\t') {
            lexer_skip_ws(lexer);
        } else {
            switch (lexer->c) {
                case '#': 
                    return lexer_get_scaler_token(lexer);
                case '@': 
                    return lexer_get_call_token(lexer);
                case '\n':
                    return lexer_get_new_line_token(lexer);
                case ':':
                    return lexer_get_label_token(lexer);
                default:
                    return lexer_get_non_prefix_token(lexer);
            }
        }
    }
    return init_token(token_eof, "EOF");
}


Token* lexer_get_function_token(Lexer* lexer) {
    lexer_move(lexer);
    Token* token = lexer_get_identifier_token(lexer);
    return token;
}

Token* lexer_get_non_prefix_token(Lexer* lexer) {
    Token* token = lexer_get_identifier_token(lexer);
    if(!strcmp("add", token->value)) token->type = token_add; 
    if(!strcmp("sub", token->value)) token->type = token_sub;
    if(!strcmp("mult", token->value)) token->type = token_mult;
    if(!strcmp("div", token->value)) token->type = token_div; 
    if(!strcmp("and", token->value)) token->type = token_and; 
    if(!strcmp("or", token->value)) token->type = token_or; 
    if(!strcmp("xor", token->value)) token->type = token_xor;
    if(!strcmp("jmp", token->value)) token->type = token_jmp;
    if(!strcmp("load", token->value)) token->type = token_load;
    if(!strcmp("halt", token->value)) token->type = token_halt;
    if(!strcmp("show", token->value)) token->type = token_show;
    if(!strcmp("func", token->value)) token->type = token_func;
    if(!strcmp("end", token->value)) token->type = token_end;
    if(!strcmp("A", token->value) || 
       !strcmp("B", token->value) ||
       !strcmp("C", token->value)) token->type = token_reg;
    return token;
}

Token* lexer_get_scaler_token(Lexer* lexer) {
    lexer_move(lexer);
    char* str = calloc(1, sizeof(char));
    str[0] = '\0';
    char *sch;
    while(lexer->c != ' ' && lexer->c != '\n' && lexer->c != '\0') {
        if(lexer->c >= '0' && lexer->c <= '9')  {
            sch = lexer_get_char_as_string(lexer);
            str = realloc(str, sizeof(char)  * (strlen(str) + strlen(sch) + 1));
            strcat(str, sch);
        }
        lexer_move(lexer);
    }
    return init_token(token_scaler, str);
}

Token* lexer_get_identifier_token(Lexer* lexer) {
    char* str = calloc(1, sizeof(char));
    str[0] = '\0';
    char *sch;

    while(lexer->c != ' ' && lexer->c != '\n' && lexer->c != '\0') { 
        sch = lexer_get_char_as_string(lexer);
        str = realloc(str, sizeof(char)  * (strlen(str) + strlen(sch) + 1));
        strcat(str, sch);
        lexer_move(lexer);
    }

    return init_token(token_identifier, str);
}

Token* lexer_get_register_token(Lexer* lexer) {
    char* reg = lexer_get_char_as_string(lexer);
    return init_token(token_reg, reg);
}

char* lexer_get_char_as_string(Lexer* lexer) {
    char* str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';
    return str;
}

Token* lexer_move_with_token(Lexer* lexer, Token* token) {
    lexer_move(lexer);
    return token;
}

Token* lexer_get_new_line_token(Lexer* lexer) {
    lexer_move(lexer);
    return init_token(token_nline, "nline");
}

Token* lexer_get_label_token(Lexer* lexer) {
    lexer_move(lexer);
    Token* token = lexer_get_identifier_token(lexer);
    token->type = token_label;
    return token;
}

Token* lexer_get_call_token(Lexer* lexer) {
    lexer_move(lexer);
    Token* token = lexer_get_identifier_token(lexer);
    token->type = token_call;
    return token;
}


int lexer_is_ws(Lexer* lexer) {
    if(lexer->c == ' ' || lexer->c == '\t' || lexer->c == '\n')
        return 1;
    return 0;
}
