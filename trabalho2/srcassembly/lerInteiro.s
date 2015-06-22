;Este programa pega o que o usuário digitou, A, e soma mais 10, B, imprimindo resultado na tela

section .data
	B	EQU	10

msg_debug1 		db '.DEU ERRADO POXA1: '
	DEBUG1SIZE		EQU $-msg_debug1
msg_debug2 		db 'DEU MAIS ERRADO AINDA POXA2: '
	DEBUG2SIZE		EQU $-msg_debug2
msg_debug3 		db 'No final: '
	DEBUG3SIZE		EQU $-msg_debug3
msg_debug4 		db 'Loop '
	DEBUG4SIZE		EQU $-msg_debug4

section .bss
	RESPOSTA	resb	4		;Usuário determinou que o tamanho da resposta terá no máximo 4 bytes
	A			resb	4		;coisa do usuário

	numero		resb	1 	; NECESSÁRIO: um byte para mostrar um número em ASCII
	valor			resb	1 	; NECESSÁRIO: 4 bytes para armazenar inteiro
	imprime		resb	32	;NECESSÁRIO: jeitinho para imprimir no máximo 32 dígitos, hehe

section .text
global _start
	_start:
	
		;******************** LER INTEIRO ********************
		call lerInteiro
		;mov eax, [valor]
		;mov [A], eax		;move para a label que o usuário quer que tenha o inteiro
		;******************** FIM DE LER INTEIRO ********************
push eax
push ebx
push ecx
push edx

mov eax, 4
				mov ebx, 1
				mov ecx, msg_debug3
				mov edx, DEBUG3SIZE
				int 80h

				mov eax, 4
				mov ebx, 1
				mov ecx, valor
				mov edx, 1
				int 80h
pop edx
pop ecx
pop ebx
pop eax


		; Encerra programa
		mov eax, 1
		mov ebx, 0
		int 80h


;*****************************************************
;			Ler inteiro
;	
;*	 retorna no endereço valor o número que o usuário digitou (em inteiro)
;**********************************************************

	lerInteiro:
			loopLerInteiro:
push eax
push ebx
push ecx
push edx
				mov eax, 4
				mov ebx, 1
				mov ecx, msg_debug4
				mov edx, DEBUG4SIZE
				int 80h

pop edx
pop ecx
pop ebx
pop eax
				mov eax, 0
				mov [numero], eax
				mov eax, 3
				mov ebx, 0
				mov ecx, numero		;Leio um byte em ascii
				mov edx, 1
				int 80h
			
				mov ebx, [numero]		;transfere para variável ebx o que está em numero

				cmp ebx, 0x0A		;compara se é igual a enter
				jz fimLerInteiro

				;sub ebx, 0x30		; tiro a parte ascii
				add ebx, 0x01

				mov eax, [valor]	;pego o que tiver em [valor]
				add eax, ebx		;adiciono
				mov [valor], eax	;retorno para [valor]

push eax
push ebx
push ecx
push edx
				mov eax, 4
				mov ebx, 1
				mov ecx, msg_debug1
				mov edx, DEBUG1SIZE
				int 80h

				mov eax, 4
				mov ebx, 1
				mov ecx, valor
				mov edx, 1
				int 80h
pop edx
pop ecx
pop ebx
pop eax

				jmp loopLerInteiro	
			
			fimLerInteiro:
push eax
push ebx
push ecx
push edx
				mov eax, 4
				mov ebx, 1
				mov ecx, msg_debug2
				mov edx, DEBUG2SIZE
				int 80h

				mov eax, 4
				mov ebx, 1
				mov ecx, valor
				mov edx, 1
				int 80h
pop edx
pop ecx
pop ebx
pop eax
				ret