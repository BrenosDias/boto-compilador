%{
#include <iostream>
#include <string>
#include <sstream>
#include<unordered_map>
#include<iostream>
#include<vector>

#define YYSTYPE atributos

using namespace std;

int vet_cedulas[200];

struct atributos
{
	string label;
	string traducao;
	string type;
};

struct Symbol {
    std::string nome;
    std::string tipo;
}; 

int var_temp_qnt;
unordered_map<string, Symbol> symbolTable;

int yylex(void);
void yyerror(string);
string gentempcode();
%}

%token TK_NUM
%token TK_MAIN TK_ID TK_TIPO_INT
%token TK_FIM TK_ERROR

%start S

%left '+' '-'
%left '*' '/'

%%

S 			: TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				string codigo = "/*Compilador boto*/\n"
								"#include <iostream>\n"
								"#include<string.h>\n"
								"#include<stdio.h>\n"
								"int main(void) {\n";
								

				for(int i = 1; i <= var_temp_qnt; i++)
				{
					codigo += "\tint t" + to_string(i) + ";\n";
				}

				codigo += "\n";

				codigo += $5.traducao;
								
				codigo += 	"\treturn 0;"
							"\n}";

				cout << codigo << endl;
			}
			;

BLOCO		: '{' COMANDOS '}'
			{
				$$.traducao = $2.traducao;
			}
			;

COMANDOS	: COMANDO COMANDOS
			{
				$$.traducao = $1.traducao + $2.traducao;
			}
			|
			{
				$$.traducao = "";
			}
			;

COMANDO 	: E ';'
			{
				$$ = $1;
			}
			;
			| TK_TIPO_INT TK_ID ';'
			{
				Symbol val;
				val.nome = $2.label;
				val.tipo = "int";

				symbolTable.insert({val.nome, val});

				$$.traducao = "";
				$$.label = "";
			}
			;

E 			: E '+' E
			{
				$$.label = gentempcode();
				$$.type = "int";
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
					" = " + $1.label + " + " + $3.label + ";\n";
			}
			| E '-' E
			{
				$$.label = gentempcode();
				$$.type = "int";
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
					" = " + $1.label + " - " + $3.label + ";\n";
			}
			| E '*' E
			{
				$$.label = gentempcode();
				$$.type = "int";
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
					" = " + $1.label + " * " + $3.label + ";\n";
			}
			| E '/' E
			{
				$$.label = gentempcode();
				$$.type = "int";
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
					" = " + $1.label + " / " + $3.label + ";\n";
			}
			| '(' E ')' 
			{
				$$.label = $2.label;
				$$.type = $2.type;
				$$.traducao = $2.traducao;
			}
			| TK_ID
			{
				auto it = symbolTable.find($1.label);
				if (it != symbolTable.end()) {
					$$.type = it->second.tipo;
					// $$.label = $1.label;
					$$.label = gentempcode();
					// $$.traducao = "";
					$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";

				} else {
					yyerror("Variável não declarada.");
				}
			}
			| TK_NUM
			{
				$$.type = "int";
				$$.label = gentempcode();
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
			}
			| TK_ID '=' E
			{
				auto it = symbolTable.find($1.label);
				if (it == symbolTable.end()) {
					yyerror("Variável do lado esquerdo não declarada.");
				}

				// $$.label = "";
				$$.label = gentempcode();
				$$.type = "int";
				$$.traducao = $3.traducao + "\t" + $1.label + " = " + $3.label + ";\n";
			}
%%

#include "lex.yy.c"

int yyparse();

string gentempcode()
{
	var_temp_qnt++;
	string nome = "t" + to_string(var_temp_qnt);

	return nome;
}

int main(int argc, char* argv[])
{
	var_temp_qnt = 0;

	yyparse();

	return 0;
}

void yyerror(string MSG)
{
	cout << MSG << endl;
	exit (0);
}				
