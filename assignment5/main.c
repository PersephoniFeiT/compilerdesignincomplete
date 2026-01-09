#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
#include "ChainedSymbolTable.h"
#include "typeCheck.h"
#include "intermediateCode.h"

extern FILE *yyin;
extern int yyparse();
extern int yyerror();
SymbolTable* table;

int main(int argc, char** argv){
    table = constructTable(128, NULL);
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening input file");
        return 1;
    }

    yyin = input_file;
    yyparse();         
    fclose(input_file);
    return 0;
}
