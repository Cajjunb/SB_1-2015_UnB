SECTION	TEXT
INPUT	Y
COPY	Y, ZERO		;<-- ERRO
LOAD	Y
SUB		ONE
JMPN	FIM
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
ONE:	CONST 0x1
RESULT_FAT:	SPACE
AUX:	SPACE