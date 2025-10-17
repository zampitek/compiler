#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/codegen.h"
#include "../include/compiler.h"

void emitByte(Compiler *c, uint8_t byte) {
    if (c->chunk.count + 1 >= c->chunk.capacity) {
        c->chunk.capacity = c->chunk.capacity < 256 ? 256 : c->chunk.capacity * 2;
        c->chunk.code = realloc(c->chunk.code, c->chunk.capacity);
    }

    c->chunk.code[c->chunk.count] = byte;
    c->chunk.count++;
}

void emitInteger(Compiler *c, uint32_t value) {
    if (c->chunk.count + sizeof(uint32_t) >= c->chunk.capacity) {
        c->chunk.capacity = c->chunk.capacity < 256 ? 256 : c->chunk.capacity * 2;
        c->chunk.code = realloc(c->chunk.code, c->chunk.capacity);
    }

    c->chunk.code[c->chunk.count++] = (value >> 0) & 0xFF;
    c->chunk.code[c->chunk.count++] = (value >> 8) & 0xFF;
    c->chunk.code[c->chunk.count++] = (value >> 16) & 0xFF;
    c->chunk.code[c->chunk.count++] = (value >> 24) & 0xFF;
}

void emitOpCode(Compiler *c, OpCode op) {
    switch (op) {
        case PUSH:  emitByte(c, 0x01); break;
        case ADD:   emitByte(c, 0x02); break;
        case SUB:   emitByte(c, 0x03); break;
        case MUL:   emitByte(c, 0x04); break;
        case DIV:   emitByte(c, 0x05); break;
        case RET:   emitByte(c, 0x06); break;
        case HALT:  emitByte(c, 0xff); break;

        default:    emitByte(c, 0x00); break;
    }
}

void writeToFile(const char *file_path, Compiler *c) {
    FILE *file = fopen(file_path, "wb");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open %s for writing\n", file_path);
        return;
    }

    FileHeader header = {
        .magic = MAGIC_NUMBER,
        .version_major = VERSION_MAJOR,
        .version_minor = VERSION_MINOR,
        .code_size = c->chunk.count
    };
    fwrite(&header, sizeof(FileHeader), 1, file);

    fwrite(c->chunk.code, 1,c->chunk.count, file);
    fclose(file);
}
