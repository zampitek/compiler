#ifndef LEXER_H
#define LEXER_H

#include "compiler.h"
#include "tokens.h"

Token *tokenize(char *raw, Compiler *c);
Token handle_numbers(char **raw, int *line, int *column);
Token handle_symbols(char **raw, int *line, int *column);
Token handle_keywords(char **raw, int *line, int *column);
void append(Token **list, int *count, int *capacity, Token token);
TokenType identify_keyword(const char *buffer);

#endif
