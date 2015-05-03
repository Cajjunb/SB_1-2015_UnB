#include "../include/arquivo.h"
#include "../include/tabela.h"

using namespace std;


int main(){
    ifstream arq1;
    vector<tipoInstrucao> instrucao;
    vector<tipoGramatica> gramatica;
    vector<tipoDiretiva> diretiva;
    tipoGramatica g;
    tipoDiretiva d;
    tipoInstrucao i;

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

    g = pegaGramatica(gramatica, "aDd");
    if(!g.nome.empty())
        cout << "Achou instrucao aDd" << endl;
    else
        cout << "ops :(" << endl;

    i = pegaInstrucao(instrucao, "Adicionar");
    if(!i.nome.empty())
        cout << "Achou instrucao Adicionar" << endl;
    else
        cout << "ops :(" << endl;

    d = pegaDiretiva(diretiva, "BEGIN");
    if(!d.nome.empty())
        cout << "Achou diretiva BEGIN" << endl;
    else
        cout << "ops :(" << endl;

    return 0;
}
