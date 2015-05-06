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

// Recebe um arquivo, preprocessa ele para ser lido pelo compilador e salva o arquivo preprocessado
// com o nome "titulo_arquivo" e retorna o objeto ofstream do arquivo preprocessado.
// caso dar erro retorna nulo
bool preProcessaArq(char nomeArquivo[] , vector<tipoGramatica>& gramatica);

