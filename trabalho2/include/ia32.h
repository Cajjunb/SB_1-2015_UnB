#pragma once

#include "base.h"
#include <map>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

//Cria Tabela de Símbolos para IA32
//Separa em .bss e .data baseado na tabela de símbolos do assembly inventado
void insereTabelaSimbolosIA32(string token, map<string, tipoTS>& simbolo, int *pcia32, map<string, tipoTSIA32>& simboloIA32);

//Edita tabela de símbolos de ia32
//Edita o endereço baseado num tamanho passado. Feito para SPACE
void editaTabelaSimbolosIA32(string token, map<string, tipoTSIA32>& simboloIA32, int tamanho);

