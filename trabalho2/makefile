CFLAG= -std=c++11 -O2 
PATHSRC ='.\src\'
INCLUDE = tabela.o base.o
PASSAGEM = passagem1.o passagem2.o


all: $(INCLUDE)
	g++  $(INCLUDE) tradutor.cpp -o tradutor


base.o:
	g++ -c $(CFLAG) src/base.cpp

tabela.o: src/tabela.cpp
	g++ -c $(CFLAG) src/tabela.cpp