CFLAG= -Wall
PATHMAIN='.\testes\'
PATHSRC ='.\src\'
PATHBIN ='.\bin\Release\'

all: arquivo.o  main.o ligacao

teste_preprocessa: arquivo.o tabela.o preprecessa.o 
	g++   $(PATHSRC)arquivo.o $(PATHSRC)tabela.o $(PATHMAIN)main.o  -o $(PATHBIN)teste_preprocessa1.exe

tabela.o:
	g++ -c $(CFLAG) $(PATHSRC)tabela.cpp -o $(PATHSRC)tabela.o

preprecessa.o:
	g++ -c $(CFLAG) $(PATHMAIN)testando_preprocessamento.cpp -o $(PATHMAIN)main.o

ligacao:
	g++ $(PATHMAIN)main.o $(PATHSRC)*.o -o '.\bin\Release\Teste1'

arquivo.o:
	g++ -c  $(CFLAG) $(PATHSRC)arquivo.cpp -o $(PATHSRC)arquivo.o

main.o:
	g++ -c $(CFLAG) .\testes\testando_arquivo.cpp -o $(PATHMAIN)main.o
