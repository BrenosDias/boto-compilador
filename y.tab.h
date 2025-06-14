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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    TK_TIPO_FLOAT = 258,           /* TK_TIPO_FLOAT  */
    TK_NOT = 259,                  /* TK_NOT  */
    TK_OR = 260,                   /* TK_OR  */
    TK_AND = 261,                  /* TK_AND  */
    TK_MAIOR = 262,                /* TK_MAIOR  */
    TK_MAIOR_IGUAL = 263,          /* TK_MAIOR_IGUAL  */
    TK_MENOR = 264,                /* TK_MENOR  */
    TK_MENOR_IGUAL = 265,          /* TK_MENOR_IGUAL  */
    TK_IGUAL_IGUAL = 266,          /* TK_IGUAL_IGUAL  */
    TK_DIFERENTE = 267,            /* TK_DIFERENTE  */
    TK_INT = 268,                  /* TK_INT  */
    TK_FLOAT = 269,                /* TK_FLOAT  */
    TK_CHAR = 270,                 /* TK_CHAR  */
    TK_BOOLEAN = 271,              /* TK_BOOLEAN  */
    TK_MAIN = 272,                 /* TK_MAIN  */
    TK_ID = 273,                   /* TK_ID  */
    TK_TIPO_INT = 274,             /* TK_TIPO_INT  */
    TK_VAR = 275,                  /* TK_VAR  */
    TK_FIM = 276,                  /* TK_FIM  */
    TK_ERROR = 277,                /* TK_ERROR  */
    TK_PRINT = 278,                /* TK_PRINT  */
    TK_INPUT = 279                 /* TK_INPUT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define TK_TIPO_FLOAT 258
#define TK_NOT 259
#define TK_OR 260
#define TK_AND 261
#define TK_MAIOR 262
#define TK_MAIOR_IGUAL 263
#define TK_MENOR 264
#define TK_MENOR_IGUAL 265
#define TK_IGUAL_IGUAL 266
#define TK_DIFERENTE 267
#define TK_INT 268
#define TK_FLOAT 269
#define TK_CHAR 270
#define TK_BOOLEAN 271
#define TK_MAIN 272
#define TK_ID 273
#define TK_TIPO_INT 274
#define TK_VAR 275
#define TK_FIM 276
#define TK_ERROR 277
#define TK_PRINT 278
#define TK_INPUT 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
