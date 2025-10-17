#ifndef ERRORS_H
#define ERRORS_H

#include "tokens.h"
typedef enum {
    ERR_UNEXPECTED_TOKEN,
    ERR_INVALID_TOKEN,
    ERR_EXPECTED_SEMICOLON,
    ERR_MALFORMED_EXPRESSION,
    ERR_NO_FILE,
    ERR_FILE_ERROR,
    ERR_COMPILER_ERROR
} ErrorType;

typedef struct {
    ErrorType type;
    int line;
    int column;
    const char *message;
    Token token;
} Error;

typedef struct {
    Error *errors;
    int count;
    int capacity;
} ErrorList;

void initErrorList(ErrorList *errors);
void addError(ErrorList *errors, ErrorType type, const char *msg, int line, int column, Token token);
void reportErrors(ErrorList *errors);
void printError(Error error);
void freeErrorList(ErrorList *errors);

#endif
