SECTION	TEXT
INPUT	Y
COPY	Y,RESULT_FAT
LOAD	Y
SUB		ONE
JMPN	FIM2 	;<-- ERRO
JMPZ	FIM
LOOP: STORE	AUX
MULT	RESULT_FAT
STORE	RESULT_FAT
LOAD	AUX
SUB		ONE
JMPZ	FIM
JMP 	LOOP
FIM:	OUTPUT	RESULT_FAT
STOP


SECTION	DATA
Y:	SPACE
ZERO:	CONST 0
ONE:	CONST 1
RESULT_FAT:	SPACE
AUX:	SPACE