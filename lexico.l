%{
#include <string>

%}

ESPACO [ \t]
DIGITO [0-9]
FLOAT [0-9]*\.[0-9]+|[0-9]+\.[0-9]*
LETRA [A-Za-z_]


DELIM {ESPACO}+
INT {DIGITO}+
REAL {INT}+("."{INT}+)?
CHAR \'[ -~]\'
BOOLEAN true|false
ID {LETRA}({LETRA}|{INT})*

%%

"\n"		{}

{DELIM} 	{}

{CHAR} { yylval.label = yytext; return TK_CHAR; }

"main"		{return TK_MAIN;}

"int"		{return TK_TIPO_INT;}

"var"		{return TK_VAR;}


[(){}[\];,]	{ return *yytext; }

[+\-*/]		{ return *yytext; }

"="		    { return '='; }

{INT}		{ yylval.label = yytext; return TK_INT; }
{REAL}		{ yylval.label = yytext; return TK_FLOAT; }
{BOOLEAN}   { yylval.label = yytext; return TK_BOOLEAN; }
{ID}		{ yylval.label = yytext; return TK_ID; }

.			{ *yytext; }

%%
