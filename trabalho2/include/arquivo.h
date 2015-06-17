#pragma once

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include "tabela.h"
#include "erro.h"

using namespace std;

//Retorna se acha token no arquivo
bool buscaTokenArq(ifstream& arq, string token); //Busca sequencial
//  Linha   tab
//  0       (SECTION,TEXT)
//  1       (Rótulo, instrução, argumentos)
void criaVetorTab(ifstream& arq, vector< vector<string> >& mTab); //Mapeia o arquivo em linhas x tab

// Recebe um arquivo, preprocessa ele para ser lido pelo compilador e salva o arquivo preprocessado
// com o nome "titulo_arquivo" e retorna o objeto ofstream do arquivo preprocessado.
// caso dar erro retorna nulo
//bool preProcessaArq(char nomeArquivo[] , vector<tipoGramatica>& gramatica, vector<tipoDiretiva>& diretiva);

// Recebe um arquivo presumidamente com codigo assembly inventado e cria um arquivo chamado pre_processado.txt
// Parametros o endereco do arquivo a ser preprocessado, eh necessario que os comandos e os argumentos nao estejam separados por \n
void preProcessaArq2(string nomeArquivo, map<string, tipoTS>& simbolo);

//  Verifica se a linha possui EQU ou IF e, se tiver, realiza devidos tratamentos
//  Retorna TRUE se pode imprimir a linha atual, ou seja, não tem nem EQU nem IF, ou FALSE se não pode, ou seja, se tem EQU ou IF
//  Nota: sempre retorna false se EQU ou IF estiverem corretos
//  Se linha atual é um IF, edita
bool verificaNotEQUIF(string linha, map<string, int>& valorEQU, int *prox);

//Se a linha não for de definição de EQU, troca labels que são EQUs por seu respectivo valor
//retorna a linha certa para ser escrita
void trocaEQU(string op, string arg, map<string, tipoTS>& simbolo);

//	Funcao auxiliar retira tabs duplos desnecessarios
//	Retorna a string formatada ja
string formataTabs(string formatada);

//	Funcao auxiliar retira o comentario de uma instrucao
//	Retorna a string formatada ja
string retiraComentarios(string formatada);


//	Funcao auxiliar transforma em espaços em branco em tabs
//	Retorna a string formatada ja
string transformaEspacoEmBranco(string formatada);

//	Funcao Auxiliar retira NL de um objeto string
//	Retorna a string sem ele
string retiraNL(string formatada);


//	Funcao Auxiliar retira LF de um objeto string
//	Retorna a string sem ele
std::string retiraLF(std::string formatada);
