#ifndef COMPILER_H
#define COMPILER_H

#include "tokens.h"
#include "errors.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t *code;
    int capacity;
    int count;
} ByteCodeChunk;

typedef struct {
    ByteCodeChunk chunk;
    Token *tokens;
    int current;
    ErrorList *errors;
    bool had_error;
} Compiler;

void initCompiler(Compiler *c, ErrorList *e);
void addTokens(Compiler *c, Token *tokens);
void freeCompiler(Compiler *c);

#endif
