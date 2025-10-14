#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/codegen.h"
#include "../include/compiler.h"

void emitInstruction(Compiler *c, const char *instruction) {
    int len = strlen(instruction);

    if (c->chunk.count + len >= c->chunk.capacity) {
        c->chunk.capacity = c->chunk.capacity > 256 ? 256 : c->chunk.capacity * 2;
        c->chunk.code = realloc(c->chunk.code, c->chunk.capacity);
    }

    strcpy(c->chunk.end, instruction);
    c->chunk.end += len;
    c->chunk.count  += len;
}

void emitInteger(Compiler *c, const char *integer) {
    int len = strlen(integer);

    if (c->chunk.count + len >= c->chunk.capacity) {
        c->chunk.capacity = c->chunk.capacity > 256 ? 256 : c->chunk.capacity * 2;
        c->chunk.code = realloc(c->chunk.code, c->chunk.capacity);
    }

    strcpy(c->chunk.end, integer);
    c->chunk.end += len;
    c->chunk.count  += len;
}

void emitNewLine(Compiler *c) {
    if (c->chunk.count + 1 >= c->chunk.capacity) {
        c->chunk.capacity = c->chunk.capacity > 256 ? 256 : c->chunk.capacity * 2;
        c->chunk.code = realloc(c->chunk.code, c->chunk.capacity);
    }

    c->chunk.end[0] = '\n';
    c->chunk.end++;
    c->chunk.count++;
}

void writeToFile(const char *file_path, Compiler *c) {
    c->chunk.end[0] = '\0';

    FILE *file = fopen(file_path, "w");
    fwrite(c->chunk.code, 1,c->chunk.count, file);
    fclose(file);
}
