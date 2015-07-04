Trabalho 2 de Software Básico - 
1/2015 Turma B

*******************************************
*
*	Integrantes:
*
*******************************************
	Leandro Ramalho Motta Ferreira 		-10/0033571
	Sinayra Pascoal Cotts Moreira 		-10/0020666

*******************************************
*
*	Resumo:
*
*******************************************

	Este trabalho foi dividido em apenas uma parte: tradutor.cpp para a linguagem Assembly inventado definida pelo professor. O tradutor recebe um arquivo de entrada com o assembly inventado e gera dois arquivos, um com o código assembly da Intel IA32 e outro com o código máquina das respectivas instruções geradas pelo primeiro arquivo. A linguagem escolhida para este trabalho foi C++ utilizando o padrão C11.

	O trabalho utiliza como estrutura de dados arquivos temporários. As instruções, diretivas, gramáticas e regras de tradução foram descritas nos arquivos da pasta "tabelas". 

É necessário que o arquivo tradutor.cpp estejam um nível acima das pastas "src", "include" e "tabelas.

	O processo de montagem escolhido foi o de duas passagens, com verificação dos seguintes erros listados:
	1- 	Declaração ausente
	2- 	Declaração de símbolos (na sessão de dados) repetida
	3- 	Instrução com operandos invalidados
	4- 	Diretivas ou instruções na seção incorreta
	5- 	Instruções ou diretivas inválidas
	6- 	Divisão por constante com valor 0
	7- 	Instruções com quantidade de operandos incorretas
	8- 	Detecção de erros léxicos
			8.a) Números só podem ser escritos da forma decimal ou hexadecimal (indicado por 0x)
			8.b) Símbolos/Rótulos não podem começar com número
	9- 	Definição de rótulos (na sessão de texto) repetida
	10-	Dois ou mais rótulos na mesma linha
			Nota: Não foram considerados os casos de rótulos ou símbolos separados por uma linha, levando em conta somente os casos em que instruções ou diretivas estiverem na mesma linha do rótulo ou símbolo
	11- 	Seção TEXT ausente
			11.a) Caso haja símbolos não definidos no código e não há seção de dados, também é indicado seção DATA ausente
	12- 	Seção inválida
	13- 	Segmetation Fault
	14- 	Modificação de valor de constante
		Nota: Foram considerados o caso das instruções STORE e COPY para modificação de valor de um endereço
	15- 	Instrução ou diretiva com tipo de argumento incorreto
	16-	Um ou mais diretivas EQU só podem ser definidas no início do código

	Caso ocorra algum desses erros, é exibido a mensagem de erro e a linha correspondente do arquivo original, não criando os arquivos de saída. Caso haja mais de um erro do mesmo tipo na mesma linha, é mostrado somente o primeiro erro deste tipo.
	
	Cada variável declarada na seção de dados do tipo SPACE possui o tamanho de 4 bytes.

	O arquivo em IA32 gerado no final sempre colocará as funções de ler inteiro do teclado e escrever inteiro na tela, mesmo que estas não sejam utilizadas.

*******************************************
*
*	Para executar este trabalho:
*
*******************************************
	O trabalho foi feito no Lubuntu 14.04 e no Windows 8.1. Porém, recomendamos que este trabalho seja executado em alguma distribuição Linux.
	Para compilar o tradutor, execute o comando:
		make tradutor
	Será gerado arquivos executáveis sem extensão para Linux.

	Para executar o montador, execute o comando:
		./tradutor arq1


PS: Este trabalho foi feito com suor, sangue e ódio. Esperamos não cometer os mesmos erros do primeiro trabalho (╯°□°）╯︵ ┻━┻
