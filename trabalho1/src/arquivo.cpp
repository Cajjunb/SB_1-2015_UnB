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
    arq.clear();
    arq.seekg(0, arq.beg); //rewind
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
    arq.clear();
    arq.seekg(0, arq.beg); //rewind
}

bool preProcessaArq(char nomeArquivo[] , vector<tipoGramatica>& gramatica, vector<tipoDiretiva>& diretiva){
    FILE *ponteiroLeitura, *ponteiroEscrita ;
    ponteiroLeitura = fopen(nomeArquivo, "r");
    tipoGramatica instrucaoBuffer, instrucaoAux;                                        // Variavel String
    tipoDiretiva  diretivaBuffer, diretivaAux;
    char    streamValor[301];                                                           // NUMERO MÁXIMO DE CHARS POR IDENTIFICADOR
    std::size_t zero = 0;
    std::string stringCplusplus ;
    int linha = 1;

    diretivaBuffer.qtdOperandos  = 0;
    instrucaoBuffer.qtdOperandos = 0;                                                   // INICIALIZA O BUFFER
    if(ponteiroLeitura == NULL ){
        printf("ERRO NA leitura do teste");
        exit(EXIT_FAILURE);
    }else{
        ponteiroEscrita = fopen("pre_processado.txt","w");
        if(ponteiroEscrita == NULL)
            exit(EXIT_FAILURE);
        while( feof(ponteiroLeitura) == false){
            fscanf(ponteiroLeitura,"%s",streamValor);
            stringCplusplus = streamValor;                                                          // Convertendo C* para Strings CPLUPLUS
            instrucaoAux = pegaGramatica(gramatica,streamValor);                                    // VERIFICA SE EH UMA INSTRUCAO CONHECIDA
            if(instrucaoAux.qtdOperandos <  0 ){                                                    // NAO ACHOU UMA COM O BUFFER STRING ATUAL INSTRUCAO NA GRAMATICA?
                if(instrucaoBuffer.qtdOperandos > 0){
                    fprintf(ponteiroEscrita, "%s\t",streamValor);                                   // ESCREVE
                    instrucaoBuffer.qtdOperandos-- ;                                                // ESCREVEU UM OPERANDO DA INSTRUCAO
                    if(instrucaoBuffer.qtdOperandos <= 0)
                        fprintf(ponteiroEscrita, "\n");                                             // ESCREVE QUEBRA DE LINHA SE ACABOU OS OPERANDOS INSTRUCA
                }else{
                    if(diretivaBuffer.qtdOperandos > 0){                                            // AINDA TEM O NO BUFFER DE DIRETIVAS OPERANDOS PARA SEREM ESCRITOS?
                        fprintf(ponteiroEscrita, "%s\t",streamValor);                               // ESCREVE NO ARQUIVO
                        diretivaBuffer.qtdOperandos-- ;                                             // ESCREVEU UM OPERANDO DE UMA DIRETIVA
                        if(diretivaBuffer.qtdOperandos <= 0)
                            fprintf(ponteiroEscrita, "\n");                                         // ESCREVE QUEBRA DE LINHA SE ACABOU OS OPERANDOS DIRETIVA
                    }else{                                                                          // NO BUFFER A QUANTIDADE DE OPERANDOS JA ACABOU
                        diretivaAux = pegaDiretiva(diretiva, streamValor);                          // VERIFICA Se É UMA DIRETIVA NA TABELA
                        int tam_string = ((int) stringCplusplus.size() -1);
                        bool achou_diretiva = isDiretiva(diretiva,stringCplusplus) ;
                        if(( stringCplusplus.find(';') == zero )||(achou_diretiva == true)
                             ||( stringCplusplus.at(tam_string) == ':' )){                          // CASO COMECE UM COMENTARIO OU DIRETIVA
                            cout << "\n\tExcessoes! O que foi achado ="<< stringCplusplus << "linha = " << linha  ;
                            if(( stringCplusplus.find(';') == zero )){                              // EH COMENTARIO
                                fscanf(ponteiroLeitura,"%*[^\n]");                                  // PULA ATE O \n!
                                linha++;
                            }if(achou_diretiva == true){                                            // CASO SEJA DIRETIVA
                                diretivaBuffer = diretivaAux;                                       // COLOCA A DIRETIVA NO BUFFER
                                fprintf(ponteiroEscrita, "%s\t", streamValor);                      // ESCREVE
                                if(diretivaBuffer.qtdOperandos == 0)                                // CASO SEJA UMA DIRETIVA QUE TENHA ZERO OPERANDOS 
                                    fprintf(ponteiroEscrita, "\n" );                                // IMPRIME NOVA LINHA
                                if(diretivaBuffer.nome == "SPACE"){                                 // CASO DO SPACE
                                    fscanf(ponteiroLeitura,"%s",streamValor);
                                    stringCplusplus = streamValor;
                                    tam_string = ((int) stringCplusplus.size() -1);
                                    cout << "Excessao do tipo SPACE = " << streamValor;
                                    if(isDiretiva(diretiva,streamValor)){                           // A PROXIMA EH UMA DIRETIVA?
                                        fprintf(ponteiroEscrita,"\n");                              // QUEBRA A LINHA
                                    }if(isGramatica(gramatica,streamValor)){
                                        fprintf(ponteiroEscrita,"\n");
                                    }if( stringCplusplus.at(tam_string) == ':'){
                                        fprintf(ponteiroEscrita,"\n");
                                    }if((stringCplusplus.at(tam_string) != ':')&&
                                        (!isGramatica(gramatica,streamValor))&&
                                        (!isDiretiva(diretiva,streamValor))){
                                        cout << "Eh  argumento" ;
                                        fprintf(ponteiroEscrita,"%s\n",streamValor);
                                    }
                                }
                            }if( stringCplusplus.at(tam_string) == ':' ){                           // CASO SEJA DEFINICAO ROTULO
                                fprintf(ponteiroEscrita, "%s\t", streamValor);                      // ESCREVE
                            }
                        }else{
                            cout << "\n\tErro SINTATICO 1 esperado argumentos da instrucao = " << instrucaoBuffer.nome << "Linha = " << linha;
                        }
                    }
                }
            }else{                                                                              // ACHOU  COM O BUFFER STRING ATUAL INSTRUCAO NA GRAMATICA!
                if(instrucaoBuffer.qtdOperandos > 0){
                    cout << "\n\tErro SINTATICO 2 esperado argumentos da instrucao = " << instrucaoBuffer.nome << "Linha = " << linha;
                }else{
                    instrucaoBuffer = instrucaoAux;                                             // GUARDA NO BUFFER A MEMORIA
                    fprintf(ponteiroEscrita, "%s\t",streamValor);
                    linha++;
                    if(instrucaoBuffer.qtdOperandos == 0)                                       // CASO SEJA UMA INSTRUCAO QUE TENHA ZERO OPERANDOS 
                        fprintf(ponteiroEscrita, "\n" );
                }
            }
        }
        fclose(ponteiroEscrita);
        fclose(ponteiroLeitura);
    }

}



bool preProcessaArq2(char nomeArquivo[]){
    std::ifstream  ponteiroLeitura(nomeArquivo) ;
    FILE *ponteiroEscrita ;
    string stringCplusplus ;
    unsigned int i = 0;
//    int linha = 1;
    ;                                                   // INICIALIZA O BUFFER
    if(!ponteiroLeitura.is_open() ){
        printf("ERRO NA leitura do teste");
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
                for( i = 0; i < stringCplusplus.size(); i++)
                    printf("\n\tDEBUG2 CODIFICAO = %d ", stringCplusplus[i]);
                if(!stringCplusplus.empty() && stringCplusplus.size() > 1 ){
                    cout << "\n\tDEBUG3 Printei no arquivo" ;
                    fprintf(ponteiroEscrita,"%s\n",stringCplusplus.c_str());
                }
            }
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


std::string formataTabs(std::string formatada){
    std::size_t achado;
    while(formatada.at(0) =='\t'){
        formatada.erase(0,1);    
        if(formatada.empty())
            formatada = "\n";
    }
    achado  = formatada.find("\t\t"); 
    cout << "\n\t Resultado  DEBUG 0 = \"" << formatada << "\" size =" << formatada.size();
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
