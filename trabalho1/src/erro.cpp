#include "../include/erro.h"

bool sectionData = false; //global que define se seção data foi declarada
bool sectionText = false; //global que define se seção text foi declarada
char sectionAtual = (char)0; //global que diz a atual seção

void imprimeErro(tipoErro e, int linha){
    cout << ">>>>>ERRO: ";
    switch(e){
        case ERRO_REDEFINICAO:
            cout << "Semantico: Redefinicao de simbolos";
        break;
        case ERRO_NAO_ENCONTRADO:
            cout << "Semantico: Simbolo nao encontrado";
        break;
        case ERRO_INVALIDO:
            cout << "Lexico: token invalido";
        break;
        case ERRO_TEXT_AUSENTE:
            cout << "Sintatico: secao TEXT ausente";
        break;
        case ERRO_USO_INCORRETO:
            cout << "Semantico: uso incorreto de token";
        break;
        default:
            cout << "Erro Indefinido";
        break;
    }

    if(linha > -1)
        cout << "\t linha: " << linha;
    cout << "<<<<<" << endl;
}

void verificaSectionText(){
    if(!sectionText)
        imprimeErro(ERRO_TEXT_AUSENTE);
}

void atualizaSection(string arg, int linha){
    if(strcasecmp("DATA", arg.c_str()) == 0){
        if(!sectionData){
            sectionData = true;
            sectionAtual = 'd';
        }
        else
            imprimeErro(ERRO_REDEFINICAO, linha);
    }
    else if(strcasecmp("TEXT", arg.c_str()) == 0){
        if(!sectionText){
            sectionText = true;
            sectionAtual = 't';
        }
        else
            imprimeErro(ERRO_REDEFINICAO, linha);
    }
    else
        imprimeErro(ERRO_INVALIDO, linha);
}

char getSectionAtual(){
    return sectionAtual;
}
