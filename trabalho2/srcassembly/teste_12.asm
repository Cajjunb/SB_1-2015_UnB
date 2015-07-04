;**********************************
; 			ASSEMBLY INVENTADO
;	Lê dois números do teclado, mutiplica ambos utilizando soma e imprime resultado
;**********************************

SECTION TEXT
INPUT	A
INPUT	B

LOAD ZERO
STORE RESPOSTA

multiplica: LOAD B
	JMPZ IMPRIME
	ADD MENOSUM
	STORE B

	LOAD RESPOSTA
	ADD A
	STORE RESPOSTA

	JMP multiplica

imprime: LOAD	RESPOSTA
OUTPUT RESPOSTA
STOP

SECTION DATA
A:				SPACE		
B:				SPACE
RESPOSTA:	SPACE
MENOSUM:	CONST -1
ZERO:			CONST    0x0		