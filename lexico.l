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
CHAR \'({LETRA}|{INT})\'
ID {LETRA}({LETRA}|{INT})*

%%

"\n"		{}

{DELIM} 	{}

"main"		{return TK_MAIN;}

"int"		{return TK_TIPO_INT;}

"var"		{return TK_VAR;}


[(){}[\];,]	{ return *yytext; }

[+\-*/]		{ return *yytext; }

"="		    { return '='; }

{INT}		{ yylval.label = yytext; return TK_INT; }
{REAL}		{ yylval.label = yytext; return TK_FLOAT;}
{ID}		{ yylval.label = yytext; return TK_ID; }

.			{ *yytext; }

%%
