#include "../include/erro.h"

bool sectionData = false; //global que define se seção data foi declarada
bool sectionText = false; //global que define se seção text foi declarada
char sectionAtual = (char)0; //global que diz a atual seção
bool modBegin = false; //global que diz quando um módulo começa
bool modEnd = false; //global que diz quando um módulo termina
bool deuErro = false; //global que indica se deu erro em algum lugar
bool instrStop = false; //global que indica se tem stop
vector<tipoLinhaErro> linhasDefeito; //global que indica quais linhas tem defeito

void imprimeErro(tipoErro e, int linha){
    deuErro = true;
    stringstream msg;
    bool existeTipoErro = false;
    tipoLinhaErro l;

    msg.str(string());
    msg.clear();

    l.linha = linha;

    msg << ">>>>>ERRO: ";
    switch(e){
        case ERRO_REDEFINICAO:
            msg << "Semantico: Redefinicao de simbolos";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_ROTULO_REPETIDO:
            msg << "Semantico: Rotulo repetido";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_NAO_ENCONTRADO:
            msg << "Semantico: Rotulo nao encontrado";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_COMANDO_NAO_ENCONTRADO:
            msg << "Sintatico: Instrucao ou diretiva nao encontrada";
            l.e = ERRO_SINTATICO;
        break;
        case ERRO_INVALIDO:
            msg << "Lexico: Token invalido";
            l.e = ERRO_LEXICO;
        break;
        case ERRO_TEXT_AUSENTE:
            msg << "Semantico: SECTION TEXT ausente";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_DATA_AUSENTE:
            msg << "Semantico: SECTION DATA necessaria";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_BEGIN_AUSENTE:
            msg << "Semantico: Existe definicao de diretiva END, mas nao de LABEL: BEGIN";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_STOP_AUSENTE:
            msg << "Semantico: Instrucao STOP ausente";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_USO_INCORRETO:
            msg << "Sintatico: Uso incorreto de token";
            l.e = ERRO_SINTATICO;
        break;
        case ERRO_LOCAL_INCORRETO:
            msg << "Semantico: Token utilizado na secao incorreta";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_FALTA_DEFINICAO_EXTERN:
            msg << "Semantico: Falta de definicoes de simbolos externos";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_FALTA_ARQUIVO:
            msg << "Necessario passar outro arquivo para finalizacao do processo de ligacao";
            l.e = ERRO_DESCONHECIDO;
        break;
        case ERRO_DIVISAO_POR_ZERO:
            msg << "Semantico: Nao e permitido divisao por zero";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_ALTERANDO_CONSTANTE:
            msg << "Semantico: Nao e permitido alterar valor de constante";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_SIMBOLO_NAO_DEFINIDO:
            msg << "Semantico: Simbolo nao definido";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_SECTION_DATA_ANTES:
            msg << "Semantico: SECTION DATA definido antes de SECTION TEXT";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_OP_INVALIDO:
            msg << "Semantico: Operacao com rotulo invalidado";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_DEF_LABELS_MESMA_LINHA:
            msg << "Sintatico: Definicao de mais de um simbolo na mesma linha";
            l.e = ERRO_SINTATICO;
        break;
        case ERRO_ARG_INVALIDO:
            msg << "Semantico: Instrucao com argumentos invalidados";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_QTD_ARG:
            msg << "Sintatico: Instrucao com quantidade de argumentos invalidos";
            l.e = ERRO_SINTATICO;
        break;
        case ERRO_ENCERRA_PROGRAMA:
            msg << "Semantico: Nao e permitido instrucao apos STOP";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_ACESSO_ENDERECO_NAO_RESERVADO:
            msg << "Semantico: Segmetation fault";
            l.e = ERRO_SEMANTICO;
        break;
        case ERRO_ARG_INCORRETO:
            msg << "Sintatico: Instrucao ou diretiva com tipo de argumento incorreto";
            l.e = ERRO_SINTATICO;
        break;
        default:
            msg << "Erro Indefinido";
            l.e = ERRO_DESCONHECIDO;
        break;
    }

    if(linha > -1)
        msg << "\t linha: " << linha;
    msg << "<<<<<" << endl;

    for(vector<tipoLinhaErro>::iterator it = linhasDefeito.begin(); it != linhasDefeito.end(); ++it){
        if((*it).linha == l.linha){
            if((*it).e == l.e){
                existeTipoErro = true;
                break; //quebra este loop, pois encontrou o mesmo tipo de erro na mesma linha
            }
        }
    }
    if(!existeTipoErro){
        linhasDefeito.push_back(l);
        cout << msg.str();
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
