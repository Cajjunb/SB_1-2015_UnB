#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <iostream>
#include <sstream>
#include "base.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;



void criaGramatica(ifstream& arq, vector<tipoGramatica>& gramatica); //"Retorna" vetor com as regras da gramática a partir de um txt
void criaDiretiva(ifstream& arq, vector<tipoDiretiva>& diretiva); //"Retorna" vetor com regras das diretivas a partir de um txt
void criaInstrucao(ifstream& arq, vector<tipoInstrucao>& instrucao); //"Retorna" vetor de instruções válidas a partir de um txt
void  criaInstrucaoIa32(ifstream& arq, vector<tipoInstrucaoIA32>& instrucaoIA32); // Cria um vetor e instrucoes ia 32 mapeadas com assembly inventado

tipoGramatica pegaGramatica(vector<tipoGramatica>& gramatica, string token); //Retorna struct gramática correspondente ao token. Retorna struct nula se não achar
tipoDiretiva pegaDiretiva(vector<tipoDiretiva>& diretiva, string token); //Retorna struct diretiva correspondente ao token. Retorna struct nula se não achar
tipoInstrucao pegaInstrucao(vector<tipoInstrucao>& instrucao, string token); //Retorna struct instrucao correspondente ao token. Retorna struct nula se não achar
tipoInstrucaoIA32 pegaInstrucaoIA32(vector<tipoInstrucaoIA32>& instrucao, string token); //Retorna struct instrucao correspondente ao token. Retorna struct nula se não achar
tipoInstrucao pegaInstrucaoOpcode(vector<tipoInstrucao>& instrucao, int op); //Retorna struct instrucao correspondente ao opcode. Retorna struct nula se não achar



//  A função que faz uma busca entre tabelas inventado e ia 32 e retorna o código em formato string do código ia 32 do inventado passado
string inventadoParaIA32(vector<tipoInstrucaoIA32>& instrucoes,string operacao,std::vector<string> argumentos);
//  A função que faz uma busca entre tabelas inventado e ia 32 e retorna o código em formato string do código maquina do inventado passado
string inventadoParaMaquina(std::vector<tipoInstrucaoIA32>& instrucoesia32 ,string operacao,std::vector<int> argumentos);

bool isGramatica(vector<tipoGramatica>& gramatica, string token); //Retorna se token é gramatica
bool isDiretiva(vector<tipoDiretiva>& diretiva, string token); //Retorna se token é diretiva
bool isInstrucao(vector<tipoInstrucao>& instrucao, string token); //Retorna se token é instrução
bool isInstrucaoIA32(vector<tipoInstrucaoIA32>& instrucao, string token); //Retorna se token é instrução

