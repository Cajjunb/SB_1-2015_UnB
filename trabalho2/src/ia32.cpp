#include "../include/ia32.h"

string inventadoParaIA32(vector<tipoInstrucao>& instrucoes,string operacao){
	bool achado = false;
	for(int i = 0; i < (int)instrucoes.size(); i++){
        if(strcasecmp(instrucoes[i].nome.c_str(), operacao.c_str()) == 0)
        	achado = true;
    }
    if(achado){

    }
}

void editaTabelaSimbolosIA32(string token, map<string, tipoTSIA32>& simboloIA32, int tamanho){
    map<string, tipoTSIA32>::iterator it;
    it = simboloIA32.find(token);
    if(it != simboloIA32.end())
        (it->second).endereco += tamanho;
}

void insereTabelaSimbolosIA32(string token, map<string, tipoTS>& simbolo, int *pcia32, map<string, tipoTSIA32>& simboloIA32){
    map<string, tipoTS>::iterator rot;
    tipoTSIA32 s32;
    tipoTS s;

    rot = simbolo.find(token);
    s = rot->second;

    if(s.section != '0'){ //se símbolo for diferente de EQU
        if(s.section == 't'){ //se for rótulo na seção text
            s32.section = 't';
            s32.endereco = *pcia32;
            s32.valorConstante = 0;
            s32.tipoConstante = false;
        }
        else{ //é símbolo na seção data
            if(s.tipoConstante){ //se for constante
                s32.section = 'd';
                s32.endereco = *pcia32 + 4; //mais 4 de constante que é inteiro
                s.valorConstante = s.valorConstante;
                s32.tipoConstante = true;
            }
            else{ //É um space
                s32.section = 'b';
                s32.endereco = *pcia32;
                s32.valorConstante = 0;
                s32.tipoConstante = false;
            }
        }
    }

    simboloIA32.insert(pair<string, tipoTSIA32>(rot->first, s32));
}
