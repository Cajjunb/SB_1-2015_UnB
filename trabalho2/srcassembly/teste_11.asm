;**********************************
; 			ASSEMBLY INVENTADO
;	Lê quatro números do teclado, armazena num vetor e imprime os números das posições ímpares (começando em 0)
;**********************************

SECTION TEXT
INPUT	NUM1
INPUT	NUM2
INPUT	NUM3
INPUT	NUM4

LOAD NUM1
STORE VETOR

LOAD NUM2
STORE VETOR+1

LOAD NUM3
STORE VETOR+2

LOAD NUM4
STORE VETOR+3

OUTPUT VETOR+1
OUTPUT VETOR+3

STOP

SECTION DATA
NUM1:				SPACE		
NUM2:				SPACE	
NUM3:				SPACE	
NUM4:				SPACE	
VETOR:	SPACE		4