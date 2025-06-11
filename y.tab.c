/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "sintatico.y"

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <set>
#include <iostream>
#include <vector>
#include <stack>

#define YYSTYPE atributos

int yydebug = 1;

using namespace std;

using CaseInfo = pair<string, string>;

int vet_cedulas[200];

struct atributos
{
	string label;
	string traducao;
	string type;
};

struct Symbol {
    string nome;
    string tipo;
	string temp;
}; 

struct TabelaSimbolos
{
	vector<unordered_map<string, Symbol>> escopos;
	int quantidade;
};

// Estrutura para guardar os rótulos de um laço
struct InfoLaco {
    string inicio;
    string fim;
};

struct SwitchContext {
    string temp_var;      // Temp que guarda o valor da expressão do switch
    string end_label;       // Rótulo para o 'break' pular
    string default_label;   // Rótulo para o 'default' (pode ser o mesmo que end_label)
    bool has_default = false;  // Flag para saber se um default foi definido
    vector<CaseInfo> cases; // Vetor com todos os cases (valor, rótulo)
};
 

typedef struct {
    char* str;
    int length;
} String;

int var_temp_qnt;
// Pilha para os rótulos de saída (para o 'break') - continua igual
stack<string> breakLabels;
stack<string> continueLabels;
// NOVA Pilha para gerenciar os laços ativos
vector<InfoLaco> pilhaLacos;
stack<SwitchContext> switchStack;
vector<Symbol> tempsVector;
set<string> tempsAdicionados;
TabelaSimbolos symbolTable;

int yylex(void);
void yyerror(string);
string gentempcode(string tipo);
void printSymbolTable();
void checkUndefinedTypes();
void insertTempsST(const string& nome, const string& tipo);
void typeValue(string& resultType,  string& leftType,  string& rightType,  string& leftLabel,  string& rightLabel);
void implicitConversion(atributos& esquerda, atributos& direita, atributos& final , string operacao);
void reportSemanticError(string type1, string type3, string text);
void entraEscopo();
void saiEscopo();
void declaraVariavel(Symbol& simbolo);
string genlabel();
String strCopy(String source);
// string searchType(const string& label);

#line 158 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    TK_INPUT = 279,                /* TK_INPUT  */
    TK_STRING = 280,               /* TK_STRING  */
    TK_WHILE = 281,                /* TK_WHILE  */
    TK_FOR = 282,                  /* TK_FOR  */
    TK_DO = 283,                   /* TK_DO  */
    TK_IF = 284,                   /* TK_IF  */
    TK_BREAK = 285,                /* TK_BREAK  */
    TK_CONTINUE = 286,             /* TK_CONTINUE  */
    TK_BREAKOUT = 287,             /* TK_BREAKOUT  */
    TK_SWITCH = 288,               /* TK_SWITCH  */
    TK_CASE = 289,                 /* TK_CASE  */
    TK_DEFAULT = 290,              /* TK_DEFAULT  */
    LOWER_THAN_ELSE = 291,         /* LOWER_THAN_ELSE  */
    TK_ELSE = 292                  /* TK_ELSE  */
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
#define TK_STRING 280
#define TK_WHILE 281
#define TK_FOR 282
#define TK_DO 283
#define TK_IF 284
#define TK_BREAK 285
#define TK_CONTINUE 286
#define TK_BREAKOUT 287
#define TK_SWITCH 288
#define TK_CASE 289
#define TK_DEFAULT 290
#define LOWER_THAN_ELSE 291
#define TK_ELSE 292

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TK_TIPO_FLOAT = 3,              /* TK_TIPO_FLOAT  */
  YYSYMBOL_TK_NOT = 4,                     /* TK_NOT  */
  YYSYMBOL_TK_OR = 5,                      /* TK_OR  */
  YYSYMBOL_TK_AND = 6,                     /* TK_AND  */
  YYSYMBOL_TK_MAIOR = 7,                   /* TK_MAIOR  */
  YYSYMBOL_TK_MAIOR_IGUAL = 8,             /* TK_MAIOR_IGUAL  */
  YYSYMBOL_TK_MENOR = 9,                   /* TK_MENOR  */
  YYSYMBOL_TK_MENOR_IGUAL = 10,            /* TK_MENOR_IGUAL  */
  YYSYMBOL_TK_IGUAL_IGUAL = 11,            /* TK_IGUAL_IGUAL  */
  YYSYMBOL_TK_DIFERENTE = 12,              /* TK_DIFERENTE  */
  YYSYMBOL_TK_INT = 13,                    /* TK_INT  */
  YYSYMBOL_TK_FLOAT = 14,                  /* TK_FLOAT  */
  YYSYMBOL_TK_CHAR = 15,                   /* TK_CHAR  */
  YYSYMBOL_TK_BOOLEAN = 16,                /* TK_BOOLEAN  */
  YYSYMBOL_TK_MAIN = 17,                   /* TK_MAIN  */
  YYSYMBOL_TK_ID = 18,                     /* TK_ID  */
  YYSYMBOL_TK_TIPO_INT = 19,               /* TK_TIPO_INT  */
  YYSYMBOL_TK_VAR = 20,                    /* TK_VAR  */
  YYSYMBOL_TK_FIM = 21,                    /* TK_FIM  */
  YYSYMBOL_TK_ERROR = 22,                  /* TK_ERROR  */
  YYSYMBOL_TK_PRINT = 23,                  /* TK_PRINT  */
  YYSYMBOL_TK_INPUT = 24,                  /* TK_INPUT  */
  YYSYMBOL_TK_STRING = 25,                 /* TK_STRING  */
  YYSYMBOL_TK_WHILE = 26,                  /* TK_WHILE  */
  YYSYMBOL_TK_FOR = 27,                    /* TK_FOR  */
  YYSYMBOL_TK_DO = 28,                     /* TK_DO  */
  YYSYMBOL_TK_IF = 29,                     /* TK_IF  */
  YYSYMBOL_TK_BREAK = 30,                  /* TK_BREAK  */
  YYSYMBOL_TK_CONTINUE = 31,               /* TK_CONTINUE  */
  YYSYMBOL_TK_BREAKOUT = 32,               /* TK_BREAKOUT  */
  YYSYMBOL_TK_SWITCH = 33,                 /* TK_SWITCH  */
  YYSYMBOL_TK_CASE = 34,                   /* TK_CASE  */
  YYSYMBOL_TK_DEFAULT = 35,                /* TK_DEFAULT  */
  YYSYMBOL_36_ = 36,                       /* '+'  */
  YYSYMBOL_37_ = 37,                       /* '-'  */
  YYSYMBOL_38_ = 38,                       /* '*'  */
  YYSYMBOL_39_ = 39,                       /* '/'  */
  YYSYMBOL_LOWER_THAN_ELSE = 40,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_TK_ELSE = 41,                   /* TK_ELSE  */
  YYSYMBOL_42_ = 42,                       /* ';'  */
  YYSYMBOL_43_ = 43,                       /* '='  */
  YYSYMBOL_44_ = 44,                       /* '('  */
  YYSYMBOL_45_ = 45,                       /* ')'  */
  YYSYMBOL_46_ = 46,                       /* '{'  */
  YYSYMBOL_47_ = 47,                       /* '}'  */
  YYSYMBOL_48_ = 48,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_S = 50,                         /* S  */
  YYSYMBOL_LISTA_DECLARACOES_GLOBAIS = 51, /* LISTA_DECLARACOES_GLOBAIS  */
  YYSYMBOL_DECLARACAO_GLOBAL = 52,         /* DECLARACAO_GLOBAL  */
  YYSYMBOL_FUNCAO_MAIN = 53,               /* FUNCAO_MAIN  */
  YYSYMBOL_BLOCO = 54,                     /* BLOCO  */
  YYSYMBOL_COMANDOS = 55,                  /* COMANDOS  */
  YYSYMBOL_COMANDO = 56,                   /* COMANDO  */
  YYSYMBOL_PUSH_ESCOPO = 57,               /* PUSH_ESCOPO  */
  YYSYMBOL_POP_ESCOPO = 58,                /* POP_ESCOPO  */
  YYSYMBOL_FOR_DECL_OU_EXPR = 59,          /* FOR_DECL_OU_EXPR  */
  YYSYMBOL_FOR_INIT = 60,                  /* FOR_INIT  */
  YYSYMBOL_FOR_COND = 61,                  /* FOR_COND  */
  YYSYMBOL_FOR_INCR = 62,                  /* FOR_INCR  */
  YYSYMBOL_ESTRUTURA_DE_CONTROLE = 63,     /* ESTRUTURA_DE_CONTROLE  */
  YYSYMBOL_SWITCH = 64,                    /* SWITCH  */
  YYSYMBOL_SWITCH_HEADER = 65,             /* SWITCH_HEADER  */
  YYSYMBOL_LISTA_CASES = 66,               /* LISTA_CASES  */
  YYSYMBOL_CASE_BLOCO = 67,                /* CASE_BLOCO  */
  YYSYMBOL_LABEL_CASE = 68,                /* LABEL_CASE  */
  YYSYMBOL_INICIO_LOOP = 69,               /* INICIO_LOOP  */
  YYSYMBOL_EXPRESSAO = 70,                 /* EXPRESSAO  */
  YYSYMBOL_E = 71                          /* E  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   463

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      44,    45,    38,    36,     2,    37,     2,    39,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    42,
       2,    43,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,    47,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   113,   113,   162,   163,   168,   177,   191,   199,   205,
     210,   216,   244,   254,   275,   279,   283,   293,   304,   317,
     323,   330,   341,   348,   353,   359,   365,   376,   381,   386,
     422,   458,   510,   528,   565,   572,   608,   623,   628,   634,
     641,   651,   666,   686,   778,   782,   800,   842,   849,   856,
     863,   870,   883,   900,   913,   927,   940,   954,   971,   988,
    1005,  1015,  1025,  1029,  1062,  1070,  1077,  1091,  1098
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TK_TIPO_FLOAT",
  "TK_NOT", "TK_OR", "TK_AND", "TK_MAIOR", "TK_MAIOR_IGUAL", "TK_MENOR",
  "TK_MENOR_IGUAL", "TK_IGUAL_IGUAL", "TK_DIFERENTE", "TK_INT", "TK_FLOAT",
  "TK_CHAR", "TK_BOOLEAN", "TK_MAIN", "TK_ID", "TK_TIPO_INT", "TK_VAR",
  "TK_FIM", "TK_ERROR", "TK_PRINT", "TK_INPUT", "TK_STRING", "TK_WHILE",
  "TK_FOR", "TK_DO", "TK_IF", "TK_BREAK", "TK_CONTINUE", "TK_BREAKOUT",
  "TK_SWITCH", "TK_CASE", "TK_DEFAULT", "'+'", "'-'", "'*'", "'/'",
  "LOWER_THAN_ELSE", "TK_ELSE", "';'", "'='", "'('", "')'", "'{'", "'}'",
  "':'", "$accept", "S", "LISTA_DECLARACOES_GLOBAIS", "DECLARACAO_GLOBAL",
  "FUNCAO_MAIN", "BLOCO", "COMANDOS", "COMANDO", "PUSH_ESCOPO",
  "POP_ESCOPO", "FOR_DECL_OU_EXPR", "FOR_INIT", "FOR_COND", "FOR_INCR",
  "ESTRUTURA_DE_CONTROLE", "SWITCH", "SWITCH_HEADER", "LISTA_CASES",
  "CASE_BLOCO", "LABEL_CASE", "INICIO_LOOP", "EXPRESSAO", "E", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-86)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -5,    -1,    42,    27,    -5,   -30,   -86,    30,   -86,   -86,
     -86,   165,     5,     7,   165,   -86,   -86,   -86,   -86,   -86,
      10,   -86,   165,   368,    11,   165,   424,   165,   188,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   -86,     9,   205,   246,   -86,   391,   424,    -6,    -6,
      -6,    -6,     0,     0,    -4,    -4,   -86,   -86,   -86,   -86,
     114,   -86,   -86,    14,    40,    17,   -86,    26,   -86,    31,
      34,    36,    37,    39,    33,   114,   114,   -86,   -86,     6,
      43,   384,    87,     2,   165,    44,    49,   114,   165,   -86,
     -86,   -86,   165,   -86,   -86,   -86,    33,    71,   -86,    45,
       6,    38,   -86,    50,   384,   -86,   165,   256,   165,    69,
     -86,    47,   -86,    70,   266,   307,   -86,   -86,   -86,   -86,
     114,    53,   376,   -86,   317,    56,   165,    60,   114,    61,
     -86,   -86,   -86,   114,   165,    66,   384,   165,    68,   -86,
     -86,   384,   148,   327,   114,    65,   -86,    72,   -86,   -86,
     -86,   114,   -86
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     0,     4,     0,     1,     0,     2,     3,
       5,     0,     0,     0,     0,    64,    65,    67,    66,    63,
       0,    68,     0,     0,     0,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,     0,     0,     0,    62,    59,    58,    51,    56,
      52,    55,    54,    53,    47,    48,    49,    50,    19,     7,
      10,    61,    60,    63,     0,     0,    42,     0,    42,     0,
       0,     0,     0,     0,     0,    10,    10,    15,    34,    38,
       0,    44,     0,     0,     0,     0,    24,     0,     0,    16,
      18,    17,     0,    20,     8,     9,     0,     0,    41,     0,
      38,     0,    11,     0,    43,    12,     0,     0,     0,     0,
      23,     0,    22,     0,     0,     0,    14,    40,    35,    37,
      10,     0,     0,    45,     0,     0,    26,     0,     0,     0,
      39,    46,    13,     0,     0,     0,    25,     0,    32,    36,
      29,    21,    28,     0,     0,     0,    27,     0,    33,    42,
      30,     0,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -86,   -86,   109,   -86,   -86,   -86,   -70,   -85,    74,    23,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,    20,   -86,   -86,
     -67,   -82,   -11
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,     8,    59,    74,    75,    76,    94,
     110,   111,   135,   145,    77,    78,    79,    99,   100,   101,
      85,    80,    81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      23,    87,   113,    26,   112,    95,    96,    31,    32,    33,
      34,    28,    10,    11,    43,     1,    44,     5,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      37,    38,    39,    40,    39,    40,    37,    38,    39,    40,
      97,    98,     6,   138,   105,   106,     7,    12,   140,    24,
     130,    25,    13,    14,    27,    58,    42,    82,    83,   148,
     146,    84,    15,    16,    17,    18,   152,    63,    20,   109,
      86,   104,    65,   107,    21,    88,    89,   114,    90,    91,
      93,   115,   151,    92,   117,   102,   120,   125,   108,   126,
      13,    14,   118,    22,   121,   122,   127,   124,   131,   134,
      15,    16,    17,    18,   137,    19,    20,   139,   142,   144,
     149,   103,    21,     9,   150,   136,    60,    13,    14,   116,
     119,     0,     0,   141,     0,     0,   143,    15,    16,    17,
      18,    22,    63,    20,    64,     0,     0,    65,     0,    21,
      66,    67,    68,    69,    70,    71,    72,    73,     0,     0,
       0,    13,    14,     0,     0,     0,     0,     0,    22,     0,
      58,    15,    16,    17,    18,     0,    63,    20,    13,    14,
       0,    65,     0,    21,     0,     0,     0,     0,    15,    16,
      17,    18,     0,    19,    20,     0,     0,     0,     0,     0,
      21,     0,    22,    29,    30,    31,    32,    33,    34,    35,
      36,     0,     0,     0,     0,     0,     0,     0,     0,    22,
      29,    30,    31,    32,    33,    34,    35,    36,     0,     0,
       0,     0,     0,     0,    37,    38,    39,    40,     0,     0,
       0,     0,     0,    45,     0,     0,     0,     0,     0,     0,
       0,    37,    38,    39,    40,     0,     0,     0,     0,     0,
      61,    29,    30,    31,    32,    33,    34,    35,    36,     0,
       0,    29,    30,    31,    32,    33,    34,    35,    36,     0,
       0,    29,    30,    31,    32,    33,    34,    35,    36,     0,
       0,     0,    37,    38,    39,    40,     0,     0,     0,     0,
       0,    62,    37,    38,    39,    40,     0,     0,     0,     0,
       0,   123,    37,    38,    39,    40,     0,     0,     0,     0,
       0,   128,    29,    30,    31,    32,    33,    34,    35,    36,
       0,     0,    29,    30,    31,    32,    33,    34,    35,    36,
       0,     0,    29,    30,    31,    32,    33,    34,    35,    36,
       0,     0,     0,    37,    38,    39,    40,     0,     0,     0,
       0,     0,   129,    37,    38,    39,    40,     0,     0,     0,
       0,     0,   133,    37,    38,    39,    40,     0,     0,     0,
       0,     0,   147,    29,    30,    31,    32,    33,    34,    35,
      36,    29,    30,    31,    32,    33,    34,    35,    36,    29,
      30,    31,    32,    33,    34,    35,    36,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,     0,
      41,     0,    37,    38,    39,    40,     0,     0,   132,     0,
      37,    38,    39,    40,     0,     0,     0,    37,    38,    39,
      40,    31,    32,    33,    34,    35,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,    38,    39,    40
};

static const yytype_int16 yycheck[] =
{
      11,    68,    87,    14,    86,    75,    76,     7,     8,     9,
      10,    22,    42,    43,    25,    20,    27,    18,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      36,    37,    38,    39,    38,    39,    36,    37,    38,    39,
      34,    35,     0,   128,    42,    43,    19,    17,   133,    44,
     120,    44,     3,     4,    44,    46,    45,    43,    18,   144,
     142,    44,    13,    14,    15,    16,   151,    18,    19,    20,
      44,    82,    23,    84,    25,    44,    42,    88,    42,    42,
      47,    92,   149,    44,    13,    42,    48,    18,    44,    42,
       3,     4,    47,    44,    44,   106,    26,   108,    45,    43,
      13,    14,    15,    16,    44,    18,    19,    46,    42,    41,
      45,    24,    25,     4,    42,   126,    42,     3,     4,    96,
     100,    -1,    -1,   134,    -1,    -1,   137,    13,    14,    15,
      16,    44,    18,    19,    20,    -1,    -1,    23,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    -1,    -1,
      -1,     3,     4,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      46,    13,    14,    15,    16,    -1,    18,    19,     3,     4,
      -1,    23,    -1,    25,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    -1,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    44,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
       5,     6,     7,     8,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      45,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      -1,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      -1,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      -1,    -1,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    45,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    45,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    45,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,    -1,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    45,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    45,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    45,     5,     6,     7,     8,     9,    10,    11,
      12,     5,     6,     7,     8,     9,    10,    11,    12,     5,
       6,     7,     8,     9,    10,    11,    12,     6,     7,     8,
       9,    10,    11,    12,    36,    37,    38,    39,    -1,    -1,
      42,    -1,    36,    37,    38,    39,    -1,    -1,    42,    -1,
      36,    37,    38,    39,    -1,    -1,    -1,    36,    37,    38,
      39,     7,     8,     9,    10,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    20,    50,    51,    52,    18,     0,    19,    53,    51,
      42,    43,    17,     3,     4,    13,    14,    15,    16,    18,
      19,    25,    44,    71,    44,    44,    71,    44,    71,     5,
       6,     7,     8,     9,    10,    11,    12,    36,    37,    38,
      39,    42,    45,    71,    71,    45,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    46,    54,
      57,    45,    45,    18,    20,    23,    26,    27,    28,    29,
      30,    31,    32,    33,    55,    56,    57,    63,    64,    65,
      70,    71,    43,    18,    44,    69,    44,    69,    44,    42,
      42,    42,    44,    47,    58,    55,    55,    34,    35,    66,
      67,    68,    42,    24,    71,    42,    43,    71,    44,    20,
      59,    60,    70,    56,    71,    71,    58,    13,    47,    66,
      48,    44,    71,    45,    71,    18,    42,    26,    45,    45,
      55,    45,    42,    45,    43,    61,    71,    44,    56,    46,
      56,    71,    42,    71,    41,    62,    70,    45,    56,    45,
      42,    69,    56
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    53,    54,    55,
      55,    56,    56,    56,    56,    56,    56,    56,    56,    57,
      58,    59,    59,    60,    60,    61,    61,    62,    62,    63,
      63,    63,    63,    63,    63,    64,    65,    66,    66,    67,
      68,    68,    69,    70,    70,    70,    70,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     3,     5,     5,     3,     2,
       0,     2,     3,     5,     3,     1,     2,     2,     2,     1,
       1,     4,     1,     1,     0,     1,     0,     1,     0,     6,
       8,    10,     5,     7,     1,     3,     5,     2,     0,     3,
       2,     1,     0,     3,     1,     4,     5,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     3,
       4,     4,     3,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* S: LISTA_DECLARACOES_GLOBAIS FUNCAO_MAIN  */
#line 114 "sintatico.y"
                    {

			    string codigo = "/*Compilador boto*/\n"
			                    "#include <iostream>\n"
			                    "#include<string.h>\n"
			                    "#include<stdio.h>\n\n";

			    set<string> tempsGlobaisDeclarados;

			    if (!symbolTable.escopos.empty()) {
			        const auto& escopoGlobal = symbolTable.escopos[0];
			        for (const auto& par : escopoGlobal) {
			            const Symbol& simbolo = par.second;
			            // Só declara variáveis com nome (não temporários) e com tipo definido
			            if (simbolo.tipo != "undefined" && !simbolo.nome.empty() && simbolo.nome[0] != 't' && simbolo.nome[0] != 'b') {
			                codigo += simbolo.tipo + " " + simbolo.temp + ";\n";
			                tempsGlobaisDeclarados.insert(simbolo.temp);
			            }
			        }
			    }
			    codigo += "\n";


			    codigo += "int main(void) {\n";

			    for (const Symbol& simbolo : tempsVector) {
			        if (!simbolo.temp.empty() && tempsGlobaisDeclarados.find(simbolo.temp) == tempsGlobaisDeclarados.end() && tempsAdicionados.insert(simbolo.temp).second) {
			            // Se o tipo for undefined, talvez queira usar um tipo padrão como int
			            string tipo_a_declarar = (simbolo.tipo == "undefined") ? "int" : simbolo.tipo;
			            codigo += "\t" + tipo_a_declarar + " " + simbolo.temp + ";\n";
			        }
			    }
			    codigo += "\n";

			    codigo += yyvsp[-1].traducao;

			    codigo += yyvsp[0].traducao;
			                    

			    codigo += "\treturn 0;\n"
			              "}\n";

			    cout << codigo << endl;
		    }
#line 1533 "y.tab.c"
    break;

  case 5: /* DECLARACAO_GLOBAL: TK_VAR TK_ID ';'  */
#line 169 "sintatico.y"
                    {
		        
		        Symbol val;
		        val.nome = yyvsp[-1].label;
		        val.tipo = "undefined";
		        val.temp = ""; 
		        declaraVariavel(val);
		    }
#line 1546 "y.tab.c"
    break;

  case 6: /* DECLARACAO_GLOBAL: TK_VAR TK_ID '=' E ';'  */
#line 178 "sintatico.y"
                    {

		        Symbol val;
		        val.nome = yyvsp[-3].label;
		        val.tipo = yyvsp[-1].type;

		        val.temp = gentempcode(val.tipo);
		        declaraVariavel(val);
		        // insertTempsST(val.temp, val.tipo);

		    }
#line 1562 "y.tab.c"
    break;

  case 7: /* FUNCAO_MAIN: TK_TIPO_INT TK_MAIN '(' ')' BLOCO  */
#line 192 "sintatico.y"
                        {
				
				yyval.traducao = yyvsp[0].traducao;

			}
#line 1572 "y.tab.c"
    break;

  case 8: /* BLOCO: PUSH_ESCOPO COMANDOS POP_ESCOPO  */
#line 200 "sintatico.y"
                        {
				yyval.traducao = yyvsp[-1].traducao;
			}
#line 1580 "y.tab.c"
    break;

  case 9: /* COMANDOS: COMANDO COMANDOS  */
#line 206 "sintatico.y"
                        {
				yyval.traducao = yyvsp[-1].traducao + yyvsp[0].traducao;
			}
#line 1588 "y.tab.c"
    break;

  case 10: /* COMANDOS: %empty  */
#line 210 "sintatico.y"
                        {
				yyval.traducao = "";
			}
#line 1596 "y.tab.c"
    break;

  case 11: /* COMANDO: EXPRESSAO ';'  */
#line 217 "sintatico.y"
                    {
		        yyval = yyvsp[-1];
		    }
#line 1604 "y.tab.c"
    break;

  case 12: /* COMANDO: TK_VAR TK_ID ';'  */
#line 245 "sintatico.y"
                    {
		        Symbol val;
		        val.nome = yyvsp[-1].label;
		        val.tipo = "undefined";
		        val.temp = "";
		        declaraVariavel(val);
		        yyval.traducao = "";
		        yyval.label = "";
		    }
#line 1618 "y.tab.c"
    break;

  case 13: /* COMANDO: TK_VAR TK_ID '=' E ';'  */
#line 255 "sintatico.y"
                    {
		        Symbol val;
		        val.nome = yyvsp[-3].label;
		        val.tipo = yyvsp[-1].type;
		        val.temp = gentempcode(yyvsp[-3].label);
		        cout << "\nNome "+val.nome << endl;
				cout << "\nTemp "+val.temp << endl;
		        declaraVariavel(val);
				yyval.traducao = yyvsp[-1].traducao;
		        yyval.label = "";

				if (yyvsp[-1].type == "String") {
					// Gera a tradução com strCopy
					yyval.traducao = yyvsp[-1].traducao + "\t" + yyvsp[-1].label + " = strCopy(" + yyvsp[-1].label + ");\n";
				} else {
					// Para os outros tipos, atribuição direta
					yyval.traducao = yyvsp[-1].traducao;
				}

		    }
#line 1643 "y.tab.c"
    break;

  case 14: /* COMANDO: PUSH_ESCOPO COMANDOS POP_ESCOPO  */
#line 276 "sintatico.y"
                    {
		    	yyval.traducao = yyvsp[-1].traducao;
		    }
#line 1651 "y.tab.c"
    break;

  case 15: /* COMANDO: ESTRUTURA_DE_CONTROLE  */
#line 280 "sintatico.y"
                    {
		    	yyval = yyvsp[0];
		    }
#line 1659 "y.tab.c"
    break;

  case 16: /* COMANDO: TK_BREAK ';'  */
#line 284 "sintatico.y"
                    {
		        if (breakLabels.empty()) {
		            yyerror("Comando 'break' fora de um laço (while/for)");
		            yyval.traducao = "";
		        } else {
		            // Perfeito, continua funcionando!
		            yyval.traducao = "goto " + breakLabels.top() + ";\n";
		        }
		    }
#line 1673 "y.tab.c"
    break;

  case 17: /* COMANDO: TK_BREAKOUT ';'  */
#line 294 "sintatico.y"
                    {
		        // A verificação é na pilha de laços principal
		        if (pilhaLacos.empty()) {
		            yyerror("Comando 'breakout' fora de um laço");
		            yyval.traducao = "";
		        } else {
		            // Pega o primeiro elemento (o mais externo) com .front()
		            yyval.traducao = "goto " + pilhaLacos.front().fim + ";\n";
		        }
		    }
#line 1688 "y.tab.c"
    break;

  case 18: /* COMANDO: TK_CONTINUE ';'  */
#line 305 "sintatico.y"
                    {
		        if (continueLabels.empty()) {
		            yyerror("Comando 'continue' fora de um laço (while/for)");
		            yyval.traducao = "";
		        } else {
		            // Perfeito, continua funcionando!
		            yyval.traducao = "goto " + continueLabels.top() + ";\n";
		        }
		    }
#line 1702 "y.tab.c"
    break;

  case 19: /* PUSH_ESCOPO: '{'  */
#line 318 "sintatico.y"
                        {
				entraEscopo();
			}
#line 1710 "y.tab.c"
    break;

  case 20: /* POP_ESCOPO: '}'  */
#line 324 "sintatico.y"
                        {
				saiEscopo();
			}
#line 1718 "y.tab.c"
    break;

  case 21: /* FOR_DECL_OU_EXPR: TK_VAR TK_ID '=' E  */
#line 331 "sintatico.y"
                    {
		        // Ação semântica para declarar a variável
		        Symbol val;
		        val.nome = yyvsp[-2].label;
		        val.tipo = yyvsp[0].type;
		        val.temp = yyvsp[0].label;
		        declaraVariavel(val);
		        yyval.traducao = yyvsp[0].traducao; // Passa a tradução da inicialização
		        yyval.label = "";
		    }
#line 1733 "y.tab.c"
    break;

  case 22: /* FOR_DECL_OU_EXPR: EXPRESSAO  */
#line 342 "sintatico.y"
                    {
		        yyval = yyvsp[0];
		    }
#line 1741 "y.tab.c"
    break;

  case 23: /* FOR_INIT: FOR_DECL_OU_EXPR  */
#line 349 "sintatico.y"
                    {
		        yyval.traducao = yyvsp[0].traducao; 
		    }
#line 1749 "y.tab.c"
    break;

  case 24: /* FOR_INIT: %empty  */
#line 353 "sintatico.y"
                    {
		        yyval.traducao = ""; 
		    }
#line 1757 "y.tab.c"
    break;

  case 25: /* FOR_COND: E  */
#line 360 "sintatico.y"
                    { 
		    	yyval.traducao = yyvsp[0].traducao; 
		    	yyval.label = yyvsp[0].label; 
			}
#line 1766 "y.tab.c"
    break;

  case 26: /* FOR_COND: %empty  */
#line 365 "sintatico.y"
                    {
		        // Se a condição for vazia, o laço é infinito (condição sempre verdadeira).
		        // Geramos um booleano temporário com valor 'true'.
		        string temp_true = gentempcode("boolean");
		        insertTempsST(temp_true, "int");
		        yyval.traducao = temp_true + " = 1;\n"; // 1 para 'true'
		        yyval.label = temp_true;
		    }
#line 1779 "y.tab.c"
    break;

  case 27: /* FOR_INCR: EXPRESSAO  */
#line 377 "sintatico.y"
                    {
		     	yyval.traducao = yyvsp[0].traducao; 
		 	}
#line 1787 "y.tab.c"
    break;

  case 28: /* FOR_INCR: %empty  */
#line 381 "sintatico.y"
                    {
		     	yyval.traducao = ""; 
		    }
#line 1795 "y.tab.c"
    break;

  case 29: /* ESTRUTURA_DE_CONTROLE: TK_WHILE INICIO_LOOP '(' E ')' COMANDO  */
#line 387 "sintatico.y"
                        {
				InfoLaco lacoAtual = pilhaLacos.back();

				if (yyvsp[-2].label[0] != 'b'){
					yyerror("Essa expressao nao e um boolean");
				}

				string temp = gentempcode("int");
				insertTempsST(temp, "int");
				
				// Extraindo os labels de início e fim

				string traducao;

				traducao += lacoAtual.inicio + ": \n";
				traducao += yyvsp[-2].traducao;
				traducao += temp + " = !(" + yyvsp[-2].label + "); \n";
				traducao += "if (" + temp + ") goto " + lacoAtual.fim + ";\n";
				traducao += yyvsp[0].traducao;
				traducao += "goto " + lacoAtual.inicio + ";\n";
				traducao += lacoAtual.fim + ": \n";


				yyval.traducao = traducao;

		        if (!pilhaLacos.empty()) {
		            pilhaLacos.pop_back();
		       		cout << "pop pilha" << endl;

		        }
		        if (!breakLabels.empty()) {
		            breakLabels.pop();
		       		cout << "pop pilha" << endl;	
		       	}			
			}
#line 1835 "y.tab.c"
    break;

  case 30: /* ESTRUTURA_DE_CONTROLE: TK_DO INICIO_LOOP COMANDO TK_WHILE '(' E ')' ';'  */
#line 423 "sintatico.y"
                        {
		        // Pega os rótulos da pilha, preparados pelo PREPARA_LACO
		        InfoLaco lacoAtual = pilhaLacos.back();

		        if (yyvsp[-2].label[0] != 'b'){ // $6 é o não-terminal E
		            yyerror("Essa expressao nao e um boolean");
		        }

		        string traducao;

		        // 1. Rótulo de início do laço
		        traducao += lacoAtual.inicio + ":\n";

		        // 2. Código do corpo (COMANDO), que é $3
		        traducao += yyvsp[-5].traducao;

		        // 3. Código da expressão condicional (E), que é $6
		        traducao += yyvsp[-2].traducao;

		        // 4. Salto condicional de volta para o início se a condição for VERDADEIRA
		        traducao += "if (" + yyvsp[-2].label + ") goto " + lacoAtual.inicio + ";\n";

		        // 5. Rótulo de fim, para onde o 'break' e 'breakout' pularão
		        traducao += lacoAtual.fim + ":\n";

		        yyval.traducao = traducao;

		        // 6. Limpeza das pilhas, exatamente como na regra do 'while'
		        if (!pilhaLacos.empty()) {
		            pilhaLacos.pop_back();
		        }
		        if (!breakLabels.empty()) {
		            breakLabels.pop();
		        }
			}
#line 1875 "y.tab.c"
    break;

  case 31: /* ESTRUTURA_DE_CONTROLE: TK_FOR '(' FOR_INIT ';' FOR_COND ';' FOR_INCR ')' INICIO_LOOP COMANDO  */
#line 459 "sintatico.y"
                    {
		        // Pega os rótulos preparados pelo PREPARA_LACO ($9)
		        InfoLaco lacoAtual = pilhaLacos.back();

		        // Pega o código de cada parte
		        string init_code = yyvsp[-7].traducao;
		        string cond_code = yyvsp[-5].traducao;
		        string cond_label = yyvsp[-5].label;
		        string incr_code = yyvsp[-3].traducao;
		        string body_code = yyvsp[0].traducao;

		        string traducao;

		        // 1. Código da inicialização (executado uma vez, fora do laço)
		        traducao += init_code;

		        // 2. Rótulo de início do laço
		        traducao += lacoAtual.inicio + ":\n";

		        // 3. Código da condição
		        traducao += cond_code;

		        // 4. Verificação da condição (salta para o fim se for falsa)
		        string temp = gentempcode("boolean");
		        insertTempsST(temp, "int");
		        traducao += temp + " = !(" + cond_label + ");\n";
		        traducao += "if (" + temp + ") goto " + lacoAtual.fim + ";\n";

		        // 5. Código do corpo
		        traducao += body_code;

		        // 6. Código do incremento
		        traducao += incr_code;

		        // 7. Salto incondicional de volta para o início
		        traducao += "goto " + lacoAtual.inicio + ";\n";

		        // 8. Rótulo de fim (para onde o break e o if_false pulam)
		        traducao += lacoAtual.fim + ":\n";

		        yyval.traducao = traducao;

		        // 9. Limpeza das pilhas
		        if (!pilhaLacos.empty()) {
		            pilhaLacos.pop_back();
		        }
		        if (!breakLabels.empty()) {
		            breakLabels.pop();
		        }
		    }
#line 1930 "y.tab.c"
    break;

  case 32: /* ESTRUTURA_DE_CONTROLE: TK_IF '(' E ')' COMANDO  */
#line 511 "sintatico.y"
                        {
				if (yyvsp[-2].label[0] != 'b'){
					yyerror("Essa expressao nao e um boolean");
				}
					string temp = gentempcode("int");        
					insertTempsST(temp, "int");              
					string ifLabel = genlabel();

					string traducao = yyvsp[-2].traducao;

					traducao += temp + " = !(" + yyvsp[-2].label + "); \n";
					traducao += "if (" + temp + ") goto " + ifLabel + ";\n";
					traducao += yyvsp[0].traducao;
					traducao += ifLabel + ": \n";

					yyval.traducao = traducao;
			}
#line 1952 "y.tab.c"
    break;

  case 33: /* ESTRUTURA_DE_CONTROLE: TK_IF '(' E ')' COMANDO TK_ELSE COMANDO  */
#line 529 "sintatico.y"
                    {
		        if (yyvsp[-4].label[0] != 'b'){
		            yyerror("Essa expressao nao e um boolean");
		        }
		        
		        // 1. Gerar DOIS rótulos
		        string elseLabel = genlabel();
		        string fimIfLabel = genlabel();

		        string temp = gentempcode("boolean");
		        insertTempsST(temp, "int");

		        string traducao;

		        // 2. Tradução da condição
		        traducao += yyvsp[-4].traducao;

		        // 3. Salto para o ELSE se a condição for FALSA
		        traducao += temp + " = !(" + yyvsp[-4].label + ");\n";
		        traducao += "if (" + temp + ") goto " + elseLabel + ";\n";

		        // 4. Código do bloco THEN ($5)
		        traducao += yyvsp[-2].traducao;

		        // 5. Salto INCONDICIONAL para o fim para pular o ELSE
		        traducao += "\tgoto " + fimIfLabel + ";\n";

		        // 6. Rótulo e código do bloco ELSE ($7)
		        traducao += elseLabel + ":\n";
		        traducao += yyvsp[0].traducao;

		        // 7. Rótulo final
		        traducao += fimIfLabel + ":\n";

		        yyval.traducao = traducao;
		    }
#line 1993 "y.tab.c"
    break;

  case 34: /* ESTRUTURA_DE_CONTROLE: SWITCH  */
#line 566 "sintatico.y"
                    {
		    	yyval = yyvsp[0];	
		    }
#line 2001 "y.tab.c"
    break;

  case 35: /* SWITCH: SWITCH_HEADER LISTA_CASES '}'  */
#line 573 "sintatico.y"
                    {
		        // AÇÃO DE MONTAGEM FINAL
		        SwitchContext ctx = switchStack.top(); // Pega o contexto que foi criado em SWITCH_HEADER
		        string switch_code;

		        // --- Monta a Tabela de Saltos ---
		        for (const auto& case_info : ctx.cases) {
		            switch_code += "if (" + ctx.temp_var + " == " + case_info.first + ") goto " + case_info.second + ";\n";
		        }
		        
		        // --- Salto para default ou para o fim ---
		        if (ctx.has_default) {
		            switch_code += "goto " + ctx.default_label + ";\n\n";
		        } else {
		            switch_code += "goto " + ctx.end_label + ";\n\n";
		        }

		        // --- Anexa o código dos blocos de case (vindo de LISTA_CASES) ---
		        switch_code += yyvsp[-1].traducao; // Agora é $2 porque LISTA_CASES é o segundo símbolo

		        // --- Rótulo final ---
		        switch_code += ctx.end_label + ":\n";

		        // $1 (SWITCH_HEADER) não tem tradução, mas precisamos da tradução da expressão E
		        // Para isso, o SWITCH_HEADER precisa passar a tradução de E para cima.
		        // Vamos ajustar SWITCH_HEADER para isso.
		        yyval.traducao = yyvsp[-2].traducao + switch_code;

		        // --- Limpeza das pilhas ---
		        switchStack.pop();
		        breakLabels.pop();
		    }
#line 2038 "y.tab.c"
    break;

  case 36: /* SWITCH_HEADER: TK_SWITCH '(' E ')' '{'  */
#line 609 "sintatico.y"
                    {
		        // AÇÃO DE PREPARO
		        SwitchContext ctx;
		        ctx.temp_var = yyvsp[-2].label;
		        ctx.end_label = genlabel();
		        switchStack.push(ctx);

		        breakLabels.push(switchStack.top().end_label);

		        yyval.traducao = yyvsp[-2].traducao;
		    }
#line 2054 "y.tab.c"
    break;

  case 37: /* LISTA_CASES: CASE_BLOCO LISTA_CASES  */
#line 624 "sintatico.y"
                    {
		    	yyval.traducao = yyvsp[-1].traducao + yyvsp[0].traducao;
		    }
#line 2062 "y.tab.c"
    break;

  case 38: /* LISTA_CASES: %empty  */
#line 628 "sintatico.y"
                    {
		         yyval.traducao = ""; 
		    }
#line 2070 "y.tab.c"
    break;

  case 39: /* CASE_BLOCO: LABEL_CASE ':' COMANDOS  */
#line 635 "sintatico.y"
                    {
		         yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao; 
		    }
#line 2078 "y.tab.c"
    break;

  case 40: /* LABEL_CASE: TK_CASE TK_INT  */
#line 642 "sintatico.y"
                    {
	            if (switchStack.empty()) { yyerror("case fora de um switch."); } 
	            else {
	                string case_val = yyvsp[0].label;
	                string case_label = genlabel();
	                switchStack.top().cases.push_back({case_val, case_label});
	                yyval.traducao = case_label + ":\n";
	            }
		    }
#line 2092 "y.tab.c"
    break;

  case 41: /* LABEL_CASE: TK_DEFAULT  */
#line 652 "sintatico.y"
                {
	            if (switchStack.empty()) { yyerror("default fora de um switch."); }
	            else if (switchStack.top().has_default) { yyerror("múltiplos defaults em um switch."); }
	            else {
	                string default_label = genlabel();
	                switchStack.top().default_label = default_label;
	                switchStack.top().has_default = true;
	                yyval.traducao = default_label + ":\n";
	            }
	        }
#line 2107 "y.tab.c"
    break;

  case 42: /* INICIO_LOOP: %empty  */
#line 666 "sintatico.y"
                    {
		        // 1. Cria os rótulos
		        InfoLaco novoLaco;
		        novoLaco.inicio = genlabel();
		        novoLaco.fim = genlabel();

		        // 2. Empilha o rótulo de FIM na pilha de breaks
		        breakLabels.push(novoLaco.fim);

		        continueLabels.push(novoLaco.inicio);

		        // 3. Empilha a estrutura completa na pilha de laços
		        pilhaLacos.push_back(novoLaco);    	
		       	cout << "entrou no while" << endl;
		    }
#line 2127 "y.tab.c"
    break;

  case 43: /* EXPRESSAO: TK_ID '=' E  */
#line 687 "sintatico.y"
                    {	
        		auto it = symbolTable.escopos.begin()->end(); 
		    	bool achou = false;
		        for (int i = symbolTable.escopos.size() - 1; i >= 0; --i) {
		            auto& escopoAtual = symbolTable.escopos[i]; 
		            it = escopoAtual.find(yyvsp[-2].label);

		            if (it != escopoAtual.end()) {
		            	achou = true;
		            	break;
		            }
		        }

		        if (!achou)
		        {
		        	yyerror("Variável do lado esquerdo não declarada.");
		        }

		        if (it->second.tipo == "undefined") {
					it->second.tipo = yyvsp[0].type;
					it->second.temp = yyvsp[0].label;
					cout << "LHS: " << it->second.tipo << ", RHS: " << yyvsp[0].type << endl;
				}

				// Agora: processa a atribuição se o tipo do LHS for string
				if (it->second.tipo == "String") {
					cout << "\nAtribuição de string com strCopy\n";
					yyval.type = "string";

					if (yyvsp[0].type != "string") {
						yyerror("Atribuição inválida: string esperado");
					}

					yyval.traducao = yyvsp[0].traducao
    					+ "\t" + yyvsp[-2].label + " = strCopy(" + yyvsp[0].label + ");\n";
						
					yyval.label = yyvsp[-2].label;
				}

				else {

		        if(it->second.tipo == yyvsp[0].type && it->second.temp[0] == yyvsp[0].label[0]){
					
		        	cout << "\nMesmo tipo" << endl;

		        	// it->second.temp = $3.label;
			        yyval.type = yyvsp[0].type;
			        yyval.traducao = yyvsp[0].traducao + "\t" + it->second.temp + " = " + yyvsp[0].label + ";\n";
			        yyval.label = yyvsp[-2].label;	

		        }
		        else if(it->second.tipo == "int" && it->second.temp[0] != 'b'){
		        	cout << "\nInt normal temp = " + it->second.temp  << endl;
					// it->second.temp = $3.label;

        			string auxTipo = "("+ it->second.tipo +") " + yyvsp[0].label;
        			string temp = gentempcode(it->second.tipo);
					string traducaoAux = "\t" + temp + " = " + auxTipo + ";\n";

					yyval.type = yyvsp[-2].type;
					yyval.traducao = yyvsp[0].traducao + traducaoAux + "\t" + it->second.temp + " = " + yyvsp[0].label + ";\n";
		        }
		        else if(it->second.tipo == "float" && yyvsp[0].type != "int"||yyvsp[0].type != "float"){
		        	cout << "\nFloat" << endl;
					// it->second.temp = $3.label;

		        	string auxTipo = "("+ it->second.tipo +") " + yyvsp[0].label;
        			string temp = gentempcode(it->second.tipo);
					string traducaoAux = "\t" + temp + " = " + auxTipo + ";\n";

					yyval.type = yyvsp[-2].type;
					yyval.traducao = yyvsp[0].traducao + traducaoAux + "\t" + it->second.temp + " = " + yyvsp[0].label + ";\n";
		        }
		        else if((it->second.temp[0] == 'b' || it->second.tipo == "char") && yyvsp[0].type == "int"){
		        	cout << "Boolean ou  char" << endl;
					// it->second.temp = $3.label;
		  
		        	string auxTipo = "("+ it->second.tipo +") " + yyvsp[0].label;
        			string temp = gentempcode(it->second.tipo);
					string traducaoAux = "\t" + temp + " = " + auxTipo + ";\n";

					yyval.type = yyvsp[-2].type;
					yyval.traducao = yyvsp[0].traducao + traducaoAux + "\t" + it->second.temp + " = " + yyvsp[0].label + ";\n";
		       
		        }else{
		        	yyerror("Variável recebendo valores de tipos não conversiveis");
		        }
			}


		    }
#line 2223 "y.tab.c"
    break;

  case 44: /* EXPRESSAO: E  */
#line 779 "sintatico.y"
                    {
		        yyval = yyvsp[0];
		    }
#line 2231 "y.tab.c"
    break;

  case 45: /* EXPRESSAO: TK_PRINT '(' E ')'  */
#line 782 "sintatico.y"
                                             {

				string formato = "";

				if (yyvsp[-1].type == "int" ) {
					formato = "%d";
				} else if (yyvsp[-1].type == "float") {
					formato = "%f";
				} else if (yyvsp[-1].type == "string") {
					formato = "%s";
				} else if (yyvsp[-1].type == "char") {
					formato = "%c";
				} else {
					yyerror("Tipo inválido no print.");
				}

				yyval.traducao = yyvsp[-1].traducao + "\tprintf(\"" + formato + "\", " + yyvsp[-1].label + ");\n";
			}
#line 2254 "y.tab.c"
    break;

  case 46: /* EXPRESSAO: TK_ID '=' TK_INPUT '(' ')'  */
#line 801 "sintatico.y"
                        {

			    bool achou = false;
			    auto it = symbolTable.escopos.begin()->end(); 
			    
			    for (int i = symbolTable.escopos.size() - 1; i >= 0; --i) {
			        auto& escopoAtual = symbolTable.escopos[i];
			        it = escopoAtual.find(yyvsp[-4].label); // Procura pelo nome da variável
			        
			        if (it != escopoAtual.end()) {
			            achou = true;
			            break; 
			        }
			    }

			    if (!achou) {
			        yyerror("Variavel '" + yyvsp[-2].label + "' nao declarada para input.");
			    }
			    

			    if (it->second.tipo == "undefined") {
			        it->second.tipo = "int"; 
			    }

			    string tipo = it->second.tipo;

				if (tipo == "int") {
					yyval.traducao = "\tscanf(\"%d\", &" + yyvsp[-4].label + ");\n";
				} else if (tipo == "float") {
					yyval.traducao = "\tscanf(\"%f\", &" + yyvsp[-4].label + ");\n";
				} else if (tipo == "char") {
					yyval.traducao = "\tscanf(\" %c\", &" + yyvsp[-4].label + ");\n";
				} else {
					yyerror("Tipo inválido para input.");
				}

				yyval.label = yyvsp[-4].label;
			}
#line 2297 "y.tab.c"
    break;

  case 47: /* E: E '+' E  */
#line 843 "sintatico.y"
                    {
		        typeValue(yyval.type, yyvsp[-2].type, yyvsp[0].type, yyvsp[-2].label, yyvsp[0].label);
		        yyval.label = gentempcode(yyval.type);
		        insertTempsST(yyval.label, yyval.type);
		        implicitConversion(yyvsp[-2], yyvsp[0], yyval, " + ");
		    }
#line 2308 "y.tab.c"
    break;

  case 48: /* E: E '-' E  */
#line 850 "sintatico.y"
                    {
		        typeValue(yyval.type, yyvsp[-2].type, yyvsp[0].type, yyvsp[-2].label, yyvsp[0].label);
		        yyval.label = gentempcode(yyval.type);
		        insertTempsST(yyval.label, yyval.type);
		        implicitConversion(yyvsp[-2], yyvsp[0], yyval, " - ");
		    }
#line 2319 "y.tab.c"
    break;

  case 49: /* E: E '*' E  */
#line 857 "sintatico.y"
                    {
		        typeValue(yyval.type, yyvsp[-2].type, yyvsp[0].type, yyvsp[-2].label, yyvsp[0].label);
		        yyval.label = gentempcode(yyval.type);
		        insertTempsST(yyval.label, yyval.type);
		        implicitConversion(yyvsp[-2], yyvsp[0], yyval, " * ");
		    }
#line 2330 "y.tab.c"
    break;

  case 50: /* E: E '/' E  */
#line 864 "sintatico.y"
                    {
		        typeValue(yyval.type, yyvsp[-2].type, yyvsp[0].type, yyvsp[-2].label, yyvsp[0].label);
		        yyval.label = gentempcode(yyval.type);
		        insertTempsST(yyval.label, yyval.type);
		        implicitConversion(yyvsp[-2], yyvsp[0], yyval, " / ");
		    }
#line 2341 "y.tab.c"
    break;

  case 51: /* E: E TK_MAIOR E  */
#line 871 "sintatico.y"
                    {
				implicitConversion(yyvsp[-2], yyvsp[0], yyval, " > ");
				insertTempsST(yyval.label, yyval.type);
				if((yyvsp[-2].type != "int" && yyvsp[-2].type != "float") || (yyvsp[0].type != "int" && yyvsp[0].type != "float"))
				{
					yyerror("Operação '>' requer operandos do tipo inteiro ou float.");
				}
				yyval.type = "int";
		        yyval.label = gentempcode("boolean");		        
				insertTempsST(yyval.label, yyval.type);
				yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + "\t" + yyval.label + " = " + yyvsp[-2].label + " > " + yyvsp[0].label + ";\n";
		    }
#line 2358 "y.tab.c"
    break;

  case 52: /* E: E TK_MENOR E  */
#line 885 "sintatico.y"
                    {	
		    	cout << "\n Esq = "+ yyvsp[-2].label + "Dir = " + yyvsp[0].label << endl;


				implicitConversion(yyvsp[-2], yyvsp[0], yyval, " < ");
				insertTempsST(yyval.label, yyval.type);
				if((yyvsp[-2].type != "int" && yyvsp[-2].type != "float") || (yyvsp[0].type != "int" && yyvsp[0].type != "float"))
				{
					yyerror("Operação '<' requer operandos do tipo inteiro ou float.");
				}
				yyval.type = "int";
		        yyval.label = gentempcode("boolean");
		        insertTempsST(yyval.label, yyval.type);
				yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + "\t" + yyval.label + " = " + yyvsp[-2].label + " < " + yyvsp[0].label + ";\n";
		    }
#line 2378 "y.tab.c"
    break;

  case 53: /* E: E TK_DIFERENTE E  */
#line 901 "sintatico.y"
                    {
				implicitConversion(yyvsp[-2], yyvsp[0], yyval, " != ");
				insertTempsST(yyval.label, yyval.type);
				if((yyvsp[-2].type != "int" && yyvsp[-2].type != "float") || (yyvsp[0].type != "int" && yyvsp[0].type != "float"))
				{
					yyerror("Operação '!' requer operandos do tipo inteiro ou float.");
				}
				yyval.type = "int";
		        yyval.label = gentempcode("boolean");
		        insertTempsST(yyval.label, yyval.type);
				yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + "\t" + yyval.label + " = " + yyvsp[-2].label + " != " + yyvsp[0].label + ";\n";
		    }
#line 2395 "y.tab.c"
    break;

  case 54: /* E: E TK_IGUAL_IGUAL E  */
#line 914 "sintatico.y"
                    {
				implicitConversion(yyvsp[-2], yyvsp[0], yyval, " == ");
				insertTempsST(yyval.label, yyval.type);
				if((yyvsp[-2].type != "int" && yyvsp[-2].type != "float") || (yyvsp[0].type != "int" && yyvsp[0].type != "float"))
				{
					yyerror("Operação '==' requer operandos do tipo inteiro ou float.");
				}

				yyval.type = "int";
		        yyval.label = gentempcode("boolean");
		        insertTempsST(yyval.label, yyval.type);
				yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + "\t" + yyval.label + " = " + yyvsp[-2].label + " == " + yyvsp[0].label + ";\n";
		    }
#line 2413 "y.tab.c"
    break;

  case 55: /* E: E TK_MENOR_IGUAL E  */
#line 928 "sintatico.y"
                    {
				implicitConversion(yyvsp[-2], yyvsp[0], yyval, " <= ");
		        insertTempsST(yyval.label, yyval.type);
				if((yyvsp[-2].type != "int" && yyvsp[-2].type != "float") || (yyvsp[0].type != "int" && yyvsp[0].type != "float"))
				{
					yyerror("Operação '<=' requer operandos do tipo inteiro ou float.");
				}
				yyval.type = "int";
		        yyval.label = gentempcode("boolean");
		        insertTempsST(yyval.label, yyval.type);
				yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + "\t" + yyval.label + " = " + yyvsp[-2].label + " <= " + yyvsp[0].label + ";\n";
		    }
#line 2430 "y.tab.c"
    break;

  case 56: /* E: E TK_MAIOR_IGUAL E  */
#line 941 "sintatico.y"
                    {
				implicitConversion(yyvsp[-2], yyvsp[0], yyval, " >= ");
				
		        insertTempsST(yyval.label, yyval.type);
				if((yyvsp[-2].type != "int" && yyvsp[-2].type != "float") || (yyvsp[0].type != "int" && yyvsp[0].type != "float"))
				{
					yyerror("Operação '>=' requer operandos do tipo inteiro ou float.");
				}
				yyval.type = "int";
		        yyval.label = gentempcode("boolean");
		        insertTempsST(yyval.label, yyval.type);
				yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + "\t" + yyval.label + " = " + yyvsp[-2].label + " >= " + yyvsp[0].label + ";\n";
		    }
#line 2448 "y.tab.c"
    break;

  case 57: /* E: TK_NOT E  */
#line 955 "sintatico.y"
                    {
				yyval.type = "int";
		        yyval.label = gentempcode("boolean");

		        for (int i = symbolTable.escopos.size() - 1; i >= 0; --i) {
		            auto& escopoAtual = symbolTable.escopos[i]; 
		            auto it = escopoAtual.find(yyvsp[0].label);

					if (it != escopoAtual.end()) {
						if (it->second.temp[0] != 'b') {
							yyerror("Operação not requer operandos do tipo bool.");
						}
					}
		        }
				yyval.traducao = yyvsp[0].traducao  + "\t" + yyval.label + " = " + "!" + yyvsp[0].label + ";\n";
		    }
#line 2469 "y.tab.c"
    break;

  case 58: /* E: E TK_AND E  */
#line 972 "sintatico.y"
                    {
				yyval.type = "int";
		        yyval.label = gentempcode("boolean");

		        for (int i = symbolTable.escopos.size() - 1; i >= 0; --i) {
		            auto& escopoAtual = symbolTable.escopos[i]; 
		            auto it = escopoAtual.find(yyvsp[-1].label);

					if (it != escopoAtual.end()) {
						if (it->second.temp[0] != 'b') {
							yyerror("Operação not requer operandos do tipo bool.");
						}
					}
		        }
				yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + "\t" + yyval.label + " = " + yyvsp[-2].label + " && " + yyvsp[0].label + ";\n";
		    }
#line 2490 "y.tab.c"
    break;

  case 59: /* E: E TK_OR E  */
#line 989 "sintatico.y"
                    {
				yyval.type = "int";
		        yyval.label = gentempcode("boolean");

		        for (int i = symbolTable.escopos.size() - 1; i >= 0; --i) {
		            auto& escopoAtual = symbolTable.escopos[i]; 
		            auto it = escopoAtual.find(yyvsp[-1].label);

					if (it != escopoAtual.end()) {
						if (it->second.temp[0] != 'b') {
							yyerror("Operação not requer operandos do tipo bool.");
						}
					}
		        }
				yyval.traducao = yyvsp[-2].traducao + yyvsp[0].traducao + "\t" + yyval.label + " = " + yyvsp[-2].label + " || " + yyvsp[0].label + ";\n";
		    }
#line 2511 "y.tab.c"
    break;

  case 60: /* E: TK_TIPO_INT '(' E ')'  */
#line 1006 "sintatico.y"
                    {
				if(yyvsp[-1].type == "char"){
					yyerror("Não é possível essa conversão.");
				}
				yyval.type = "int";
				yyval.label = gentempcode("int");

				yyval.traducao = yyvsp[-1].traducao  + "\t" + yyval.label + " = " + "(int)" + yyvsp[-1].label + ";\n";
		    }
#line 2525 "y.tab.c"
    break;

  case 61: /* E: TK_TIPO_FLOAT '(' E ')'  */
#line 1016 "sintatico.y"
                    {
				if(yyvsp[-1].type == "char"){
					yyerror("Não é possível essa conversão.");
				}
				yyval.type = "float";
				yyval.label = gentempcode("float");

				yyval.traducao = yyvsp[-1].traducao  + "\t" + yyval.label + " = " + "(float)" + yyvsp[-1].label + ";\n";
		    }
#line 2539 "y.tab.c"
    break;

  case 62: /* E: '(' E ')'  */
#line 1026 "sintatico.y"
                    {
		        yyval = yyvsp[-1];
		    }
#line 2547 "y.tab.c"
    break;

  case 63: /* E: TK_ID  */
#line 1030 "sintatico.y"
                        {
			        // --- PASSO 1: Busca pela variável ---
			        bool achou = false; 
			        auto it = symbolTable.escopos.begin()->end(); // Inicializador seguro

			        for (int i = symbolTable.escopos.size() - 1; i >= 0; --i) {
			            auto& escopoAtual = symbolTable.escopos[i];
			            it = escopoAtual.find(yyvsp[0].label);
			            if (it != escopoAtual.end()) {
			                achou = true;
			                break; 
			            }
			        }

			        if (!achou) {
			            yyerror("Variavel '" + yyvsp[0].label + "' nao declarada.");
			            YYABORT; 
			        }

			        // --- PASSO 2: Verificação de segurança ---
			        if (it->second.temp.empty()) {
			            yyerror("Variavel '" + yyvsp[0].label + "' usada sem ter um valor inicial.");
			            YYABORT;
			        }
			        
			        // --- PASSO 3: Lógica Otimizada ---
			        // O resultado desta expressão É o próprio temporário existente.
			        // Não criamos um novo nem geramos código de cópia.
			        yyval.label = it->second.temp; 
			        yyval.type = it->second.tipo;
			        yyval.traducao = ""; // NENHUM CÓDIGO NOVO É GERADO!
			    }
#line 2584 "y.tab.c"
    break;

  case 64: /* E: TK_INT  */
#line 1063 "sintatico.y"
                    {
		        yyval.type = "int";
		        yyval.label = gentempcode(yyval.type);
		        insertTempsST(yyval.label, yyval.type);
		        yyval.traducao = "\t" + yyval.label + " = " + yyvsp[0].label + ";\n";
		    }
#line 2595 "y.tab.c"
    break;

  case 65: /* E: TK_FLOAT  */
#line 1071 "sintatico.y"
                    {
		        yyval.type = "float";
		        yyval.label = gentempcode(yyval.type);
		        insertTempsST(yyval.label, yyval.type);
		        yyval.traducao = "\t" + yyval.label + " = " + yyvsp[0].label + ";\n";
		    }
#line 2606 "y.tab.c"
    break;

  case 66: /* E: TK_BOOLEAN  */
#line 1078 "sintatico.y"
                    {	
		        yyval.type = "int";
		        yyval.label = gentempcode("boolean");

		        string label;
		        if(yyvsp[0].label == "true"){
		        	label = "1";
		        }else{
		        	label = "0";
		        }
		        insertTempsST(yyval.label, yyval.type);
		        yyval.traducao = "\t" + yyval.label + " = " + label + ";\n";
		    }
#line 2624 "y.tab.c"
    break;

  case 67: /* E: TK_CHAR  */
#line 1092 "sintatico.y"
                    {
		        yyval.type = "char";
		        yyval.label = gentempcode(yyval.type);
		        insertTempsST(yyval.label, yyval.type);
		        yyval.traducao = "\t" + yyval.label + " = " + yyvsp[0].label + ";\n";
		    }
#line 2635 "y.tab.c"
    break;

  case 68: /* E: TK_STRING  */
#line 1099 "sintatico.y"
                        {
				yyval.type = "String";
				yyval.label = gentempcode(yyval.type);
				insertTempsST(yyval.label, yyval.type);

				std::string originalString = yyvsp[0].label; // Ex: "\"hello\""
				std::string traducao = "";

				std::string valorSemAspas;
				int size = 0;

				// Lê caractere por caractere, desconsiderando as aspas e lidando com escapes
				for (int i = 1; i < originalString.length() - 1; i++) {
					char c = originalString[i];

					if (c == '\\' && i + 1 < originalString.length() - 1) {
						char next = originalString[i + 1];
						if (next == 'n') {
							valorSemAspas += '\n';
						} else if (next == 't') {
							valorSemAspas += '\t';
						} else if (next == '\\') {
							valorSemAspas += '\\';
						} else if (next == '"') {
							valorSemAspas += '"';
						} else {
							valorSemAspas += next;
						}
						i++; // pula o caractere escapado
					} else {
						valorSemAspas += c;
					}

					size++;
				}

				// Alocação da string (com +1 pro \0)
				traducao += "\t" + yyval.label + ".str = (char*) malloc(" + std::to_string(size + 1) + ");\n";

				// Cópia dos caracteres
				for (int i = 0; i < valorSemAspas.length(); i++) {
					char c = valorSemAspas[i];

					// Escapa corretamente caracteres especiais no código C
					if (c == '\n') {
						traducao += "\t" + yyval.label + ".str[" + std::to_string(i) + "] = '\\n';\n";
					} else if (c == '\t') {
						traducao += "\t" + yyval.label + ".str[" + std::to_string(i) + "] = '\\t';\n";
					} else if (c == '\\') {
						traducao += "\t" + yyval.label + ".str[" + std::to_string(i) + "] = '\\\\';\n";
					} else if (c == '\'') {
						traducao += "\t" + yyval.label + ".str[" + std::to_string(i) + "] = '\\'';\n";
					} else {
						traducao += "\t" + yyval.label + ".str[" + std::to_string(i) + "] = '" + c + "';\n";
					}
				}

				// Finaliza com \0
				traducao += "\t" + yyval.label + ".str[" + std::to_string(size) + "] = '\\0';\n";

				// Define o tamanho
				traducao += "\t" + yyval.label + ".length = " + std::to_string(size) + ";\n";

				yyval.traducao = traducao;
			}
#line 2705 "y.tab.c"
    break;


#line 2709 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1167 "sintatico.y"


#include "lex.yy.c"

int yyparse();

string gentempcode(string tipo) {
    var_temp_qnt++;
    string temp;

    if(tipo != "boolean")
    {
    	temp = "t" + to_string(var_temp_qnt);
    }else{
    	temp = "b" + to_string(var_temp_qnt);
		//printf("temp = %s\n", temp);
    	tipo = "int";
    }

	 cout << "\n" + temp << endl;

    return temp;
}

String strCopy(String source) {
    String dest;
    dest.length = source.length;

    // Aloca memória para os caracteres + '\0'
    dest.str = (char*) malloc((dest.length + 1) * sizeof(char));

    // Copia os caracteres
    for (int i = 0; i < dest.length; i++) {
        dest.str[i] = source.str[i];
    }

    // Finaliza com '\0'
    dest.str[dest.length] = '\0';

    return dest;
}

void typeValue(string& resultType,  string& leftType,  string& rightType,  string& leftLabel,  string& rightLabel){


	for (int i = symbolTable.escopos.size() - 1; i >= 0; --i) {
	    auto& escopoAtual = symbolTable.escopos[i];
		auto itLeft = escopoAtual.find(leftLabel);
		if (itLeft != escopoAtual.end()) {
		    Symbol simbolo = itLeft->second;
		    if (simbolo.temp[0] == 'b') {
				printf("%c 1", simbolo.temp[1]);
		        yyerror("Não é permitido operações com Booleanos");

		    }
		}

		auto itRight = escopoAtual.find(rightLabel);
		if (itRight != escopoAtual.end()) {
		    Symbol simbolo = itRight->second;
		    if (simbolo.temp[0] == 'b') {
				printf("%c 2", simbolo.temp[0]);
		        yyerror("Não é permitido operações com Booleanos");
		    }
		}
	}

    // if (leftType == "float" || rightType == "float") {
    //     resultType = "float";
    // } else if (leftType == "int" || rightType == "int") {
    //     resultType = "int";
    // } else if (leftType == "char" && rightType == "char") {
    //     resultType = "int"; // soma de dois chars resulta em int
    // }

}
void implicitConversion(atributos& esquerda, atributos& direita, atributos& final , string operacao){
    string resultado;
    string temp;
    string traducaoAux;

    if (esquerda.type == "int" && direita.type == "float") {
        string auxFloat = "(float) " + esquerda.label;
        temp = gentempcode("float");
		traducaoAux = "\t" + temp + " = " + auxFloat + ";\n";
        resultado = final.label + " = " + temp + operacao + direita.label;
        final.traducao =  esquerda.traducao + direita.traducao + traducaoAux + "\t" + resultado + ";\n";
    }
    else if (esquerda.type == "float" && direita.type == "int") {
        string auxFloat = "(float) " + direita.label;
		temp = gentempcode("float");
		traducaoAux = "\t" + temp + " = " + auxFloat + ";\n";
        resultado = final.label + " = " + temp + operacao + esquerda.label;
        final.traducao =  esquerda.traducao + direita.traducao + traducaoAux + "\t" + resultado + ";\n";
    }
    else {
        resultado = final.label + " = " + esquerda.label + operacao + direita.label;
        final.traducao = esquerda.traducao + direita.traducao + "\t" + resultado + ";\n";
    }
}

void entraEscopo(){
	unordered_map<string, Symbol> escopo;
	symbolTable.escopos.push_back(escopo);
	symbolTable.quantidade++;
}

void saiEscopo(){
	symbolTable.escopos.pop_back();
	symbolTable.quantidade--;
}

void declaraVariavel(Symbol& var){


	symbolTable.escopos[symbolTable.quantidade - 1][var.nome] = var;
	tempsVector.push_back(var);

}

void insertTempsST(const string& nome, const string& tipo)
{
	Symbol simbolo;
    simbolo.nome = nome;
    simbolo.tipo = tipo;
    simbolo.temp = nome;

	symbolTable.escopos[symbolTable.quantidade - 1][simbolo.nome] = simbolo;

	tempsVector.push_back(simbolo);
    // symbolTable.insert({nome, simbolo});
}


void checkUndefinedTypes(const TabelaSimbolos& symbolTable) { 

    for (const auto& scope_map : symbolTable.escopos) {
        for (const auto& par : scope_map) {
            const Symbol& simbolo = par.second; 

            if (simbolo.tipo == "undefined" && !simbolo.nome.empty() && simbolo.nome[0] != 't') {
                cerr << "Erro: Variável '" << simbolo.nome << "' usada sem tipo definido.\n";
                exit(1); 
            }
        }
    }
}

int labelCount = 0;

string genlabel() {
    return "L" + to_string(labelCount++);
}

// string searchType(const string& label) {
//     auto it = symbolTable.find(label);
//     if (it != symbolTable.end()) {
//         return it->second.tipo;
//     } else {
//         yyerror("Variável '" + label + "' não declarada.");
//         return "undefined"; 
//     }
// }


void printSymbolTable() {
    cout << "\n========= SYMBOL TABLE =========" << endl;

    if (symbolTable.escopos.empty()) {
        cout << "A tabela de símbolos está vazia." << endl;
        cout << "================================\n" << endl;
        return;
    }

    for (size_t i = 0; i < symbolTable.escopos.size(); ++i) {
        cout << "--- ESCOPO " << i << " ---" << endl;
        const auto& current_scope_map = symbolTable.escopos[i];

        if (current_scope_map.empty()) {
            cout << "  (Escopo vazio)" << endl;
        } else {
            for (const auto& entry : current_scope_map) {
                const Symbol& simbolo = entry.second; 
                cout << "  Nome: " << simbolo.nome
                          << ", Tipo: " << simbolo.tipo
                          << ", Temp: " << simbolo.temp << endl;
            }
        }
    }
    cout << "================================\n" << endl;
}

int main(int argc, char* argv[])
{
	var_temp_qnt = 0;
	entraEscopo();

    // Symbol val;
    // val.nome = "mari";
    // val.tipo = "undefined";
    // val.temp = "EU TE AMO";
    // symbolTable.insert({val.nome, val});

    // declaraVariavel(val);
	// cout << symbolTable.escopos[0][val.nome].temp << endl;
	yyparse();

	saiEscopo();
	printSymbolTable();

	return 0;
}

void yyerror(string MSG)
{
	cout << MSG << endl;
	exit (0);
}		
