#pragma once

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include "tabela.h"

using namespace std;

//Retorna se acha token no arquivo
bool buscaTokenArq(ifstream& arq, string token); //Busca sequencial
//  Linha   tab
//  0       (SECTION,TEXT)
//  1       (Rótulo, instrução, argumentos)
void criaVetorTab(ifstream& arq, vector<vector<string>>& mTab); //Mapeia o arquivo em linhas x tab

// Recebe um arquivo, preprocessa ele para ser lido pelo compilador e salva o arquivo preprocessado
// com o nome "titulo_arquivo" e retorna o objeto ofstream do arquivo preprocessado.
// caso dar erro retorna nulo
bool preProcessaArq(ifstream& arquivo, string titulo_arquivo);
