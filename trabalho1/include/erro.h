#pragma once

#include <string>
#include <iostream>
#include "string.h"

typedef enum{
    ERRO_LEXICO = 0,
    ERRO_SINTATICO,
    ERRO_SEMANTICO,
    ERRO_REDEFINICAO,
    ERRO_DEFINIDO_ANTES,
    ERRO_INVALIDO = 5,
    ERRO_SIMBOLO_NAO_DEFINIDO ,
    ERRO_TEXT_AUSENTE,
    ERRO_BEGIN_AUSENTE,
    ERRO_USO_INCORRETO,
    ERRO_NAO_ENCONTRADO,
    ERRO_FALTA_DEFINICAO_EXTERN,
    ERRO_LOCAL_INCORRETO,
    ERRO_FALTA_ARQUIVO
}tipoErro;

using namespace std;

//0: nenhuma seção foi declarada
//d: section data
//t: section text
char getSectionAtual(); //retorna seção atual do código

void setBegin(bool s); //seta quando módulo começa a ser definido
bool getBegin(); //retorna se módulo foi definido ou não
void setEnd(bool s); //seta quando módulo termina
bool getEnd(); //retorna se módulo foi definido ou não

void imprimeErro(tipoErro e, int linha = -1); //imprime mensagem de erro. Mostra endereço de PC e linha caso seja passado
void verificaSectionText(); //Verifica se seção text foi declarada
void atualizaSection(string arg, int linha); //atualiza sectionAtual e verifica se é uma section válida

// Funcao que verifica dado um token se ele é valido lexicamente
bool isTokenValido(string token);
// Funcao que analissa lexicamente uma linha completa e retorna qual dos tokens é invalido, caso contrario retorna
// CORRETO_LEXICO
int analisaLexico(std::vector<string> tokens); 
