SECTION	TEXT
INPUT	Y
COPY	Y,RESULT_FAT
LOAD	Y, ONE ;<-- ERRO
SUB		ONE
JMPN	FIM
JMPZ	FIM
LOOP: STORE	AUX
MULT	RESULT_FAT
STORE	RESULT_FAT
LOAD	AUX
SUB		ONE
JmPZ	FIM
JMP 	LOOP
FIM:	OUTPUT	RESULT_FAT
STOP


SECTION	DATA
Y:	SPACE
ZERO:	CONST 0
ONE:	CONST 0x1
RESULT_FAT:	SPACE
AUX:	SPACE