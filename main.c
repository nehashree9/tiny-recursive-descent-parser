#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

int main(int argc, char *argv[]) {
    char *filename = "input.tiny";
    if (argc > 1) {
        filename = argv[1];
    }
    
    source = fopen(filename, "r");
    if (source == NULL) {
        fprintf(stderr, "File %s not found\n", filename);
        return 1;
    }
    
    printf("--------------------------------\n");
    printf("TINY Recursive Descent Parser\n");
    printf("--------------------------------\n");
    printf("Reading %s...\n", filename);
    printf("Parsing started...\n\n");
    
    parse();
    
    printf("Parsing Successful\n");
    
    fclose(source);
    return 0;
}
