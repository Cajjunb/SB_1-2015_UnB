#include "../include/passagem1.h"

void insereSimbolo(map<string, tipoTS>& simbolo, string& token, tipoTS s, int linha){

    if(simbolo.find(token) == simbolo.end()){ //se não existe símbolo na tabela
        simbolo.insert(pair<string, tipoTS>(token, s)); //insere no map
    }
    else
         imprimeErro(ERRO_REDEFINICAO, s.posicao, linha);
}

void insereUso(map<string, vector<int>>& uso, string& token, int linha){
    vector<int> fim;

    fim.push_back(-1);
    if(uso.find(token) == uso.end()){
        uso.insert(pair<string, vector<int>>(token, fim)); //se endereco  = -1, então chegou a última chamada deste rótulo
    }
    else
        imprimeErro(ERRO_REDEFINICAO, -1, linha);
}

void insereDefinicao(map<string, int>& definicao, string& token, int endereco, int linha){
    if(definicao.find(token) == definicao.end()){
        definicao.insert(pair<string, int>(token, endereco)); //se endereco  = -1, então ainda nao foi definido endereco
    }
    else
        imprimeErro(ERRO_REDEFINICAO, endereco, linha);
}

void editaUso(map<string, vector<int>>& uso, string token, int endereco, int linha){

    for (map<string, vector<int>>::iterator it = uso.begin(); it != uso.end(); ++it){
        if(strcasecmp(it->first.c_str(), token.c_str()) == 0){
            vector<int> add = it->second;
            add.push_back(endereco);
            break;
        }
    }

    imprimeErro(ERRO_NAO_ENCONTRADO, endereco, linha);

}

void editaDefinicao(map<string, int>& definicao, string token, int endereco, int linha){

    for (map<string, int>::iterator it = definicao.begin(); it != definicao.end(); ++it){
        if(strcasecmp(it->first.c_str(), token.c_str()) == 0){
            it->second = endereco;
            break;
        }
    }

}

int calculaPC(vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, string token, int linha, vector<string> vTab){

    if(isDiretiva(diretiva, token)){
        tipoDiretiva d;
        d = pegaDiretiva(diretiva, token);
        if(d.tamanho == -1){ //se tamanho == -1, então deve ter argumento dizendo o tamanho
            //LABEL:    SPACE   N
            //vTab[0]   vTab[1] vTab[2]
            if(vTab[2].empty())
                return 1; //Não tem argumentos
            else
                return atoi(vTab[2].c_str()); //transforma argumento em número
        }
        return d.tamanho;
    }
    else if(isInstrucao(instrucao, token)){
        tipoInstrucao i;
        i = pegaInstrucao(instrucao, token);
        return i.tamanho;
    }

    imprimeErro(ERRO_NAO_ENCONTRADO, -1, linha);
    return 0;
}

void criaTabelas(ifstream& arq, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, map<string, vector<int>>& uso, map<string, int>& definicao){
    int pc = 0;
    int i = 0; //contador de linhas
    string linha;

    while(getline(arq, linha)){
        i++; //leu uma linha
        vector<string> vTab;
        int tamanho;

        string::size_type pos = 0;
        string::size_type prev = 0;
        while ((pos = linha.find('\t', prev)) != string::npos){ //enquanto cada \t encontrando não for uma posição inválida da string
            vTab.push_back(linha.substr(prev, pos - prev)); //adicione no vetor de tabs a substring de onde este tab foi encontrado até o começo
            prev = pos + 1;
        }
        vTab.push_back(linha.substr(prev)); //coloque a última subdivisão de tab

        //Se a primeira string tiver :, é definição de rótulo
        tamanho = vTab[0].size();
        if(vTab[0][tamanho - 1] == ':'){
            tipoTS s;
            vTab[0][vTab[0].size() - 1] = '\0'; //eliminando :

            if(strcasecmp(vTab[1].c_str(), "EXTERN") == 0){ //Se a próxima string for extern, então insere na tabela de uso
                insereUso(uso, vTab[0], i);
                s.posicao = 0;
                s.externo = true;
            }
            else{
                s.posicao = pc;
                s.externo = false;
            }
            insereSimbolo(simbolo, vTab[0], s, i);
            editaDefinicao(definicao, vTab[0], s.posicao, i); //atualize endereço em TD caso símbolo esteja em TD

            //inserido rótulo, calcula PC
            pc += calculaPC(instrucao, diretiva, vTab[1], i, vTab);
        }
        else{ //somente calcula o pc
            if(strcasecmp(vTab[0].c_str(), "PUBLIC") == 0) //Se diretiva for PUBLIC, insere na tabela de definição
                insereDefinicao(definicao, vTab[1], 0, i);
            pc += calculaPC(instrucao, diretiva, vTab[0], i, vTab);
        }

    }

    arq.seekg(0); //rewind
}
