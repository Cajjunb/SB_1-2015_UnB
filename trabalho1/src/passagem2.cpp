#include "../include/passagem2.h"

void escreveOp(ofstream& out, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, string token, string arg, int tipo){ //tipo é INSTRUÇÃO = 0 ou DIRETIVA = 1
    switch(tipo){
        case 0: {
            tipoInstrucao i;
            string aux; //string auxiliar que contém argumentos
            vector<string> copyArg; //vetor de string para conter argumentos que estão separados por vírgula ou por +

            i = pegaInstrucao(instrucao, token);

            out << i.op << " ";
            cout << i.op << " ";

            if(i.tamanho > 1){ //se tamanho for maior que 1, então no mínimo tem argumentos
                aux.append(arg); //Supõe formato INSTR   ARG
                explode(copyArg, aux, ", "); //procura se na string aux tem copy

                do{
                    if(!copyArg.empty()){ //enquanto copyArg tiver argumentos
                        aux.clear();
                        aux.append(copyArg.front());
                        copyArg.erase(copyArg.begin());
                    }

                    map<string, tipoTS>::iterator it = simbolo.find(aux);
                    tipoTS s = it->second;
                    if(!s.externo){
                        out << s.posicao << " ";
                        cout << s.posicao << endl;
                    }
                    else{
                        out << "00 ";
                        cout << s.posicao;
                    }
                    cout << endl;
                    out << " ";

                }while(copyArg.size() > 0);
            }
            break;
        }
        case 1:{
            tipoDiretiva d;
            d = pegaDiretiva(diretiva, token);

            if(d.formato == 'N'){
                if(arg.find("x") != string::npos){ //Número está em hexadecimal
                    cout << strtol(arg.c_str(), NULL, 16);
                    out << strtol(arg.c_str(), NULL, 16);
                }
                else{ //É um número em decimal
                    cout << arg;
                    out << arg;
                }
                cout << endl;
                out << " ";
            }
            break;
        }
    }
}

void separaOp(ofstream& out, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, vector<string> vTab){
    if(isInstrucao(instrucao, vTab[0])){ //INSTRUÇÃO ARG
        if(vTab.size() > 1)
            escreveOp(out, instrucao, diretiva, simbolo, vTab[0], vTab[1], 0);
        else
            escreveOp(out, instrucao, diretiva, simbolo, vTab[0], vTab[0], 0); //STOP
    }
    else if(isDiretiva(diretiva, vTab[0])){
        if(vTab.size() > 1)
            escreveOp(out, instrucao, diretiva, simbolo, vTab[0], vTab[1], 1);
        else
            escreveOp(out, instrucao, diretiva, simbolo, vTab[0], "00", 1); //SPACE SEM ARGUMENTO
    }else{ //é rótulo
        if(isInstrucao(instrucao, vTab[1])){
            if(vTab.size() > 2)
                escreveOp(out, instrucao, diretiva, simbolo, vTab[1], vTab[2], 0);
            else
                escreveOp(out, instrucao, diretiva, simbolo, vTab[1], vTab[0], 0); //LABEL: STOP

        }
        else if(isDiretiva(diretiva, vTab[1])){
            if(vTab.size() > 2)
            escreveOp(out, instrucao, diretiva, simbolo, vTab[1], vTab[2], 1);
        else
            escreveOp(out, instrucao, diretiva, simbolo, vTab[1], "00", 1); //SPACE SEM ARGUMENTO
        }
    }
}

void criaArqObj(ifstream& in, ofstream& out, vector<tipoGramatica>& gramatica, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, map<string, vector<int>>& uso, map<string, int>& definicao){
    string linha;
    int i = 0;
    if(!uso.empty()){
        out << "TABLE USE" << endl;
        cout << "TABLE USE" << endl;
        for (map<string, vector<int>>::iterator it = uso.begin(); it != uso.end(); ++it){
            for(vector<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++ it2){
                out << it->first << " " << *it2 << endl;
                cout << it->first << " " << *it2 << endl;
            }
        }
    }
    if(!definicao.empty()){
        out << "TABLE DEFINITION" << endl;
        cout << "TABLE DEFINITION" << endl;
        for (map<string, int>::iterator it = definicao.begin(); it != definicao.end(); ++it)
            out << it->first << " " << it->second << endl;
            cout << it->first << " " << it->second << endl;
    }

    if(!definicao.empty() || !uso.empty()){
        out << "CODE" << endl;
        cout << "CODE" << endl;
    }

    while(getline(in, linha)){
        vector<string> vTab;
        int tamanho;

        i++;
        //cout << linha << endl;

        explode(vTab, linha, "\t");

        tamanho = vTab[0].size();
        if(vTab[0][tamanho - 1] == ':'){
            vTab[0] = vTab[0].substr(0, tamanho - 1); //eliminando :

            map<string, tipoTS>::iterator it = simbolo.find(vTab[0]);
            if(it == simbolo.end())
                imprimeErro(ERRO_NAO_ENCONTRADO, i);
        }
        separaOp(out, instrucao, diretiva, simbolo, vTab);
       /* else{
            pc += calculaPC(instrucao, diretiva, vTab[0], i, vTab);
        }*/
    }
    in.seekg(0, in.beg); //rewind
}
