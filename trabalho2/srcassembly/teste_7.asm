;**********************************
; 			ASSEMBLY INVENTADO
;	Lê um número do teclado
;	Soma 10
;	Subtrai 9
;	Multiplica por 25
;	Divide por 5
;	Mostra resultado
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
A:				SPACE		4
DEZ:				CONST		0xa
NOVE:				CONST		9
VINTECINCO:		CONST		25
CINCO:			CONT		5
RESPOSTA:	SPACE		4