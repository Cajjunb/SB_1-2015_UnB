
CFLAG= -std=c++11 -O2 
PATHSRC ='.\src\'
INCLUDE = arquivo.o base.o erro.o tabela.o 
PASSAGEM = passagem1.o passagem2.o

montador:	montadorCompleto
	rm -f *.o

ligador:	ligadorCompleto
	rm -f *.o

montadorCompleto:	$(INCLUDE) $(PASSAGEM) montador.o
	g++ $(CFLAG) $(INCLUDE) $(PASSAGEM) montador.o  -o montador

ligadorCompleto:	$(INCLUDE) ligador.o
	g++ $(CFLAG) $(INCLUDE) ligador.o  -o ligador

arquivo.o:	src/arquivo.cpp
	g++ -c $(CFLAG) src/arquivo.cpp

base.o: src/base.cpp
	g++ -c $(CFLAG) src/base.cpp

erro.o: src/erro.cpp
	g++ -c $(CFLAG) src/erro.cpp

passagem1.o: src/passagem1.cpp
	g++ -c $(CFLAG) src/passagem1.cpp

passagem2.o: src/passagem2.cpp
	g++ -c $(CFLAG) src/passagem2.cpp

tabela.o: src/tabela.cpp
	g++ -c $(CFLAG) src/tabela.cpp

#######################
#		Principal
#######################
montador.o: montador.cpp
	g++ -c $(CFLAG) montador.cpp

ligador.o: ligador.cpp
	g++ -c $(CFLAG) ligador.cpp