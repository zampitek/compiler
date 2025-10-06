#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
    TOKEN_EOF = 0,
    TOKEN_NUMBER,
    
    TOKEN_KEYWORD_RETURN,

    TOKEN_SEMICOLON,

    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    const char *value;
} Token;

#endif