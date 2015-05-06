#include "../include/arquivo.h"


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

void criaVetorTab(ifstream& arq, vector<vector<string>>& mTab){
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
    arq.seekg(0);
}

bool preProcessaArq(char nomeArquivo[] , vector<tipoGramatica>& gramatica){
    FILE *ponteiroLeitura, *ponteiroEscrita ;
    ponteiroLeitura = fopen(nomeArquivo, "r");
    tipoGramatica instrucaoBuffer, instrucaoAux;                                      // Variavel String
    char    streamValor[301];                                           // NUMERO MÁXIMO DE CHARS POR IDENTIFICADOR
    std::size_t zero = 0;
    string stringCplusplus ;
    int linha = 1;

    instrucaoBuffer.qtdOperandos = 0;                                           // INICIALIZA O BUFFER
    if(ponteiroLeitura == NULL ){
        printf("ERRO NA leitura do teste");
        exit(EXIT_FAILURE);
    }else{
        ponteiroEscrita = fopen("pre_processado.txt","w");
        int i ;
        if(ponteiroEscrita == NULL)
            exit(EXIT_FAILURE);
        while( feof(ponteiroLeitura) == false){
            fscanf(ponteiroLeitura,"%s",streamValor);
            stringCplusplus = streamValor;                                  // Convertendo C* para Strings CPLUPLUS
            instrucaoAux = pegaGramatica(gramatica,streamValor);
            if(instrucaoAux.qtdOperandos <  0 ){                                 // NAO ACHOU UMA COM O BUFFER STRING ATUAL INSTRUCAO NA GRAMATICA?
                if(instrucaoBuffer.qtdOperandos > 0){
                    fprintf(ponteiroEscrita, "%s\t",streamValor);
                    instrucaoBuffer.qtdOperandos-- ;
                }else{
                    if( stringCplusplus.find(';') == zero ){                         // CASO COMECE UM COMENTARIO LE ATE O FINAL DA LINHA
                        cout << "\n\tCOMECOU O COMENTARIO!!";
                        fscanf(ponteiroLeitura,"%*[^\n]");                          // PULA ATE O \n!
                    }else{
                    cout << "\n\tErro SINTATICO 2 esperado argumentos da instrucao = " << instrucaoBuffer.nome << "Linha = " << linha;
                    }
                }
            }else{                                                              // ACHOU  COM O BUFFER STRING ATUAL INSTRUCAO NA GRAMATICA!
                if(instrucaoBuffer.qtdOperandos > 0){
                    cout << "\n\tErro SINTATICO 2 esperado argumentos da instrucao = " << instrucaoBuffer.nome << "Linha = " << linha;
                }else{
                    instrucaoBuffer = instrucaoAux;                         // GUARDA NO BUFFER A MEMORIA
                    fprintf(ponteiroEscrita, "\n%s\t",streamValor);
                    linha++;
                }
            }
        }
        fclose(ponteiroEscrita);
        fclose(ponteiroLeitura);
    }

}
