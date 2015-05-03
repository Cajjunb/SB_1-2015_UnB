MAIN = montador

all:	montador clean

clean:
	rm *.o

montador:	$(MAIN).o arquivo.o passagem1.o tabela.o
	g++ $(MAIN).o arquivo.o passagem1.o tabela.o -std=c++11  -o montador

arquivo.o:	src/arquivo.cpp
	g++ -c src/arquivo.cpp

passagem1.o: src/passagem1.cpp
	g++ -c src/passagem1.cpp

tabela.o: src/tabela.cpp
	g++ -c src/tabela.cpp

montador.o: montador.cpp
	g++ -c montador.cpp

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
