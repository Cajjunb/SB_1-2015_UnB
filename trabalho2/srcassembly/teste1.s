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
	
	imprime		resb	32	; NECESSÁRIO: jeitinho para imprimir no máximo 32 dígitos, hehe
	valor			resb	4 	; NECESSÁRIO: 4 bytes para armazenar inteiro
	digitos		resb	4	; NECESSÁRIO: 4 bytes para contar quantidade de dígitos
	numero		resb	1 	; NECESSÁRIO: um byte para mostrar um número em ASCII. Precisa ser a última coisa adicionada no .bss

section .text
global _start
	_start:
	
		;******************** LER INTEIRO ********************
		mov eax, [valor]
		mov eax, 0
		mov [valor], eax	;valor neutro
		mov eax, 1
		mov [digitos], eax	;valor neutro
		call lerInteiro
		mov eax, [valor]
		mov [A], eax		;move para a label que o usuário quer que tenha o inteiro
		;******************** FIM DE LER INTEIRO ********************

		;******************** ESCREVER INTEIRO ********************
		mov eax, [A]		;label que contenha o número que o usuário quer imprimir
		mov ebx, imprime
		call escreverInteiro
		mov eax, 4
		mov ebx, 1
		mov ecx, imprime			;label que tem a resposta em ascii
		mov edx, 32
		int 80h	
		;******************** FIM DE ESCREVER INTEIRO ********************

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
			
		sub ebx, 0x30		; tiro a parte ascii
		mov eax, [valor]	;pego o que tiver em [valor]
		mov ecx, [digitos]
		mul ecx
		add eax, ebx		;adiciono
		mov [valor], eax	;retorno para [valor]

		mov eax, [digitos]
		mov ecx, 10
		mul ecx
		mov [digitos], eax
		
		mov [digitos], ecx

		jmp lerInteiro	
		
		fimLerInteiro:
			ret

;*****************************************************
;			Escreve Inteiro
;	Arg: 
;	eax: número
;	ebx: endereço de memória
;	
;	 escreverInteiro vai colocar o número em ascii na forma little endian, colocando este número no endereço ebx
;**********************************************************
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
			;shr ecx, 8			;shifto 8 para esquerda os bits que estão em [valor]   ********************AQUI QUE FALTA, WUUU
			or ecx, edx		;adiciono edx à ecx na posição menos significativa, sem interferir no que tinha antes
			mov [ebx], ecx	;coloco o resultado em [ebx]
			add ebx, 1

			jmp loopEscreverInteiro		;volto pro loop

			fimEscreverInteiro:
				add ebx, 1
				add eax, 0x30	;eax é menor que 10, então coloque ele na posição menos significativa, sem interferir os outros bits
				mov ecx, [ebx]
				;shr ecx, 8  ; ********************AQUI QUE FALTA, WUUU
				or ecx, eax
				mov [ebx], ecx

				ret