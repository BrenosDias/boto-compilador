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
STRING    \"([^\\\n\"]|\\.)*\"
BOOLEAN true|false
ID {LETRA}({LETRA}|{INT})*
MAIOR_IGUAL     {MAIOR_QUE}{IGUAL}
MENOR_IGUAL     {MENOR_QUE}{IGUAL}
IGUAL_IGUAL     {IGUAL}{IGUAL}
DIFERENTE       {NEGACAO}{IGUAL}


%%

"\n"		{}

{DELIM} 	{}



"main"		{return TK_MAIN;}

"String"    {return TK_STRING; }

"int"		{return TK_TIPO_INT;}

"float"		{return TK_TIPO_FLOAT;}

"var"		{return TK_VAR;}

"not"       {return TK_NOT;}

"and"       {return TK_AND;}

"or"        {return TK_OR;}

"print"     {return TK_PRINT;}

"while"     {return TK_WHILE;}

"for"     {return TK_FOR;}

"do"      {return TK_DO;}

"if"        {return TK_IF;}

"else"      {return TK_ELSE;}

"switch"    {return TK_SWITCH;}

"case"      {return TK_CASE;}

"break"      {return TK_BREAK;}

"breakout"      {return TK_BREAKOUT;}

"continue"      {return TK_CONTINUE;}

{MAIOR_IGUAL}   { return TK_MAIOR_IGUAL;}

{MENOR_IGUAL}   { return TK_MENOR_IGUAL;}

{IGUAL_IGUAL}   { return TK_IGUAL_IGUAL;}

{DIFERENTE}     { return TK_DIFERENTE;}

{MAIOR_QUE}     { return TK_MAIOR;}

{MENOR_QUE}     { return TK_MENOR;}



[(){};:,=+\-*/<>] { return yytext[0]; }


{CHAR}      {yylval.label = yytext; return TK_CHAR;}
{INT}		{ yylval.label = yytext; return TK_INT; }
{REAL}		{ yylval.label = yytext; return TK_FLOAT; }
{BOOLEAN}   { yylval.label = yytext; return TK_BOOLEAN; }
{ID}		{ yylval.label = yytext; return TK_ID; }
{STRING} {
    yylval.label = strdup(yytext);  // Faz uma cópia da string reconhecida
    return TK_STRING;
}


.			{ *yytext; }

%%