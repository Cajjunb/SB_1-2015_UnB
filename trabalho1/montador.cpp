#include "include/arquivo.h"
#include "include/tabela.h"
#include <iostream>

using namespace std;

bool temExtensao(const char* nomeArq){
    string aux;

    aux.append(nomeArq);

    for(int i = aux.size(); i > 0; i--){ //analisando de trás pra frente o nome do arquivo
        if(aux[i] == '.') //se tiver caracter .
            return true; //usuário passou extensão do arquivo
    }

    return false; //não foi passada extensao
}

int main(int argc, char *argv[]){
    string input, output;

    if(argc != 3){
        cout << "Numero de argumentos incorretos. Encerrando";
        exit(EXIT_FAILURE);
    }

    input.append(argv[1]);
    if(!temExtensao(argv[1]))
        input.append(".asm");

    output.append(argv[2]);
    if(!temExtensao(argv[2]))
        output.append(".o");

    return 0;
}
