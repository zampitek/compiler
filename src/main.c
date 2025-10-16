#include <stdbool.h>

#include "../include/utils.h"
#include "../include/tokens.h"
#include "../include/lexer.h"
#include "../include/compiler.h"
#include "../include/codegen.h"
#include "../include/parser.h"
#include "../include/errors.h"

char *token_lookup(Token token);

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        Error noFileError = (Error){ERR_NO_FILE, 0, 0, "No file provided", (Token){ERROR, "", 0, 0}};
        printError(noFileError);

        return -1;
    }

    char *input = argv[1];
    char *output = argv[2];

    Compiler c;
    ErrorList e;
    initCompiler(&c, &e);
    initErrorList(&e);

    char *file_content = read_file(input);
    Token *tokens = tokenize(file_content, &c);
    if (c.had_error) {
        reportErrors(c.errors);
        freeErrorList(c.errors);
        freeCompiler(&c);

        return -1;
    }

    addTokens(&c, tokens);

    parseProgram(&c, &tokens);
    if (c.had_error) {
        reportErrors(c.errors);
        freeErrorList(c.errors);
        freeCompiler(&c);

        return -1;
    }

    writeToFile(output, &c);
    freeCompiler(&c);

    return 0;
}
