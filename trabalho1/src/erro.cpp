#include "../include/erro.h"

bool sectionData = false; //global que define se seção data foi declarada
bool sectionText = false; //global que define se seção text foi declarada
char sectionAtual = (char)0; //global que diz a atual seção
bool modBegin = false; //global que diz quando um módulo começa
bool modEnd = false; //global que diz quando um módulo termina
bool deuErro = false; //global que indica se deu erro em algum lugar
bool instrStop = false; //global que indica se tem stop
vector<int> linhasDefeito;

void imprimeErro(tipoErro e, int linha){
    deuErro = true;

    if(find(linhasDefeito.begin(), linhasDefeito.end(), linha) == linhasDefeito.end()){ //imprima somente um erro por linha
        linhasDefeito.push_back(linha);
        cout << ">>>>>ERRO: ";
        switch(e){
            case ERRO_REDEFINICAO:
                cout << "Semantico: Redefinicao de simbolos";
            break;
            case ERRO_ROTULO_REPETIDO:
                cout << "Semantico: Rotulo repetido";
            break;
            case ERRO_NAO_ENCONTRADO:
                cout << "Semantico: Rotulo nao encontrado";
            break;
            case ERRO_COMANDO_NAO_ENCONTRADO:
                cout << "Lexico: Instrucao ou diretiva nao encontrada";
            break;
            case ERRO_INVALIDO:
                cout << "Lexico: Token invalido";
            break;
            case ERRO_TEXT_AUSENTE:
                cout << "Semantico: SECTION TEXT ausente";
            break;
            case ERRO_DATA_AUSENTE:
                cout << "Semantico: SECTION DATA necessaria";
            break;
            case ERRO_BEGIN_AUSENTE:
                cout << "Semantico: Existe definicao de diretiva END, mas nao de LABEL: BEGIN";
            break;
            case ERRO_STOP_AUSENTE:
                cout << "Semantico: Instrucao STOP ausente";
            break;
            case ERRO_USO_INCORRETO:
                cout << "Sintatico: Uso incorreto de token";
            break;
            case ERRO_LOCAL_INCORRETO:
                cout << "Semantico: Token utilizado na secao incorreta";
            break;
            case ERRO_FALTA_DEFINICAO_EXTERN:
                cout << "Semantico: Falta de definicoes de simbolos externos";
            break;
            case ERRO_FALTA_ARQUIVO:
                cout << "Necessario passar outro arquivo para finalizacao do processo de ligacao";
            break;
            case ERRO_DIVISAO_POR_ZERO:
                cout << "Semantico: Nao e permitido divisao por zero";
            break;
            case ERRO_ALTERANDO_CONSTANTE:
                cout << "Semantico: Nao e permitido alterar valor de constante";
            break;
            case ERRO_SIMBOLO_NAO_DEFINIDO:
                cout << "Sintatico: Simbolo nao definido";
            break;
            case ERRO_SECTION_DATA_ANTES:
                cout << "Semantico: SECTION DATA definido antes de SECTION TEXT";
            break;
            case ERRO_OP_INVALIDO:
                cout << "Semantico: Operacao com rotulo invalidado";
            break;
            case ERRO_DEF_LABELS_MESMA_LINHA:
                cout << "Sintatico: Definicao de mais de um simbolo na mesma linha";
            break;
            case ERRO_ARG_INVALIDO:
                cout << "Sintatico: Instrucao com argumentos invalidados";
            break;
            case ERRO_QTD_ARG:
                cout << "Sintatico: Instrucao com quantidade de argumentos invalidos";
            break;
            case ERRO_ENCERRA_PROGRAMA:
                cout << "Semantico: Nao e permitido instrucao apos STOP";
            break;
            case ERRO_ACESSO_ENDERECO_NAO_RESERVADO:
                cout << "Semantico: Segmetation fault";
            break;
            case ERRO_ARG_INCORRETO:
                cout << "Sintatico: Instrucao ou diretiva com tipo de argumento incorreto";
            break;
            default:
                cout << "Erro Indefinido";
            break;
        }

        if(linha > -1)
            cout << "\t linha: " << linha;
        cout << "<<<<<" << endl;

    }
}

bool teveErro(){
    return deuErro;
}

bool getStop(){
    return instrStop;
}

void verificaSectionText(){
    if(!sectionText)
        imprimeErro(ERRO_TEXT_AUSENTE);
}

void atualizaSection(string arg, int linha){
    if(strcasecmp("DATA", arg.c_str()) == 0){
        if(!sectionData){
            sectionData = true;
            sectionAtual = 'd';
        }
        else
            imprimeErro(ERRO_REDEFINICAO, linha);
    }
    else if(strcasecmp("TEXT", arg.c_str()) == 0){
        if(!sectionText){
            if(sectionData) //se seção data estiver definida antes de texto
                imprimeErro(ERRO_SECTION_DATA_ANTES);
            sectionText = true;
            sectionAtual = 't';
        }
        else
            imprimeErro(ERRO_REDEFINICAO, linha);
    }
    else
        imprimeErro(ERRO_USO_INCORRETO, linha);
}

char getSectionAtual(){
    return sectionAtual;
}

void setBegin(bool s){
    modBegin = s;
}

void setStop(bool s){
    instrStop = s;
}
void setEnd(bool s){
    modEnd = s;
}

bool getBegin(){
    return modBegin;
}
bool getEnd(){
    return modEnd;
}

bool getData(){
    return sectionData;
}

bool isTokenValido(string token){
    if(token.size() > 100)
        return false;
    if(isNumber(token))
        return true;
    else{
        if(isdigit(token[0]))
            return false;
        else
            return true;
    }
}

int analisaLexico(vector<string> tokens){
    unsigned int tamanho = tokens.size();
    for ( unsigned int i = 0; i < tamanho; ++i){
        if(!isTokenValido(tokens[i]) )
            return i;
    }
    return ERRO_LEXICO;
}

bool isDivisaoPorZero(string& token,map<string, tipoTS>& simbolo){
    //cout << "\n\t SIMBOL[TOKEN] =" <<  simbolo[token].valorConstante;
    if(simbolo[token].valorConstante == 0)
        return true;
    else
        return false;
}

bool isMudancaDeValorConstante(vector<string> tokens, map<string, tipoTS>& simbolo,  vector<tipoGramatica>& gramatica ){
    tipoGramatica gramaticaInstrucao = pegaGramatica(gramatica ,tokens[0]);                            // pega gramatica
    bool args[3] = {false,false,false};
    for(unsigned int i = 0;  i < tokens.size(); i++){
        locale loc;
        toUpper(tokens[i],loc);
        map<string, tipoTS>::iterator it = simbolo.find(tokens[i]);
        if(it != simbolo.end()){
            args[i] = it->second.tipoConstante;
        }
    }
    if( ((gramaticaInstrucao.comportamentoConstante == NAO_ACEITA) && (args[1] == true) ) ||
        ( (gramaticaInstrucao.comportamentoConstante == SOMENTE_SRC )&&(args[2] == true)) ){
        return true;
    }
    else
        return false;
}

bool isJMPEnderecoInvalido(vector<string> tokens,map<string, tipoTS>& simbolo){
    string instrucao = tokens[0];
    if( (strcasecmp(instrucao.c_str(), "JMP") == 0)    ||
        (strcasecmp(instrucao.c_str(), "JMPP") == 0)   ||
        (strcasecmp(instrucao.c_str(), "JMZ") == 0)   ||
        (strcasecmp(instrucao.c_str(), "JMPN") == 0)
        ){
        tipoTS simboloConstante = simbolo[";END"];
        int endereco_maximo = simboloConstante.valorConstante;
        simboloConstante = simbolo[tokens[1]];
        if(endereco_maximo < simboloConstante.valorConstante){
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool isAcessoMemoriaNaoReservado(vector<string> tokens,map<string, tipoTS>& simbolo){
    int tamanho = tokens.size();
    std::vector<string> operandoSoma;
    for(int i = 1 ; i < tamanho; i++){
        explode(operandoSoma,tokens[i],"+");
        if(operandoSoma.size() > 1){
            locale loc;
            toUpper(operandoSoma[0],loc);
            map<string, tipoTS>::iterator it = simbolo.find(operandoSoma[0]);
            if(it != simbolo.end()){
                if((unsigned)std::stoi(operandoSoma[1])  > it->second.tamanhoMemoria -1)
                    return true;
            }
        }
    }
    return false;
}
void verificaLabels(vector<string> vTab, int linha){
    int contador = 0;

    for(vector<string>::iterator it = vTab.begin(); it != vTab.end(); ++it){
        int tamanho = (*it).size();

        if((*it)[tamanho - 1] == ':')
            contador++;
    }
    if(contador > 0)
        imprimeErro(ERRO_DEF_LABELS_MESMA_LINHA, linha);
}
