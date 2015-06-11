#pragma once

#include "arquivo.h"
#include "tabela.h"
#include "passagem1.h"
#include "passagem2.h"
#include "erro.h"
#include "base.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

void monta(vector<string> asmInventado); //Cria arquivo .e baseado no código assembly
