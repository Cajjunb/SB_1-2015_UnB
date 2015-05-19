#include "../include/erro.h"

bool sectionData = false; //global que define se seção data foi declarada
bool sectionText = false; //global que define se seção text foi declarada
char sectionAtual = (char)0; //global que diz a atual seção
bool modBegin = false; //global que diz quando um módulo começa
bool modEnd = false; //global que diz quando um módulo termina

void imprimeErro(tipoErro e, int linha){
    cout << ">>>>>ERRO: ";
    switch(e){
        case ERRO_REDEFINICAO:
            cout << "Semantico: Redefinicao de simbolos";
        break;
        case ERRO_NAO_ENCONTRADO:
            cout << "Semantico: Label nao encontrado";
        break;
        case ERRO_COMANDO_NAO_ENCONTRADO:
            cout << "Lexico: Instrucao ou diretiva nao encontrada";
        break;
        case ERRO_INVALIDO:
            cout << "Lexico: token invalido";
        break;
        case ERRO_TEXT_AUSENTE:
            cout << "Semantico: SECTION TEXT ausente";
        break;
        case ERRO_BEGIN_AUSENTE:
            cout << "Semantico: existe definicao de diretiva END, mas nao de LABEL: BEGIN";
        break;
        case ERRO_USO_INCORRETO:
            cout << "Sintatico: uso incorreto de token";
        break;
        case ERRO_LOCAL_INCORRETO:
            cout << "Semantico: token utilizado na secao incorreta";
        break;
        case ERRO_FALTA_DEFINICAO_EXTERN:
            cout << "Semantico: falta de definicoes de simbolos externos";
        break;
        case ERRO_FALTA_ARQUIVO:
            cout << "Necessario passar outro arquivo para finalizacao do processo de ligacao";
        break;
        case ERRO_DEFINIDO_ANTES:
            cout << "Semantico: simbolo ja definido em outro modulo";
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

void setBegin(bool s){
    modBegin = s;
}
void setEnd(bool s){
    modEnd = s;
}

bool getBegin(){
    return modBegin;
}
bool getEnd(){
    return modEnd;
}
