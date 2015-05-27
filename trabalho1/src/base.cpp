#include "../include/base.h"

void explode(vector<string>& destino, string& fonte, const char* delimitador){
    int tamanho = 0;
    size_t found; //verifica se string/char é encontrada
    string::size_type pos = 0;
    string::size_type prev = 0;

    while(delimitador[tamanho] != '\0' && delimitador[tamanho] != EOF){
        tamanho++;
    }

    found = fonte.find(delimitador); //verifica se acha, no argumento, a string delimitador

    if(found != string::npos){
        while ((pos = fonte.find(delimitador, prev)) != string::npos){ //enquanto cada ", " encontrando não for uma posição inválida da string
            destino.push_back(fonte.substr(prev, pos - prev)); //adicione no vetor de tabs a substring de onde este tab foi encontrado até o começo
            prev = pos + tamanho; //pula tamanho do delimitador
        }

    }
    destino.push_back(fonte.substr(prev)); //coloque a última subdivisão
    vector<string>::iterator it = destino.begin();
    while(it != destino.end()){ //retirandos strings vazias
        if((*it).empty()){
            destino.erase(it);
        }
        else
            ++it;
    }
}

bool isNumber(string token){
        //positivo                                  negativo
    std::string tokenAux = token;
    if(token[0] == '-'){
        tokenAux.erase(0,1);
    }
    if((tokenAux[0] == '0' && tokenAux[1] == 'X') || (tokenAux[1] == '0' && tokenAux[2] == 'X')){ //É um número hexadecimal
        if( (token.size() == 3 && token.back() == '0') || 0L != strtol(token.c_str(), NULL, 16)) //se pode ser convertido em um número
            return true;
        else
            return false;
    }
    else{
        if(tokenAux.find_first_not_of("0123456789") == std::string::npos) //se string só possui números
            return true;
    }

    return false;
}

void toUpper(string& str,locale loc){
    for (string::size_type i=0; i<str.length(); ++i)
        str[i] = toupper(str[i],loc);
}

