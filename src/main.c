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
        if (token.type == TOKEN_EOF) {
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
    case TOKEN_KEYWORD_RETURN:
        return "TOKEN_KEYWORD_RETURN";
        break;
    case TOKEN_NUMBER:
        snprintf(buffer, sizeof(buffer), "TOKEN_NUMBER:%s", token.value);
        return buffer;
    case TOKEN_SEMICOLON:
        return "TOKEN_SEMICOLON";
        break;
    case TOKEN_EOF:
        return "TOKEN_EOF";
        break;

    default:
        return NULL;
    }
}
