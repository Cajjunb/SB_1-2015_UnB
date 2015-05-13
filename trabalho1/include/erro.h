#pragma once

#include <string>
#include <iostream>
#include "string.h"

typedef enum{
    ERRO_LEXICO = 0,
    ERRO_SINTATICO,
    ERRO_SEMANTICO,
    ERRO_REDEFINICAO,
    ERRO_INVALIDO,
    ERRO_TEXT_AUSENTE,
    ERRO_USO_INCORRETO,
    ERRO_NAO_ENCONTRADO
}tipoErro;

using namespace std;

//0: nenhuma seção foi declarada
//d: section data
//t: section text
char getSectionAtual(); //retorna seção atual do código

void imprimeErro(tipoErro e, int linha = -1); //imprime mensagem de erro. Mostra endereço de PC e linha caso seja passado
void verificaSectionText(); //Verifica se seção text foi declarada
void atualizaSection(string arg, int linha); //atualiza sectionAtual e verifica se é uma section válida

