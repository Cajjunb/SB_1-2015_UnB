#include "../include/passagem2.h"


int escreveObj(ofstream& out, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, vector<string> vTab){

    if(isInstrucao(instrucao, vTab[0])){
        tipoInstrucao i;
        i = pegaInstrucao(instrucao, vTab[0]);
        map<string, tipoTS>::iterator it = simbolo.find(vTab[0]);
        out << i.op << " " << it->second.posicao << " ";
    }
    else if(isDiretiva(diretiva, vTab[0])){

    }else{ //é rótulo

    }
}

void criaArqObj(ifstream& in, ofstream& out, vector<tipoGramatica>& gramatica, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, map<string, vector<int>>& uso, map<string, int>& definicao){
    string linha;
    int pc = 0;
    int i = 0;

    if(!uso.empty()){
        out << "TABLE USE" << endl;
    }

    while(getline(in, linha)){
        vector<string> vTab;
        int tamanho;
        i++;
        //cout << linha << endl;

        string::size_type pos = 0;
        string::size_type prev = 0;
        while ((pos = linha.find('\t', prev)) != string::npos){ //enquanto cada \t encontrando não for uma posição inválida da string
            vTab.push_back(linha.substr(prev, pos - prev)); //adicione no vetor de tabs a substring de onde este tab foi encontrado até o começo
            prev = pos + 1;
        }
        vTab.push_back(linha.substr(prev)); //coloque a última subdivisão de tab
        for (vector<string>::iterator it = vTab.begin() ; it != vTab.end(); ++it){ //retirandos strings vazias
            if((*it).empty())
                vTab.erase(it);
        }

        tamanho = vTab[0].size();
        if(vTab[0][tamanho - 1] == ':'){
            vTab[0][tamanho - 1] = '\0'; //eliminando :

            map<string, tipoTS>::iterator it = simbolo.find(vTab[0]);
            if(it == simbolo.end())
                imprimeErro(ERRO_NAO_ENCONTRADO, i);
        }
        //VERIFICA ARGUMENTOS AQUI
        escreveObj(out, instrucao, diretiva, simbolo, vTab);
       /* else{
            pc += calculaPC(instrucao, diretiva, vTab[0], i, vTab);
        }*/
    }
    in.seekg(0, in.beg); //rewind
}
