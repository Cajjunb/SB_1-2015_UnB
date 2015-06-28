
CFLAG= -std=c++11 -O2 
PATHSRC ='.\src\'
INCLUDE = arquivo.o base.o erro.o tabela.o ia32.o
PASSAGEM = passagem1.o passagem2.o
MONTADOR = montador.o


tradutor:	tradutorCompleto
	rm -f *.o

tradutorCompleto:	$(INCLUDE) $(PASSAGEM)  $(MONTADOR) tradutor.o 
	g++ $(CFLAG) $(INCLUDE) $(PASSAGEM) $(MONTADOR) tradutor.o  -o tradutor

arquivo.o:	src/arquivo.cpp
	g++ -c $(CFLAG) src/arquivo.cpp

base.o: src/base.cpp
	g++ -c $(CFLAG) src/base.cpp

erro.o: src/erro.cpp
	g++ -c $(CFLAG) src/erro.cpp

ia32.o: src/ia32.cpp
	g++ -c $(CFLAG) src/ia32.cpp

passagem1.o: src/passagem1.cpp
	g++ -c $(CFLAG) src/passagem1.cpp

passagem2.o: src/passagem2.cpp
	g++ -c $(CFLAG) src/passagem2.cpp

tabela.o: src/tabela.cpp
	g++ -c $(CFLAG) src/tabela.cpp

montador.o: $(INCLUDE) $(PASSAGEM) $(MONTADOR) src/montador.cpp
	g++ -c $(CFLAG) $(INCLUDE) $(PASSAGEM) $(MONTADOR) src/montador.cpp

ligador.o: src/ligador.cpp
	g++ -c $(CFLAG) src/ligador.cpp

#######################
#		Principal
#######################
tradutor.o: tradutor.cpp
	g++ -c $(CFLAG) tradutor.cpp