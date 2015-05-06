#include "../include/erro.h"

void imprimeErro(tipoErro e, int endereco, int linha){
    cout << "------ERRO------ " << endl;
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
    if(endereco > -1)
        cout << "\t endereco: " << endereco;
    cout << endl;
}
