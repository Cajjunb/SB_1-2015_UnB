#include "../include/arquivo.h"

bool comecaCodigo = false; //global que indica se o programa que será escrito definitivamente no arquivo começou

bool buscaTokenArq(ifstream& arq, string token){

    if(arq.is_open()){
        string tokenLido;

        do{
            getline(arq, tokenLido, '\t'); //leia até o tab

            if(strcasecmp(token.c_str(), tokenLido.c_str()) == 0){
                arq.seekg(0); //rewind
                return true;
            }
            else{
                string aux;
                getline(arq, aux); //leia até a próxima linha
            }
        }while(!arq.eof()); //enquanto não for fim de arquivo
    }
    else{
        cout << "Erro ao buscar no arquivo";
        exit(EXIT_FAILURE);
    }
    arq.clear();
    arq.seekg(0, arq.beg); //rewind
    return false;
}

void criaVetorTab(ifstream& arq, vector<vector<string> >& mTab){
    string linha;

    while(getline(arq, linha)){
        vector<string> vTab;
        string::size_type pos = 0;
        string::size_type prev = 0;

        while ((pos = linha.find('\t', prev)) != string::npos){ //enquanto cada \t encontrando não for uma posição inválida da string
            vTab.push_back(linha.substr(prev, pos - prev)); //adicione no vetor de tabs a substring de onde este tab foi encontrado até o começo
            prev = pos + 1;
        }
        vTab.push_back(linha.substr(prev)); //coloque a última subdivisão de tab
        mTab.push_back(vTab);
    }
    arq.clear();
    arq.seekg(0, arq.beg); //rewind
}


void trocaEQU(string op, string arg, map<string, tipoTS>& simbolo, stringstream& definitivo){
    vector<string> vTab;
    string argAux;

    //cout << arg << endl;
    explode(vTab, arg, ".");
    argAux.clear();

    //cout << "op: " << op << endl;
    definitivo << op << "\t";

    for(vector<string>::iterator it = vTab.begin(); it != vTab.end(); it++){ //para cada argumento separado por vírgula
        string aux;
        vector<string> maisAux;
        vector<string> virgulaAux;
        aux.clear();
        maisAux.clear();
        aux.append(*it);
        bool virgula = false;

        if(aux.find("+") != string::npos){ //se tiver +

            explode(maisAux, aux, "+");
            aux.clear();
            aux.append(maisAux[0]); //o primeiro troço antes do + é label
            //cout << "aux1: " << aux << endl;
        }
        if(aux[aux.size() - 1] == ','){ //se tiver +
            aux = aux.substr(0, aux.size() - 1);
            virgula = true;
            //cout << "aux2 :" << aux << endl;
        }

        map<string, tipoTS>::iterator it2 = simbolo.find(aux);
        if(it2 != simbolo.end()){
            aux.clear();
            tipoTS s = it2->second;
            aux.append(to_string(s.valorConstante));
         }

         definitivo << aux;

         if(!maisAux.empty()){
            definitivo << "+";

            aux.clear();
            aux.append(maisAux[1]);
            //cout << "aux3: " << aux << endl;
            if(aux[aux.size() - 1] == ','){ //se tiver +
                aux = aux.substr(0, aux.size() - 1);
                virgula = true;
                //cout << "aux4 :" << aux << endl;
            }

            it2 = simbolo.find(aux);
            if(it2 != simbolo.end()){
                aux.clear();
                tipoTS s = it2->second;
                aux.append(to_string(s.valorConstante));
             }
             definitivo << aux;
        }
        if(virgula)
            definitivo << ",";
        definitivo << "\t";
    }
}

bool verificaNotEQUIF(string linha, map<string, tipoTS>& simbolo, bool *prox, stringstream& definitivo){
    vector<string> vTab;
    string args;
    int tamanho;
    int aux;

    //cout << linha << endl;

    explode(vTab, linha, "\t");

    for(vector<string>::iterator it = vTab.begin() + 1; it != vTab.end() - 1; it++){
        args.append(*it);
        args.append(".");
    }

    trocaEQU(vTab[0], args, simbolo, definitivo); //substitui valores de EQU's já anteriormente definidos
    definitivo << vTab.back(); //coloca número da linha

    linha.clear();
    linha.append(definitivo.str());
    //cout << linha << endl;
    //cin.get();

    vTab.clear();
    explode(vTab, linha, "\t");

    aux = (int) strtol(vTab.back().c_str(),NULL, 10);
    tamanho = vTab[0].size();

    if(vTab[0][tamanho - 1] == ':'){ //LABEL, PODE SER EQU

        if(strcasecmp(vTab[1].c_str(), "EQU") == 0){ //É EQU, então pode processar
            if(comecaCodigo)
                imprimeErro(ERRO_EQU_DEPOIS, aux);

            vTab[0] = vTab[0].substr(0, tamanho - 1); //eliminando :

            map<string, tipoTS>::iterator it = simbolo.find(vTab[0]);
            if(it == simbolo.end() && isTokenValido(vTab[0])){ //É token válido
                if(vTab.size() == 4){
                    if(isNumber(vTab[2])){
                        tipoTS s;
                        if(vTab[2].find("X") != string::npos) //hexadecimal
                            s.valorConstante = (int) strtol(vTab[2].c_str(),NULL, 16);
                        else //decimal
                            s.valorConstante = (int) strtol(vTab[2].c_str(),NULL, 10);
                        s.externo = false;
                        s.posicao = 0;
                        s.section = '0';
                        s.tamanhoMemoria = 0;
                        s.tipoConstante = false;
                        simbolo.insert(pair<string, tipoTS>(vTab[0], s));
                        return false;
                    }
                }
            }
        }


    }
    else{

        if(strcasecmp(vTab[0].c_str(), "IF") == 0){

            if(!isTokenValido(vTab[1]))
                imprimeErro(ERRO_INVALIDO, aux);

            if(!isNumber(vTab[1]))
                imprimeErro(ERRO_ARG_INCORRETO, aux);
            else{
                if(vTab.size() != 3)
                    imprimeErro(ERRO_QTD_ARG, aux);

                long int n;
                if(vTab[2].find("X") != string::npos) //Número está em hexadecimal
                        n = strtol(vTab[1].c_str(), NULL, 16);
                else
                    n = strtol(vTab[1].c_str(), NULL, 10);

                if(n != 0)
                    *prox = true; //a próxima instrução pode ser escrita
                else
                    *prox = false; //a próxima instrução não pode ser escrita

                return false;
            }

        }
    }

    return true;
}


void preProcessaArq2(string nomeArquivo, map<string, tipoTS>& simbolo){
    std::ifstream  ponteiroLeitura(nomeArquivo) ;
    FILE *ponteiroEscrita ;
    string stringCplusplus ;
    unsigned int linha = 1;

    bool instAtual = true;
                                                       // INICIALIZA O BUFFER
    if(!ponteiroLeitura.is_open() ){
        printf("Erro ao abrir o arquivo. Encerrando.");
        exit(EXIT_FAILURE);
    }else{
        ponteiroEscrita = fopen("pre_processado.txt","w");
        if(ponteiroEscrita == NULL)
            exit(EXIT_FAILURE);
        while( !ponteiroLeitura.eof()){
            getline(ponteiroLeitura,stringCplusplus,'\n');
            if(!stringCplusplus.empty() ){
                stringCplusplus = transformaEspacoEmBranco(stringCplusplus);
                stringCplusplus = retiraComentarios(stringCplusplus);
                stringCplusplus = formataTabs(stringCplusplus);
                stringCplusplus = retiraNL(stringCplusplus);
                stringCplusplus = retiraLF(stringCplusplus);
                if(!stringCplusplus.empty() && stringCplusplus.size() > 1 ){
                    stringstream definitivo;
                    stringCplusplus =  stringCplusplus +"\t" +std::to_string(linha);

                    locale loc;
                    toUpper(stringCplusplus,loc); //passa tudo para uppercase

                    stringCplusplus = formataTabs(stringCplusplus);
                    if(verificaNotEQUIF(stringCplusplus, simbolo, &instAtual, definitivo)){
                        comecaCodigo = true;
                        if(instAtual) //se instrução atual pode ser escrita
                            fprintf(ponteiroEscrita,"%s\n",definitivo.str().c_str());
                        else
                            instAtual = true; //seta flag como verdadeiro para próxima instrução ter a possibilidade de ser escrita
                    }

                }
            }
            linha++;
        }
    }
    fclose(ponteiroEscrita);
    ponteiroLeitura.close();
}



std::string retiraNL(std::string formatada){
    std::size_t achado;
    achado  = formatada.find("\n");
    while(achado != std::string::npos){
        formatada.erase(achado,1);
        achado  = formatada.find("\n");
    }
    return formatada;
}

std::string retiraLF(std::string formatada){
    std::size_t achado;
    achado  = formatada.find("\r");
    while(achado != std::string::npos){
        formatada.erase(achado,1);
        achado  = formatada.find("\r");
    }
    return formatada;
}


std::string formataTabs(std::string formatada){
    std::size_t achado;
    while(formatada.at(0) =='\t'){
        formatada.erase(0,1);
        if(formatada.empty())
            formatada = "\n";
    }
    achado  = formatada.find("\t\t");
    while(achado != std::string::npos){
        formatada.erase(achado,1);
        achado  = formatada.find("\t\t");
    }
    return formatada;
}


std::string retiraComentarios(std::string formatada){
    std::size_t achado;
    achado  = formatada.find(";");
    if(achado != std::string::npos){
        formatada.erase(achado,formatada.length() );
        formatada.replace(achado,1,"\n");
    }
    return formatada;
}

std::string transformaEspacoEmBranco(std::string formatada){
    std::size_t achado;
    achado  = formatada.find(" ");
    while(achado != std::string::npos){
        formatada.replace(achado,1,"\t");
        achado  = formatada.find(" ");
    }
    return formatada;
}
