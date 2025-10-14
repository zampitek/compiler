#ifndef LEXER_H
#define LEXER_H

#include "tokens.h"

Token *tokenize(char *raw);
Token handle_numbers(char **raw);
Token handle_symbols(char **raw);
Token handle_keywords(char **raw);
void append(Token **list, int *count, int *capacity, Token token);
TokenType identify_keyword(const char *buffer);

#endif
