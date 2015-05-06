#include "../include/tabela.h"

void criaGramatica(ifstream& arq, vector<tipoGramatica>& gramatica){

    if(arq.is_open()){
        while(!arq.eof()){
            tipoGramatica aux;
            string auxQtd;

            getline(arq, aux.nome, '\t'); //leia até o primeiro tab: nome
            cout << "Nome: " << aux.nome << endl;

            arq >> aux.qtdOperandos;
            cout << "Qtd: " << aux.qtdOperandos << endl;
            arq.get(); //\t que sobrou

            getline(arq, aux.formato); //leia até final da linha: formato dos operandos
            cout << "Formato: " << aux.formato << endl;
            gramatica.push_back(aux);
        }

        arq.seekg(0); //rewind
    }else{
        cout << "O arquivo nao foi encontrado";
    }
}

void criaDiretiva(ifstream& arq, vector<tipoDiretiva>& diretiva){

    while(!arq.eof()){
        tipoDiretiva aux;
        string auxQtd;

        getline(arq, aux.nome, '\t'); //leia até o primeiro tab: nome

        arq >> aux.qtdOperandos;
        arq.get(); //\t que sobrou

        getline(arq, auxQtd, '\t'); //leia até terceiro tab: formato dos operandos
        aux.formato = auxQtd[0]; //formato 0 significa que não tem formato

        arq >> aux.tamanho;
        arq.get(); //\n que sobrou

        diretiva.push_back(aux);
    }

    arq.seekg(0); //rewind
}

void criaInstrucao(ifstream& arq, vector<tipoInstrucao>& instrucao){

    while(!arq.eof()){
        tipoInstrucao aux;
        string auxQtd;

        getline(arq, aux.nome, '\t'); //leia até o primeiro tab: nome

        arq >> aux.op;
        arq.get(); //\t que sobrou

        arq >> aux.tamanho;
        arq.get(); //\n que sobrou

        instrucao.push_back(aux);
    }

    arq.seekg(0); //rewind
}

tipoGramatica pegaGramatica(vector<tipoGramatica>& gramatica, string token){
    tipoGramatica nulo;

    for(int i = 0; i < (int)gramatica.size(); i++){
        if(strcasecmp(gramatica[i].nome.c_str(), token.c_str()) == 0)
            return gramatica[i]; //achou
    }

    nulo.nome = "";
    nulo.formato = "";
    nulo.qtdOperandos = -1;
    return nulo; //não achou
}

tipoDiretiva pegaDiretiva(vector<tipoDiretiva>& diretiva, string token){
    tipoDiretiva nulo;

    for(int i = 0; i < (int)diretiva.size(); i++){
        if(strcasecmp(diretiva[i].nome.c_str(), token.c_str()) == 0)
            return diretiva[i]; //achou
    }

    nulo.nome = "";
    nulo.formato = (char)0;
    nulo.qtdOperandos = -1;
    nulo.tamanho = -1;
    return nulo; //não achou
}

tipoInstrucao pegaInstrucao(vector<tipoInstrucao>& instrucao, string token){
    tipoInstrucao nulo;

    for(int i = 0; i < (int)instrucao.size(); i++){
        if(strcasecmp(instrucao[i].nome.c_str(), token.c_str()) == 0)
            return instrucao[i]; //achou
    }

    nulo.nome = "";
    nulo.op = -1;
    nulo.tamanho = -1;
    return nulo; //não achou
}

bool isGramatica(vector<tipoGramatica>& gramatica, string token){

    for(int i = 0; i < (int)gramatica.size(); i++){
        if(strcasecmp(gramatica[i].nome.c_str(), token.c_str()) == 0)
            return true; //achou
    }

    return false; //não achou
}

bool isDiretiva(vector<tipoDiretiva>& diretiva, string token){

    for(int i = 0; i < (int)diretiva.size(); i++){
        if(strcasecmp(diretiva[i].nome.c_str(), token.c_str()) == 0)
            return true; //achou
    }
    return false; //não achou
}

bool isInstrucao(vector<tipoInstrucao>& instrucao, string token){

    for(int i = 0; i < (int)instrucao.size(); i++){
        if(strcasecmp(instrucao[i].nome.c_str(), token.c_str()) == 0)
            return true; //achou
    }
    return false; //não achou
}
