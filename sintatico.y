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
void checkUndefinedTypes();
void insertTempsST(const string& nome, const string& tipo);
void typeValue(string& resultType,  string& leftType,  string& rightType,  string& leftLabel,  string& rightLabel);
void implicitConversion(string type1, string type3, string label1, string label3, string traducao1, string traducao3, string resultLabel, string &traducaoFinal, string type2);
void reportSemanticError(string type1, string type3, string text);
%}


%token TK_INT TK_FLOAT TK_CHAR TK_BOOLEAN
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

					bool encontrado = false;
					for (const Symbol &temp : tempsVector) {
						if (temp.nome == simbolo.nome && temp.tipo != "undefinaded") {
							encontrado = true;
							break;
						}
					}

					if (!encontrado) {
						codigo += "\t" + simbolo.tipo + " " + simbolo.nome + ";\n";
					}
				}

				// for (auto &par : symbolTable) {
				// 	const Symbol &simbolo = par.second;

				// 	// Se o nome NÃO começa com 't', é uma variável do usuário (ex: a, b)
				// 	if (!simbolo.nome.empty() && simbolo.nome[0] != 't') {
				// 		codigo += "\t" + simbolo.tipo + " " + simbolo.nome + ";\n";
				// 	}
				// }

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

COMANDO 
		    : EXPRESSAO ';'
		    {
		        $$ = $1;
		    }
		    | TK_ID
		    {
		        auto it = symbolTable.find($1.label);
		        if (it != symbolTable.end()) {
		            $$.type = it->second.tipo;
		            string origem = it->second.temp.empty() ? $1.label : it->second.temp;
		            $$.label = gentempcode($$.type);
		            insertTempsST($$.label, $$.type);
		            $$.traducao = "\t" + $$.label + " = " + origem + ";\n";
		        } else {
		            yyerror("Variável não declarada.");
		        }
		    }
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

// EXPRESSAO separa atribuições de E
EXPRESSAO
		    : TK_ID '=' E
		    {
		        auto it = symbolTable.find($1.label);
		        if (it == symbolTable.end()) {
		            yyerror("Variável do lado esquerdo não declarada.");
		        }

		        if (it->second.tipo == "undefined") {
		            it->second.tipo = $3.type;
		        }

		        it->second.temp = $3.label;

		        $$.type = $3.type;
		        $$.traducao = $3.traducao + "\t" + $1.label + " = " + $3.label + ";\n";
		        $$.label = $1.label;
		    }
		    | E
		    {
		        $$ = $1;
		    }
		    ;
// Expressões matemáticas e terminais
E 
		    : E '+' E
		    {
		        typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        $$.label = gentempcode($$.type);
		        insertTempsST($$.label, $$.type);
		        string resultado;
		        implicitConversion($1.type, $3.type, $1.label, $3.label, $1.traducao, $3.traducao, $$.label, $$.traducao, " + ");
		    }
		    | E '-' E
		    {
		        typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        $$.label = gentempcode($$.type);
		        insertTempsST($$.label, $$.type);
		        $$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " - " + $3.label + ";\n";
		        implicitConversion($1.type, $3.type, $1.label, $3.label, $1.traducao, $3.traducao, $$.label, $$.traducao, " - ");
		    }
		    | E '*' E
		    {
		        typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        $$.label = gentempcode($$.type);
		        insertTempsST($$.label, $$.type);
		        $$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " * " + $3.label + ";\n";
		        implicitConversion($1.type, $3.type, $1.label, $3.label, $1.traducao, $3.traducao, $$.label, $$.traducao, " * ");
		    }
		    | E '/' E
		    {
		        typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        $$.label = gentempcode($$.type);
		        insertTempsST($$.label, $$.type);
		        $$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " / " + $3.label + ";\n";
		        implicitConversion($1.type, $3.type, $1.label, $3.label, $1.traducao, $3.traducao, $$.label, $$.traducao, " / ");
		    }
		    | '(' E ')'
		    {
		        $$ = $2;
		    }
		    | TK_ID
		    {
		        auto it = symbolTable.find($1.label);
		        if (it != symbolTable.end()) {
		        	string tipo;
		            if(it->second.temp[0] == 'b'){

		            	$$.type = "boolean";
		            }
		            else{
		            	$$.type = it->second.tipo;
		            }
		            

		            $$.label = gentempcode($$.type);

		            insertTempsST($$.label, $$.type);
		            string origem = it->second.temp.empty() ? $1.label : it->second.temp;
		            $$.traducao = "\t" + $$.label + " = " + origem + ";\n";
		        } else {
		            yyerror("Variável não declarada.");
		        }
		    }
		    | TK_INT
		    {
		        $$.type = "int";
		        $$.label = gentempcode($$.type);

		        insertTempsST($$.label, $$.type);
		        $$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
		    }

		    | TK_FLOAT
		    {
		        $$.type = "float";
		        $$.label = gentempcode($$.type);
		        insertTempsST($$.label, $$.type);
		        $$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
		    }
		    | TK_BOOLEAN
		    {	
		        $$.type = "int";
		        $$.label = gentempcode("boolean");

		        string label;
		        if($1.label == "true"){
		        	label = "1";
		        }else{
		        	label = "0";
		        }
		        insertTempsST($$.label, $$.type);
		        $$.traducao = "\t" + $$.label + " = " + label + ";\n";
		    }
		    | TK_CHAR
		    {
		        $$.type = "char";
		        $$.label = gentempcode($$.type);
		        insertTempsST($$.label, $$.type);
		        $$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
		    }
		    ;


%%

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
    	tipo = "int";
    }

    Symbol val; 
    val.nome = temp;
    val.tipo = tipo;
	val.temp = temp;

    tempsVector.push_back(val);
    return temp;
}

<<<<<<< HEAD
void typeValue(string& resultType,  string& leftType,  string& rightType,  string& leftLabel,  string& rightLabel){


	auto itLeft = symbolTable.find(leftLabel);
	if (itLeft != symbolTable.end()) {
	    Symbol simbolo = itLeft->second;
	    if (simbolo.temp[0] == 'b') {
	        yyerror("Não é permitido operações com Booleanos");
	    }
	}

	auto itRight = symbolTable.find(rightLabel);
	if (itRight != symbolTable.end()) {
	    Symbol simbolo = itRight->second;
	    if (simbolo.temp[0] == 'b') {
	        yyerror("Não é permitido operações com Booleanos");
	    }
	}

    if (leftType == "float" || rightType == "float") {
        resultType = "float";
    } else if (leftType == "int" || rightType == "int") {
        resultType = "int";
    } else if (leftType == "char" && rightType == "char") {
        resultType = "int"; // soma de dois chars resulta em int
=======

void typeValue(string& result, const string& left, const string& right){

    if (left == "char" || right == "char")
        {
            yyerror("Não é permitido operações com char");
        }

    if (left == "float" || right == "float") {
        result = "float";
    } else if (left == "int" || right == "int") {
        result = "int";
    } else if (left == "char" && right == "char") {
        result = "int"; // soma de dois chars resulta em int
>>>>>>> 1b203cf (Feat: Adicionado mensagem de erro para operacoes com char)
    } else {
        resultType = "undefined";
    }
}

void implicitConversion(string type1, string type3, string label1, string label3, string traducao1, string traducao3, string resultLabel, string &traducaoFinal, string type2)
{
    string resultado;


    if (type1 == "int" && type3 == "float") {
        string auxFloat = "(float) " + label1;
        string aux = label3;
        resultado = resultLabel + " = " + auxFloat + type2 + aux;
        traducaoFinal = traducao1 + traducao3 + "\t" + resultado + ";\n";
    }
    else if (type1 == "float" && type3 == "int") {
        string aux = label1;
        string auxFloat = "(float) " + label3;
        resultado = resultLabel + " = " + aux + type2 + auxFloat;
        traducaoFinal = traducao1 + traducao3 + "\t" + resultado + ";\n";
    }
    else {
        resultado = resultLabel + " = " + label1 + type2 + label3;
        traducaoFinal = traducao1 + traducao3 + "\t" + resultado + ";\n";
    }
}



void insertTempsST(const string& nome, const string& tipo)
{
	Symbol simbolo;
    simbolo.nome = nome;
    simbolo.tipo = tipo;
    simbolo.temp = nome;

    symbolTable.insert({nome, simbolo});
}

void checkUndefinedTypes() {
    for (const auto& par : symbolTable) {
        const Symbol& simbolo = par.second;
        if (simbolo.tipo == "undefined" && (simbolo.nome.empty() || simbolo.nome[0] != 't')) {
            cerr << "Erro: Variável '" << simbolo.nome << "' usada sem tipo definido.\n";
            exit(1);
        }
    }
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