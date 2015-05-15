#pragma once

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include "tabela.h"

using namespace std;

//Retorna se acha token no arquivo
bool buscaTokenArq(ifstream& arq, string token); //Busca sequencial

// Recebe um arquivo, preprocessa ele para ser lido pelo compilador e salva o arquivo preprocessado
// com o nome "titulo_arquivo" e retorna o objeto ofstream do arquivo preprocessado.
// caso dar erro retorna nulo
bool preProcessaArq(char nomeArquivo[] , vector<tipoGramatica>& gramatica, vector<tipoDiretiva>& diretiva);

// Recebe um arquivo presumidamente com codigo assembly inventado e cria um arquivo chamado pre_processado.txt
// Parametros o endereco do arquivo a ser preprocessado, eh necessario que os comandos e os argumentos nao estejam separados por \n
bool preProcessaArq2(char nomeArquivo[]);

//	Funcao auxiliar retira tabs duplos desnecessarios
//	Retorna a string formatada ja
std::string formataTabs(std::string formatada);

//	Funcao auxiliar retira o comentario de uma instrucao
//	Retorna a string formatada ja
std::string retiraComentarios(std::string formatada);


//	Funcao auxiliar transforma em espaços em branco em tabs
//	Retorna a string formatada ja
std::string transformaEspacoEmBranco(std::string formatada);


std::string retiraNL(std::string formatada);