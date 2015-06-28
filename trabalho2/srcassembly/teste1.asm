;**********************************
; 			ASSEMBLY INVENTADO
;**********************************

SECTION TEXT
INPUT	A
LOAD	A
ADD	B
STORE	RESPOSTA
OUTPUT RESPOSTA
STOP

SECTION DATA
A:				SPACE		4
B:				CONST		10
RESPOSTA:	SPACE		4