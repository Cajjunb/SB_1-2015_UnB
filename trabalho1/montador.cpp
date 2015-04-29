#include "include/arquivo.h"
#include "include/tabela.h"
#include <iostream>

using namespace std;

bool temExtensao(string aux){

    for(int i = aux.size(); i > 0; i--){ //analisando de trás pra frente o nome do arquivo
        if(aux[i] == '.') //se tiver caracter .
            return true; //usuário passou extensão do arquivo
    }

    return false; //não foi passada extensao
}

int main(int argc, char *argv[]){
    string input, output;
    vector<tipoInstrucao> instrucao;
    vector<tipoGramatica> gramatica;
    vector<tipoDiretiva> diretiva;
    ifstream arq;

    //Verifica passagem de argumentos
    if(argc != 3){
        cout << "Numero de argumentos incorretos. Encerrando";
        exit(EXIT_FAILURE);
    }

    //Verifica arquivos de entrada e saída
    input.append(argv[1]);
    if(!temExtensao(input))
        input.append(".asm");

    output.append(argv[2]);
    if(!temExtensao(output))
        output.append(".o");

    //Cria vetores com informações das instruções, da gramática e das diretivas
    arq.open("tabelas/instrucoes.txt");
    criaInstrucao(arq, instrucao);
    arq.close();

    arq.open("tabelas/gramatica.txt");
    criaGramatica(arq, gramatica);
    arq.close();

    arq.open("tabelas/diretiva.txt");
    criaDiretiva(arq, diretiva);
    arq.close();

    return 0;
}
