#pragma once

#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include "tabela.h"

using namespace std;

//posicoa: posição na memória que se encontra
//externo: diz se rótulo é externo ou não
typedef struct{
    int posicao;
    bool externo;
}tipoTS; //tabela de símbolos

void criaTS(ifstream& arq, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo); //"Retorna" tabela de símbolos
