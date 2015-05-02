#include "../include/arquivo.h"
#include "../include/tabela.h"

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
    arq.seekg(0); //rewind
    return false;
}

bool preProcessaArq(char nomeArquivo[] , vector<tipoInstrucao>& gramatica){
    FILE *ponteiroLeitura, *ponteiroEscrita ;
    ponteiroLeitura = fopen(nomeArquivo, "r");
    tipoInstrucao instrucaoObjeto;                                      // Variavel String
    char    streamValor[101];                                           // NUMERO MÁXIMO DE CHARS POR IDENTIFICADOR
    string stringCplusplus ;
    char aux[101] ;
    if(ponteiroLeitura == NULL ){
        exit(EXIT_FAILURE);
    }else{
        ponteiroEscrita = fopen("pre_precossado.txt","w");
        int i ;
        if(ponteiroEscrita == NULL)
            exit(EXIT_FAILURE);
        while( fscanf(ponteiroLeitura,"%s",streamValor) != EOF){
            stringCplusplus = streamValor;                                  // Convertendo C* para Strings CPLUPLUS
            instrucaoObjeto = pegaInstrucao(gramatica,streamValor);
            if(instrucaoObjeto.op != -1){
                cout << "\n\tOLHA! intruc = " << instrucaoObjeto.nome << "\n\t op = " << instrucaoObjeto.op;
                getchar();
             }
        }
    }

}
