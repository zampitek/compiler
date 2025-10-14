#ifndef PARSER_H
#define PARSER_H

#include "tokens.h"

void parseProgram(Token **tokens);
void parseStatement(Token **tokens);
void parseExpression(Token **tokens);
void parseTerm(Token **tokens);
void parseFactor(Token **tokens);

#endif
