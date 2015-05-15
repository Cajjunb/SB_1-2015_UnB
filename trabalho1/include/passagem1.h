#pragma once

#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include "tabela.h"
#include <stdlib.h>
#include <string.h>
#include "erro.h"
#include "base.h"

using namespace std;

//posicoa: posição na memória que se encontra
//externo: diz se rótulo é externo ou não
typedef struct{
    int posicao;
    bool externo;
}tipoTS; //tabela de símbolos

void editaDefinicao(map<string, int>& definicao, string token, int endereco); //Edita endereço na tabela de definição baseado no token
void editaUso(map<string, vector<int>>& uso, string token, int endereco); //Adiciona na tabela de uso o valor do endereço baseado no token

void insereDefinicao(map<string, int>& definicao, string& token, int linha); //insere na tabela de definição
void insereUso(map<string, vector<int>>& uso, string& token, int linha); //Insere na tabela de uso
void insereSimbolo(map<string, tipoTS>& simbolo, string& token, int linha); //Insere na tabela de símbolos

int calculaPC(vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, vector<int>>& uso, string token, int linha, vector<string>& vTab, int endereco); //Baseado na intrução ou diretiva, calcula pc

void criaTabelas(ifstream& arq, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, map<string, vector<int>>& uso, map<string, int>& definicao); //Cria tabelas de símbolos, de definição e de uso

void separaSectionArgs(vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, vector<string>& vTab, int linha); //Prepara argumentos de section para atualizar section atual
