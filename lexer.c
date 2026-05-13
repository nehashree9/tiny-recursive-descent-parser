#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

int lineno = 1;
char tokenString[MAXTOKENLEN+1];
FILE *source;

static int EOF_flag = 0;

static int getNextChar(void) {
    if (EOF_flag) return EOF;
    int c = fgetc(source);
    if (c == '\n') lineno++;
    if (c == EOF) EOF_flag = 1;
    return c;
}

static void ungetNextChar(int c) {
    if (c == EOF) return;
    ungetc(c, source);
    if (c == '\n') lineno--;
}

static struct {
    char* str;
    TokenType tok;
} reservedWords[] = {
    {"if", IF}, {"then", THEN}, {"else", ELSE}, {"end", END},
    {"repeat", REPEAT}, {"until", UNTIL}, {"read", READ},
    {"write", WRITE}
};

static TokenType reservedLookup(char *s) {
    for (int i=0; i<8; i++) {
        if (strcmp(s, reservedWords[i].str) == 0)
            return reservedWords[i].tok;
    }
    return ID;
}

TokenType getToken(void) {
    int tokenStringIndex = 0;
    TokenType currentToken;
    int state = 0; /* 0=START, 1=INASSIGN, 2=INCOMMENT, 3=INNUM, 4=INID, 5=DONE */
    
    while (state != 5) {
        int c = getNextChar();
        int save = 1;
        switch (state) {
            case 0:
                if (isdigit(c)) state = 3;
                else if (isalpha(c)) state = 4;
                else if (c == ':') state = 1;
                else if (c == '{') { save = 0; state = 2; }
                else if (c == ' ' || c == '\t' || c == '\n' || c == '\r') save = 0;
                else {
                    state = 5;
                    switch (c) {
                        case EOF: save = 0; currentToken = ENDFILE; break;
                        case '=': currentToken = EQ; break;
                        case '<': currentToken = LT; break;
                        case '+': currentToken = PLUS; break;
                        case '-': currentToken = MINUS; break;
                        case '*': currentToken = TIMES; break;
                        case '/': currentToken = OVER; break;
                        case '(': currentToken = LPAREN; break;
                        case ')': currentToken = RPAREN; break;
                        case ';': currentToken = SEMI; break;
                        default: currentToken = ERROR; break;
                    }
                }
                break;
            case 1:
                state = 5;
                if (c == '=') {
                    currentToken = ASSIGN;
                } else {
                    ungetNextChar(c);
                    save = 0;
                    currentToken = ERROR;
                }
                break;
            case 2:
                save = 0;
                if (c == '}') state = 0;
                else if (c == EOF) { state = 5; currentToken = ENDFILE; }
                break;
            case 3:
                if (!isdigit(c)) {
                    ungetNextChar(c);
                    save = 0;
                    state = 5;
                    currentToken = NUM;
                }
                break;
            case 4:
                if (!isalpha(c)) {
                    ungetNextChar(c);
                    save = 0;
                    state = 5;
                    currentToken = ID;
                }
                break;
            case 5:
                break;
        }
        if (save && tokenStringIndex < MAXTOKENLEN) {
            tokenString[tokenStringIndex++] = (char) c;
        }
        if (state == 5) {
            tokenString[tokenStringIndex] = '\0';
            if (currentToken == ID) {
                currentToken = reservedLookup(tokenString);
            }
        }
    }
    return currentToken;
}

void printToken(TokenType token, const char* tokenString) {
    switch (token) {
        case IF: case THEN: case ELSE: case END: case REPEAT: case UNTIL: case READ: case WRITE:
            printf("reserved word: %s\n", tokenString); break;
        case ASSIGN: printf(":=\n"); break;
        case LT: printf("<\n"); break;
        case EQ: printf("=\n"); break;
        case LPAREN: printf("(\n"); break;
        case RPAREN: printf(")\n"); break;
        case SEMI: printf(";\n"); break;
        case PLUS: printf("+\n"); break;
        case MINUS: printf("-\n"); break;
        case TIMES: printf("*\n"); break;
        case OVER: printf("/\n"); break;
        case ENDFILE: printf("EOF\n"); break;
        case NUM: printf("NUM, val= %s\n", tokenString); break;
        case ID: printf("ID, name= %s\n", tokenString); break;
        case ERROR: printf("ERROR: %s\n", tokenString); break;
        default: printf("Unknown token: %d\n", token);
    }
}
