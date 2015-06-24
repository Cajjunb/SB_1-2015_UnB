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
msg_debug6 		db '.'
	DEBUG6SIZE		EQU $-msg_debug6

section .bss
	RESPOSTA	resb	4		;Usuário determinou que o tamanho da resposta terá no máximo 4 bytes
	A			resb	4		;coisa do usuário
	
	imprime		resb	32	; NECESSÁRIO: jeitinho para imprimir no máximo 32 dígitos, hehe
	valor			resb	4 	; NECESSÁRIO: 4 bytes para armazenar inteiro
	casas			resb	4	; NECESSÁRIO: casas decimais
	digitos		resb	4	; NECESSÁRIO: 4 bytes para contar quantidade de dígitos
	numero		resb	1 	; NECESSÁRIO: um byte para mostrar um número em ASCII. Precisa ser a última coisa adicionada no .bss

section .text
global _start
	_start:
		;******************** ZERANDO VARIÁVEIS ********************
		mov eax, 0
		mov [valor], eax	;valor neutro
		mov [imprime], eax	;valor neutro
		mov [numero], eax	;valor neutro
		mov [digitos], eax	;valor neutro
		mov eax, 1
		mov [casas], eax	;valor neutro
		;******************** FIM DE ZERANDO VARIÁVEIS ********************

		;******************** ESCREVER INTEIRO ********************
		;mov eax, [A]		;label que contenha o número que o usuário quer imprimir
		mov eax, 12345678
		mov ebx, 7
		mov [digitos], ebx
		call escreverInteiro
		
		;******************** FIM DE ESCREVER INTEIRO ********************

		;******************** ENCERRA PROGRAMA ********************
		mov eax, 1
		mov ebx, 0
		int 80h
		;******************** FIM DE ENCERRA PROGRAMA ********************


;*****************************************************
;			Escreve Inteiro
;	Arg: 
;	eax: número
;	
;	 escreverInteiro vai colocar o número em ascii na forma little endian, colocando este número no endereço ebx
;**********************************************************

	escreverInteiro:
		mov edx, 0
		mov [valor], edx

		push eax		;salva número na pilha
		mov eax, [digitos]
		mov ebx, 4
		mov edx, 0
		div ebx
		
		mov [digitos], eax	;quantidade de words
		pop eax		;pega número que está na pilha
		
		mov edx, 4
		push edx	;coloca quantidade de bytes na pilha

		loopEscreverInteiro: 
			cmp eax, 10	;Comparo o número com 10
			jb fimEscreverInteiro	;se número for menor que 10, vá para prepara volta
;se não
			mov ecx, 10	
			mov edx, 0x0	; limpo edx porque, na divisão, eax concatena com edx
			div ecx	;divido eax/ecx

			add edx, 0x30		;edx tem o resto, então coloque na forma ascii
			mov ecx, [valor]	;pego o valor do endereço
			shl ecx, 8			;shifto 8 para esquerda os bits que estão em [valor]
			or ecx, edx		;adiciono edx à ecx na posição menos significativa, sem interferir no que tinha antes
			mov [valor], ecx	;coloco o resultado em [ebx]

			pop edx
			dec edx
			cmp edx, -1
			push edx
			jne loopEscreverInteiro
			pop edx
			mov edx, 4
			push edx
			
			mov ebx, imprime
			push eax
			mov eax, 4
			mov edx, [digitos]
			mul edx
			dec edx
			mov [digitos], edx

			add ebx, eax
			mov eax, [valor]
			or[ebx], eax
			mov eax, 0
			mov [valor], eax

			pop eax

			jmp loopEscreverInteiro		

			fimEscreverInteiro:
				pop edx
				add eax, 0x30	;eax é menor que 10, então coloque ele na posição menos significativa, sem interferir os outros bits
				mov ecx, [valor]
				shl ecx, 8
				or ecx, eax
				mov [valor], ecx
				mov ecx, [valor]
				mov [imprime], ecx

				push eax
				push ebx
				push ecx
				push edx
					mov eax, 4
					mov ebx, 1
					mov ecx, imprime		;label que tem a resposta em ascii
					mov edx, 32
					int 80h	
				pop edx
				pop ecx
				pop ebx
				pop eax

				ret