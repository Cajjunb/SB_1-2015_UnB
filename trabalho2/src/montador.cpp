#include "../include/montador.h"

using namespace std;

void monta(vector<string> asmInventado){
    string input, outputia32,outputCod;
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
    ofstream arq3;

    //Verifica arquivos de entrada e saída
    input.append(asmInventado[0]);
    if(!temExtensao(input))
        input.append(".asm");

    if(!temExtensao(outputia32))
        outputia32.append(".o");

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

    //cout << "criou tabelas" << endl;
    //cin.get();

    /*for(vector<tipoInstrucaoIA32>::iterator it = instrucoesIA32.begin(); it != instrucoesIA32.end(); it++){
        cout << (*it).nome << " " << (*it).tamanhoTotal << endl;
    }
    */
    preProcessaArq2(input, simbolo);
    arq1.open("pre_processado.txt");
    arq2.open(asmInventado[1]);
    arq3.open(asmInventado[2]);

    //cout << "criou pre-processado" << endl;
    //cin.get();
    criaTabelas(arq1, instrucao, diretiva, simbolo, uso, definicao, bits, instrucoesIA32, simboloIA32); //primeira passagem
    //cout << "primeira passagem" << endl;
    //cin.get();
    criaArqObj(arq1, arq2, arq3, gramatica, instrucao, diretiva, simbolo, instrucoesIA32,simboloIA32); //segunda passagem
    //cout << "segunda passagem" << endl;
    //cin.get();
    arq1.close();
    arq2.close();
    arq3.close();


    if(teveErro()){ //se teve erro
        cout << "Erro na geração de " << outputia32 << " e " << asmInventado[2] << endl;
        remove(outputia32.c_str()); //apague arquivo de saída
        remove(asmInventado[2].c_str()); //apague arquivo de saída
    }
    remove("pre_processado.txt"); //remoção do arquivo pré-processado temporário
}
