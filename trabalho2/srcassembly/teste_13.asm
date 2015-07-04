;**********************************
; 			ASSEMBLY INVENTADO
;	Lê um número e subtrai ele por 10. 
;	Se ele for maior que 0, imprime 1.
;	Se ele for menor que 0, imprime 2
;	Se ele for igual a 0, volta pro início
;**********************************

SECTION DATA
A:				SPACE		
ZERO:			CONST    0x0		
UM:			CONST 1
DOIS:		const 2
dez:			const 10

SECTION TEXT
INICIO: INPUT	A
LOAD A
SUB dez
store A

LOAD A
JMPN MENOR
JMPP MAIOR
JMPZ INICIO

MENOR:  OUTPUT dois
STOP

MAIOR: OUTPUT UM
STOP