#ifndef COMPILER_H
#define COMPILER_H

#include "tokens.h"

typedef struct {
    char *code;
    int capacity;
    int count;
    char *end;
} ByteCodeChunk;

typedef struct {
    ByteCodeChunk chunk;
    Token *tokens;
    int current;
} Compiler;

void initCompiler(Compiler *c, Token *tokens);
void freeCompiler(Compiler *c);

#endif
