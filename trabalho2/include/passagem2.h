#pragma once

#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include <locale>
#include "tabela.h"
#include <stdlib.h>
#include <string.h>
#include "erro.h"
#include "passagem1.h"
#include "ia32.h"

using namespace std;

//Edita tabela de uso e cria arquivo com opcodes
//retorna se arquivo precisa ser ligado ou não
bool criaArqObj(ifstream& in, ofstream& out, vector<tipoGramatica>& gramatica, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, map<string, vector<int> >& uso, map<string, int>& definicao, vector<int>& bits, vector<tipoInstrucaoIA32>& instrucoesIA32,map<string,tipoTSIA32>& simboloIA32);
void separaOp(ofstream& out,vector<tipoInstrucaoIA32>& instrucoesIA32,map<string,tipoTSIA32>& simboloIA32, vector<tipoInstrucao>& instrucao, vector<tipoGramatica>& gramatica, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, vector<string> vTab, int linha); //Separa linha em rótulo: instr arg

void escreveOp(ofstream& out,vector<tipoInstrucaoIA32>& instrucoesIA32,map<string, tipoTSIA32>& simboloIA32, vector<tipoGramatica>& gramatica, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, string token, string arg, int tipo, int linha); //tipo é INSTRUÇÃO = 0 ou DIRETIVA = 1

//	Funcao que procede todas as checagens de erros da instrução
//	Caso de algum erro retorna true, caso contrario retorna falso
bool detectarErrosInstrucao(map<string, tipoTS>& simbolo,  vector<string> vTab,vector<tipoGramatica>& gramatica , int linha);