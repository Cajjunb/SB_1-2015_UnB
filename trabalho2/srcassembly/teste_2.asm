;**********************************
; 			ASSEMBLY INVENTADO
;	Lê dois números do teclado,A e B, não troca A por B  e imprime A e B
;**********************************
TROCA: EQU 0

SECTION DATA
A:				SPACE		
B:				SPACE		

SECTION TEXT
INPUT	A
INPUT B

IF TROCA
	COPY A, B

OUTPUT A
OUTPUT B

STOP