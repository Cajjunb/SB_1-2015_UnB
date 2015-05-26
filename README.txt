Trabalho 1 de Software Básico - 
1/2015 Turma B

Integrantes:
	Leandro Ramalho Motta Ferreira 		-10/0033571
	Sinayra Pascoal Cotts Moreira 		-10/0020666

Resumo:
	Este trabalho foi dividido em duas partes: o montador e o ligador para a linguagem Assembly inventado definida pelo professor. O montador gera um arquivo objeto em formato texto com códigos na base decimal. A linguagem escolhida para este trabalho foi C++ utilizando o padrão C11.

	O trabalho utiliza como estrutura de dados arquivos temporários. As instruções, diretivas e gramáticas foram descritas nos arquivos da pasta "tabelas". 

	TABELAS:
	gramatica.txt: tabela que dita instruções definidas na gramática.
		Formato:<nome_instrucao>	<nro_argumentos>	<comportamento_const>	<sintaxe>
		nome_instrucao:		Auto explicativo
		nro_argumentos:		Auto explicativo
		comportamento_constante: 	T = aceita constante como argumento
									F = Não aceita constante como argumento
									S = Somente aceita constante como argumento de source e não destino.
		sintaxe:			formato da instrucao

	instrucoes.txt: tabela que dita as relações codigo máquina e o assembly
		Formato:<nome_instrucao>	<opcode>			<tamanho_words>
			nome_instrucao:		Auto explicativo
			opcode:				Auto explicativo
			tamanho_words:	indica o tamanho de words no .o

	diretiva.txt: tabela que dita diretivas e informações sobre ela
		Formato:<nome_diretiva>		<nro_operandos>		<formato_diretivas>		<tamanho_em_word>
			nome_diretiva:		Auto explicativo
			nro_operandos:		Auto explicativo
			Tamanho_em_word: 	que será alocado no arquivo objeto
			formato_diretivas:	Ñ sei!


É necessário que o arquivo montador.cpp e ligador.cpp estejam um nível acima das pastas "src", "include" e "tabelas.

	O processo de montagem escolhido foi o de duas passagens, com vericação dos seguintes erros listados:
	1- Declaração ausente
	2- Declaração de símbolos (na sessão de dados) repetida
	3- Instrução com operandos invalidados
	4- Diretivas ou instruções na seção incorreta
	5- Instruções ou diretivas inválidas
	6- Divisão por constante com valor 0
	7- Instruções com quantidade de operandos incorretas
	8- Detecção de erros léxicos
		8.a) Números só podem ser escritos da forma decimal ou hexadecimal (indicado por 0x)
		8.b) Símbolos/Rótulos não podem começar com número
	9- Definição de rótulos (na sessão de texto) repetida
	10- Dois ou mais rótulos na mesma linha
		Nota: Não foram considerados os casos de rótulos ou símbolos separados por uma linha, levando em conta somente os casos em que instruções ou diretivas estiverem na mesma linha do rótulo ou símbolo
	11- Seção TEXT ausente
		11.a) Caso haja símbolos não definidos no código e não há seção de dados, também é indicado seção DATA ausente
	12- Seção inválida
	13- Segmetation Fault
	14- Modificação de valor de constante
		Nota: Foram considerados o caso das instruções STORE e COPY para modificação de valor de um endereço
	
	Caso ocorra algum desses erros, é exibido a mensagem de erro e a linha correspondente do arquivo original. Caso haja mais de um erro na mesma linha, é mostrado somente um único erro por linha.
	
	O ligador irá ligar dois arquivos somente quando necessário, indicando uma mensagem de erro quando um dos arquivos não precisar.

Para executar este trabalho:
	O trabalho foi feito no Lubuntu 14.04, no Windows 8.1 e testado no Windows 7 Starter. Porém, recomendamos que este trabalho seja executado em alguma distribuição Linux.
	Para compilar o montador, execute o comando:
		make montador
	Para compilar o ligador, execute o comando:
		make ligador
	Será gerado arquivos executáveis sem extensão para Linux.

	Para executar o montador, execute o comando:
		./montador arq1 arq2
		Nota: caso não sejam passados extensões, o montador irá supor que para "arq1", a extensão seja ".asm" e para "arq2" seja a extensão ".o". Caso o arquivo não precise ser ligado, "arq2" terá a extensão ".e" caso não seja passado extensão.
	
	Para executar o ligador, execute o comando:
		./ligador arq 1 arq2 arq3
		Nota: caso não sejam passados extensões, o ligador irá supor que para "arq1" e "arq2", a extensão seja ".o" e para "arq3" a extensão seja ".e".

PS: Este trabalho foi feito com amor pensando no bem estar dos nossos monitores (*^▽^*)