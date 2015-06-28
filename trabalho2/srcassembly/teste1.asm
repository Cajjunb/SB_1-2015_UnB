;**********************************
; 			ASSEMBLY INVENTADO
;**********************************

SECTION TEXT
;INPUT	A
STORE	A
ADD	B
LOAD	RESPOSTA
;OUTPUT RESPOSTA
STOP

SECTION DATA
A:				SPACE		4
B:				CONST		10
RESPOSTA:	SPACE		4