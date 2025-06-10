%{
#include <iostream>
#include <string>
#include <sstream>
#include<unordered_map>
#include <set>
#include<iostream>
#include<vector>
#include <stack>

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

struct TabelaSimbolos
{
	vector<unordered_map<string, Symbol>> escopos;
	int quantidade;
};

// Estrutura para guardar os rótulos de um laço
struct InfoLaco {
    std::string inicio;
    std::string fim;
};

// Pilha para os rótulos de saída (para o 'break') - continua igual
std::stack<std::string> breakLabels;
stack<string> continueLabels;
// NOVA Pilha para gerenciar os laços ativos
vector<InfoLaco> pilhaLacos;

int var_temp_qnt;
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
%}

%token TK_TIPO_FLOAT
%token TK_NOT TK_OR TK_AND
%token TK_MAIOR TK_MAIOR_IGUAL TK_MENOR TK_MENOR_IGUAL TK_IGUAL_IGUAL TK_DIFERENTE
%token TK_INT TK_FLOAT TK_CHAR TK_BOOLEAN
%token TK_MAIN TK_ID TK_TIPO_INT TK_VAR
%token TK_FIM TK_ERROR
%token TK_PRINT
%token TK_WHILE TK_FOR TK_DO TK_IF TK_ELSE TK_BREAK TK_CONTINUE TK_BREAKOUT


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
				// entraEscopo();

				string codigo = "/*Compilador boto*/\n"
								"#include <iostream>\n"
								"#include<string.h>\n"
								"#include<stdio.h>\n"
								"int main(void) {\n";

				



				// // Iterate through each scope in the symbolTable
				// for (const auto& escopoAtual : symbolTable.escopos) {
				// 	// Iterate through each symbol (key-value pair) within the current scope map
				// 	for (const auto& par : escopoAtual) {
				// 		const Symbol& simbolo = par.second;

				// 		bool encontrado = false;
				// 		for (const Symbol& temp : tempsVector) {
				// 			// Assuming 'temp.nome' is the unique identifier for comparison
				// 			// and 'temp.tipo' needs to be defined
				// 			if (temp.nome == simbolo.nome && temp.tipo != "undefined") {
				// 				encontrado = true;
				// 				break;
				// 			}
				// 		}

				// 		if (!encontrado) {
				// 			codigo += "\t" + simbolo.tipo + " " + simbolo.nome + ";\n";
				// 		}
				// 	}
				// }

			for (const Symbol& simbolo : tempsVector) {
			    // SÓ DECLARE a variável se o tipo for conhecido (diferente de "undefined")
			    if (simbolo.tipo != "undefined" && tempsAdicionados.insert(simbolo.temp).second) {
			        codigo += "\t" + simbolo.tipo + " " + simbolo.temp + ";\n";
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

COMANDO 
		    : EXPRESSAO ';'
		    {
		        $$ = $1;
		    }
		    | TK_ID
		    {

		        bool achou = false;
		        for (int i = symbolTable.quantidade - 1; i >= 0; --i) {
		            auto& escopoAtual = symbolTable.escopos[i]; 

		            auto it = escopoAtual.find($1.label);
		            if (it != escopoAtual.end()) {
		                $$.type = it->second.tipo;
		                string origem = it->second.temp.empty() ? $1.label : it->second.temp;
		                $$.label = gentempcode($$.type);
		                insertTempsST($$.label, $$.type); 
		                $$.traducao = "\t" + $$.label + " = " + origem + ";\n";
		                achou = true;
		                break;
		            }
		        }
		        if (!achou)
		        {
		        	yyerror("Variável não declarada.");
		        }

		    }
		    | TK_VAR TK_ID ';'
		    {
		        Symbol val;
		        val.nome = $2.label;
		        val.tipo = "undefined";
		        val.temp = "";
		        declaraVariavel(val);
		        $$.traducao = "";
		        $$.label = "";
		    }
			| TK_VAR TK_ID '=' E ';' 
		    {
		        Symbol val;
		        val.nome = $2.label;
		        val.tipo = $4.type;
		        val.temp = $4.label;
		        cout << "\nNome "+val.nome << endl;
				cout << "\nTemp "+val.temp << endl;
		        declaraVariavel(val);
				$$.traducao = $4.traducao;
		        $$.label = "";
		    }
		    | PUSH_ESCOPO COMANDOS POP_ESCOPO
		    {
		    	$$.traducao = $2.traducao;
		    }
		    |ESTRUTURA_DE_CONTROLE
		    {
		    	$$ = $1;
		    }
		    | TK_BREAK ';' 
		    {
		        if (breakLabels.empty()) {
		            yyerror("Comando 'break' fora de um laço (while/for)");
		            $$.traducao = "";
		        } else {
		            // Perfeito, continua funcionando!
		            $$.traducao = "goto " + breakLabels.top() + ";\n";
		        }
		    }
		    | TK_BREAKOUT ';'
		    {
		        // A verificação é na pilha de laços principal
		        if (pilhaLacos.empty()) {
		            yyerror("Comando 'breakout' fora de um laço");
		            $$.traducao = "";
		        } else {
		            // Pega o primeiro elemento (o mais externo) com .front()
		            $$.traducao = "goto " + pilhaLacos.front().fim + ";\n";
		        }
		    }		    
		    | TK_CONTINUE ';' 
		    {
		        if (continueLabels.empty()) {
		            yyerror("Comando 'continue' fora de um laço (while/for)");
		            $$.traducao = "";
		        } else {
		            // Perfeito, continua funcionando!
		            $$.traducao = "goto " + continueLabels.top() + ";\n";
		        }
		    }

		    ;

PUSH_ESCOPO : '{' 
			{
				entraEscopo();
			}
			;

POP_ESCOPO  : '}'
			{
				saiEscopo();
			}
			;

FOR_DECL_OU_EXPR
		    : TK_VAR TK_ID '=' E  // Ex: var a = 0
		    {
		        // Ação semântica para declarar a variável
		        Symbol val;
		        val.nome = $2.label;
		        val.tipo = $4.type;
		        val.temp = $4.label;
		        declaraVariavel(val);
		        $$.traducao = $4.traducao; // Passa a tradução da inicialização
		        $$.label = "";
		    }
		    | EXPRESSAO            // Ex: a = 0 (se 'a' já existe)
		    {
		        $$ = $1;
		    }
		    ;

FOR_INIT
		    : FOR_DECL_OU_EXPR
		    {
		        $$.traducao = $1.traducao; 
		    }
		    | /* epsilon */
		    {
		        $$.traducao = ""; 
		    }
		    ;

FOR_COND
		    : E 
		    { 
		    	$$.traducao = $1.traducao; 
		    	$$.label = $1.label; 
			}
		    | 
		    {
		        // Se a condição for vazia, o laço é infinito (condição sempre verdadeira).
		        // Geramos um booleano temporário com valor 'true'.
		        string temp_true = gentempcode("bool");
		        insertTempsST(temp_true, "bool");
		        $$.traducao = temp_true + " = 1;\n"; // 1 para 'true'
		        $$.label = temp_true;
		    }
		    ;

FOR_INCR
		    : EXPRESSAO  
		    {
		     	$$.traducao = $1.traducao; 
		 	}
		    | 
		    {
		     	$$.traducao = ""; 
		    }
		    ;
ESTRUTURA_DE_CONTROLE 
			: TK_WHILE INICIO_LOOP '(' E ')' COMANDO
			{
				InfoLaco lacoAtual = pilhaLacos.back();

				if ($4.label[0] != 'b'){
					yyerror("Essa expressao nao e um boolean");
				}

				string temp = gentempcode("int");
				insertTempsST(temp, "int");
				
				// Extraindo os labels de início e fim

				string traducao;

				traducao += lacoAtual.inicio + ": \n";
				traducao += $4.traducao;
				traducao += temp + " = !(" + $4.label + "); \n";
				traducao += "if (" + temp + ") goto " + lacoAtual.fim + ";\n";
				traducao += $6.traducao;
				traducao += "goto " + lacoAtual.inicio + ";\n";
				traducao += lacoAtual.fim + ": \n";


				$$.traducao = traducao;

		        if (!pilhaLacos.empty()) {
		            pilhaLacos.pop_back();
		       		cout << "pop pilha" << endl;

		        }
		        if (!breakLabels.empty()) {
		            breakLabels.pop();
		       		cout << "pop pilha" << endl;	
		       	}			
			}
			|TK_DO INICIO_LOOP COMANDO TK_WHILE '(' E ')' ';'
			{
		        // Pega os rótulos da pilha, preparados pelo PREPARA_LACO
		        InfoLaco lacoAtual = pilhaLacos.back();

		        if ($6.label[0] != 'b'){ // $6 é o não-terminal E
		            yyerror("Essa expressao nao e um boolean");
		        }

		        string traducao;

		        // 1. Rótulo de início do laço
		        traducao += lacoAtual.inicio + ":\n";

		        // 2. Código do corpo (COMANDO), que é $3
		        traducao += $3.traducao;

		        // 3. Código da expressão condicional (E), que é $6
		        traducao += $6.traducao;

		        // 4. Salto condicional de volta para o início se a condição for VERDADEIRA
		        traducao += "if (" + $6.label + ") goto " + lacoAtual.inicio + ";\n";

		        // 5. Rótulo de fim, para onde o 'break' e 'breakout' pularão
		        traducao += lacoAtual.fim + ":\n";

		        $$.traducao = traducao;

		        // 6. Limpeza das pilhas, exatamente como na regra do 'while'
		        if (!pilhaLacos.empty()) {
		            pilhaLacos.pop_back();
		        }
		        if (!breakLabels.empty()) {
		            breakLabels.pop();
		        }
			}
			| TK_FOR '(' FOR_INIT ';' FOR_COND ';' FOR_INCR ')' INICIO_LOOP COMANDO
		    {
		        // Pega os rótulos preparados pelo PREPARA_LACO ($9)
		        InfoLaco lacoAtual = pilhaLacos.back();

		        // Pega o código de cada parte
		        string init_code = $3.traducao;
		        string cond_code = $5.traducao;
		        string cond_label = $5.label;
		        string incr_code = $7.traducao;
		        string body_code = $10.traducao;

		        string traducao;

		        // 1. Código da inicialização (executado uma vez, fora do laço)
		        traducao += init_code;

		        // 2. Rótulo de início do laço
		        traducao += lacoAtual.inicio + ":\n";

		        // 3. Código da condição
		        traducao += cond_code;

		        // 4. Verificação da condição (salta para o fim se for falsa)
		        string temp = gentempcode("bool");
		        insertTempsST(temp, "bool");
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

		        $$.traducao = traducao;

		        // 9. Limpeza das pilhas
		        if (!pilhaLacos.empty()) {
		            pilhaLacos.pop_back();
		        }
		        if (!breakLabels.empty()) {
		            breakLabels.pop();
		        }
		    }
		    ;
			| TK_IF '(' E ')' COMANDO
			{
				if ($3.label[0] != 'b'){
					yyerror("Essa expressao nao e um boolean");
				}
					string temp = gentempcode("int");        
					insertTempsST(temp, "int");              
					string ifLabel = genlabel();

					string traducao = $3.traducao;

					traducao += temp + " = !(" + $3.label + "); \n";
					traducao += "if (" + temp + ") goto " + ifLabel + ";\n";
					traducao += $5.traducao;
					traducao += ifLabel + ": \n";

					$$.traducao = traducao;
			}
			;

INICIO_LOOP
		    : 
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
		    ;

// EXPRESSAO separa atribuições de E
EXPRESSAO
		    : TK_ID '=' E
		    {	
        		auto it = symbolTable.escopos.begin()->end(); 
		    	bool achou = false;
		        for (int i = symbolTable.escopos.size() - 1; i >= 0; --i) {
		            auto& escopoAtual = symbolTable.escopos[i]; 
		            it = escopoAtual.find($1.label);

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
		            it->second.tipo = $3.type;
		            it->second.temp = $3.label;

		        }


		        if(it->second.tipo == $3.type && it->second.temp[0] == $3.label[0]){
					
		        	cout << "\nMesmo tipo" << endl;

		        	// it->second.temp = $3.label;
			        $$.type = $3.type;
			        $$.traducao = $3.traducao + "\t" + it->second.temp + " = " + $3.label + ";\n";
			        $$.label = $1.label;	

		        }
		        else if(it->second.tipo == "int" && it->second.temp[0] != 'b'){
		        	cout << "\nInt normal temp = " + it->second.temp  << endl;
					// it->second.temp = $3.label;

        			string auxTipo = "("+ it->second.tipo +") " + $3.label;
        			string temp = gentempcode(it->second.tipo);
					string traducaoAux = "\t" + temp + " = " + auxTipo + ";\n";

					$$.type = $1.type;
					$$.traducao = $3.traducao + traducaoAux + "\t" + it->second.temp + " = " + $3.label + ";\n";
		        }
		        else if(it->second.tipo == "float" && $3.type != "int"||$3.type != "float"){
		        	cout << "\nFloat" << endl;
					// it->second.temp = $3.label;

		        	string auxTipo = "("+ it->second.tipo +") " + $3.label;
        			string temp = gentempcode(it->second.tipo);
					string traducaoAux = "\t" + temp + " = " + auxTipo + ";\n";

					$$.type = $1.type;
					$$.traducao = $3.traducao + traducaoAux + "\t" + it->second.temp + " = " + $3.label + ";\n";
		        }
		        else if((it->second.temp[0] == 'b' || it->second.tipo == "char") && $3.type == "int"){
		        	cout << "Boolean ou  char" << endl;
					// it->second.temp = $3.label;
		  
		        	string auxTipo = "("+ it->second.tipo +") " + $3.label;
        			string temp = gentempcode(it->second.tipo);
					string traducaoAux = "\t" + temp + " = " + auxTipo + ";\n";

					$$.type = $1.type;
					$$.traducao = $3.traducao + traducaoAux + "\t" + it->second.temp + " = " + $3.label + ";\n";
		       
		        }else{
		        	yyerror("Variável recebendo valores de tipos não conversiveis");
		        }


		    }
		    | TK_PRINT '(' E ')' {

                string formato = "";

                std::cout << "\n" << $3.type << std::endl;

                 if ($3.type == "int" ) {
                    formato = "%d";
                } else if ($3.label[0] == 'b') {
                    formato = "%d";
                } else if ($3.type == "float") {
                    formato = "%f";
                }else if ($3.type == "string") {
                    formato = "%s";
                } else if ($3.type == "char") {
                    formato = "%c";
                } else {
                    yyerror("Tipo inválido no print.");
                }

                $$.traducao = $3.traducao + "\tprintf(\"" + formato + "\", " + $3.label + ");\n";
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
				implicitConversion($1, $3, $$, " > ");
				insertTempsST($$.label, $$.type);
				if(($1.type != "int" && $1.type != "float") || ($3.type != "int" && $3.type != "float"))
				{
					yyerror("Operação '>' requer operandos do tipo inteiro ou float.");
				}
				$$.type = "int";
		        $$.label = gentempcode("boolean");		        
				insertTempsST($$.label, $$.type);
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " > " + $3.label + ";\n";
		    }
			| E TK_MENOR E

		    {	
		    	cout << "\n Esq = "+ $1.label + "Dir = " + $3.label << endl;


				implicitConversion($1, $3, $$, " < ");
				insertTempsST($$.label, $$.type);
				if(($1.type != "int" && $1.type != "float") || ($3.type != "int" && $3.type != "float"))
				{
					yyerror("Operação '<' requer operandos do tipo inteiro ou float.");
				}
				$$.type = "int";
		        $$.label = gentempcode("boolean");
		        insertTempsST($$.label, $$.type);
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " < " + $3.label + ";\n";
		    }
			| E TK_DIFERENTE E
		    {
				implicitConversion($1, $3, $$, " != ");
				insertTempsST($$.label, $$.type);
				if(($1.type != "int" && $1.type != "float") || ($3.type != "int" && $3.type != "float"))
				{
					yyerror("Operação '!' requer operandos do tipo inteiro ou float.");
				}
				$$.type = "int";
		        $$.label = gentempcode("boolean");
		        insertTempsST($$.label, $$.type);
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " != " + $3.label + ";\n";
		    }
			| E TK_IGUAL_IGUAL E
		    {
				implicitConversion($1, $3, $$, " == ");
				insertTempsST($$.label, $$.type);
				if(($1.type != "int" && $1.type != "float") || ($3.type != "int" && $3.type != "float"))
				{
					yyerror("Operação '==' requer operandos do tipo inteiro ou float.");
				}

				$$.type = "int";
		        $$.label = gentempcode("boolean");
		        insertTempsST($$.label, $$.type);
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " == " + $3.label + ";\n";
		    }
			| E TK_MENOR_IGUAL E
		    {
				implicitConversion($1, $3, $$, " <= ");
		        insertTempsST($$.label, $$.type);
				if(($1.type != "int" && $1.type != "float") || ($3.type != "int" && $3.type != "float"))
				{
					yyerror("Operação '<=' requer operandos do tipo inteiro ou float.");
				}
				$$.type = "int";
		        $$.label = gentempcode("boolean");
		        insertTempsST($$.label, $$.type);
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " <= " + $3.label + ";\n";
		    }
			| E TK_MAIOR_IGUAL E
		    {
				implicitConversion($1, $3, $$, " >= ");
				
		        insertTempsST($$.label, $$.type);
				if(($1.type != "int" && $1.type != "float") || ($3.type != "int" && $3.type != "float"))
				{
					yyerror("Operação '>=' requer operandos do tipo inteiro ou float.");
				}
				$$.type = "int";
		        $$.label = gentempcode("boolean");
		        insertTempsST($$.label, $$.type);
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " >= " + $3.label + ";\n";
		    }
			| TK_NOT E 
		    {
				$$.type = "int";
		        $$.label = gentempcode("boolean");

		        for (int i = symbolTable.escopos.size() - 1; i >= 0; --i) {
		            auto& escopoAtual = symbolTable.escopos[i]; 
		            auto it = escopoAtual.find($2.label);

					if (it != escopoAtual.end()) {
						if (it->second.temp[0] != 'b') {
							yyerror("Operação not requer operandos do tipo bool.");
						}
					}
		        }
				$$.traducao = $2.traducao  + "\t" + $$.label + " = " + "!" + $2.label + ";\n";
		    }
			| E TK_AND E 
		    {
				$$.type = "int";
		        $$.label = gentempcode("boolean");

		        for (int i = symbolTable.escopos.size() - 1; i >= 0; --i) {
		            auto& escopoAtual = symbolTable.escopos[i]; 
		            auto it = escopoAtual.find($2.label);

					if (it != escopoAtual.end()) {
						if (it->second.temp[0] != 'b') {
							yyerror("Operação not requer operandos do tipo bool.");
						}
					}
		        }
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + " = " + $1.label + " && " + $3.label + ";\n";
		    }
			| E TK_OR E 
		    {
				$$.type = "int";
		        $$.label = gentempcode("boolean");

		        for (int i = symbolTable.escopos.size() - 1; i >= 0; --i) {
		            auto& escopoAtual = symbolTable.escopos[i]; 
		            auto it = escopoAtual.find($2.label);

					if (it != escopoAtual.end()) {
						if (it->second.temp[0] != 'b') {
							yyerror("Operação not requer operandos do tipo bool.");
						}
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

		        bool achou = false; 

		        for (int i = symbolTable.escopos.size() - 1; i >= 0; --i) {
		            auto& escopoAtual = symbolTable.escopos[i];

		            auto it = escopoAtual.find($1.label);
		            if (it != escopoAtual.end()) {
		                string tipo;

		                if (it->second.temp[0] == 'b') {
		                    $$.type = "int";
							$$.label = gentempcode("boolean");

		                } else {
		                    $$.type = it->second.tipo;
							$$.label = gentempcode($$.type);
		                }

		                insertTempsST($$.label, $$.type);
		                string origem = it->second.temp.empty() ? $1.label : it->second.temp;
		                $$.traducao = "\t" + $$.label + " = " + origem + ";\n";

		                achou = true; 
		                break;       
		            }
		        }

		        if (!achou) {
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
		//printf("temp = %s\n", temp);
    	tipo = "int";
    }

	 cout << "\n" + temp << endl;

    return temp;
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
                std::cerr << "Erro: Variável '" << simbolo.nome << "' usada sem tipo definido.\n";
                exit(1); 
            }
        }
    }
}

int labelCount = 0;

string genlabel() {
    return "L" + to_string(labelCount++);
}

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