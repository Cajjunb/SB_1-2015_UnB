#include "../include/passagem1.h"

void insereSimbolo(map<string, tipoTS>& simbolo, string& token, tipoTS s, int linha){

    if(simbolo.find(token) == simbolo.end()){ //se n�o existe s�mbolo na tabela
        simbolo.insert(pair<string, tipoTS>(token, s)); //insere no map
    }
    else
         imprimeErro(ERRO_REDEFINICAO, linha);
}

void insereUso(map<string, vector<int>>& uso, string& token, int linha){
    vector<int> fim;

    fim.push_back(-1);
    if(uso.find(token) == uso.end()){
        uso.insert(pair<string, vector<int>>(token, fim)); //se endereco  = -1, ent�o chegou a �ltima chamada deste r�tulo
    }
    else
        imprimeErro(ERRO_REDEFINICAO,linha);
}

void insereDefinicao(map<string, int>& definicao, string& token, int endereco, int linha){
    if(definicao.find(token) == definicao.end()){
        definicao.insert(pair<string, int>(token, endereco)); //se endereco  = -1, ent�o ainda nao foi definido endereco
    }
    else
        imprimeErro(ERRO_REDEFINICAO, linha);
}

void editaDefinicao(map<string, int>& definicao, string token, int endereco){

    for (map<string, int>::iterator it = definicao.begin(); it != definicao.end(); ++it){
        if(strcasecmp(it->first.c_str(), token.c_str()) == 0){
            it->second = endereco;
            break;
        }
    }

}

void editaUso(map<string, vector<int>>& uso, string token, int endereco){

    for (map<string, vector<int>>::iterator it = uso.begin(); it != uso.end(); ++it){
        if(strcasecmp(it->first.c_str(), token.c_str()) == 0){
            it->second.push_back(endereco);
            break;
        }
    }

}


int calculaPC(vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, vector<int>>& uso, string token, int linha, vector<string> vTab, int endereco){

    if(isDiretiva(diretiva, token)){
        tipoDiretiva d;
        d = pegaDiretiva(diretiva, token);
        if(d.tamanho == -1){ //se tamanho == -1, ent�o deve ter argumento dizendo o tamanho
            //LABEL:    SPACE   N
            //vTab[0]   vTab[1] vTab[2]
            if(vTab.size() == 3)
                return atoi(vTab[2].c_str()); //transforma argumento em n�mero
            else
                return 1; //N�o tem argumentos
        }
        return d.tamanho;
    }
    else if(isInstrucao(instrucao, token)){
        tipoInstrucao i;
        size_t found; //verifica se string/char � encontrada
        string aux; //string auxiliar que cont�m argumentos
        int endAux = endereco; //endere�o auxiliar (o tamanho de uma instru��o leva em considera��o seus argumentos, ent�o cada argumento +1 no endere�o)
        vector<string> copyArg; //vetor de string para conter argumentos que est�o separados por v�rgula ou por +

        i = pegaInstrucao(instrucao, token);

        aux.append(vTab[1]); //Sup�e formato INSTR   ARG
        if(vTab.size() == 3){ //est� no formato: LABEL:  INSTR   ARG
            aux.clear();
            aux.append(vTab[2]);
        }

        found = aux.find(", "); //verifica se acha, no argumento, a string ", "
        if(found != string::npos){ //Achou um Copy. Aux est� na forma "LABEL, LABEL"
            string::size_type pos = 0;
            string::size_type prev = 0;
            while ((pos = aux.find(", ", prev)) != string::npos){ //enquanto cada ", " encontrando n�o for uma posi��o inv�lida da string
                copyArg.push_back(aux.substr(prev, pos - prev)); //adicione no vetor de tabs a substring de onde este tab foi encontrado at� o come�o
                prev = pos + 2; //pula duas posi��es
            }
            copyArg.push_back(aux.substr(prev)); //coloque a �ltima subdivis�o
            for (vector<string>::iterator it = copyArg.begin() ; it != copyArg.end(); ++it){ //retirandos strings vazias
                if((*it).empty())
                    vTab.erase(it);
            }
        }

        do{
            endAux++;
            if(!copyArg.empty()){ //enquanto copyArg tiver argumentos
                aux.clear();
                aux.append(copyArg.front());
                copyArg.erase(copyArg.begin());
            }
            map<string, vector<int>>::iterator it = uso.find(aux);

            if(it == uso.end()){
                //NAO DESISTE, AINDA PODE ESTAR: INSTR LABEL + N�MERO
                size_t found = aux.find("+");

                if(found != string::npos){
                    //subdivide a string de alguma forma

                }
                 //se n�o tiver achado, ent�o n�o tem mesmo
            }
            else{

                editaUso(uso, aux, endAux);
            }
        }while(copyArg.size() > 0);


        return i.tamanho;
    }

    imprimeErro(ERRO_NAO_ENCONTRADO, linha);
    return 0;
}

void criaTabelas(ifstream& arq, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, map<string, vector<int>>& uso, map<string, int>& definicao){
    int pc = 0;
    int i = 0; //contador de linhas
    string linha;

    while(getline(arq, linha)){
        i++; //leu uma linha
        vector<string> vTab;
        string aux;
        int tamanho;

        string::size_type pos = 0;
        string::size_type prev = 0;
        while ((pos = linha.find('\t', prev)) != string::npos){ //enquanto cada \t encontrando n�o for uma posi��o inv�lida da string
            vTab.push_back(linha.substr(prev, pos - prev)); //adicione no vetor de tabs a substring de onde este tab foi encontrado at� o come�o
            prev = pos + 1;
        }
        vTab.push_back(linha.substr(prev)); //coloque a �ltima subdivis�o de tab
        for (vector<string>::iterator it = vTab.begin() ; it != vTab.end(); ++it){ //retirandos strings vazias
            if((*it).empty())
                vTab.erase(it);
        }
        //Se a primeira string tiver :, � defini��o de r�tulo
        tamanho = vTab[0].size();
        if(vTab[0][tamanho - 1] == ':'){
            tipoTS s;
            vTab[0] = vTab[0].substr(0, tamanho - 1); //eliminando :

            if(strcasecmp(vTab[1].c_str(), "EXTERN") == 0){ //Se a pr�xima string for extern, ent�o insere na tabela de uso
                insereUso(uso, vTab[0], i);
                s.posicao = 0;
                s.externo = true;
            }
            else{
                s.posicao = pc;
                s.externo = false;
            }
            insereSimbolo(simbolo, vTab[0], s, i);
            editaDefinicao(definicao, vTab[0], i); //atualize endere�o em TD caso s�mbolo esteja em TD

            //inserido r�tulo, calcula PC
            aux.append(vTab[1]);
        }
        else{ //somente calcula o pc
            if(strcasecmp(vTab[0].c_str(), "PUBLIC") == 0) //Se diretiva for PUBLIC, insere na tabela de defini��o
                insereDefinicao(definicao, vTab[1], pc, i);
            aux.append(vTab[0]);
        }

        pc += calculaPC(instrucao, diretiva, uso, aux, i, vTab, pc);

    }

    arq.seekg(0, arq.beg); //rewind
}
