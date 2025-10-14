#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/utils.h"
#include "../include/tokens.h"
#include "../include/lexer.h"

char *token_lookup(Token token);

int main(int argc, char *argv[]) {
    char *file = "/home/ricky/coding/c/language/compiler/prova.txt";
    char *file_content = read_file(file);

    Token *tokens = tokenize(file_content);

    int i = 0;
    Token token;
    while (true) {
        token = tokens[i];
        if (token.type == END_OF_FILE) {
            break;
        }
        printf("%s ", token_lookup(token));
        i++;
    }
    putchar('\n');

    free(tokens);
    free(file_content);

    return 0;
}

char *token_lookup(Token token) {
    static char buffer[256];

    switch (token.type) {
    case RETURN:
        return "TOKEN_KEYWORD_RETURN";
        break;
    case INTEGER:
        snprintf(buffer, sizeof(buffer), "TOKEN_NUMBER:%s", token.value);
        return buffer;
    case SEMICOLON:
        return "TOKEN_SEMICOLON";
        break;
    case PLUS:
        return "TOKEN_PLUS";
        break;
    case MINUS:
        return "TOKEN_MINUS";
        break;
    case MULTIPLY:
        return "TOKEN_MULTIPLY";
        break;
    case DIVIDE:
        return "TOKEN_DIVIDE";
        break;
    case LESS:
        return "TOKEN_LESS";
        break;
    case LESS_EQUAL:
        return "TOKEN_LESS_EQUAL";
        break;
    case GREATER:
        return "TOKEN_GREATER";
        break;
    case GREATER_EQUAL:
        return "TOKEN_GREATER_EQUAL";
        break;
    case EOF:
        return "TOKEN_EOF";
        break;

    default:
        return NULL;
    }
}
