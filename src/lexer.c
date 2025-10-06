#include "../include/lexer.h"
#include "../include/tokens.h"
#include "../include/utils.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Token handle_numbers(char **raw);
Token handle_symbols(char **raw);
Token handle_keywords(char **raw);

char consume(char **pt);
char peek(char *pt);
void append(Token **last_element, Token token);

TokenType identify_symbol(const char *buffer);
TokenType identify_keyword(const char *buffer);

Token *tokenize(char *raw) {
    Token *token_list = (Token *)malloc(sizeof(Token) * length(raw) + 1);
    Token *last_element = token_list;

    while (true) {
        char ch = *raw;

        if (ch == '\0') {
            break;
        }

        if (isspace(ch) || ch == '\n' || ch == '\t') {
            raw++;
            continue;
        }

        if (isdigit(ch)) {
            Token token = handle_numbers(&raw);
            if (token.type == TOKEN_ERROR || token.value == NULL) {
                perror("Error parsing number");
                exit(-1);
            }
            append(&last_element, token);
        } else if (ispunct(ch)) {
            Token token = handle_symbols(&raw);
            if (token.type == TOKEN_ERROR || token.value == NULL) {
                perror("Error parsing operator");
                exit(-1);
            }
            append(&last_element, token);
        } else if (isalpha(ch)) {
            Token token = handle_keywords(&raw);
            if (token.type == TOKEN_ERROR || token.value == NULL) {
                perror("Error parsing operator");
                exit(-1);
            }
            append(&last_element, token);
        }
    }

    append(&last_element, (Token){TOKEN_EOF, "\0"});

    return token_list;
}

Token handle_numbers(char **raw) {
    const char *start = *raw;
    const char *end = *raw;

    while (isdigit(*end)) {
        end++;
    }

    size_t buffer_size = end - start;
    char *buffer = (char *)malloc(buffer_size + 1);
    if (buffer == NULL) {
        return (Token){TOKEN_ERROR, NULL};
    }
    memcpy(buffer, start, buffer_size);

    buffer[buffer_size] = '\0';
    *raw = (char *)end;

    Token token = {TOKEN_NUMBER, buffer};
    return token;
}

Token handle_symbols(char **raw) {
    const char *start = *raw;
    const char *end = *raw;

    while (ispunct(*end)) {
        end++;
    }

    size_t buffer_size = end - start;
    char *buffer = (char *)malloc(buffer_size + 1);
    if (buffer == NULL) {
        return (Token){TOKEN_ERROR, NULL};
    }
    memcpy(buffer, start, buffer_size);

    buffer[buffer_size] = '\0';
    *raw = (char *)end;

    TokenType type = identify_symbol(buffer);
    if (type == TOKEN_ERROR) {
        return (Token){type, NULL};
    }

    Token token = {type, buffer};
    return token;
}

Token handle_keywords(char **raw) {
    const char *start = *raw;
    const char *end = *raw;

    while (isalpha(*end)) {
        end++;
    }

    size_t buffer_size = end - start;
    char *buffer = (char *)malloc(buffer_size + 1);
    if (buffer == NULL) {
        return (Token){TOKEN_ERROR, NULL};
    }
    memcpy(buffer, start, buffer_size);

    buffer[buffer_size] = '\0';
    *raw = (char *)end;

    TokenType type = identify_keyword(buffer);
    if (type == TOKEN_ERROR) {
        return (Token){type, NULL};
    }

    Token token = {type, buffer};
    return token;
}

void append(Token **last_element, Token token) {
    *last_element[0] = token;
    (*last_element)++;
}

TokenType identify_symbol(const char *buffer) {
    if (strcmp(buffer, ";") == 0) {
        return TOKEN_SEMICOLON;
    }  else {
        return TOKEN_ERROR;
    }
}

TokenType identify_keyword(const char *buffer) {
    if (strcmp(buffer, "return") == 0) {
        return TOKEN_KEYWORD_RETURN;
    } else  {
        return TOKEN_ERROR;
    }
}
