#include "../include/arquivo.h"
#include "../include/tabela.h"

using namespace std;


int main(){
    ifstream arq1;
    vector<tipoInstrucao> instrucao;
    vector<tipoGramatica> gramatica ;
    vector<tipoDiretiva> diretiva;
    tipoGramatica g;
    tipoDiretiva d;
    tipoInstrucao i;
    char aux[301] = "nao_preprocessado/teste1.asm";

    arq1.open("tabelas/instrucoes.txt");
    criaInstrucao(arq1, instrucao);
    arq1.close();


    arq1.open("tabelas/gramatica.txt");
    criaGramatica(arq1, gramatica);
    arq1.close();


    arq1.open("tabelas/diretiva.txt");
    criaDiretiva(arq1, diretiva);
    arq1.close();

    cout << "------------Gramatica------------"<< endl;
    for(int i = 0; i < gramatica.size(); i++){
        cout << "Instrução: " << gramatica[i].nome << endl;
        cout << "\tOp: " << instrucao[i].op << "\tFormato: " << gramatica[i].formato << endl;
    }

    cout << "------------Diretivas------------"<< endl;
    for(int i = 0; i < diretiva.size(); i++){
        cout << "Diretiva: " << diretiva[i].nome << endl;
        cout << "\tTamanho: " << diretiva[i].tamanho << "\tFormato: " << diretiva[i].formato << endl;
    }

    preProcessaArq(aux, instrucao);

    return 0;
}
