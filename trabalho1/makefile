
CFLAG= -Wall -std=c++11
PATHMAIN='.\testes\'
PATHSRC ='.\src\'
PATHBIN ='.\bin\Release\'
MAIN = testando_preprocessamento

all:	montador clean

clean:
	rm *.o

montador:	$(MAIN).o arquivo.o passagem1.o tabela.o
	g++ $(CFLAG) $(MAIN).o arquivo.o passagem1.o tabela.o  -o montador.exe

arquivo.o:	src/arquivo.cpp
	g++ -c $(CFLAG) src/arquivo.cpp

passagem1.o: src/passagem1.cpp
	g++ -c $(CFLAG) src/passagem1.cpp

tabela.o: src/tabela.cpp
	g++ -c $(CFLAG) src/tabela.cpp

montador.o: montador.cpp
	g++ -c $(CFLAG) montador.cpp

################
# Arquivos de testes
################
testando_tabela.o: testes/testando_tabela.cpp
	g++ -c testes/testando_tabela.cpp

testando_arquivo.o: testes/testando_arquivo.cpp
	g++ -c testes/testando_arquivo.cpp

teste_passagem1.o: testes/teste_passagem1.cpp
	g++ -c testes/teste_passagem1.cpp

testando_preprocessamento.o: testes/testando_preprocessamento.cpp
	g++ -c testes/testando_preprocessamento.cpp
