;**********************************
; 			ASSEMBLY INVENTADO
;	Lê quatro números do teclado, armazena num vetor e imprime os números das posições ímpares (começando em 0)
;**********************************

SECTION TEXT
INPUT	NUM
LOAD NUM
STORE VETOR

INPUT NUM
LOAD NUM
STORE VETOR+1

INPUT NUM
LOAD NUM
STORE VETOR+2

INPUT NUM
LOAD NUM
STORE VETOR+3

INPUT NUM
LOAD NUM
STORE VETOR+4

OUTPUT VETOR+1
OUTPUT VETOR+3

STOP

SECTION DATA
NUM:				SPACE		
VETOR:	SPACE		4