#include "../include/compiler.h"
#include "../include/errors.h"

#include <stdlib.h>

void initCompiler(Compiler *c, ErrorList *e) {
    c->chunk.code = (char *)malloc(256);
    c->chunk.capacity = 256;
    c->chunk.count = 0;
    c->chunk.end = c->chunk.code;

    c->errors = e;
}

void addTokens(Compiler *c, Token *tokens) {
    c->tokens = tokens;
    c->current = 0;
}

void freeCompiler(Compiler *c) {
    free(c->chunk.code);
    c->chunk.code = NULL;
    c->chunk.count = 0;
    c->chunk.capacity = 0;
}
