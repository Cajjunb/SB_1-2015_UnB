#include "include/arquivo.h"
#include "include/tabela.h"
#include "include/passagem1.h"
#include "include/passagem2.h"
#include "include/erro.h"
#include <iostream>
#include <cstdio>

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
    map<string, tipoTS> simbolo; //Tabela de símbolos
    map<string, int> definicao; //Tabela de definição <nome, endereço>
    map<string, vector<int>> uso; //Tabela de uso <nome, endereços>
    vector<int> bits; //mapa de bits: indica endereços absolutos e relativos
    ifstream arq1;
    ofstream arq2;
    bool ligar;

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
    arq1.open("tabelas/instrucoes.txt");
    criaInstrucao(arq1, instrucao);
    arq1.close();

    arq1.open("tabelas/gramatica.txt");
    criaGramatica(arq1, gramatica);
    arq1.close();

    arq1.open("tabelas/diretiva.txt");
    criaDiretiva(arq1, diretiva);
    arq1.close();

    preProcessaArq2(input);

    arq1.open("pre_processado.txt");
    arq2.open(output);
        criaTabelas(arq1, instrucao, diretiva, simbolo, uso, definicao, bits); //primeira passagem
        ligar = criaArqObj(arq1, arq2, gramatica, instrucao, diretiva, simbolo, uso, definicao, bits); //segunda passagem
    arq1.close();
    arq2.close();

    if(!ligar){ //se não precisa ligar
        string aux;
        output.clear();

        output.append(argv[2]);
        if(!temExtensao(output)){ //se não tiver extensão
            output.append(".e"); //coloca extensão .e,

            aux.append(argv[2]);
            aux.append(".o"); //coloca extensão .o

            rename(aux.c_str(), output.c_str());
        }
    }

    if(teveErro()){ //se teve erro
        cout << "Erro na geração de " << output << endl;
        remove(output.c_str()); //apague arquivo de saída
    }

    remove("pre_processado.txt"); //remoção do arquivo pré-processado temporário

    return 0;
}
