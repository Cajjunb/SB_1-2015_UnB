#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>

#include "include/base.h"
#include "include/erro.h"

using namespace std;

bool temExtensao(string aux){

    for(int i = aux.size(); i > 0; i--){ //analisando de trás pra frente o nome do arquivo
        if(aux[i] == '.') //se tiver caracter .
            return true; //usuário passou extensão do arquivo
    }

    return false; //não foi passada extensao
}

void criaTabelaGlobalDefinicao(ifstream& in, map<string, int>& definicao, int fator){
    string linha;

    while(getline(in,linha)){
        if(linha.compare("TABLE DEFINITION") == 0) //se achar a tabela de definicao
            break; //pare o loop
    }
    if(in.eof()){
        cout << "Arquivo no formato incorreto. Encerrando";
        exit(EXIT_FAILURE);
    }

    do{
        map<string, int>::iterator it;
        vector<string> vTab;

        getline(in,linha); //Pegue uma linha do arquivo
        if(!linha.empty()){ //se não for vazia
            explode(vTab, linha, " "); //separa seus argumentos
            it = definicao.find(vTab[0]);
            //cout << vTab[0] << "--" << vTab[1] << endl;
            if(it == definicao.end()){
                int valor = strtol(vTab[1].c_str(), NULL, 10);
                valor += fator;
                definicao.insert(pair<string, int>(vTab[0], valor));
            }
            else
                imprimeErro(ERRO_REDEFINICAO);
        }
    }while(!linha.empty());

    in.clear();
    in.seekg(0, in.beg);
}

int calculaFatorCorrecao(ifstream& arq){
    string linha;
    int tamanho = 0;

    while(getline(arq,linha)){
        //cout << linha << endl;
        if(linha.compare("CODE") == 0)
            break;

    }
    if(arq.eof()){
        arq.close();
        cout << "Arquivo nao precisa ser ligado. Encerrando";
        exit(EXIT_SUCCESS);
    }

    while(getline(arq,linha, ' ')){
        tamanho++;
        //cout << linha << " tamanho:" << tamanho <<endl;
    }
    tamanho++; //mais um para indicar pŕoximo espaço vazio

    //cout << "fator de correção: " << tamanho << endl;
    arq.clear();
    arq.seekg(0, arq.beg);
    return tamanho;
}

void escreveExe(ifstream& in, ofstream& out, map<string, int>& definicao, int fator){
    string linha;
    map<int, string> uso; //tabela de uso
    vector<string> bits; //mapa de bits
    int endereco = 0; //contador de endereço

    getline(in, linha); //TABLE USE
    while(getline(in, linha) && !linha.empty()){ //constrói tabela de uso
        vector<string> vTab;
        explode(vTab, linha, " ");
        uso.insert(pair<int, string>(strtol(vTab[1].c_str(), NULL, 10), vTab[0]));
    }

    while(linha.compare("R") != 0){ //enquanto não achar R
        getline(in, linha); //pegue linha
    }//achou R

    getline(in, linha); //pegue linha
    explode(bits, linha, " "); //divide cada bit em posição de vetor

    while(linha.compare("CODE") != 0){
        getline(in, linha);
    } //achou CODE


    getline(in, linha); //pega toda a linha do código objeto
    vector<string> obj;
    explode(obj, linha, " ");
    //em geral, vetor obj estará
    //obj[0]    obj[1]  obj[2]  obj[3]
    //op        arg     op      arg
    for(    vector<string>::iterator codigo = obj.begin(), bit = bits.begin();
            codigo != obj.end(), bit != bits.end();
            codigo++, bit++, endereco++
        ){
        int soma = 0;
        if((*bit).compare("1") == 0){
            map<int, string>::iterator it;

            if(!uso.empty()){ //se ainda há pendências de uso pra resolver
                it = uso.find(endereco);
                if(it != uso.end()){ //se achar este endereço atual deste arquivo na tabela de uso
                    string label;
                    map<string, int>::iterator def;

                    label.clear();
                    label.append(it->second);
                    def = definicao.find(label);
                    //out << (def->second + fator + strtol((*codigo).c_str(), NULL, 10)) << " ";
                    soma = def->second - fator; //subtrai o valor de fator porque este endereço está na tabela geral de definição, logo o fator já foi calculado

                    uso.erase(it); //free

                }
            }
            out << (soma + fator + strtol((*codigo).c_str(), NULL, 10)) << " ";
            //cout << " endereco: "<< (soma + fator + strtol((*codigo).c_str(), NULL, 10)) << endl;
            //cin.get();
        }
        else{
            out << *codigo << " "; //escreve opcode (fixo)
            //cout << "codigo: " << *codigo << " "; //escreve opcode (fixo)
            //cout << " bit: " << *bit << " ";
        }
    }
}

int main(int argc, char *argv[]){
    string input1 = "",input2 = "", output = "";
    ifstream in, arq;
    ofstream out;
    int fatorCorrecao = 0;
    map<string, int> definicao;
    map<string, vector<int>> uso;

    //Verifica passagem de argumentos
    if(argc != 4){
        cout << "Numero de argumentos incorretos. Encerrando";
        exit(EXIT_FAILURE);
    }

    //Verifica arquivos de entrada e saída
    input1.append(argv[1]);
    if(!temExtensao(input1))
        input1.append(".o");

    input2.append(argv[2]);
    if(!temExtensao(input1))
        input2.append(".o");

    output.append(argv[3]);
    if(!temExtensao(output))
        output.append(".e");


    in.open(input1);
    if(!in.is_open()){
        cout << "Erro ao abrir o arquivo " << input1 << ". Encerrando";
        exit(EXIT_FAILURE);
    }

    fatorCorrecao = calculaFatorCorrecao(in);
    if(input2.empty()){
        imprimeErro(ERRO_FALTA_ARQUIVO);
    }
    else{

        out.open(output, std::ofstream::out | std::ofstream::trunc);
        criaTabelaGlobalDefinicao(in, definicao, 0);
        in.close();

        in.open(input2);
         if(!in.is_open()){
            cout << "Erro ao abrir o arquivo " << input2 << ". Encerrando";
            exit(EXIT_FAILURE);
        }
        criaTabelaGlobalDefinicao(in, definicao, fatorCorrecao);
        in.close();

        in.open(input1);
        escreveExe(in, out, definicao, 0);
        in.close();

        in.open(input2);
        escreveExe(in, out, definicao, fatorCorrecao);
        in.close();

        out.close();
    }

    in.close();

    return 0;
}
