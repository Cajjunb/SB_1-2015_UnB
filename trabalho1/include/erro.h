#pragma once

#include <string>
#include <iostream>

typedef enum{
    ERRO_LEXICO = 0,
    ERRO_SINTATICO,
    ERRO_SEMANTICO,
    ERRO_REDEFINICAO,
    ERRO_NAO_ENCONTRADO
}tipoErro;

using namespace std;

void imprimeErro(tipoErro e, int endereco = -1, int linha = -1); //imprime mensagem de erro. Mostra endereço de PC e linha caso seja passado
