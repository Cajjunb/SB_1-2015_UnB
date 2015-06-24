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

		;******************** LER INTEIRO ********************
		;call lerInteiro
		;mov eax, [valor]
		;mov [A], eax		;move para a label que o usuário quer que tenha o inteiro
		;******************** FIM DE LER INTEIRO ********************

		;******************** ESCREVER INTEIRO ********************
		;mov eax, [A]		;label que contenha o número que o usuário quer imprimir
		mov eax, 1234
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
		push eax
		mov eax, 0
		mov [valor], eax	;valor neutro
		mov eax, [digitos]

		mov ecx, 4
		mov edx, 0
		div ecx
		mov [digitos], eax 	;quantidade de words
push eax
push ebx
push ecx
push edx
	mov ecx, [digitos]
	add ecx, 0x30
	mov [digitos], ecx

	mov eax, 4
	mov ebx, 1
	mov ecx, digitos
	mov edx, 1
	int 80h	

				mov eax, 4
				mov ebx, 1
				mov ecx, msg_debug5
				mov edx, DEBUG5SIZE
				int 80h
	
	mov ecx, [digitos]
	sub ecx, 0x30
	mov [digitos], ecx
pop edx
pop ecx
pop ebx
pop eax
		pop eax

		push ecx

		loopEscreverInteiro:

			cmp eax, 10	;Comparo o número com 10
			jb fimEscreverInteiro	;se número for menor que 10, vá para fimEscreverInteiro
;se não
push eax
push ebx
push ecx
push edx
				mov eax, 4
				mov ebx, 1
				mov ecx, msg_debug1
				mov edx, DEBUG1SIZE
				int 80h

pop edx
pop ecx
pop ebx
pop eax
			mov ecx, 10	
			mov edx, 0x0	; limpo edx porque, na divisão, eax concatena com edx
			div ecx	;divido eax/ecx
			
			add edx, 0x30		;edx tem o resto, então coloque na forma ascii
			mov ecx, [valor]	;pego o valor do endereço
			shl ecx, 8			;shifto 8 para esquerda os bits que estão em [valor] 
			or ecx, edx		;adiciono edx à ecx na posição menos significativa, sem interferir no que tinha antes
			mov [valor], ecx	;coloco o resultado em [ebx]
		
			pop ecx
			dec ecx
			cmp ecx, 0
			push ecx
			jne loopEscreverInteiro
push eax
push ebx
push ecx
push edx
				mov eax, 4
				mov ebx, 1
				mov ecx, msg_debug2
				mov edx, DEBUG2SIZE
				int 80h

pop edx
pop ecx
pop ebx
pop eax
			mov ebx, imprime
			mov ecx, [digitos]
			push eax
			mov eax, 4
			mul ecx		;multiplica quantidade de words por 4 bytes
			add ebx, eax	;adiciona esse endereço ao endereço de imprime, dando localização exata de onde tem que colocar essa word
			mov eax, [valor]
			or [ebx], eax	;coloca na posição correta
			dec ecx
			mov [digitos], ecx
			pop eax

			mov ecx, 0
			mov [valor], ecx
			pop ecx
			mov ecx, 4
			push ecx

			jmp loopEscreverInteiro		;volto pro loop

			fimEscreverInteiro:
				pop ecx
				dec ecx
				cmp ecx, 0

				jne continuaFimEscreverInteiro
push eax
push ebx
push ecx
push edx
				mov eax, 4
				mov ebx, 1
				mov ecx, msg_debug3
				mov edx, DEBUG3SIZE
				int 80h

pop edx
pop ecx
pop ebx
pop eax
				mov ebx, imprime
				mov ecx, [digitos]
				push eax
				mov eax, 4
				mul ecx		;multiplica quantidade de words por 4 bytes
				add ebx, eax	;adiciona esse endereço ao endereço de imprime, dando localização exata de onde tem que colocar essa word
				mov eax, [valor]
				or [ebx], eax	;coloca na posição correta
				dec ecx
				mov [digitos], ecx
				pop eax

				mov ecx, 0
				mov [valor], ecx

				continuaFimEscreverInteiro:
					add eax, 0x30	;eax é menor que 10, então coloque ele na posição menos significativa, sem interferir os outros bits
					mov ecx, [valor]
					shl ecx, 8 
					or ecx, eax
					mov [valor], ecx

					mov eax, [valor]
					or [imprime], eax	;coloca na posição correta
			
					push eax
					push ebx
					push ecx
					push edx
						mov eax, 4
						mov ebx, 1
						mov ecx, valor		;label que tem a resposta em ascii
						mov edx, 4
						int 80h	
					pop edx
					pop ecx
					pop ebx
					pop eax

				ret