#include "include/arquivo.h"
#include "include/tabela.h"
#include "include/passagem1.h"
#include "include/passagem2.h"

using namespace std;



int main(){
    ifstream arq1;
    ofstream arq2;
    vector<tipoInstrucao> instrucao;
    vector<tipoGramatica> gramatica;
    vector<tipoDiretiva> diretiva;

    //Isso aqui pode mudar
    map<string, tipoTS> simbolo; //Tabela de símbolos
    map<string, int> definicao; //Tabela de definição <nome, endereço>
    map<string, vector<int>> uso; //Tabela de uso <nome, endereços>

    arq1.open("tabelas/instrucoes.txt");
        criaInstrucao(arq1, instrucao);
    arq1.close();

    arq1.open("tabelas/gramatica.txt");
        criaGramatica(arq1, gramatica);
    arq1.close();

    arq1.open("tabelas/diretiva.txt");
        criaDiretiva(arq1, diretiva);
    arq1.close();

    arq1.open("teste_assembly/pre-processado/teste2.asm");
        criaTabelas(arq1, instrucao, diretiva, simbolo, uso, definicao);
    arq1.close();

    cout << "---------- Tabela de Simbolos ----------" << endl;
    cout << "Rotulo\t Externo\t Posicao" << endl;
    for (map<string, tipoTS>::iterator it = simbolo.begin(); it != simbolo.end(); ++it)
        cout << it->first << "\t " << it->second.externo << "\t " << it->second.posicao << endl;
    cout << endl;

    cout << "---------- Tabela de Definicoes ----------" << endl;
    cout << "Rotulo\t Posicao" << endl;
    for (map<string, int>::iterator it = definicao.begin(); it != definicao.end(); ++it)
        cout << it->first << "\t " << it->second << endl;

    cout << "---------- Tabela de Uso ----------" << endl;
    cout << "Rotulo\t Posicao" << endl;
    for (map<string, vector<int>>::iterator it = uso.begin(); it != uso.end(); ++it){
        cout << it->first << "\t " << "\t";
        for(vector<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++ it2)
            cout << *it2 << "<-";
        cout << endl;
    }

    arq1.open("teste_assembly/pre-processado/teste2.asm");
    arq2.open("teste.txt", std::ofstream::out | std::ofstream::trunc);
        criaArqObj(arq1, arq2, gramatica, instrucao, diretiva, simbolo, uso, definicao);
    arq1.close();
    arq2.close();

    return 0;
}

