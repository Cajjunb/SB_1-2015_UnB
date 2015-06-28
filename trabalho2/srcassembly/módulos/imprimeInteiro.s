;Este programa pega o que o usuário digitou, A, e soma mais 10, B, imprimindo resultado na tela

section .data
	B	EQU	10

newline			db 0dh, 0ah
NEWLINESIZE		EQU $-newline

section .bss
	imprime		resb	32	; NECESSÁRIO: jeitinho para imprimir no máximo 9 dígitos, hehe
	valor			resb	4 	; NECESSÁRIO: 4 bytes para armazenar inteiro
	casas			resb	4	; NECESSÁRIO: casas decimais
	digitos		resb	4	; NECESSÁRIO: 4 bytes para contar quantidade de dígitos
	numero		resb	1 	; NECESSÁRIO: um byte para mostrar um número em ASCII. Precisa ser a última coisa adicionada no .bss

	RESPOSTA	resb	4		;Usuário determinou que o tamanho da resposta terá no máximo 4 bytes
	A			resb	4		;coisa do usuário

section .text
global _start
	_start:
			
		
		;******************** ESCREVER INTEIRO ********************
		mov eax, 12355
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
		;******************** ZERANDO VARIÁVEIS ********************
		mov ebx, 0
		mov [valor], ebx	;valor neutro
		mov [imprime], ebx	;valor neutro
		mov [digitos], ebx	;valor neutro
		;******************** FIM DE ZERANDO VARIÁVEIS ********************		

		push eax
		mov ebx, 0	;quantidade de dígitos
		mov ecx, 10
		escreverInteiroContaDigitos:
			mov edx, 0
			div ecx
			inc ebx
			cmp eax, 0
			jne escreverInteiroContaDigitos
		pop eax
		dec ebx
		mov [digitos], ebx

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
			cmp edx, 0
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

			add ebx, eax
			mov eax, [valor]
			or[ebx], eax
			mov eax, 0
			mov [valor], eax
			
			mov edx, [digitos]
			dec edx
			mov [digitos], edx

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
					
					mov eax, 4
					mov ebx, 1
					mov ecx, newline
					mov edx, NEWLINESIZE
					int 80h	
				pop edx
				pop ecx
				pop ebx
				pop eax

				ret