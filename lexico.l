%{
#include <string>

%}

ESPACO [ \t]
DIGITO [0-9]
FLOAT [0-9]*\.[0-9]+|[0-9]+\.[0-9]*
LETRA [A-Za-z_]
MAIOR_QUE    ">"
MENOR_QUE    "<"
IGUAL        "="
NEGACAO      "!"


DELIM {ESPACO}+
INT {DIGITO}+
REAL {INT}+("."{INT}+)?
CHAR \'[ -~]\'
BOOLEAN true|false
ID {LETRA}({LETRA}|{INT})*
MAIOR_IGUAL     {MAIOR_QUE}{IGUAL}
MENOR_IGUAL     {MENOR_QUE}{IGUAL}
IGUAL_IGUAL     {IGUAL}{IGUAL}
DIFERENTE       {NEGACAO}{IGUAL}


%%

"\n"		{}

{DELIM} 	{}

{CHAR}      {yylval.label = yytext; return TK_CHAR;}

"main"		{return TK_MAIN;}

"int"		{return TK_TIPO_INT;}

"var"		{return TK_VAR;}

"not"       {return TK_NOT;}

"and"       {return TK_AND;}

"or"        {return TK_OR;}

{MAIOR_IGUAL}   { return TK_MAIOR_IGUAL;}

{MENOR_IGUAL}   { return TK_MENOR_IGUAL;}

{IGUAL_IGUAL}   { return TK_IGUAL_IGUAL;}

{DIFERENTE}     { return TK_DIFERENTE;}

{MAIOR_QUE}     { return TK_MAIOR;}

{MENOR_QUE}     { return TK_MENOR;}



[(){}[\];,]	{ return *yytext; }

[+\-*/]		{ return *yytext; }

"="		    { return '='; }

{INT}		{ yylval.label = yytext; return TK_INT; }
{REAL}		{ yylval.label = yytext; return TK_FLOAT; }
{BOOLEAN}   { yylval.label = yytext; return TK_BOOLEAN; }
{ID}		{ yylval.label = yytext; return TK_ID; }


.			{ *yytext; }

%%
