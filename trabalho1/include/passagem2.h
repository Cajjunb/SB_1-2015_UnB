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

using namespace std;

//Edita tabela de uso e cria arquivo com opcodes
//retorna se arquivo precisa ser ligado ou não
bool criaArqObj(ifstream& in, ofstream& output, vector<tipoGramatica>& gramatica, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, map<string, vector<int> >& uso, map<string, int>& definicao, vector<int>& bits);
void separaOp(ofstream& out, vector<tipoInstrucao>& instrucao, vector<tipoGramatica>& gramatica, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, vector<string> vTab, int linha); //Separa linha em rótulo: instr arg

void escreveOp(ofstream& out, vector<tipoGramatica>& gramatica, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, string token, string arg, int tipo, int linha); //escreve em arquivo de acordo com instr

//	Funcao que procede todas as checagens de erros da instrução
//	Caso de algum erro retorna true, caso contrario retorna falso
bool detectarErrosInstrucao(map<string, tipoTS>& simbolo,  vector<string> vTab,vector<tipoGramatica>& gramatica , int linha);
