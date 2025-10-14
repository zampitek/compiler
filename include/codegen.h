#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdint.h>

#include "compiler.h"

void emitInstruction(Compiler *c, const char *instruction);
void emitInteger(Compiler *c, const char *integer);
void emitNewLine(Compiler *c);
void writeToFile(const char *file_path, Compiler *c);

#endif
