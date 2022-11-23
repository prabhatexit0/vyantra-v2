#ifndef LEXER_H
#define LEXER_H
#include "token.h"

typedef struct LexerStruct {
    char c; 
    unsigned int i;
    char* source_code;
} Lexer;

Lexer* init_lexer(char* source_code);

void lexer_move(Lexer* lexer);

void lexer_skip_ws(Lexer* lexer);

Token* lexer_get_next_token(Lexer* lexer);

Token* lexer_get_start_end_token(Lexer* lexer);

Token* lexer_get_function_token(Lexer* lexer);

Token* lexer_get_scaler_token(Lexer* lexer);

Token* lexer_get_non_prefix_token(Lexer* lexer);

Token* lexer_get_identifier_token(Lexer* lexer);

char* lexer_get_char_as_string(Lexer* lexer);

Token* lexer_move_with_token(Lexer* lexer, Token* token);

Token* lexer_get_new_line_token(Lexer* lexer);

Token* lexer_get_label_token(Lexer* lexer);

#endif
