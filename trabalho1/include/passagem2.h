#pragma once

#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include "tabela.h"
#include <stdlib.h>
#include <string.h>
#include "erro.h"
#include "passagem1.h"

using namespace std;

void criaArqObj(ifstream& in, ofstream& output, vector<tipoGramatica>& gramatica, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, map<string, vector<int>>& uso, map<string, int>& definicao); //Edita tabela de uso e cria arquivo com opcodes

