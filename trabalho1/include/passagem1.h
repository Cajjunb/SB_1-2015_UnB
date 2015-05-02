#pragma once

#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include "tabela.h"

using namespace std;

//posicoa: posi��o na mem�ria que se encontra
//externo: diz se r�tulo � externo ou n�o
typedef struct{
    int posicao;
    bool externo;
}tipoTS; //tabela de s�mbolos

void criaTS(ifstream& arq, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo); //"Retorna" tabela de s�mbolos
