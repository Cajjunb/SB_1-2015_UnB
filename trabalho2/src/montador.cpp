#include "../include/montador.h"

using namespace std;

void monta(vector<string> asmInventado){
    string input, output;
    vector<tipoInstrucaoIA32> instrucoesIA32;
    vector<tipoInstrucao> instrucao;
    vector<tipoGramatica> gramatica;
    vector<tipoDiretiva> diretiva;
    map<string, tipoTS> simbolo; //Tabela de símbolos
    map<string, int> definicao; //Tabela de definição <nome, endereço>
    map<string, vector<int> > uso; //Tabela de uso <nome, endereços>
    map<string, tipoTSIA32> simboloIA32; //tabela de símbolos de IA32
    vector<int> bits; //mapa de bits: indica endereços absolutos e relativos
    ifstream arq1;
    ofstream arq2;
    bool ligar;


    //Verifica arquivos de entrada e saída
    input.append(asmInventado[0]);
    if(!temExtensao(input))
        input.append(".asm");

    output.append(asmInventado[1]);
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

    arq1.open("tabelas/inv_ia32_intrucoes.txt");
    criaInstrucaoIa32( arq1, instrucoesIA32);
    arq1.close();

    /*for(vector<tipoInstrucaoIA32>::iterator it = instrucoesIA32.begin(); it != instrucoesIA32.end(); it++){
        cout << (*it).nome << " " << (*it).tamanhoTotal << endl;
    }
    */


    preProcessaArq2(input, simbolo);

    arq1.open("pre_processado.txt");
    arq2.open(output);
        criaTabelas(arq1, instrucao, diretiva, simbolo, uso, definicao, bits, instrucoesIA32, simboloIA32); //primeira passagem
        ligar = criaArqObj(arq1, arq2, gramatica, instrucao, diretiva, simbolo, uso, definicao, bits, instrucoesIA32,simboloIA32); //segunda passagem

        cout << endl << "Tabela de simbolos IA32" << endl;
        for(map<string, tipoTSIA32>::iterator it = simboloIA32.begin(); it != simboloIA32.end(); it++){
            cout << it->first << " Sessao: " << (it->second).section << " Tamanho: " << (it->second).tamanho << " Endereco: " << (it->second).endereco << endl;
        }
    arq1.close();
    arq2.close();

    if(!ligar){ //se não precisa ligar
        string aux;
        output.clear();

        output.append(asmInventado[1]);
        if(!temExtensao(output)){ //se não tiver extensão
            output.append(".e"); //coloca extensão .e,

            aux.append(asmInventado[1]);
            aux.append(".o"); //coloca extensão .o

            rename(aux.c_str(), output.c_str());
        }
    }

    if(teveErro()){ //se teve erro
        cout << "Erro na geração de " << output << endl;
        remove(output.c_str()); //apague arquivo de saída
    }
    remove("pre_processado.txt"); //remoção do arquivo pré-processado temporário
}
