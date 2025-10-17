#include "../include/tokens.h"
#include "../include/compiler.h"
#include "../include/parser.h"
#include "../include/codegen.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

void parseProgram(Compiler *c, Token **tokens) {
    while ((*tokens)->type != END_OF_FILE) {
        parseStatement(c, tokens);
    }
    emitOpCode(c, HALT);
}

void parseStatement(Compiler *c, Token **tokens) {
    if ((*tokens)->type == RETURN) {
        (*tokens)++;
        parseExpression(c, tokens);

        if ((*tokens)->type == SEMICOLON) {
            (*tokens)++;
        } else {
            addError(c->errors, ERR_EXPECTED_SEMICOLON, "Expected semicolon. Found other token instead", (*tokens)->line, (*tokens)->column, **tokens);
            c->had_error = true;
        }

        emitOpCode(c, RET);
    } else {
        addError(c->errors, ERR_UNEXPECTED_TOKEN, "Unexpected token found. Expected: return", (*tokens)->line, (*tokens)->column, **tokens);
        c->had_error = true;
    }
}

void parseExpression(Compiler *c, Token **tokens) {
    parseTerm(c, tokens);

    while ((*tokens)->type  == PLUS || (*tokens)->type == MINUS) {
        TokenType op = (*tokens)->type;
        (*tokens)++;
        parseTerm(c, tokens);

        if (op == PLUS) {
            emitOpCode(c, ADD);
        } else {
            emitOpCode(c, SUB);
        }
    }
}

void parseTerm(Compiler *c, Token **tokens) {
    parseFactor(c, tokens);


    while ((*tokens)->type == MULTIPLY || (*tokens)->type == DIVIDE) {
        TokenType op = (*tokens)->type;
        (*tokens)++;
        parseFactor(c, tokens);

        if (op == MULTIPLY) {
            emitOpCode(c, MUL);
        } else {
            emitOpCode(c, DIV);
        }
    }
}

void parseFactor(Compiler *c, Token **tokens) {
    if ((*tokens)->type != INTEGER) {
        addError(c->errors, ERR_UNEXPECTED_TOKEN, "Unexpected token found. Expected: Integer", (*tokens)->line, (*tokens)->column, **tokens);
        c->had_error = true;
        return;
    }
    uint32_t value = (uint32_t)strtoul((*tokens)->value, NULL, 10);

    emitOpCode(c, PUSH);
    emitInteger(c, value);
    (*tokens)++;
}
