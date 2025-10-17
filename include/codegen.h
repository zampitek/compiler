#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdint.h>

#include "compiler.h"

#define MAGIC_NUMBER 0x5049434F
#define VERSION_MAJOR 0x01
#define VERSION_MINOR 0x00

typedef struct {
    uint32_t magic;
    uint16_t version_major;
    uint16_t version_minor;
    uint32_t code_size;
} FileHeader;

typedef enum {
    INVALID = 0x00,
    PUSH    = 0x01,
    ADD     = 0x02,
    SUB     = 0x03,
    MUL     = 0x04,
    DIV     = 0x05,
    RET     = 0x06,
    HALT    = 0xff
} OpCode;

void emitByte(Compiler *c, uint8_t byte);
void emitInteger(Compiler *c, uint32_t value);
void emitOpCode(Compiler *c, OpCode op);
void writeToFile(const char *file_path, Compiler *c);

#endif
