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
#include "base.h"

using namespace std;


void editaDefinicao(map<string, int>& definicao, string token, int endereco); //Edita endere�o na tabela de defini��o baseado no token
void editaUso(map<string, vector<int> >& uso, string token, int endereco); //Adiciona na tabela de uso o valor do endere�o baseado no token

void insereDefinicao(map<string, int>& definicao, string& token, int linha); //insere na tabela de defini��o
void insereUso(map<string, vector<int> >& uso, string& token, int linha); //Insere na tabela de uso
void insereSimbolo(map<string, tipoTS>& simbolo, string& token, int linha); //Insere na tabela de s�mbolos
void editaTamanhoSimbolo(map<string, tipoTS>& simbolo, string& token, unsigned int tamanhoMemoria); // Edita o valor da memoria alocada para aquele simbolo em especifico

//	Verifica se o simbolo est� na tabela de simbolos
//	Retorna bool
bool isSimbolo(map<string, tipoTS>& simbolo, string& token);

int calculaPC(vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, vector<int> >& uso, string token, int linha, vector<string>& vTab, int endereco, vector<int>& bits); //Baseado na intru��o ou diretiva, calcula pc

void criaTabelas(ifstream& arq, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, map<string, vector<int> >& uso, map<string, int>& definicao, vector<int>& bits); //Cria tabelas de s�mbolos, de defini��o e de uso

void separaSectionArgs(vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, vector<string>& vTab, int linha); //Prepara argumentos de section para atualizar section atual
