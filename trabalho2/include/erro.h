#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "string.h"
#include <vector>
#include <map>
#include "passagem1.h"
#include <locale>         // std::locale, std::isdigit

using namespace std;

//0: nenhuma seção foi declarada
//d: section data
//t: section text
char getSectionAtual(); //retorna seção atual do código

void setBegin(bool s); //seta quando módulo começa a ser definido
bool getBegin(); //retorna se módulo foi definido ou não
void setEnd(bool s); //seta quando módulo termina
bool getEnd(); //retorna se módulo foi definido ou não
bool getData(); //retorna se seção data já foi definida ou não
void setStop(bool s); //seta quando arquivo tem instrução STOP
bool getStop(); //retorna se arquivo tem instrução stop ou não
bool teveErro(); //retorna se arquivo gerou erros ou não

void imprimeErro(tipoErro e, int linha = -1); //imprime mensagem de erro. Mostra endereço de PC e linha caso seja passado
void verificaSectionText(); //Verifica se seção text foi declarada
void atualizaSection(string arg, int linha); //atualiza sectionAtual e verifica se é uma section válida
void verificaLabels(vector<string> vTab, int linha); //verifica se na linha existe mais de uma label. Se tiver, imprime erro

// Funcao que verifica dado um token se ele é valido lexicamente
bool isTokenValido(string token);
// Funcao que analissa lexicamente uma linha completa e retorna qual dos tokens é invalido, caso contrario retorna
// CORRETO_LEXICO
int analisaLexico(vector<string> tokens);

// Funcao que faz a verificacao se uma operacao de divisao sera por zero
// caso sim retorna true! caso contrario retorna false
bool isDivisaoPorZero(string& token,map<string, tipoTS>& simbolo);

//  Funcao que verifica se a instrucao passada vai acabar gerando uma mudança de valor de uma constante
//  Caso sim retorna true, caso não false.
bool isMudancaDeValorConstante(vector<string> tokens, map<string, tipoTS>& simbolo,  vector<tipoGramatica>& gramatica );

//  Funcao que verifica dado um vector de tokens, se é uma instrucao do tipo jmp e afins e se está pulando para um endereco
//  nao alocado, Caso sim retorna true, caso contrario retorna false
bool isJMPEnderecoInvalido(vector<string> tokens,map<string, tipoTS>& simbolo);

//  Funcao que verifica dado um vector de tokens, se uma instrucao ao tentar calcular o endereco acessa uma posicao na memoria que
//  Nao eh reservada para aquele simbolo. Caso ocorra o erro retorna True, caso contrario retorna falso.
bool isAcessoMemoriaNaoReservado(vector<string> tokens,map<string, tipoTS>& simbolo);
