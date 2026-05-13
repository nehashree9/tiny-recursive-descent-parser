#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    /* Book-keeping tokens */
    ENDFILE, ERROR,
    /* Reserved words */
    IF, THEN, ELSE, END, REPEAT, UNTIL, READ, WRITE,
    /* Multicharacter tokens */
    ID, NUM,
    /* Special symbols */
    ASSIGN, EQ, LT, PLUS, MINUS, TIMES, OVER, LPAREN, RPAREN, SEMI
} TokenType;

#endif
