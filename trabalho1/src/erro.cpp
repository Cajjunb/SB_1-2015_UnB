#include "../include/erro.h"

void imprimeErro(tipoErro e, int linha){
    cout << ">>>>>ERRO: ";
    switch(e){
        case ERRO_REDEFINICAO:
            cout << "Redefinicao de simbolos";
        break;
        case ERRO_NAO_ENCONTRADO:
            cout << "Simbolo nao encontrado";
        break;
        default:
            cout << "Erro Indefinido";
        break;
    }

    if(linha > -1)
        cout << "\t linha: " << linha;
    cout << "<<<<<" << endl;
}
