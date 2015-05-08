#pragma once

#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include "tabela.h"
#include <stdlib.h>
#include <string.h>
#include "erro.h"

using namespace std;

//posicoa: posi��o na mem�ria que se encontra
//externo: diz se r�tulo � externo ou n�o
typedef struct{
    int posicao;
    bool externo;
}tipoTS; //tabela de s�mbolos

void editaDefinicao(map<string, int>& definicao, string token, int endereco); //Edita endere�o na tabela de defini��o baseado no token
void editaUso(map<string, vector<int>>& uso, string token, int endereco); //Adiciona na tabela de uso o valor do endere�o baseado no token

void insereDefinicao(map<string, int>& definicao, string& token, int linha); //insere na tabela de defini��o
void insereUso(map<string, vector<int>>& uso, string& token, int linha); //Insere na tabela de uso
void insereSimbolo(map<string, tipoTS>& simbolo, string& token, int linha); //Insere na tabela de s�mbolos

int calculaPC(vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, vector<int>>& uso, string token, int linha, vector<string> vTab, int endereco); //Baseado na intru��o ou diretiva, calcula pc

void criaTabelas(ifstream& arq, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, map<string, vector<int>>& uso, map<string, int>& definicao); //Cria tabelas de s�mbolos, de defini��o e de uso
