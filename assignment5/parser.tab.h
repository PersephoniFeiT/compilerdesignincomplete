/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    WHILE = 258,                   /* WHILE  */
    DO = 259,                      /* DO  */
    BREAK = 260,                   /* BREAK  */
    IF = 261,                      /* IF  */
    ELSE = 262,                    /* ELSE  */
    ENDIF = 263,                   /* ENDIF  */
    FALSE = 264,                   /* FALSE  */
    TRUE = 265,                    /* TRUE  */
    ID = 266,                      /* ID  */
    BASIC = 267,                   /* BASIC  */
    NUM = 268,                     /* NUM  */
    REAL = 269,                    /* REAL  */
    PLUS = 270,                    /* PLUS  */
    MINUS = 271,                   /* MINUS  */
    MULTIPLY = 272,                /* MULTIPLY  */
    DIVIDE = 273,                  /* DIVIDE  */
    LPAREN = 274,                  /* LPAREN  */
    RPAREN = 275,                  /* RPAREN  */
    LBRACK = 276,                  /* LBRACK  */
    RBRACK = 277,                  /* RBRACK  */
    LCURL = 278,                   /* LCURL  */
    RCURL = 279,                   /* RCURL  */
    EQUAL = 280,                   /* EQUAL  */
    UNEQUAL = 281,                 /* UNEQUAL  */
    OR = 282,                      /* OR  */
    AND = 283,                     /* AND  */
    LESS = 284,                    /* LESS  */
    NOT = 285,                     /* NOT  */
    LESSEQ = 286,                  /* LESSEQ  */
    GREAT = 287,                   /* GREAT  */
    GREATEQ = 288,                 /* GREATEQ  */
    ASSIGN = 289,                  /* ASSIGN  */
    SEMI = 290                     /* SEMI  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "parser.y"

    int numval;
    BasicType basicval;
    char* idval;
    double realval;
    char* boolval;
    TypeRecord* typeval;
    DimensionList dimsval;

#line 109 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
