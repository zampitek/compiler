#include "../include/tokens.h"
#include "../include/parser.h"

void parseProgram(Token **tokens) {
    while ((*tokens)->type != END_OF_FILE) {
        parseStatement(tokens);
    }
}

void parseStatement(Token **tokens) {
    if ((*tokens)->type == RETURN) {
        (*tokens)++;
        parseExpression(tokens);

        if ((*tokens)->type == SEMICOLON) {
            (*tokens)++;
        } else {
            // expected semicolon
        }
    } else {
        // unexpected token
    }
}

void parseExpression(Token **tokens) {
    parseTerm(tokens);

    while ((*tokens)->type  == PLUS || (*tokens)->type == MINUS) {
        (*tokens)++;
        parseTerm(tokens);
    }
}

void parseTerm(Token **tokens) {
    parseFactor(tokens);


    while ((*tokens)->type == MULTIPLY || (*tokens)->type == DIVIDE) {
        (*tokens)++;
        parseFactor(tokens);
    }
}

void parseFactor(Token **tokens) {
    if ((*tokens)->type != INTEGER) {
        // unexpected token
    }
    (*tokens)++;
}
