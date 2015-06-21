#include "../include/tabela.h"

void criaGramatica(ifstream& arq, vector<tipoGramatica>& gramatica){

    if(!arq.is_open()){
        cout << "ERRO: O arquivo de tabelas nao foi encontrado. Encerrando" << endl;
        exit(EXIT_FAILURE);
    }
    while(!arq.eof()){
        tipoGramatica aux;
        string auxQtd;

        getline(arq, aux.nome, '\t'); //leia até o primeiro tab: nome

        arq >> aux.qtdOperandos;
        arq.get(); //\t que sobrou
        string auxChar ;

        getline(arq, auxChar, '\t'); //leia até o primeiro tab: comportamentoConstante
        aux.comportamentoConstante = (tipoComportamento) auxChar[0];               // DA CAST PARA DAR MATCH COM O TIPO DE DADO ENUMERADO

        getline(arq, aux.formato); //leia até final da linha: formato dos operandos
        gramatica.push_back(aux);
    }
    arq.clear();
    arq.seekg(0, arq.beg); //rewind
}

void  criaInstrucaoIa32(ifstream& arq, vector<tipoInstrucaoIA32>& instrucaoIA32){
    if(!arq.is_open()){
        cout << "ERRO: O arquivo de tabelas nao foi encontrado. Encerrando" << endl;
        exit(EXIT_FAILURE);
    }
    while(!arq.eof()){
        tipoInstrucaoIA32 instrucaoNova;
        string bufferDoArquivo ; 
        std::vector<string> bufferSegmentado;
        std::vector<string>::iterator it;
        int i ;
        int nro_argumentos;
        int tamanhoTotal = 0;
        getline(arq,bufferDoArquivo,'\n');
        explode(bufferSegmentado,bufferDoArquivo,";");
        instrucaoNova.nome = bufferSegmentado[0].c_str();
        instrucaoNova.tipo = (tipoComportamentoTraducao) bufferSegmentado[1].c_str()[0];
        if(instrucaoNova.tipo == tipoComportamentoTraducao::SINGLE)
            instrucaoNova.nroInstrucoes = 1;
        else if(instrucaoNova.tipo == tipoComportamentoTraducao::DOUBLE)
            instrucaoNova.nroInstrucoes = 2;
        else if(instrucaoNova.tipo == tipoComportamentoTraducao::TRIPLE)
            instrucaoNova.nroInstrucoes = 3;
        else if(instrucaoNova.tipo == tipoComportamentoTraducao::QUADRUPLE)
            instrucaoNova.nroInstrucoes = 4;
        nro_argumentos = instrucaoNova.nroInstrucoes;
        for (i = 0;i < nro_argumentos;i++){
            instrucaoNova.instrucaoAssembly.push_back(bufferSegmentado[i+2].c_str());
        }
        for ( i = 0; i < nro_argumentos; i++){
            instrucaoNova.instrucaoCodigoMaquina.push_back(bufferSegmentado[nro_argumentos+2+i].c_str());
            printf("%s\n",instrucaoNova.instrucaoCodigoMaquina[i].c_str() );
        }
        for ( i = nro_argumentos+2+i; i < bufferSegmentado.size(); ++i){
            tamanhoTotal += std::stoi( bufferSegmentado[i].c_str());
        }
        instrucaoNova.tamanhoTotal = tamanhoTotal;
        instrucaoIA32.push_back(instrucaoNova);
    }
    arq.clear();
    arq.seekg(0, arq.beg); //rewind
}


void criaDiretiva(ifstream& arq, vector<tipoDiretiva>& diretiva){

    if(!arq.is_open()){
        cout << "ERRO: O arquivo de tabelas nao foi encontrado. Encerrando" << endl;
        exit(EXIT_FAILURE);
    }
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
    arq.clear();
    arq.seekg(0, arq.beg); //rewind
}

void criaInstrucao(ifstream& arq, vector<tipoInstrucao>& instrucao){

    if(!arq.is_open()){
        cout << "ERRO: O arquivo de tabelas nao foi encontrado. Encerrando" << endl;
        exit(EXIT_FAILURE);
    }

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
    arq.clear();
    arq.seekg(0, arq.beg); //rewind
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

tipoInstrucao pegaInstrucaoOpcode(vector<tipoInstrucao>& instrucao, int op){
    tipoInstrucao nulo;

    for(int i = 0; i < (int)instrucao.size(); i++){
        if(instrucao[i].op == op)
            return instrucao[i]; //achou
    }

    nulo.nome = "";
    nulo.op = -1;
    nulo.tamanho = -1;
    return nulo; //não achou
}

tipoInstrucaoIA32 pegaInstrucaoIA32(vector<tipoInstrucaoIA32>& instrucao, string token){
    tipoInstrucaoIA32 nulo;

    for(int i = 0; i < (int)instrucao.size(); i++){
        if(strcasecmp(instrucao[i].nome.c_str(), token.c_str()) == 0)
            return instrucao[i]; //achou
    }
    nulo.nome = "";
    nulo.tamanhoTotal = -1;
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


bool isInstrucaoIA32(vector<tipoInstrucaoIA32>& instrucao, string token){
    for(int i = 0; i < (int)instrucao.size(); i++){
        if(strcasecmp(instrucao[i].nome.c_str(), token.c_str()) == 0)
            return true; //achou
    }
    return false; //não achou
}