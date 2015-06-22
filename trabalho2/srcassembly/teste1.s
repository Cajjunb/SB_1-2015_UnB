;Este programa pega o que o usuário digitou, A, e soma mais 10, B, imprimindo resultado na tela

section .data
	B	EQU	10

msg_debug1 		db '.DEU ERRADO POXA1: '
	DEBUG1SIZE		EQU $-msg_debug1
msg_debug2 		db 'DEU MAIS ERRADO AINDA POXA2: '
	DEBUG2SIZE		EQU $-msg_debug2
msg_debug3 		db 'No final: '
	DEBUG3SIZE		EQU $-msg_debug3

section .bss
	RESPOSTA	resb	4		;Usuário determinou que o tamanho da resposta terá no máximo 4 bytes
	A			resb	4		;coisa do usuário

	numero		resb	1 	; NECESSÁRIO: um byte para mostrar um número em ASCII
	valor			resb	1 	; NECESSÁRIO: 4 bytes para armazenar inteiro
	imprime		resb	32	;NECESSÁRIO: jeitinho para imprimir no máximo 32 dígitos, hehe

section .text
global _start
	
	;coloca na pilha o número inteiro que o usuário digitou
	;retorna no endereço valor o número que o usuário digitou (em inteiro)
	lerInteiro:
			loopLerInteiro:
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
				ret

	; eax: número
	;ebx: endereço de memória
	;escreverInteiro vai colocar o número em ascii na forma little endian, colocando este número no endereço ebx
	escreverInteiro: 
		loopEscreverInteiro:

			cmp eax, 10	;Comparo o número com 10
			jb fimEscreverInteiro	;se número for menor que 10, vá para fimEscreverInteiro
;se não
			mov ecx, 10	
			mov edx, 0x0	; limpo edx porque, na divisão, eax concatena com edx
			div ecx	;divido eax/ecx

			add edx, 0x30		;edx tem o resto, então coloque na forma ascii
			mov ecx, [ebx]	;pego o valor do endereço
			shl ecx, 8			;shifto 8 para esquerda os bits que estão em [valor]
			or ecx, edx		;adiciono edx à ecx na posição menos significativa, sem interferir no que tinha antes
			mov [ebx], ecx	;coloco o resultado em [ebx]

			jmp loopEscreverInteiro		;volto pro loop

			fimEscreverInteiro:

				add eax, 0x30	;eax é menor que 10, então coloque ele na posição menos significativa, sem interferir os outros bits
				mov ecx, [ebx]
				shl ecx, 8
				or ecx, eax
				mov [ebx], ecx

				ret


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
		
		;******************** ESCREVER INTEIRO ********************
;		mov eax, [valor]		;label que contenha o número que o usuário quer imprimir
;		mov ebx, imprime
;		call escreverInteiro
;		mov eax, 4
;		mov ebx, 1
;		mov ecx, imprime			;label que tem a resposta em ascii
;		mov edx, 32
;		int 80h	
		;******************** FIM DE ESCREVER INTEIRO ********************

		; Encerra programa
		mov eax, 1
		mov ebx, 0
		int 80h