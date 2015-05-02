#include "include/arquivo.h"
#include "include/tabela.h"
#include "include/passagem1.h"

using namespace std;

enum{
    REDEFINIDO = 0,
    OP_NAO_IDENTIDICADA
}ERRO;

int main(){
    ifstream arq1;
    vector<tipoInstrucao> instrucao;
    vector<tipoGramatica> gramatica;
    vector<tipoDiretiva> diretiva;
    map<string, tipoTS> simbolo;

    arq1.open("tabelas/instrucoes.txt");
        criaInstrucao(arq1, instrucao);
    arq1.close();

    arq1.open("tabelas/gramatica.txt");
        criaGramatica(arq1, gramatica);
    arq1.close();

    arq1.open("tabelas/diretiva.txt");
        criaDiretiva(arq1, diretiva);
    arq1.close();

    arq1.open("teste_assembly/pre-processado/teste4.asm");
        criaTS(arq1, instrucao, diretiva, simbolo);
    arq1.close();
    return 0;
}
