#include "../include/lexer.h"
#include "../include/tokens.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Token *tokenize(char *raw) {
    int capacity = 16;
    int count = 0;
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
            raw++;
            continue;
        }

        if (isdigit(ch)) {
            Token token = handle_numbers(&raw);
            if (token.type == ERROR || token.value == NULL) {
                perror("Error parsing number");
                for (int i = 0; i < count; i++) {
                    free(token_list[i].value);
                }
                free(token_list);
                exit(-1);
            }
            append(&token_list, &count, &capacity, token);
        } else if (ispunct(ch)) {
            Token token = handle_symbols(&raw);
            if (token.type == ERROR || token.value == NULL) {
                perror("Error parsing operator");
                for (int i = 0; i < count; i++) {
                    free(token_list[i].value);
                }
                free(token_list);
                exit(-1);
            }
            append(&token_list, &count, &capacity, token);
        } else if (isalpha(ch)) {
            Token token = handle_keywords(&raw);
            if (token.type == ERROR || token.value == NULL) {
                perror("Error parsing operator");
                for (int i = 0; i < count; i++) {
                    free(token_list[i].value);
                }
                free(token_list);
                exit(-1);
            }
            append(&token_list, &count, &capacity, token);
        }
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

Token handle_numbers(char **raw) {
    const char *start = *raw;
    const char *end = *raw;

    while (isdigit(*end)) {
        end++;
    }

    size_t buffer_size = end - start;
    char *buffer = (char *)malloc(buffer_size + 1);
    if (buffer == NULL) {
        return (Token){ERROR, NULL};
    }
    memcpy(buffer, start, buffer_size);

    buffer[buffer_size] = '\0';
    *raw = (char *)end;

    Token token = {INTEGER, buffer};
    return token;
}

Token handle_symbols(char **raw) {
    char c = **raw;
    char next = *(*raw + 1);

    if (c == '>' && next == '=') {
        *raw += 2;
        return (Token){GREATER_EQUAL, ">="};
    }
    if (c == '<' && next == '=') {
        *raw += 2;
        return (Token){LESS_EQUAL, "<="};
    }
    if (c == '=' && next == '=') {
        *raw += 2;
        return (Token){EQUAL, "=="};
    }
    if (c == '!' && next == '=') {
        *raw += 2;
        return (Token){NOT_EQUAL, "!="};
    }

    switch (c) {
        case '+': (*raw)++; return (Token){PLUS, "+"};
        case '-': (*raw)++; return (Token){MINUS, "-"};
        case '*': (*raw)++; return (Token){MULTIPLY, "*"};
        case '/': (*raw)++; return (Token){DIVIDE, "/"};
        case '<': (*raw)++; return (Token){LESS, "<"};
        case '>': (*raw)++; return (Token){GREATER, ">"};
        case ';': (*raw)++; return (Token){SEMICOLON, ";"};

        default:
            return (Token){ERROR, NULL};
    }
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
        return (Token){ERROR, NULL};
    }
    memcpy(buffer, start, buffer_size);

    buffer[buffer_size] = '\0';
    *raw = (char *)end;

    TokenType type = identify_keyword(buffer);
    if (type == ERROR) {
        free(buffer);
        return (Token){type, NULL};
    }

    Token token = {type, buffer};
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
