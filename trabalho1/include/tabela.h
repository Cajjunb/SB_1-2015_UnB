#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

//nome: nome da instrução
//op: código da instrução
//tamanho: quanto que aquela instrução ocupada na memória (decimal)
typedef struct{
    string nome;
    int op, tamanho;
}tipoInstrucao;

//nome: nome da diretiva
//formato: como que a diretiva deve ser usada
//  S: uma string
//      não é permitido uso de espaços
//  N: um número (decimal ou hexadecimal)
//      número hexadecimal é indicado por 0x<hexadecimal>
//qtdOperandos: quantidades de operandos aceitos
//tamanho: quanto que aquela diretiva ocupa na memória
typedef struct{
    string nome;
    char formato;
    int qtdOperandos, tamanho;
}tipoDiretiva;

//nome: nome da instrução
//formato: como que a instrução deve ser escrita
//  R indica label
//qtdOperandos: quantidade de operandos aceitos
typedef struct{
    string nome, formato;
    int qtdOperandos;
}tipoGramatica;

void criaGramatica(ifstream& arq, vector<tipoGramatica>& gramatica); //"Retorna" vetor com as regras da gramática a partir de um txt
void criaDiretiva(ifstream& arq, vector<tipoDiretiva>& diretiva); //"Retorna" vetor com regras das diretivas a partir de um txt
void criaInstrucao(ifstream& arq, vector<tipoInstrucao>& instrucao); //"Retorna" vetor de instruções válidas a partir de um txt

tipoGramatica pegaGramatica(vector<tipoGramatica>& gramatica, string token); //Retorna struct gramática correspondente ao token. Retorna struct nula se não achar
tipoDiretiva pegaDiretiva(vector<tipoDiretiva>& diretiva, string token); //Retorna struct diretiva correspondente ao token. Retorna struct nula se não achar
tipoInstrucao pegaInstrucao(vector<tipoInstrucao>& instrucao, string token); //Retorna struct instrucao correspondente ao token. Retorna struct nula se não achar
tipoInstrucao pegaInstrucaoOpcode(vector<tipoInstrucao>& instrucao, int op); //Retorna struct instrucao correspondente ao opcode. Retorna struct nula se não achar

bool isGramatica(vector<tipoGramatica>& gramatica, string token); //Retorna se token é gramatica
bool isDiretiva(vector<tipoDiretiva>& diretiva, string token); //Retorna se token é diretiva
bool isInstrucao(vector<tipoInstrucao>& instrucao, string token); //Retorna se token é instrução
