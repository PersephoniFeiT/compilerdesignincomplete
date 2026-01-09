%{
#include "parser.tab.h"
#include "ChainedSymbolTable.h"
#include "typeCheck.h"
extern SymbolTable* table;
extern FILE* yyin;

%}

%%
"while"                         {                                                               return WHILE; }
"do"                            {                                                               return DO; }
"break"                         {                                                               return BREAK; }
"if"                            {                                                               return IF; }
"else"                          {                                                               return ELSE; }
"false"                         { yylval.boolval = strdup(yytext);                              return FALSE; }
"true"                          { yylval.boolval = strdup(yytext);                              return TRUE; }
"int"                           { yylval.basicval = INT;                                        return BASIC; }
"float"                         { yylval.basicval = FLOAT;                                      return BASIC; }
"boolean"                       { yylval.basicval = BOOL;                                       return BASIC; }
[A-Za-z][A-Za-z0-9_]*           { yylval.idval = strdup(yytext);                                return ID; }
[0-9]+                          { yylval.numval = atoi(yytext);                                 return NUM; }
[0-9]+(\.[0-9]+)?(E[+-][0-9]+)? { yylval.realval = atof(yytext);                                return REAL; }
"+"                             {                                                               return PLUS; }
"-"                             {                                                               return MINUS; }
"*"                             {                                                               return MULTIPLY; }
"/"                             {                                                               return DIVIDE; }
"("                             {                                                               return LPAREN; }
")"                             {                                                               return RPAREN; }
"["                             {                                                               return LBRACK; }
"]"                             {                                                               return RBRACK; }
"{"                             {                                                               return LCURL; }
"}"                             {                                                               return RCURL; }
"=="                            {                                                               return EQUAL; }
"!="                            {                                                               return UNEQUAL; }
"||"                            {                                                               return OR; }
"&&"                            {                                                               return AND; }
"!"                             {                                                               return NOT; }
"<"                             {                                                               return LESS; }
"<="                            {                                                               return LESSEQ; }
">"                             {                                                               return GREAT; }
">="                            {                                                               return GREATEQ; }
"="                             {                                                               return ASSIGN; }
";"                             {                                                               return SEMI; }
[ \t\n]+    ;
%%

/*void set_input_string(const char* in) {
  yy_scan_string(in);
}

void end_lexical_scan(void) {
  yy_delete_buffer(YY_CURRENT_BUFFER);
}*/

int yywrap(){
    return 1;
}
