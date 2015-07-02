;**********************************
; 			ASSEMBLY INVENTADO
;	Lê um número do teclado, divide por 10 e imprime resultado
;**********************************

SECTION TEXT
INPUT	A
LOAD	A
DIV	B
STORE	RESPOSTA
OUTPUT RESPOSTA
STOP

SECTION DATA
A:				SPACE		
B:				CONST		10
RESPOSTA:	SPACE		