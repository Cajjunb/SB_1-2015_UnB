section	text
MOD_A:	BEGIN
Y:	EXTERN
MOD_B:	EXTERN
PUBLIC	VAL
PUBLIC	L1
INPUT	Y
LOAD	VAL
ADD	Y
STORE	Y+2
JMPP	MOD_B
L1:	STOP
section	data
VAL:	CONST	5
END