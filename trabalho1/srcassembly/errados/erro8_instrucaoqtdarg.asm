SECTION	TEXT
INPUT	Y
COPY	Y, RESULT_FAT
LOAD	Y
SUB		ONE
JMPN	FIM
JMPZ	FIM
LOOP: STORE	AUX
MULT	RESULT_FAT, ONE
STORE	RESULT_FAT
LOAD	AUX
SUB		ONE
JMPZ	FIM
JMP 	LOOP
FIM:	OUTPUT	RESULT_FAT
STOP FIM


SECTION	DATA
Y:	SPACE
ZERO:	CONST 0
ONE:	CONST 0x1
RESULT_FAT:	SPACE
AUX:	SPACE