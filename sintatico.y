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

int yylex(void);
void yyerror(string);
string gentempcode(string tipo);
void printSymbolTable();
void checkUndefinedTypes();
void insertTempsST(const string& nome, const string& tipo);
void typeValue(string& resultType,  string& leftType,  string& rightType,  string& leftLabel,  string& rightLabel);
void implicitConversion(atributos& esquerda, atributos& direita, atributos& final , string operacao);
void reportSemanticError(string type1, string type3, string text);
string searchType(const string& label);
%}

%token TK_TIPO_FLOAT
%token TK_NOT TK_OR TK_AND
%token TK_MAIOR TK_MAIOR_IGUAL TK_MENOR TK_MENOR_IGUAL TK_IGUAL_IGUAL TK_DIFERENTE
%token TK_INT TK_FLOAT TK_CHAR TK_BOOLEAN
%token TK_MAIN TK_ID TK_TIPO_INT TK_VAR
%token TK_FIM TK_ERROR
%token TK_PRINT TK_INPUT

%start S

%left TK_OR
%left TK_AND
%left TK_NOT
%left TK_IGUAL_IGUAL TK_DIFERENTE
%left TK_MAIOR TK_MAIOR_IGUAL TK_MENOR TK_MENOR_IGUAL 
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

				


				for(auto &par : symbolTable) {
					const Symbol &simbolo = par.second;

					if(simbolo.tipo == "undefined"){
						continue;
					}
					codigo += "\t" + simbolo.tipo + " " + simbolo.nome + ";\n";
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
			| TK_VAR TK_ID '=' E ';' 
		    {
		        Symbol val;
		        val.nome = $2.label;
		        val.tipo = $4.type;
		        val.temp = $4.label;
		        symbolTable.insert({val.nome, val});
				$$.traducao = $4.traducao + "\t" + $2.label + " = " + $4.label + ";\n";
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
		            it->second.temp = $3.label;

		        }


		        if(it->second.tipo == $3.type && it->second.temp[0] == $3.label[0]){
					
		        	cout << "\nMesmo tipo" << endl;
		        	it->second.temp = $3.label;
			        $$.type = $3.type;
			        $$.traducao = $3.traducao + "\t" + $1.label + " = " + $3.label + ";\n";
			        $$.label = $1.label;	

		        }
		        else if(it->second.tipo == "int" && it->second.temp[0] != 'b'){
		        	cout << "\nInt normal temp = " + it->second.temp  << endl;
					it->second.temp = $3.label;

        			string auxTipo = "("+ it->second.tipo +") " + $3.label;
        			string temp = gentempcode(it->second.tipo);
					string traducaoAux = "\t" + temp + " = " + auxTipo + ";\n";

					$$.type = $1.type;
					$$.traducao = $3.traducao + traducaoAux + "\t" + $1.label + " = " + $3.label + ";\n";
		        }
		        else if(it->second.tipo == "float" && $3.type != "int"||$3.type != "float"){
		        	cout << "\nFloat" << endl;
					it->second.temp = $3.label;

		        	string auxTipo = "("+ it->second.tipo +") " + $3.label;
        			string temp = gentempcode(it->second.tipo);
					string traducaoAux = "\t" + temp + " = " + auxTipo + ";\n";

					$$.type = $1.type;
					$$.traducao = $3.traducao + traducaoAux + "\t" + $1.label + " = " + $3.label + ";\n";
		        }
		        else if((it->second.temp[0] == 'b' || it->second.tipo == "char") && $3.type == "int"){
		        	cout << "Boolean ou  char" << endl;
					it->second.temp = $3.label;
		  
		        	string auxTipo = "("+ it->second.tipo +") " + $3.label;
        			string temp = gentempcode(it->second.tipo);
					string traducaoAux = "\t" + temp + " = " + auxTipo + ";\n";

					$$.type = $1.type;
					$$.traducao = $3.traducao + traducaoAux + "\t" + $1.label + " = " + $3.label + ";\n";
		       
		        }else{
		        	yyerror("Variável recebendo valores de tipos não conversiveis");
		        }


		    }
		    | E
		    {
		        $$ = $1;
		    }
			| TK_PRINT '(' E ')' {

				string formato = "";

				if ($3.type == "int" ) {
					formato = "%d";
				} else if ($3.type == "float") {
					formato = "%f";
				} else if ($3.type == "string") {
					formato = "%s";
				} else if ($3.type == "char") {
					formato = "%c";
				} else {
					yyerror("Tipo inválido no print.");
				}

				$$.traducao = $3.traducao + "\tprintf(\"" + formato + "\", " + $3.label + ");\n";
			}
			| TK_ID '=' TK_INPUT '(' ')' 
			{
				string tipo = searchType($1.label); // Busca o tipo da variável

				 if (tipo == "undefined") {
					tipo = "int";
					symbolTable[$1.label].tipo = tipo;
				}

				if (tipo == "int") {
					$$.traducao = "\tscanf(\"%d\", &" + $1.label + ");\n";
				} else if (tipo == "float") {
					$$.traducao = "\tscanf(\"%f\", &" + $1.label + ");\n";
				} else if (tipo == "char") {
					$$.traducao = "\tscanf(\" %c\", &" + $1.label + ");\n";
				} else {
					yyerror("Tipo inválido para input.");
				}

				$$.label = $1.label;
			}
		    ;
// Expressões matemáticas e terminais
E 
		    : E '+' E
		    {
		        typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        $$.label = gentempcode($$.type);
		        insertTempsST($$.label, $$.type);
		        implicitConversion($1, $3, $$, " + ");
		    }
		    | E '-' E
		    {
		        typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        $$.label = gentempcode($$.type);
		        insertTempsST($$.label, $$.type);
		        implicitConversion($1, $3, $$, " - ");
		    }
		    | E '*' E
		    {
		        typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        $$.label = gentempcode($$.type);
		        insertTempsST($$.label, $$.type);
		        implicitConversion($1, $3, $$, " * ");
		    }
		    | E '/' E
		    {
		        typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        $$.label = gentempcode($$.type);
		        insertTempsST($$.label, $$.type);
		        implicitConversion($1, $3, $$, " / ");
		    }
			| E TK_MAIOR E
		    {
				typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        insertTempsST($$.label, $$.type);
				if(($1.type != "int" && $1.type != "float") || ($3.type != "int" && $3.type != "float"))
				{
					yyerror("Operação '>' requer operandos do tipo inteiro ou float.");
				}
				$$.type = "int";
		        $$.label = gentempcode("boolean");
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " > " + $3.label + ";\n";
		    }
			| E TK_MENOR E
		    {
				typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        insertTempsST($$.label, $$.type);
				if(($1.type != "int" && $1.type != "float") || ($3.type != "int" && $3.type != "float"))
				{
					yyerror("Operação '>' requer operandos do tipo inteiro ou float.");
				}
				$$.type = "int";
		        $$.label = gentempcode("boolean");
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " < " + $3.label + ";\n";
		    }
			| E TK_DIFERENTE E
		    {
				typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        insertTempsST($$.label, $$.type);
				if(($1.type != "int" && $1.type != "float") || ($3.type != "int" && $3.type != "float"))
				{
					yyerror("Operação '>' requer operandos do tipo inteiro ou float.");
				}
				$$.type = "int";
		        $$.label = gentempcode("boolean");
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " != " + $3.label + ";\n";
		    }
			| E TK_IGUAL_IGUAL E
		    {
				typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        insertTempsST($$.label, $$.type);
				if(($1.type != "int" && $1.type != "float") || ($3.type != "int" && $3.type != "float"))
				{
					yyerror("Operação '>' requer operandos do tipo inteiro ou float.");
				}

				$$.type = "int";
		        $$.label = gentempcode("boolean");
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " == " + $3.label + ";\n";
		    }
			| E TK_MENOR_IGUAL E
		    {
				typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        insertTempsST($$.label, $$.type);
				if(($1.type != "int" && $1.type != "float") || ($3.type != "int" && $3.type != "float"))
				{
					yyerror("Operação '>' requer operandos do tipo inteiro ou float.");
				}
				$$.type = "int";
		        $$.label = gentempcode("boolean");
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " <= " + $3.label + ";\n";
		    }
			| E TK_MAIOR_IGUAL E
		    {
				typeValue($$.type, $1.type, $3.type, $1.label, $3.label);
		        insertTempsST($$.label, $$.type);
				if(($1.type != "int" && $1.type != "float") || ($3.type != "int" && $3.type != "float"))
				{
					yyerror("Operação '>' requer operandos do tipo inteiro ou float.");
				}
				$$.type = "int";
		        $$.label = gentempcode("boolean");
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " >= " + $3.label + ";\n";
		    }
			| TK_NOT E 
		    {
				$$.type = "int";
		        $$.label = gentempcode("boolean");

				auto it = symbolTable.find($2.label);
				if (it != symbolTable.end()) {
					if (it->second.temp[0] != 'b') {
						yyerror("Operação not requer operandos do tipo bool.");
					}
				} 
				$$.traducao = $2.traducao  + "\t" + $$.label + " = " + "!" + $2.label + ";\n";
		    }
			| E TK_AND E 
		    {
				$$.type = "int";
		        $$.label = gentempcode("boolean");

				auto it = symbolTable.find($2.label);
				if (it != symbolTable.end()) {
					if (it->second.temp[0] != 'b') {
						yyerror("Operação not requer operandos do tipo bool.");
					}
				} 
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " && " + $3.label + ";\n";
		    }
			| E TK_OR E 
		    {
				$$.type = "int";
		        $$.label = gentempcode("boolean");

				auto it = symbolTable.find($2.label);
				if (it != symbolTable.end()) {
					if (it->second.temp[0] != 'b') {
						yyerror("Operação not requer operandos do tipo bool.");
					}
				} 
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " || " + $3.label + ";\n";
		    }
			| TK_TIPO_INT '(' E ')' 
		    {
				if($3.type == "char"){
					yyerror("Não é possível essa conversão.");
				}
				$$.type = "int";
				$$.label = gentempcode("int");

				$$.traducao = $3.traducao  + "\t" + $$.label + " = " + "(int)" + $3.label + ";\n";
		    }
			| TK_TIPO_FLOAT '(' E ')' 
		    {
				if($3.type == "char"){
					yyerror("Não é possível essa conversão.");
				}
				$$.type = "float";
				$$.label = gentempcode("float");

				$$.traducao = $3.traducao  + "\t" + $$.label + " = " + "(float)" + $3.label + ";\n";
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

		            	$$.type = "int";
		            }
		            else{
		            	$$.type = it->second.tipo;
		            }
		            

		            $$.label = gentempcode("boolean");

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

    return temp;
}

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

    if (leftType == "char" || rightType == "char")
    {
        yyerror("Não é permitido operações com char");
    }

    if (leftType == "float" || rightType == "float") {
        resultType = "float";
    } else if (leftType == "int" || rightType == "int") {
        resultType = "int";
    } else if (leftType == "char" && rightType == "char") {
        resultType = "int"; // soma de dois chars resulta em int
    }

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

string searchType(const string& label) {
    auto it = symbolTable.find(label);
    if (it != symbolTable.end()) {
        return it->second.tipo;
    } else {
        yyerror("Variável '" + label + "' não declarada.");
        return "undefined"; 
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