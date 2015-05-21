#include "../include/passagem1.h"

void insereSimbolo(map<string, tipoTS>& simbolo, string& token, tipoTS s, int linha){
    if(simbolo.find(token) == simbolo.end()){ //se n�o existe s�mbolo na tabela
        simbolo.insert(pair<string, tipoTS>(token, s)); //insere no map
    }
    else
         imprimeErro(ERRO_REDEFINICAO, linha);
}

bool isSimbolo(map<string, tipoTS>& simbolo, string& token){
    if(simbolo.find(token) == simbolo.end())
        return true;
    else
        return false;
}

void insereUso(map<string, vector<int>>& uso, string& token, int linha){
    vector<int> fim;

    fim.clear();
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

void separaSectionArgs(vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, vector<string>& vTab, int linha){
    if(!isDiretiva(diretiva, vTab[0]) && !isInstrucao(instrucao, vTab[0])){ //se o primeiro tro�o da linha n�o for diretiva nem instru��o, ent�o � r�tulo
        //Se � r�tulo e o token � SECTION, ent�o est� na forma
        //LABEL:    SECTION ARG
        //vTab[0]   vTab[1] vTab[2]
        if(vTab.size() == 3)
            atualizaSection(vTab[2], linha);
        else
            imprimeErro(ERRO_USO_INCORRETO, linha);
    }
    else{
    //est� na forma
    //SECTION   ARG
        if(vTab.size() == 2)
            atualizaSection(vTab[1], linha);
        else
            imprimeErro(ERRO_USO_INCORRETO, linha);

    }
}

int calculaPC(vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, vector<int>>& uso, string token, int linha, vector<string>& vTab, int endereco, vector<int>& bits){

    if(isDiretiva(diretiva, token)){
        tipoDiretiva d;
        d = pegaDiretiva(diretiva, token);

        if(getEnd())
            imprimeErro(ERRO_LOCAL_INCORRETO, linha);

        if(d.tamanho == -1){ //se tamanho == -1, ent�o deve ter argumento dizendo o tamanho
            //LABEL:    SPACE   N
            //vTab[0]   vTab[1] vTab[2]

            if(vTab.size() == 3){
                long int n;

                if(vTab[2].find("x") != string::npos) //N�mero est� em hexadecimal
                        n = strtol(vTab[2].c_str(), NULL, 16);

                else
                    n = strtol(vTab[2].c_str(), NULL, 10);

                for(long int i = 0; i < n; i++){ //adiciona bit absoluto para cada space que existe
                    //cout << "SPACE - bit 0" << endl;
                    bits.push_back(0); //endere�o absoluto
                }
                return n;
            }
            else{
                bits.push_back(0); //endere�o absoluto
                return 1; //N�o tem argumentos
            }
        }

        if(d.nome.compare("SECTION") == 0)
            separaSectionArgs(instrucao, diretiva, vTab, linha);
        else if(d.nome.compare("BEGIN") == 0){ //se for diretiva BEGIN
            if(getSectionAtual() == 'd') //e estiver na se��o dados
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
        else if(d.nome.compare("CONST") == 0){
            //cout << "CONST - bit 0" << endl;
            bits.push_back(0); //endere�o absoluto
        }

        return d.tamanho;
    }
    else if(isInstrucao(instrucao, token)){
        tipoInstrucao i;
        string aux; //string auxiliar que cont�m argumentos
        int endAux = endereco; //endere�o auxiliar (o tamanho de uma instru��o leva em considera��o seus argumentos, ent�o cada argumento +1 no endere�o)
        vector<string> copyArg; //vetor de string para conter argumentos que est�o separados por v�rgula ou por +

        if(getSectionAtual() == 'd' || getEnd())
            imprimeErro(ERRO_LOCAL_INCORRETO, linha);

        if(i.nome.compare("STOP") == 0)
            setStop(true);

        i = pegaInstrucao(instrucao, token);
        bits.push_back(0);
        //cout << endl << "INSTR - bit 0" << endl;

        if(i.tamanho > 1){

            aux.append(vTab[1]); //Sup�e formato INSTR   ARG
            //cout << "Aux velho: " << aux << endl;
            if(vTab.size() >= 3){ //est� no formato: LABEL:  INSTR   ARG
                if(i.nome.compare("COPY") == 0){ //se for COPY
                    if(vTab.size() == 3) //COPY ARG ARG
                        aux.append(vTab[2]);
                    else if(vTab.size() == 4){ //LABEL:  COPY    ARG ARG
                        aux.clear();
                        aux.append(vTab[2]);
                        aux.append(vTab[3]);
                    }
                }
                else{
                    aux.clear();
                    aux.append(vTab[2]);
                }
            }

            //cout << "Aux novo: " << aux << endl;
            explode(copyArg, aux, ","); //procura se na string aux tem copy
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
                        vector<string> somaEndereco;
                        explode(somaEndereco, aux, "+");

                        it = uso.find(somaEndereco[0]);
                        //cout << somaEndereco[0];
                        //cin.get();

                        if(it != uso.end()){ //tem na tabela de uso
                            //cout << "ARG - bit 1 ";
                            bits.push_back(1); //endere�o relativo (argumento)
                            editaUso(uso, somaEndereco[0], endAux);
                        }
                        else{ //n�o tem na tabela de uso
                            //cout << ">>>>>>>>>aux: " << somaEndereco[0] << " bit 1" << endl;
                            //cout << "ARG - bit 1 ";
                            bits.push_back(1);
                        }

                    } //se n�o tiver achado, ent�o n�o tem mesmo na tabela de uso
                    else{
                        //cout << ">>>>>>>>>aux: " << aux << " bit 1" << endl;
                        //cout << "ARG - bit 1 ";
                        bits.push_back(1);
                    }
                }
                else{
                    //cout << ">>>>>>>>>aux: " << aux << " bit 1" << endl;
                    //cout << "ARG - bit 1 ";
                    bits.push_back(1); //endere�o relativo (argumento)
                    editaUso(uso, aux, endAux);
                }
                //cout << endl;
                //cin.get();
            }while(copyArg.size() > 0);
        }

        return i.tamanho;
    }

    imprimeErro(ERRO_COMANDO_NAO_ENCONTRADO, linha);
    return 0;
}

void criaTabelas(ifstream& arq, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, map<string, vector<int>>& uso, map<string, int>& definicao, vector<int>& bits){
    int pc = 0;
    int i; //contador de linhas
    string linha;

    while(getline(arq, linha)){
        vector<string> vTab;
        string aux;
        int tamanho;
        //cout << linha << endl;
        explode(vTab, linha, "\t");

        i = (int)strtol(vTab.back().c_str(), NULL, 10); //�ltimo elemento desta linha informa a linha no arquivo anterior
        vTab.pop_back(); //retira esse elemento

        //Se a primeira string tiver :, � defini��o de r�tulo
        tamanho = vTab[0].size();

        if(vTab[0][tamanho - 1] == ':'){
            tipoTS s;
            vTab[0] = vTab[0].substr(0, tamanho - 1); //eliminando :
            s.simbolo = vTab[0];

            if(strcasecmp(vTab[1].c_str(), "EXTERN") == 0){ //Se a pr�xima string for extern, ent�o insere na tabela de uso
                if(!getBegin() || getEnd()) //se begin n�o tiver sido definido
                    imprimeErro(ERRO_LOCAL_INCORRETO, i);
                insereUso(uso, vTab[0], i);
                s.posicao = 0;
                s.externo = true;
            }
            else{
                s.posicao = pc;
                s.externo = false;
            }
            if(strcasecmp(vTab[1].c_str(), "CONST") == 0 ){                 // Insere o valor da constante na tabela de simbolos
                s.valorConstante = (int) strtol(vTab.back().c_str(),NULL, 10);
                s.tipoConstante = true;
            }
            else{
                s.valorConstante = -1; //n�o � usado
                s.tipoConstante = false;
            }
            insereSimbolo(simbolo, vTab[0], s, i);
            editaDefinicao(definicao, vTab[0], s.posicao); //atualize endere�o em TD caso s�mbolo esteja em TD

            //inserido r�tulo, calcula PC
            aux.append(vTab[1]);
        }
        else{ //somente calcula o pc
            if(strcasecmp(vTab[0].c_str(), "PUBLIC") == 0){ //Se diretiva for PUBLIC, insere na tabela de defini��o
                insereDefinicao(definicao, vTab[1], pc, i);
                if(!getBegin() || getEnd()) //se begin n�o tiver sido definido
                    imprimeErro(ERRO_LOCAL_INCORRETO, i);
            }
            if(strcasecmp(vTab[0].c_str(), "BEGIN") == 0) //Begin DEVE ter um r�tulo
                imprimeErro(ERRO_USO_INCORRETO, i);
            aux.append(vTab[0]);
        }

        pc += calculaPC(instrucao, diretiva, uso, aux, i, vTab, pc, bits);

    }

    verificaSectionText(); //verifica se o arquivo terminou declarando uma se��o text

    arq.clear();
    arq.seekg(0, arq.beg); //rewind
}
