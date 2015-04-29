#include "../include/arquivo.h"


bool buscaTokenArq(ifstream& arq, string token){

    if(arq.is_open()){
        string tokenLido;

        do{
            getline(arq, tokenLido, '\t'); //leia até o tab

            if(strcasecmp(token.c_str(), tokenLido.c_str()) == 0)
                return true;
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

    return false;
}

bool preProcessaArq(ifstream& arquivo, string titulo_arquivo){
    string token_atual;
    if( arquivo.is_open()){
        do{

        }while(!arquivo.eof());
    }
    else{
        cout << "Erro no Preprocessamento, o Arquivo nao foi encontrado";
        exit(EXIT_FAILURE);
    }

}