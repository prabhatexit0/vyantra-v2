#ifndef TOKEN_H
#define TOKEN_H

typedef struct TokenStruct {
    enum {
        token_id,
        token_scaler,
        token_identifier,
        token_func,
        token_start,
        token_end,
        token_reg,
        token_add,
        token_sub,
        token_mult,
        token_div,
        token_and,
        token_or,
        token_xor,
        token_load,
        token_label,
        token_jmp,
        token_nline,
        token_err
    } type;
    char* value;
} Token;

Token* init_token(int type, char* value);

#endif