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

bool isAlfanumericoUnderscore(string token){
    for(int i = 0; i < (int)token.size(); i++){
        if(!isalnum(token[i])){ //se não for letra ou número
            if(token[i] != '_') //se não for _
                return false; //não é alfanumerico
        }
    }
    return true;
}

bool isAlfabeto(string token){
    for(int i = 0; i < (int)token.size(); i++){
        if(!isalpha(token[i])){ //se não for letra
                return false; //não é alfanumerico
        }
    }
    return true;
}

bool isNumber(string token){
    char *t;
    std::string tokenAux = token;
    if(token[0] == '-'){
        tokenAux.erase(0,1);
    }
    if((tokenAux[0] == '0' && tokenAux[1] == 'X') || (tokenAux[1] == '0' && tokenAux[2] == 'X')){ //É um número hexadecimal
        if( (token.size() == 3 && token.back() == '0') || 0L != strtol(token.c_str(), &t, 16)){ //se pode ser convertido em um número
            //cout << "tokenAux: " << tokenAux << endl;
            tokenAux.erase(0,2);

            //cout << "tokenAux: " << tokenAux << endl;
            if(tokenAux.find_first_not_of("0123456789ABCDEF") == std::string::npos) //se string só possui números e ABCDEF
                return true;
            else
                return false;
        }
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

bool temExtensao(string aux){

    for(int i = aux.size(); i > 0; i--){ //analisando de trás pra frente o nome do arquivo
        if(aux[i] == '.') //se tiver caracter .
            return true; //usuário passou extensão do arquivo
    }

    return false; //não foi passada extensao
}

std::vector<string> intParaHexLilEndian(int numero){
    int quociente = numero;
    short int resto = 0;
    int i = 0;
    char aux [33];
    std::vector<string> resultado(4);
    //cout << "numero: " << numero << endl;
    //cout << "\n\tHEX =\n\t" ;
    if (quociente < 0){
        //cout << "if1" << endl;
        //resto = quociente % 16;
        //quociente = quociente / 16;
        sprintf(aux,"%1x",numero);
        //cout << "aux: " << aux << endl;
        //cout << "resto: " << resto << endl;
        //cout << "quociente: " << quociente << endl;
        resultado[0].insert(0,aux,4,2);
        resultado[0].insert(0,aux,6,2);
        resultado[1].insert(0,aux,0,2);
        resultado[1].insert(0,aux,2,2);
    }else{
        while(quociente != 0 || i != 4){
            //cout << "while" << endl;
            resto = quociente % 16;
            quociente = quociente / 16;
            //itoa(resto,aux,16);
            sprintf(aux,"%1x",resto);
            resultado[i/2].insert(0,aux);
            i++;
            //cout << resto <<"," ;
        }
    }
    return resultado;
}
