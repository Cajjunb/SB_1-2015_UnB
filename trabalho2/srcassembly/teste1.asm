;**********************************
; 			ASSEMBLY INVENTADO
;**********************************

SECTION DATA
A:				SPACE		4
B:				CONST		10
RESPOSTA:	SPACE		4

SECTION TEXT
INPUT	A
STORE	A
ADD	B
LOAD	RESPOSTA
OUTPUT RESPOSTA
STOP