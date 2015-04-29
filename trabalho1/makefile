CFLAG= -Wall
PATHMAIN='.\testes\'
PATHSRC ='.\src\'

all: arquivo.o  main.o ligacao

ligacao:
	g++ $(PATHMAIN)main.o $(PATHSRC)arquivo.o -o '.\bin\Release\Teste1'

arquivo.o:
	g++ -c  $(CFLAG) $(PATHSRC)arquivo.cpp -o $(PATHSRC)arquivo.o

main.o:
	g++ -c $(CFLAG) .\testes\testando_arquivo.cpp -o $(PATHMAIN)main.o
