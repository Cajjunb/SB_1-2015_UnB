CFLAG= -std=c++11 
PATHSRC ='.\src\'
INCLUDE = tabela.o base.o arquivo.o erro.o
PASSAGEM = passagem1.o passagem2.o base.o arquivo.o erro.o tabela.o

all: $(INCLUDE)
	g++  $(INCLUDE) tradutor.cpp -o tradutor
base.o:
	g++ -c $(CFLAG) src/base.cpp
erro.o:
	g++ -c $(CFLAG) src/erro.cpp
arquivo.o:
	g++ -c $(CFLAG) src/arquivo.cpp
tabela.o: src/tabela.cpp
	g++ -c $(CFLAG) src/tabela.cpp