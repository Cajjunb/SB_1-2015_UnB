#include "../include/passagem1.h"

void criaTS(ifstream& arq, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo){
    int pc = 0;
    string linha;

    while(getline(arq, linha)){
        vector<string> vTab;

        string::size_type pos = 0;
        string::size_type prev = 0;
        while ((pos = linha.find('\t', prev)) != string::npos){ //enquanto cada \t encontrando não for uma posição inválida da string
            vTab.push_back(linha.substr(prev, pos - prev)); //adicione no vetor de tabs a substring de onde este tab foi encontrado até o começo
            prev = pos + 1;
        }
        vTab.push_back(linha.substr(prev)); //coloque a última subdivisão de tab

        //Primeira posição deve ser rótulo
        //Se não for rótulo, ou é instrução ou diretiva
        if(isInstrucao(instrucao, vTab[0])){
            tipoInstrucao i;
            i = pegaInstrucao(instrucao, vTab[0]);
            pc += i.tamanho;
        }
        else if(isDiretiva(diretiva, vTab[0])){ //AQUI FAZER CASO DE SE FOR EXTERNO
            tipoDiretiva d;
            d = pegaDiretiva(diretiva, vTab[0]);
            pc += d.tamanho;
        }
        else{
            tipoTS s;
            s.externo = false; //POR ENQUANTO
            s.posicao = pc;
            vTab[0][vTab[0].size() - 1] = '\0'; //eliminando :
            simbolo.insert(pair<string, tipoTS>(vTab[0], s));
            cout << simbolo.find(vTab[0])->first << ": " << simbolo.find(vTab[0])->second.posicao << endl;

            if(isDiretiva(diretiva, vTab[1])){ //se depois do rótulo tem uma diretiva
                tipoDiretiva d;
                d = pegaDiretiva(diretiva, vTab[1]);
                if(d.tamanho == -1){ //se o tamanho dela é -1, então seu tamanho deve estar especificado no próximo tab
                    if(vTab.size() >= 3 && !vTab[2].empty()) //se ele realmente tiver mais que 3 coisas e seu terceiro coisa não for vazio
                        pc += stoi(vTab[2],nullptr,10); //tem um número indicando seu valor
                    else
                        pc++; //não tem um número dizendo seu tamanho, então suponhamos que seja 1
                }
                else
                    pc += d.tamanho;
            }
            else if(isInstrucao(instrucao, vTab[1])){ //se depois do rótulo tem uma instrução
                tipoInstrucao i;
                i = pegaInstrucao(instrucao, vTab[1]);
                pc += i.tamanho;
            }
        }
    }

    arq.seekg(0); //rewind
}
