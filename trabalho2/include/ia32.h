#include "base.h"

//  AQUI VEM UM COMENTÁRIO DO LEANDRO, YAY
string inventadoParaIA32(vector<tipoInstrucao>& instrucoes,string operacao);

//Cria Tabela de Símbolos para IA32
//Separa em .bss e .data baseado na tabela de símbolos do assembly inventado
void criaTabelaSimbolosIA32(map<string, tipoTS>& simbolo);
