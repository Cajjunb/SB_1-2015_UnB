;**********************************
; 			ASSEMBLY INVENTADO
;	Lê um número do teclado, soma 10 e imprime resultado
;**********************************

SECTION TEXT
INPUT	A
LOAD	A
ADD	B
STORE	RESPOSTA
OUTPUT RESPOSTA
STOP

SECTION DATA
A:				SPACE		
B:				CONST		10
RESPOSTA:	SPACE		