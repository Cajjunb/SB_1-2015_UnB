#include "../include/passagem1.h"

void insereSimbolo(map<string, tipoTS>& simbolo, string& token, tipoTS s, int linha){

    if(simbolo.find(token) == simbolo.end()){ //se não existe símbolo na tabela
        simbolo.insert(pair<string, tipoTS>(token, s)); //insere no map
    }
    else
         imprimeErro(ERRO_REDEFINICAO, linha);
}

void insereUso(map<string, vector<int>>& uso, string& token, int linha){
    vector<int> fim;

    fim.clear();
    if(uso.find(token) == uso.end()){
        uso.insert(pair<string, vector<int>>(token, fim)); //se endereco  = -1, então chegou a última chamada deste rótulo
    }
    else
        imprimeErro(ERRO_REDEFINICAO,linha);
}

void insereDefinicao(map<string, int>& definicao, string& token, int endereco, int linha){
    if(definicao.find(token) == definicao.end()){
        definicao.insert(pair<string, int>(token, endereco)); //se endereco  = -1, então ainda nao foi definido endereco
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

void separaSectionArgs(vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, vector<string>& vTab, int linha){
    if(!isDiretiva(diretiva, vTab[0]) && !isInstrucao(instrucao, vTab[0])){ //se o primeiro troço da linha não for diretiva nem instrução, então é rótulo
        //Se é rótulo e o token é SECTION, então está na forma
        //LABEL:    SECTION ARG
        //vTab[0]   vTab[1] vTab[2]
        if(vTab.size() == 3)
            atualizaSection(vTab[2], linha);
        else
            imprimeErro(ERRO_USO_INCORRETO, linha);
    }
    else{
    //está na forma
    //SECTION   ARG
        if(vTab.size() == 2)
            atualizaSection(vTab[1], linha);
        else
            imprimeErro(ERRO_USO_INCORRETO, linha);

    }
}

int calculaPC(vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, vector<int>>& uso, string token, int linha, vector<string>& vTab, int endereco){

    if(isDiretiva(diretiva, token)){
        tipoDiretiva d;
        d = pegaDiretiva(diretiva, token);

        if(getEnd())
            imprimeErro(ERRO_LOCAL_INCORRETO, linha);

        if(d.tamanho == -1){ //se tamanho == -1, então deve ter argumento dizendo o tamanho
            //LABEL:    SPACE   N
            //vTab[0]   vTab[1] vTab[2]
            if(vTab.size() == 3)
                return atoi(vTab[2].c_str()); //transforma argumento em número
            else
                return 1; //Não tem argumentos
        }

        if(d.nome.compare("SECTION") == 0)
            separaSectionArgs(instrucao, diretiva, vTab, linha);
        else if(d.nome.compare("BEGIN") == 0){ //se for diretiva BEGIN
            if(getSectionAtual() == 'd') //e estiver na seção dados
                imprimeErro(ERRO_LOCAL_INCORRETO, linha); //ERRO
            setBegin(true);
            setEnd(false);
        }
        else if(d.nome.compare("END") == 0){ //se for diretiva END
            if(getBegin())
                setBegin(false);
            else
                imprimeErro(ERRO_BEGIN_AUSENTE, linha);
            setEnd(true);
        }

        return d.tamanho;
    }
    else if(isInstrucao(instrucao, token)){
        tipoInstrucao i;
        string aux; //string auxiliar que contém argumentos
        int endAux = endereco; //endereço auxiliar (o tamanho de uma instrução leva em consideração seus argumentos, então cada argumento +1 no endereço)
        vector<string> copyArg; //vetor de string para conter argumentos que estão separados por vírgula ou por +

        if(getSectionAtual() == 'd' || getEnd())
            imprimeErro(ERRO_LOCAL_INCORRETO, linha);

        i = pegaInstrucao(instrucao, token);

        if(vTab.size() > 1){

            aux.append(vTab[1]); //Supõe formato INSTR   ARG
            if(vTab.size() == 3){ //está no formato: LABEL:  INSTR   ARG
                aux.clear();
                aux.append(vTab[2]);
            }

            //cout << aux << endl();
            explode(copyArg, aux, ", "); //procura se na string aux tem copy
            do{
                endAux++;
                if(!copyArg.empty()){ //enquanto copyArg tiver argumentos
                    aux.clear();
                    aux.append(copyArg.front());
                    copyArg.erase(copyArg.begin());
                }
                map<string, vector<int>>::iterator it = uso.find(aux);

                if(it == uso.end()){
                    //NAO DESISTE, AINDA PODE ESTAR: INSTR LABEL + NÚMERO
                    size_t found = aux.find("+");

                    if(found != string::npos){
                        //subdivide a string de alguma forma
                        vector<string> somaEndereco;
                        explode(somaEndereco, aux, "+");

                        it = uso.find(somaEndereco[0]);
                        //cout << somaEndereco[0];
                        //cin.get();

                        if(it != uso.end())
                            editaUso(uso, somaEndereco[0], endAux);

                    }
                     //se não tiver achado, então não tem mesmo
                }
                else{

                    editaUso(uso, aux, endAux);
                }
            }while(copyArg.size() > 0);
        }

        return i.tamanho;
    }

    imprimeErro(ERRO_NAO_ENCONTRADO, linha);
    return 0;
}

void criaTabelas(ifstream& arq, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, map<string, vector<int>>& uso, map<string, int>& definicao){
    int pc = 0;
    int i; //contador de linhas
    string linha;

    while(getline(arq, linha)){
        vector<string> vTab;
        string aux;
        int tamanho;

        //cout << linha << endl;
        explode(vTab, linha, "\t");

        i = (int)strtol(vTab.back().c_str(), NULL, 10); //último elemento desta linha informa a linha no arquivo anterior
        vTab.pop_back(); //retira esse elemento

        //Se a primeira string tiver :, é definição de rótulo
        tamanho = vTab[0].size();

        if(vTab[0][tamanho - 1] == ':'){
            tipoTS s;
            vTab[0] = vTab[0].substr(0, tamanho - 1); //eliminando :

            if(strcasecmp(vTab[1].c_str(), "EXTERN") == 0){ //Se a próxima string for extern, então insere na tabela de uso
                if(!getBegin() || getEnd()) //se begin não tiver sido definido
                    imprimeErro(ERRO_LOCAL_INCORRETO, i);
                insereUso(uso, vTab[0], i);
                s.posicao = 0;
                s.externo = true;
            }
            else{
                s.posicao = pc;
                s.externo = false;
            }
            insereSimbolo(simbolo, vTab[0], s, i);
            editaDefinicao(definicao, vTab[0], i); //atualize endereço em TD caso símbolo esteja em TD

            //inserido rótulo, calcula PC
            aux.append(vTab[1]);
        }
        else{ //somente calcula o pc
            if(strcasecmp(vTab[0].c_str(), "PUBLIC") == 0){ //Se diretiva for PUBLIC, insere na tabela de definição
                insereDefinicao(definicao, vTab[1], pc, i);
                if(!getBegin() || getEnd()) //se begin não tiver sido definido
                    imprimeErro(ERRO_LOCAL_INCORRETO, i);
            }
            if(strcasecmp(vTab[0].c_str(), "BEGIN") == 0) //Begin DEVE ter um rótulo
                imprimeErro(ERRO_USO_INCORRETO, i);
            aux.append(vTab[0]);
        }

        pc += calculaPC(instrucao, diretiva, uso, aux, i, vTab, pc);

    }

    verificaSectionText(); //verifica se o arquivo terminou declarando uma seção text

    arq.clear();
    arq.seekg(0, arq.beg); //rewind
}
