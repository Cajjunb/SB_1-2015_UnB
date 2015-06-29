;**********************************
; 			ASSEMBLY INVENTADO
;	Lê um número do teclado, subtrai 10 e imprime resultado
;**********************************

SECTION TEXT
INPUT	A
LOAD	A
SUB	B
STORE	RESPOSTA
OUTPUT RESPOSTA
STOP

SECTION DATA
A:				SPACE		
B:				CONST		10
RESPOSTA:	SPACE		