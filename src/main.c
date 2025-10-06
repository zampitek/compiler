#include <stdio.h>
#include <stdlib.h>

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
    while ((token = tokens[i]).type != TOKEN_EOF) {
        printf("%s ", token_lookup(token));
        i++;
    }
    putchar('\n');
    
    return 0;
}

char *token_lookup(Token token) {
    char *token_s;

    switch (token.type) {
    case TOKEN_KEYWORD_RETURN:
        token_s = "TOKEN_KEYWORD_RETURN";
        break;
    case TOKEN_NUMBER:
        sprintf(token_s, "TOKEN_NUMBER:%s", token.value);
        break;
    case TOKEN_SEMICOLON:
        token_s = "TOKEN_SEMICOLON";
        break;
    case TOKEN_EOF:
        token_s = "TOKEN_EOF";
        break;
    
    default:
        return NULL;
    }

    return token_s;
}
