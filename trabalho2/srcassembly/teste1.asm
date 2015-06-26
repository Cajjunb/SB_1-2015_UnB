;**********************************
; 			ASSEMBLY INVENTADO
;**********************************

SECTION TEXT
;INPUT	A
STORE	A
ADD	B
LOAD	RESPOSTA
;OUTPUT RESPOSTA
;STOP

SECTION DATA
A:				SPACE
B:				CONST		10
RESPOSTA:	SPACE		4

D:				CONST		0x200
F:				CONST		120