#include "../include/compiler.h"

#include <stdlib.h>

void initCompiler(Compiler *c, Token *tokens) {
    c->chunk.code = (char *)malloc(256);
    c->chunk.capacity = 256;
    c->chunk.count = 0;
    c->chunk.end = c->chunk.code;

    c->tokens = tokens;
    c->current = 0;
}

void freeCompiler(Compiler *c) {
    free(c->chunk.code);
    c->chunk.code = NULL;
    c->chunk.count = 0;
    c->chunk.capacity = 0;
}
