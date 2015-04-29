#pragma once

#include <fstream>
#include <string>
#include <vector>

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
