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
    string nome;
    string tipo;
	string temp;
}; 

int var_temp_qnt;
unordered_map<string, Symbol> symbolTable;
vector<Symbol> tempsVector;

int yylex(void);
void yyerror(string);
string gentempcode(string tipo);
void printSymbolTable();
%}

%token TK_INT TK_FLOAT
%token TK_MAIN TK_ID TK_TIPO_INT TK_VAR
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

				// Declara apenas variáveis temporárias
				for (auto &t : tempsVector) {
					codigo += "\t" + t.tipo + " " + t.nome + ";\n";
				}

				for (auto &par : symbolTable) {
					const Symbol &simbolo = par.second;

					// Se o nome NÃO começa com 't', é uma variável do usuário (ex: a, b)
					if (!simbolo.nome.empty() && simbolo.nome[0] != 't') {
						codigo += "\t" + simbolo.tipo + " " + simbolo.nome + ";\n";
					}
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

			| TK_VAR TK_ID ';'
			{
				Symbol val;
				val.nome = $2.label;
				val.tipo = "undefined";
				val.temp = "";

				symbolTable.insert({val.nome, val});

				$$.traducao = "";
				$$.label = "";
			}
			;

E 			: E '+' E
			{
				$$.label = gentempcode($$.type);
				$$.type = "int";
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
					" = " + $1.label + " + " + $3.label + ";\n";
			}
			| E '-' E
			{
				$$.label = gentempcode($$.type);
				$$.type = "int";
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
					" = " + $1.label + " - " + $3.label + ";\n";
			}
			| E '*' E
			{
				$$.label = gentempcode($$.type);
				$$.type = "int";
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
					" = " + $1.label + " * " + $3.label + ";\n";
			}
			| E '/' E
			{
				$$.label = gentempcode($$.type);
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
					$$.label = gentempcode($$.type);
					// $$.traducao = "";
					$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";

				} else {
					yyerror("Variável não declarada.");
				}
			}
			| TK_INT
			{
				$$.type = "int";
				$$.label = gentempcode($$.type);
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
			}
			| TK_FLOAT
			{
				$$.type = "float";
				$$.label = gentempcode($$.type);
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
			}
			| TK_ID '=' E
			{
				auto it = symbolTable.find($1.label);
				if (it == symbolTable.end()) {
					yyerror("Variável do lado esquerdo não declarada.");
				}

				if (it->second.tipo == "undefined") {
					it->second.tipo = $3.type;
				}

				
				$$.type = $3.type;
				$$.traducao = $3.traducao + "\t" + $1.label + " = " + $3.label + ";\n";
			}
%%

#include "lex.yy.c"

int yyparse();

string gentempcode(string tipo) {
    var_temp_qnt++;
    string temp = "t" + to_string(var_temp_qnt);

    Symbol val; 
    val.nome = temp;
    val.tipo = tipo;
	val.temp = temp;

    tempsVector.push_back(val);

    return temp;
}

void printSymbolTable() {
	cout << "\n========= SYMBOL TABLE =========" << endl;
		for (const auto& entry : symbolTable) 
		{
			cout << "Nome: " << entry.second.nome
				<< ", Tipo: " << entry.second.tipo
				<< ", Temp: " << entry.second.temp << endl;
		}
	cout << "================================\n" << endl;
}

int main(int argc, char* argv[])
{
	var_temp_qnt = 0;

	yyparse();
	printSymbolTable();

	return 0;
}

void yyerror(string MSG)
{
	cout << MSG << endl;
	exit (0);
}		