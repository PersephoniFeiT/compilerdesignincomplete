%{
#include <stdio.h>
#include "ChainedSymbolTable.h"
#include "typeCheck.h"
#include "intermediateCode.h"
extern int yylex();
extern FILE* yyin;
extern SymbolTable* table;
void yyerror(const char* s);
%}

%define parse.error verbose

%union {
    int numval;
    BasicType basicval;
    char* idval;
    double realval;
    char* boolval;
    TypeRecord* typeval;
    DimensionList dimsval;
    Addr addr;
}

%token  WHILE DO BREAK 
        IF ELSE ENDIF
        FALSE TRUE 
        ID BASIC NUM REAL 
        PLUS MINUS MULTIPLY DIVIDE 
        LPAREN RPAREN LBRACK RBRACK LCURL RCURL
        EQUAL UNEQUAL OR AND LESS NOT LESSEQ GREAT GREATEQ 
        ASSIGN SEMI
%nonassoc ENDIF
%nonassoc ELSE


%type <idval> ID
%type <basicval> BASIC
%type <numval> NUM
%type <realval> REAL
%type <boolval> FALSE TRUE
%type <typeval> type
%type <dimsval> typeDimensions
%type <addr> expr term factor bool join equality rel unary loc

%start program

%%
program:
    block
;

block:
    {table = constructTable(63, table);} LCURL decls stmts RCURL {table = table->prev;}
;

decls:
    decls decl | %empty
;

decl:
    type ID SEMI
    {   put(table, $2, $1);
        free($2);
        freeTypeRecord($1);
    }
    | error SEMI { yyerrok; yyclearin; }
;

type:
    BASIC {$$ = &constructTypeRecord($1, NULL); }
    | BASIC typeDimensions {$$ = constructTypeRecord($1, $2);}
;

typeDimensions:
    LBRACK NUM RBRACK
    {
        int* dims = malloc(sizeof(int));
        dims[0] = $2;
        $$->dimensions = dims;
        $$->numDimensions = 1;
    }
    | typeDimensions LBRACK NUM RBRACK
    {
        DimensionList currlist = $1;
        int dimCount = currlist.numDimensions + 1;
        int* newDims = realloc(currlist.dimensions, sizeof(int) * dimCount);
        newDims[currlist.numDimensions] = $3;
        $$->dimensions = newDims;
        $$->numDimensions = dimCount;
    }
    | typeDimensions LBRACK error RBRACK { yyerrok; $$ = $1; yyclearin;}
;

stmts: stmts stmt | %empty
;

stmt: loc ASSIGN bool SEMI
    | IF LPAREN bool RPAREN stmt %prec ENDIF
    | IF LPAREN bool RPAREN stmt ELSE stmt
    | WHILE LPAREN bool RPAREN stmt
    | DO stmt WHILE LPAREN bool RPAREN SEMI
    | BREAK SEMI
    | block
    | error SEMI { yyerrok; yyclearin; }
;

loc: loc LBRACK bool RBRACK
    | ID {
        SymbolTableEntry* entry = get(table, $1);
        if(entry == NULL){
            printf("Error: Undeclared variable %s\n", $1);
            yyerror("Undeclared variable");
            exit(1);
        }
        $$.basicval = entry->type->baseType;
        $$.addr = createAddress(VARIABLE, entry->type->baseType, entry->offset);
        free($1);
    }
    | loc LBRACK error RBRACK { yyerrok; yyclearin; }
;

bool: bool OR join | join
;

join: join AND equality | equality 
;

equality: equality EQUAL rel | equality UNEQUAL rel | rel
;

rel: expr LESS expr
    | expr LESSEQ expr
    | expr GREATEQ expr
    | expr GREAT expr
    | expr
;

expr: expr PLUS term
    {TypeRecord exprType = maxType($1.addr.kind, $3.addr);
    Address a1 = widen($1.addr, $1.basicval, $$.basicval);
    Address a2 = widen($3.addr, $3.basicval, $$.basicval);
    $$.addr = createTempVar();
    generateCode($$.addr, a1, a2, ADD, $$.basicval);}
    | expr MINUS term
    {$$.basicval = maxType($1.basicval, $3.basicval);
    Address a1 = widen($1.addr, $1.basicval, $$.basicval);
    Address a2 = widen($3.addr, $3.basicval, $$.basicval);
    $$.addr = createTempVar();
    generateCode($$.addr, a1, a2, SUB, $$.basicval);}
    | term
;

term: term MULTIPLY unary
    {$$.basicval = maxType($1.basicval, $3.basicval);
    Address a1 = widen($1.addr, $1.basicval, $$.basicval);
    Address a2 = widen($3.addr, $3.basicval, $$.basicval);
    $$.addr = generateTemp();
    generateCode($$.addr, a1, a2, MUL, $$.basicval);}
    | term DIVIDE unary
    {$$.basicval = maxType($1.basicval, $3.basicval);
    Address a1 = widen($1.addr, $1.basicval, $$.basicval);
    Address a2 = widen($3.addr, $3.basicval, $$.basicval);
    $$.addr = generateTemp();
    generateCode($$.addr, a1, a2, DIV, $$.basicval);}
    | unary
;

unary: NOT unary
    | MINUS unary
    | factor
;

factor: LPAREN bool RPAREN
    | loc
    | NUM
    {
        $$.basicval = INT;
        $$.addr = createAddress(CONSTANT, INT, $1);
    }
    | REAL
    {
        $$.basicval = FLOAT;
        $$.addr = createAddress(CONSTANT, FLOAT, $1);
    }
    | TRUE
    {
        $$.basicval = BOOL;
        $$.addr = createAddress(CONSTANT, BOOL, 1);
    }
    | FALSE
    {
        $$.basicval = BOOL;
        $$.addr = createAddress(CONSTANT, BOOL, 0);
    }
    | LPAREN error RPAREN { yyerrok; yyclearin;}
;
%%

void yyerror(const char* s){
    printf("Error parsing file:\n%s\n", s);
}
