;**********************************
; 			ASSEMBLY INVENTADO
;**********************************

SECTION TEXT
INPUT	A
loop:	LOAD	A
ADD	B
JMP loop
STORE	RESPOSTA
OUTPUT RESPOSTA
STOP

SECTION DATA
A:				SPACE		4
B:				CONST		10
RESPOSTA:	SPACE		4