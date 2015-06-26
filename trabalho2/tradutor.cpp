#include <iostream>
#include "include/montador.h"
#include <vector>
#include <string>
#include "include/base.h"
#include "include/tabela.h"

int main(int argc, char *argv[]){ //recebe arquivo .asm do assembly inventado e cria arquivo .s(instrução em assembly) e .cod (código máquina)
    vector<string> asmInventado;
    std::vector<tipoInstrucaoIA32> instrucoesIA32;
    string nome;
    ifstream arq1;
    int tamanho = 0, extensao = -1;
     //Verifica passagem de argumentos
    intParaHexLilEndian(256);
    if(argc != 2){
        cout << "Numero de argumentos incorretos. Encerrando";
        exit(EXIT_FAILURE);
    }
    asmInventado.push_back(argv[1]); //com certeza o arquivo recebido é .asm
    if(!temExtensao(asmInventado[0])){
        cout << "Arquivo" + asmInventado[0] + " deve ter extensao. Encerrando";
        exit(EXIT_FAILURE);
    }
    tamanho = asmInventado[0].size();
    for(int i = tamanho; i > 0; i--){ //analisando de trás pra frente o nome do arquivo
        extensao++; //tamanho da extensao
        if(asmInventado[0][i] == '.') //se tiver caracter .
            break; //encontrou extensao, saia do loop
    }
    tamanho = asmInventado[0].size();
    nome = asmInventado[0].substr(0, tamanho - extensao); //eliminando .asm para pegar somente o nome


    asmInventado.push_back(nome + ".opanaoqueromudarextensaonao");
    //asmInventado.push_back(nome + ".s");

    asmInventado.push_back(nome + ".cod");
    arq1.open("tabelas/inv_ia32_intrucoes.txt");
    criaInstrucaoIa32( arq1, instrucoesIA32);
    string divi = "COPY";
    std::vector<int> argumentos(4) ;
    argumentos[0] = 41241;
    argumentos[1] = 213231;
    divi = "ADD";
    cout << inventadoParaMaquina(instrucoesIA32,divi,argumentos);
    divi = "SUB";
    cout << inventadoParaMaquina(instrucoesIA32,divi,argumentos);
    divi = "DIV";
    cout << inventadoParaMaquina(instrucoesIA32,divi,argumentos);
    divi = "MUL";
    cout << inventadoParaMaquina(instrucoesIA32,divi,argumentos);
    divi = "LOAD";
    cout << inventadoParaMaquina(instrucoesIA32,divi,argumentos);
    divi = "STORE";
    cout << inventadoParaMaquina(instrucoesIA32,divi,argumentos);
    divi = "COPY";
    cout << inventadoParaMaquina(instrucoesIA32,divi,argumentos);
    divi = "STORE";
    cout << inventadoParaMaquina(instrucoesIA32,divi,argumentos);
   return 0;
}

