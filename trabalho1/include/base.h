#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

//posicoa: posição na memória que se encontra
//externo: diz se rótulo é externo ou não
//section: diz em qual seção o rótulo percente. Aceita somente 't', SECTION TEXT, e 'd', SECTION DATA
typedef struct{
    string simbolo;
    int posicao;
    bool externo;
    int  valorConstante;
    bool tipoConstante;
    char section;
    unsigned int tamanhoMemoria;
}tipoTS; //tabela de símbolos

// Enumeracao para comportamento em relacao a constantes na gramatica
typedef enum{
	NAO_ACEITA = 'F',
	SOMENTE_SRC = 'S',
	ACEITA_TODOS = 'T'
}tipoComportamento;


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
    tipoComportamento comportamentoConstante;
}tipoGramatica;

//enumeração dos tipos de erros
typedef enum{
    ERRO_LEXICO,
    ERRO_SINTATICO,
    ERRO_SEMANTICO,
    ERRO_REDEFINICAO,
    ERRO_INVALIDO,
    ERRO_SIMBOLO_NAO_DEFINIDO ,
    ERRO_TEXT_AUSENTE,
    ERRO_DATA_AUSENTE,
    ERRO_BEGIN_AUSENTE,
    ERRO_STOP_AUSENTE,
    ERRO_USO_INCORRETO,
    ERRO_NAO_ENCONTRADO,
    ERRO_COMANDO_NAO_ENCONTRADO,
    ERRO_FALTA_DEFINICAO_EXTERN,
    ERRO_LOCAL_INCORRETO,
    ERRO_FALTA_ARQUIVO,
    ERRO_DIVISAO_POR_ZERO,
    ERRO_ALTERANDO_CONSTANTE,
    ERRO_SECTION_DATA_ANTES,
    ERRO_ACESSO_ENDERECO_NAO_RESERVADO,
    ERRO_JMP_INVALIDO,
    ERRO_OP_INVALIDO,
    ERRO_DEF_LABELS_MESMA_LINHA,
    ERRO_QTD_ARG,
    ERRO_ARG_INVALIDO,
    ERRO_ENCERRA_PROGRAMA,
    ERRO_ROTULO_REPETIDO
}tipoErro;

void explode(vector<string>& destino, string& fonte, const char* delimitador); //separa fonte por delimitador
bool isNumber(string token); //verifica se é número (inclui negativo, positivo e hexadecimal)
void toUpper(string& str,locale loc); //converte string para tudo maiúsculo
