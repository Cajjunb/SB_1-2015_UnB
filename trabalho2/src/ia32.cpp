#include "../include/ia32.h"

void editaTabelaSimbolosIA32(string token, map<string, tipoTSIA32>& simboloIA32, int tamanho){
    map<string, tipoTSIA32>::iterator it;
    it = simboloIA32.find(token);
    if(it != simboloIA32.end())
        (it->second).tamanho = tamanho;

    //enquanto antes for diferente de it:
    //A: SPACE  -endereço 0, tamanho 1
    //B: SPACE  -endereço 1 (porque A vem antes de B), tamanho 1
    //C: SPACE  -endereco 2 (porque A e B vem antes de C), tamanho 1
    for(map<string, tipoTSIA32>::iterator antes = simboloIA32.begin() ; antes != simboloIA32.end() && antes != it; ++antes){

        if(antes->second.section == it->second.section){
            //cout << "it: " << it->first << "-" <<  it->second.endereco << " antes: " << antes->first << endl;
            it->second.endereco += antes->second.tamanho;

            //cout << "it: " << it->first << "-" <<  it->second.endereco << " antes: " << antes->first << endl;
            //cin.get();
        }
    }
}

void insereTabelaSimbolosIA32(string token, map<string, tipoTS>& simbolo, int *pcia32, map<string, tipoTSIA32>& simboloIA32){
    map<string, tipoTS>::iterator rot;
    tipoTSIA32 s32;
    tipoTS s;

    rot = simbolo.find(token);
    if(rot != simbolo.end()){
        s = rot->second;

        if(s.section != '0'){ //se símbolo for diferente de EQU
            if(s.section == 't'){ //se for rótulo na seção text
                s32.section = 't';
                s32.endereco = *pcia32;
                s32.valorConstante = 0;
                s32.tipoConstante = false;
                s32.tamanho = 0;
            }
            else{ //é símbolo na seção data
                if(s.tipoConstante){ //se for constante
                    s32.section = 'd';
                    s32.endereco = 0;
                    s32.valorConstante = s.valorConstante;
                    s32.tipoConstante = true;
                    s32.tamanho = 4;
                }
                else{ //É um space
                    s32.section = 'b';
                    s32.endereco = 0;
                    s32.valorConstante = 0;
                    s32.tipoConstante = false;
                    s32.tamanho = 0;
                }
            }
        }
        simboloIA32.insert(pair<string, tipoTSIA32>(rot->first, s32));
    }
}
