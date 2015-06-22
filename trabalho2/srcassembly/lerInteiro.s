;Este programa pega o que o usuário digitou, A, e soma mais 10, B, imprimindo resultado na tela

section .data
	B	EQU	10

msg_debug1 		db  0dh, 0ah, 'Debug1: '
	DEBUG1SIZE		EQU $-msg_debug1
msg_debug2 		db 0dh, 0ah, 'Debug2: '
	DEBUG2SIZE		EQU $-msg_debug2
msg_debug3 		db 0dh, 0ah, 'No final: '
	DEBUG3SIZE		EQU $-msg_debug3
msg_debug4 		db 0dh, 0ah, 'Loop '
	DEBUG4SIZE		EQU $-msg_debug4
msg_debug5 		db 0dh, 0ah, 'Debug3 '
	DEBUG5SIZE		EQU $-msg_debug5

section .bss
	RESPOSTA	resb	4		;Usuário determinou que o tamanho da resposta terá no máximo 4 bytes
	A			resb	4		;coisa do usuário
	
	imprime		resb	32	;NECESSÁRIO: jeitinho para imprimir no máximo 32 dígitos, hehe
	valor			resb	4 	; NECESSÁRIO: 4 bytes para armazenar inteiro
	numero		resb	1 	; NECESSÁRIO: um byte para mostrar um número em ASCII. Precisa ser a última coisa adicionada no .bss

section .text
global _start
	_start:
	
		;******************** LER INTEIRO ********************
		mov eax, [A]
		mov eax, 0
		mov [A], eax
		call lerInteiro
		mov eax, [valor]
		mov [A], eax		;move para a label que o usuário quer que tenha o inteiro
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
				mov ecx, A
				mov edx, 4
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
;*	 retorna no endereço "valor" o número que o usuário digitou (em inteiro)
;**********************************************************

	lerInteiro:
				
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

		jmp lerInteiro	
		
		fimLerInteiro:
			ret