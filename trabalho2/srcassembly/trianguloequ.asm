TRIANGULO: EQU 0x0
TRIANGULO: EQU 0x1
SECTION DATA
B:		SPACE
H:		SPACE
R:		SPACE
DOIS:	CONST		2
SECTION TEXT
INPUT		B
INPUT		H
LOAD		B
MULT		H
IF TRIANGULO
DIV		DOIS
STORE		R
OUTPUT	R
STOP