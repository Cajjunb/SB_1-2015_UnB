;**********************************
; 			ASSEMBLY INVENTADO
;	Lê dois números do teclado,A e B,  troca A por B  e imprime A e B
;**********************************
TROCA: EQU 1

SECTION DATA
A:				SPACE		
B:				SPACE		

SECTION TEXT
INPUT	A
INPUT B

LOAD B
IF TROCA
	COPY A, B
STORE A

OUTPUT A
OUTPUT B

STOP