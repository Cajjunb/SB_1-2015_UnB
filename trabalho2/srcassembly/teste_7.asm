;**********************************
; 			ASSEMBLY INVENTADO
;	Lê um número do teclado			0
;	Soma 10								10
;	Subtrai 9								1
;	Multiplica por 25						25
;	Divide por 5							5
;	Mostra resultado						5
;**********************************

SECTION TEXT
INPUT	A
LOAD	A
ADD	DEZ
SUB	NOVE
MULT	VINTECINCO
DIV	CINCO
STORE	RESPOSTA
OUTPUT RESPOSTA
STOP

SECTION DATA
A:				SPACE		
DEZ:				CONST		0xa
NOVE:				CONST		9
VINTECINCO:		CONST		25
CINCO:			CONST		5
RESPOSTA:	SPACE		