#include "../include/lexer.h"
#include "../include/tokens.h"
#include "../include/errors.h"
#include "../include/compiler.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Token *tokenize(char *raw, Compiler *c) {
    int capacity = 16;
    int count = 0;
    int line = 1;
    int column = 1;

    Token *token_list = (Token *)malloc(sizeof(Token) * capacity);
    if (token_list == NULL) {
        perror("Memory allocation failed");
        exit(-1);
    }

    while (true) {
        char ch = *raw;

        if (ch == '\0') {
            break;
        }

        if (isspace(ch) || ch == '\n' || ch == '\t') {
            if (ch == '\n') {
                column = 1;
                line++;
                raw++;
                continue;
            }
            column++;
            raw++;
            continue;
        }

        Token token;
        if (isdigit(ch)) {
            token = handle_numbers(&raw, &line, &column);

            if (token.type == ERROR || token.value == NULL) {
                addError(c->errors, ERR_COMPILER_ERROR, "Compiler error during allocation. Likely not your fault", token.line, token.column, token);
                c->had_error = true;
            }
        } else if (ispunct(ch)) {
            token = handle_symbols(&raw, &line, &column);
            if (token.type == ERROR || token.value == NULL) {
                addError(c->errors, ERR_INVALID_TOKEN, "Invalid symbol(s) found", token.line, token.column, token);
                c->had_error = true;
            }
        } else if (isalpha(ch)) {
            token = handle_keywords(&raw, &line, &column);
            if (token.type == ERROR || token.value == NULL) {
                addError(c->errors, ERR_INVALID_TOKEN, "Invalid keyword found", token.line, token.column, token);
                c->had_error = true;
            }
        }

        append(&token_list, &count, &capacity, token);
    }

    char *eof_value = (char *)malloc(1);
    if (eof_value == NULL) {
        for (int i = 0; i < count; i++) {
            free(token_list[i].value);
        }
        free(token_list);
        exit(-1);
    }
    eof_value[0] = '\0';
    append(&token_list, &count, &capacity, (Token){END_OF_FILE, eof_value});

    return token_list;
}

Token handle_numbers(char **raw, int *line, int *column) {
    const char *start = *raw;
    const char *end = *raw;

    while (isdigit(*end)) {
        end++;
        (*column)++;
    }

    size_t buffer_size = end - start;
    char *buffer = (char *)malloc(buffer_size + 1);
    if (buffer == NULL) {
        return (Token){ERROR, ""};
    }
    memcpy(buffer, start, buffer_size);

    buffer[buffer_size] = '\0';
    *raw = (char *)end;

    Token token = {INTEGER, buffer, *line, (*column - (end - start))};
    return token;
}

Token handle_symbols(char **raw, int *line, int *column) {
    char c = **raw;
    char next = *(*raw + 1);

    if (c == '>' && next == '=') {
        *raw += 2;
        *column += 2;
        return (Token){GREATER_EQUAL, ">=", *line, (*column - 2)};
    }
    if (c == '<' && next == '=') {
        *raw += 2;
        *column += 2;
        return (Token){LESS_EQUAL, "<=", *line, (*column - 2)};
    }
    if (c == '=' && next == '=') {
        *raw += 2;
        *column += 2;
        return (Token){EQUAL, "==", *line, (*column - 2)};
    }
    if (c == '!' && next == '=') {
        *raw += 2;
        *column += 2;
        return (Token){NOT_EQUAL, "!=", *line, (*column - 2)};
    }

    switch (c) {
        case '+': (*raw)++; return (Token){PLUS, "+", *line, (*column)++};
        case '-': (*raw)++; return (Token){MINUS, "-", *line, (*column)++};
        case '*': (*raw)++; return (Token){MULTIPLY, "*", *line, (*column)++};
        case '/': (*raw)++; return (Token){DIVIDE, "/", *line, (*column)++};
        case '<': (*raw)++; return (Token){LESS, "<", *line, (*column)++};
        case '>': (*raw)++; return (Token){GREATER, ">", *line, (*column)++};
        case ';': (*raw)++; return (Token){SEMICOLON, ";", *line, (*column)++};

        default:
            (*raw)++;
            return (Token){ERROR, &c, *line, (*column)++};
    }
}

Token handle_keywords(char **raw, int *line, int *column) {
    const char *start = *raw;
    const char *end = *raw;

    while (isalpha(*end)) {
        (*column)++;
        end++;
    }

    size_t buffer_size = end - start;
    char *buffer = (char *)malloc(buffer_size + 1);
    if (buffer == NULL) {
        return (Token){ERROR, NULL, 0, 0};
    }
    memcpy(buffer, start, buffer_size);

    buffer[buffer_size] = '\0';
    *raw = (char *)end;

    TokenType type = identify_keyword(buffer);
    if (type == ERROR) {
        return (Token){type, buffer, *line, (*column - (end - start))};
    }

    Token token = {type, buffer, *line, (*column - (end - start))};
    return token;
}

void append(Token **list, int *count, int *capacity, Token token) {
    if (*count >= *capacity) {
        *capacity *= 2;
        Token *new_list = (Token *)realloc(*list, sizeof(Token) * (*capacity));
        if (new_list == NULL) {
            free(*list);
            *list = NULL;
            return;
        }
        *list = new_list;
    }

    (*list)[*count] = token;
    (*count)++;
}

TokenType identify_keyword(const char *buffer) {
    if (strcmp(buffer, "return") == 0) {
        return RETURN;
    } else  {
        return ERROR;
    }
}
