#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
    END_OF_FILE = 0,

    INTEGER,

    RETURN,

    SEMICOLON,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    EQUAL,
    NOT_EQUAL,

    ERROR
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

#endif
