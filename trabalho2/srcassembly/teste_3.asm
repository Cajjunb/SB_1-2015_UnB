;**********************************
; 			ASSEMBLY INVENTADO
;	Lê dois números do teclado,A e B,  troca A por B  e imprime A e B
;**********************************
TROCA: EQU 1

SECTION DATA
A:				SPACE		4
B:				SPACE		4

SECTION TEXT
INPUT	A
INPUT B

LOAD A
IF TROCA
	COPY A, B
STORE B

OUTPUT A
OUTPUT B

STOP