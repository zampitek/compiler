#include "../include/errors.h"

#include <stdio.h>
#include <stdlib.h>

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"      // Errors
#define COLOR_YELLOW  "\033[33m"      // Warnings
#define COLOR_GREEN   "\033[32m"      // Success
#define COLOR_BLUE    "\033[34m"      // Info
#define COLOR_CYAN    "\033[36m"      // Hints
#define COLOR_GRAY    "\033[90m"      // Muted text
#define COLOR_BOLD    "\033[1m"       // Bold

void initErrorList(ErrorList *errors) {
    errors->errors = (Error *)malloc(sizeof(Error) * 16);
    errors->count = 0;
    errors->capacity = 16;
}

void addError(ErrorList *errors, ErrorType type, const char *msg, int line, int column, Token token) {
    if (errors->count >= errors->capacity) {
        errors->errors = (Error *)realloc(errors->errors, errors->capacity * 2);
        errors->capacity *= 2;
    }

    errors->errors[errors->count] = (Error){type, line, column, msg, token};
    errors->count++;
}

void reportErrors(ErrorList *errors) {
    for (int i = 0; i < errors->count; i++) {
        printError(errors->errors[i]);
    }
}

void printError(Error error) {
    printf("[" COLOR_RED "ERROR" COLOR_RESET "] line " COLOR_BLUE "%d" COLOR_RESET ", column " COLOR_BLUE "%d" COLOR_RESET ":\n", error.line, error.column);
    printf("%s\n", error.message);
    printf("Affected code: " COLOR_BOLD "%s\n", error.token.value);
    printf("\n");
}

void freeErrorList(ErrorList *errors) {
    free(errors->errors);
}
