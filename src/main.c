#include <stdbool.h>

#include "../include/utils.h"
#include "../include/tokens.h"
#include "../include/lexer.h"
#include "../include/compiler.h"
#include "../include/codegen.h"
#include "../include/parser.h"

char *token_lookup(Token token);

int main(int argc, char *argv[]) {
    Compiler c;
    char *file = "/home/ricky/coding/c/language/compiler/prova.txt";
    char *file_content = read_file(file);
    Token *tokens = tokenize(file_content);

    initCompiler(&c, tokens);
    parseProgram(&c, &tokens);
    writeToFile("/home/ricky/coding/c/language/compiler/output.txt", &c);
    freeCompiler(&c);

    return 0;
}
