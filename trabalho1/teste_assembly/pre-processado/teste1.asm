SECTION	TEXT
ROT:	INPUT	N1
COPY	N1, N4
COPY	N2, N3
COPY	N3, N3+1
OUTPUT	N3+1
OUTPUT	N3
STOP	
SECTION	DATA
N1:	SPACE
N2:	CONST	-0x10
N3:	SPACE	2
N4:	SPACE