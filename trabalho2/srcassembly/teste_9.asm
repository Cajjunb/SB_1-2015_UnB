;**********************************
; 			ASSEMBLY INVENTADO
;	Lê dois números do teclado, multiplica um por 2 e outro por 3, imprimindo ambos
;**********************************

SECTION TEXT
INPUT	A
INPUT	B

LOAD A
MULT DOIS
STORE RES_A

LOAD B
MULT TRES
STORE 														RES_B


OUTPUT RES_A
OUTPUT RES_b
STOP

SECTION DATA
A:				SPACE		
B:				SPACE
RES_A:	SPACE		
RES_B:	SPACE	
DOIS:	CONST 2
TRES: CONST 0x003