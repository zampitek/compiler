#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/utils.h"
#include "../include/tokens.h"
#include "../include/lexer.h"
#include "../include/compiler.h"
#include "../include/codegen.h"
#include "../include/parser.h"
#include "../include/errors.h"

bool endsWith(const char *str, const char *suffix);

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        Error noFileError = (Error){ERR_NO_FILE, 0, 0, "No file provided", (Token){ERROR, "", 0, 0}};
        printError(noFileError);

        return -1;
    }

    char *input_file = argv[1];
    if (!endsWith(input_file, ".pc")) {
        Error fileError = (Error){ERR_FILE_ERROR, 0, 0, "Input file is not a Pico file", (Token){ERROR, 0, 0}};
        printError(fileError);

        return -1;
    }

    size_t len = strlen(input_file);
    char *output = malloc(len + 2);
    memcpy(output, input_file, len - 1);
    strcpy(output + len - 1, "co");

    Compiler c;
    ErrorList e;
    initCompiler(&c, &e);
    initErrorList(&e);

    char *file_content = read_file(input_file);
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

bool endsWith(const char *str, const char *suffix) {
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    return strcmp(str + str_len - suffix_len, suffix) == 0;
}
