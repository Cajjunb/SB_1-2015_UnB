
CFLAG= -Wall -std=c++11
PATHMAIN='.\testes\'
PATHSRC ='.\src\'
PATHBIN ='.\bin\Release\'
MAIN = montador

all:	montador clean

clean:
	rm $(PATHSRC)*.o

montador:	$(MAIN).o arquivo.o passagem1.o tabela.o erro.o base.o passagem2.o
	g++ $(CFLAG) $(MAIN).o arquivo.o passagem1.o tabela.o erro.o base.o passagem2.o -o montador.exe

arquivo.o:	src/arquivo.cpp
	g++ -c $(CFLAG) src/arquivo.cpp

passagem1.o: src/passagem1.cpp
	g++ -c $(CFLAG) src/passagem1.cpp

tabela.o: src/tabela.cpp
	g++ -c $(CFLAG) src/tabela.cpp

erro.o: src/erro.cpp
	g++ -c $(CFLAG) src/erro.cpp

base.o: src/base.cpp
	g++ -c $(CFLAG) src/base.cpp

montador.o: montador.cpp
	g++ -c $(CFLAG) montador.cpp

passagem2.o: src/passagem2.cpp
	g++ -c $(CFLAG) src/passagem2.cpp

################
# Arquivos de testes
################
testando_tabela.o: testes/testando_tabela.cpp
	g++ -c testes/testando_tabela.cpp

testando_arquivo.o: testes/testando_arquivo.cpp
	g++ -c testes/testando_arquivo.cpp

testando_passagem1.o: testes/testando_passagem1.cpp
	g++ -c testes/testando_passagem1.cpp

testando_preprocessamento.o: testes/testando_preprocessamento.cpp
	g++ -c testes/testando_preprocessamento.cpp


