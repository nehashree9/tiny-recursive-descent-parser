#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"

static TokenType token;

static void program(void);
static void stmt_seq(void);
static void stmt(void);
static void if_stmt(void);
static void repeat_stmt(void);
static void assign_stmt(void);
static void read_stmt(void);
static void write_stmt(void);
static void exp_rule(void);
static void simple_exp(void);
static void term(void);
static void factor(void);

static void syntaxError(char *message) {
    (void)message;
    fprintf(stdout, "\nSyntax Error at line %d near '%s'\n", lineno, tokenString);
    exit(1);
}

static void match(TokenType expected) {
    if (token == expected) {
        token = getToken();
    } else {
        syntaxError("Unexpected token");
    }
}

static void program(void) {
    stmt_seq();
}

static void stmt_seq(void) {
    stmt();
    while (token == SEMI) {
        match(SEMI);
        stmt();
    }
}

static void stmt(void) {
    switch (token) {
        case IF: if_stmt(); break;
        case REPEAT: repeat_stmt(); break;
        case ID: assign_stmt(); break;
        case READ: read_stmt(); break;
        case WRITE: write_stmt(); break;
        default: syntaxError("Unexpected token in statement");
    }
}

static void if_stmt(void) {
    match(IF);
    exp_rule();
    match(THEN);
    stmt_seq();
    if (token == ELSE) {
        match(ELSE);
        stmt_seq();
    }
    match(END);
}

static void repeat_stmt(void) {
    match(REPEAT);
    stmt_seq();
    match(UNTIL);
    exp_rule();
}

static void assign_stmt(void) {
    match(ID);
    match(ASSIGN);
    exp_rule();
}

static void read_stmt(void) {
    match(READ);
    match(ID);
}

static void write_stmt(void) {
    match(WRITE);
    exp_rule();
}

static void exp_rule(void) {
    simple_exp();
    if ((token == LT) || (token == EQ)) {
        match(token);
        simple_exp();
    }
}

static void simple_exp(void) {
    term();
    while ((token == PLUS) || (token == MINUS)) {
        match(token);
        term();
    }
}

static void term(void) {
    factor();
    while ((token == TIMES) || (token == OVER)) {
        match(token);
        factor();
    }
}

static void factor(void) {
    switch (token) {
        case NUM:
            match(NUM);
            break;
        case ID:
            match(ID);
            break;
        case LPAREN:
            match(LPAREN);
            exp_rule();
            match(RPAREN);
            break;
        default:
            syntaxError("Unexpected token in factor");
    }
}

void parse(void) {
    token = getToken();
    program();
    if (token != ENDFILE) {
        syntaxError("Code ends before file");
    }
}
