#include "../include/ia32.h"

map<string, tipoTSIA32>simboloIA32; //global da tabela de símbolos de IA32, porque não temos tempo pra usar variáveis globais do jeito certo

void criaTabelaSimbolosIA32(map<string, tipoTS>& simbolo){

    for(map<string, tipoTS>::iterator it = simbolo.begin(); it != simbolo.end(); it++ ){
        tipoTS s = it->second;
        tipoTSIA32 s32;
        if(s.section != '0'){ //se símbolo for diferente de EQU
            if(s.section == 't'){ //se for rótulo na seção text
                s32.section = 't';
                s32.tamanho = 0;
                s32.valorConstante = 0;
                s32.tipoConstante = false;
            }
            else{ //é símbolo na seção data
                if(s.tipoConstante){ //se for constante
                    s32.section = 'd';

                }
            }
        }
    }
}

