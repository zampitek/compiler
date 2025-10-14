#ifndef PARSER_H
#define PARSER_H

#include "compiler.h"
#include "tokens.h"

void parseProgram(Compiler *c, Token **tokens);
void parseStatement(Compiler *c, Token **tokens);
void parseExpression(Compiler *c, Token **tokens);
void parseTerm(Compiler *c, Token **tokens);
void parseFactor(Compiler *c, Token **tokens);

#endif
