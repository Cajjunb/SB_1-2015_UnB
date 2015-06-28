#include "../include/passagem2.h"

bool precisaData = false; //global que indica necessidade de section data

void escreveOp(ofstream& out,vector<tipoInstrucaoIA32>& instrucoesIA32,map<string, tipoTSIA32>& simboloIA32, vector<tipoGramatica>& gramatica, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, string token, string arg, int tipo, int linha){ //tipo é INSTRUÇÃO = 0 ou DIRETIVA = 1
    bool erro_montagem = false;
    switch(tipo){
        case 0: {
            tipoInstrucao i;
            tipoGramatica g;
            string aux; //string auxiliar que contém argumentos
            vector<string> copyArg; //vetor de string para conter argumentos que estão separados por vírgula
            vector<string> maisAux; //vetor de string para conter argumentos que estão separados por +
            int mais;
            int qtdArg = 0;
            std::vector<int> argumentos(2); // vetor de inteiros para ser usado na funcao de traducao inventado -> ia32

            //cout << "token:--" << token << "--" << endl;
            i = pegaInstrucao(instrucao, token);
            g = pegaGramatica(gramatica, token);

            //out << i.op << " ";
            //cout << i.op << " ";

            if(g.qtdOperandos > 0 && !arg.empty()){ //se qtdOperandos > 0 e argumento != vazio
                aux.append(arg); //Supõe formato INSTR   ARG
                //cout << "arg: " << arg << endl;
                explode(copyArg, aux, ","); //procura se na string aux tem copy
                do{
                    mais = 0;
                    qtdArg++;
                    if(!copyArg.empty()){ //enquanto copyArg tiver argumentos
                        aux.clear();
                        aux.append(copyArg.front());
                        copyArg.erase(copyArg.begin());
                    }
                    if(aux.find("+") != string::npos){ //se tiver +
                        explode(maisAux, aux, "+");
                        aux.clear();
                        aux.append(maisAux[0]);
                        //cout << "MaisAux[1]" << maisAux[1] << endl;

                        if(!isNumber(maisAux[1])){
                            imprimeErro(ERRO_ARG_INCORRETO, linha);
                            erro_montagem = true;
                        }
                        else{
                            if(maisAux[1].find("X") != string::npos) //Número está em hexadecimal
                                mais = (int)strtol(maisAux[1].c_str(), NULL, 16);
                            else{ //Número está em decimal
                                mais = (int)strtol(maisAux[1].c_str(), NULL, 10);

                            }
                        }
                    }
                    //cout << "Aux: " << aux << endl;

                    map<string, tipoTS>::iterator it = simbolo.find(aux);
                    if(it != simbolo.end()){
                        tipoTS s = it->second;

                        if(s.posicao == -1){
                            imprimeErro(ERRO_OP_INVALIDO, linha);
                            erro_montagem = true;
                        }
                        mais += s.posicao;
                        argumentos.insert(argumentos.end(),mais);                           // <- INSERE COMO ARGUMENTO VALIDO!
                        //cout << " aux: " << aux << " s.posicao: " << s.posicao << " mais final: " << mais << endl;
                        //cin.get();
                        //out << mais;
                        //cout << mais;
                        //cout << endl;
                        //out << " ";
                    }
                    else{
                        if(!getData())
                            precisaData = true;
                        if(isNumber(aux) && g.formato.compare("R") == 0){
                            imprimeErro(ERRO_ARG_INCORRETO, linha);
                            erro_montagem = true;
                        }
                        else if(isAlfanumericoUnderscore(aux)){
                            imprimeErro(ERRO_SIMBOLO_NAO_DEFINIDO, linha);
                            erro_montagem = true;
                        }
                        else{
                            imprimeErro(ERRO_INVALIDO, linha);
                            erro_montagem = true;
                        }
                        imprimeErro(ERRO_ARG_INVALIDO, linha);
                    }
                }while(copyArg.size() > 0);
                //cout << "g.nome: " << g.nome << " g.qtdOperandos: " << g.qtdOperandos << endl;
                //cout << "qtdArgs: " << qtdArg << endl;
                if(qtdArg != g.qtdOperandos){
                    imprimeErro(ERRO_QTD_ARG, linha);
                }
                if(erro_montagem != true){
                    cout << "instrucao = "<< i.nome <<"\t"<< "argumentos = "<< argumentos[0];
                    out << inventadoParaIA32(instrucoesIA32,i.nome,argumentos);
                }

            }
            else{
                if(i.op == 14 && !arg.empty()){ //se for STOP e tiver argumentos
                    imprimeErro(ERRO_QTD_ARG, linha); //erro
                    erro_montagem = true;
                }
                else if(i.op != 14){
                    imprimeErro(ERRO_QTD_ARG, linha); //não é STOP e não tinha argumentos
                    erro_montagem = true;
                }
            }


            break;
        }
        case 1:{
            tipoDiretiva d;
            d = pegaDiretiva(diretiva, token);

            if(d.formato == 'N'){
                if(isNumber(arg)){
                    if(arg.find("X") != string::npos){ //Número está em hexadecimal
                        if(strcasecmp(d.nome.c_str(), "SPACE") == 0){
                            long int space = strtol(arg.c_str(), NULL, 16);
                            do{
                                //cout << "00 ";
                                //out << "00 ";
                                space--;
                            }while(space > 0);
                        }
                        else{
                            //cout << strtol(arg.c_str(), NULL, 16);
                            //out << strtol(arg.c_str(), NULL, 16) << " ";
                        }
                    }
                    else{ //É um número em decimal
                        if(strcasecmp(d.nome.c_str(), "SPACE") == 0){
                            long int space = strtol(arg.c_str(), NULL, 10);
                            do{
                                //cout << "00 ";
                                //out << "00 ";
                                space--;
                            }while(space > 0);
                        }
                        else{
                            //cout << arg;
                            //out << arg << " ";
                        }
                    }
                }
                else{
                    imprimeErro(ERRO_ARG_INCORRETO, linha);
                    erro_montagem = true;
                }
            }
            else if(d.formato == 'S'){
                if(isNumber(arg))
                    imprimeErro(ERRO_ARG_INCORRETO, linha);
                    erro_montagem = true;
            }
            break;
        }
    }


}

void separaOp(ofstream& out,vector<tipoInstrucaoIA32>& instrucoesIA32,map<string, tipoTSIA32>& simboloIA32, vector<tipoInstrucao>& instrucao,vector<tipoGramatica>& gramatica, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, vector<string> vTab, int linha){

    if(isInstrucao(instrucao, vTab[0])){ //INSTRUÇÃO A
        detectarErrosInstrucao(simbolo, vTab, gramatica,  linha);

        if(isAlfabeto(vTab[0])){
            if(vTab.size() > 1){
                if(vTab.size() == 3) //COPY ARG,    ARG
                    vTab[1].append(vTab[2]);
                escreveOp(out,instrucoesIA32,simboloIA32,gramatica, instrucao, diretiva, simbolo, vTab[0], vTab[1], 0, linha);
            }else
                escreveOp(out,instrucoesIA32,simboloIA32,gramatica, instrucao, diretiva, simbolo, vTab[0], "", 0, linha); //STOP
        }
        else{
            if(!isTokenValido(vTab[0]))
                imprimeErro(ERRO_INVALIDO, linha);
            else
                imprimeErro(ERRO_DESCONHECIDO, linha);
        }
    }
    else if(isDiretiva(diretiva, vTab[0])){
        if(isAlfabeto(vTab[0])){
            if(vTab.size() > 1)
                escreveOp(out,instrucoesIA32,simboloIA32,gramatica, instrucao, diretiva, simbolo, vTab[0], vTab[1], 1, linha);
            else
                escreveOp(out,instrucoesIA32,simboloIA32,gramatica, instrucao, diretiva, simbolo, vTab[0], "00", 1, linha); //SPACE SEM ARGUMENTO
        }
        else{
            if(!isTokenValido(vTab[0]))
                imprimeErro(ERRO_INVALIDO, linha);
            else
                imprimeErro(ERRO_DESCONHECIDO, linha);
        }
    }else{//é rótulo
            if(!isAlfanumericoUnderscore(vTab[0]) || !isTokenValido(vTab[0]))
                imprimeErro(ERRO_INVALIDO, linha);

            if(isInstrucao(instrucao, vTab[1])){
                detectarErrosInstrucao(simbolo, vTab, gramatica,  linha);
                if(isAlfabeto(vTab[1])){
                    if(vTab.size() > 2){
                        if(vTab.size() == 4) //LABEL:   COPY ARG,    ARG
                            vTab[2].append(vTab[3]);
                        escreveOp(out,instrucoesIA32,simboloIA32,gramatica, instrucao, diretiva, simbolo, vTab[1], vTab[2], 0, linha);
                    }
                    else
                        escreveOp(out,instrucoesIA32,simboloIA32,gramatica, instrucao, diretiva, simbolo, vTab[1], "", 0, linha); //LABEL: STOP
                }
                else{
                    if(!isTokenValido(vTab[1]))
                        imprimeErro(ERRO_INVALIDO, linha);
                    else
                        imprimeErro(ERRO_DESCONHECIDO, linha);
                }
            }
            else if(isDiretiva(diretiva, vTab[1])){
                if(isAlfabeto(vTab[1])){
                    if(vTab.size() > 2)
                        escreveOp(out,instrucoesIA32,simboloIA32,gramatica, instrucao, diretiva, simbolo, vTab[1], vTab[2], 1, linha);
                    else
                        escreveOp(out,instrucoesIA32,simboloIA32,gramatica, instrucao, diretiva, simbolo, vTab[1], "00", 1, linha); //SPACE SEM ARGUMENTO
                }
                else{
                    if(!isTokenValido(vTab[1]))
                        imprimeErro(ERRO_INVALIDO, linha);
                    else
                        imprimeErro(ERRO_DESCONHECIDO, linha);
                }
            }
    }

    //cout << "FIM DE SEPARA" << endl;
}

bool criaArqObj(ifstream& in, ofstream& out, vector<tipoGramatica>& gramatica, vector<tipoInstrucao>& instrucao, vector<tipoDiretiva>& diretiva, map<string, tipoTS>& simbolo, map<string, vector<int> >& uso, map<string, int>& definicao, vector<int>& bits, vector<tipoInstrucaoIA32>& instrucoesIA32,map<string,tipoTSIA32>& simboloIA32){
    string linha;
    bool liga = false;
    int i = 0;
    if(!definicao.empty() || !uso.empty()){
        //out << "TABLE USE" << endl;
        //cout << "TABLE USE" << endl;
        for (map<string, vector<int> >::iterator it = uso.begin(); it != uso.end(); ++it){
            for(vector<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++ it2){
                //out << it->first << " " << *it2 << endl;
                //cout << it->first << " " << *it2 << endl;
            }
        }
        //out << endl;
        //cout << endl;
        out << "TABLE DEFINITION" << endl;
        //cout << "TABLE DEFINITION" << endl;
        for (map<string, int>::iterator it = definicao.begin(); it != definicao.end(); ++it){
            //out << it->first << " " << it->second << endl;
            //cout << it->first << " " << it->second << endl;
        }
        //out << endl;
        //out << "R" << endl;
        //cout << "TABLE DEFINITION" << endl;
        //cout << "tamanho: " << bits.size();
        for (vector<int>::iterator it = bits.begin(); it != bits.end(); it++){
            //out << *it << ' ';
            //cout << it->first << " " << it->second << endl;
        }
        //out << endl << endl;
        //cout << endl;
        //out << "CODE" << endl;
        //cout << "CODE" << endl;
        liga = true;
    }
    //cout << "\n Comeca a segunda passagem";
    while(getline(in, linha)){
        vector<string> vTab;
        int tamanho;


        explode(vTab, linha, "\t");
        i = (int)strtol(vTab.back().c_str(), NULL, 10); //último elemento desta linha informa a linha no arquivo anterior
        vTab.pop_back(); //retira esse elemento

        tamanho = vTab[0].size();
        if(vTab[0][tamanho - 1] == ':'){
            vTab[0] = vTab[0].substr(0, tamanho - 1); //eliminando :
            if(!simbolo.empty()){

                map<string, tipoTS>::iterator it = simbolo.find(vTab[0]);
                if(it == simbolo.end() && isTokenValido(vTab[0]))
                    imprimeErro(ERRO_NAO_ENCONTRADO, i);
            }
        }

        //cout << linha << endl;
        //cin.get();
        separaOp(out,instrucoesIA32,simboloIA32,instrucao,gramatica, diretiva, simbolo, vTab,i);
    }
    in.clear();
    in.seekg(0, in.beg); //rewind

    if((!getBegin() && !getEnd()) && !getStop()) //se não tiver begin/end e não tiver stop
        imprimeErro(ERRO_STOP_AUSENTE); //imprima erro

    if(precisaData)
        imprimeErro(ERRO_DATA_AUSENTE);

    return liga;
}


bool detectarErrosInstrucao(map<string, tipoTS>& simbolo , vector<string> vTab, vector<tipoGramatica>& gramatica, int linha){
    bool erro_encontrado = false;
    /*if( analisaLexico(vTab) != ERRO_LEXICO ){                        // ANALISE LEXICA DE TODA A LINHA
        imprimeErro(ERRO_INVALIDO,linha);                   // IMPRIME O ERRO
        erro_encontrado = 1;
    }*/
    if(vTab.size() > 1){
        if( (vTab[0] == "DIV" && isDivisaoPorZero(vTab[1], simbolo)) ||
           (vTab[1] == "DIV" && isDivisaoPorZero(vTab[2], simbolo))){
            imprimeErro(ERRO_DIVISAO_POR_ZERO,linha);
            erro_encontrado = true;
        }
        if(isMudancaDeValorConstante(vTab, simbolo, gramatica )){
            imprimeErro(ERRO_ALTERANDO_CONSTANTE, linha);
            erro_encontrado = true;
        }
        if(isAcessoMemoriaNaoReservado(vTab,simbolo)){
            imprimeErro(ERRO_ACESSO_ENDERECO_NAO_RESERVADO,linha);
            erro_encontrado = true;
        }

        if(isJMPEnderecoInvalido(vTab, simbolo)){
            imprimeErro(ERRO_JMP_INVALIDO, linha);
            erro_encontrado = true;
        }

    }
    if(erro_encontrado)
        return true;
    else
        return false;
}
