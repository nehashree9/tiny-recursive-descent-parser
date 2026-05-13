#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"

#define MAXTOKENLEN 256

extern char tokenString[MAXTOKENLEN+1];
extern int lineno;
extern FILE *source;

TokenType getToken(void);
void printToken(TokenType token, const char* tokenString);

#endif
