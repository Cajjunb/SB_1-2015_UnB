#include "../include/arquivo.h"

using namespace std;


int main(){
    ifstream arq1;
    ofstream arq2;
    string line;

    arq1.open("../../tabelas/gramatica.txt");

    cout << buscaTokenArq(arq1, "load");
    arq1.close();

    arq2.open("output.txt");
    arq2 << "teste";
    arq2.close();
    getchar();
    return 0;
}
