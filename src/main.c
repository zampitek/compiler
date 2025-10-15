#include <stdbool.h>
#include <stdlib.h>

#include "../include/utils.h"
#include "../include/tokens.h"
#include "../include/lexer.h"
#include "../include/compiler.h"
#include "../include/codegen.h"
#include "../include/parser.h"

char *token_lookup(Token token);

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        // no file error

        return -1;
    }

    char *input = argv[1];
    char *output = argv[2];

    Compiler c;
    char *file_content = read_file(input);
    Token *tokens = tokenize(file_content);

    initCompiler(&c, tokens);
    parseProgram(&c, &tokens);
    writeToFile(output, &c);
    freeCompiler(&c);

    return 0;
}
