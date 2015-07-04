section .data
	newline			db 0dh, 0ah
	NEWLINESIZE		EQU $-newline

	B	EQU	10

section .bss
	imprime		resb	32	
	valor			resb	4 	
	casas			resb	4	
	digitos		resb	4	
	numero		resb	4 	

	A	resb	4
	RESPOSTA	resb	4

section .text
global _start

;*****************************************************
;			Ler inteiro
;	
;	 retorna no endereço "valor" o número que o usuário digitou (em inteiro)
;**********************************************************

	lerInteiro:
		;******************** ZERANDO VARIÁVEIS ********************
		mov eax, 0
		mov [valor], eax	;valor neutro
		mov [numero], eax	;valor neutro
		mov eax, 1
		mov [casas], eax	;valor neutro
		;******************** FIM DE ZERANDO VARIÁVEIS ********************

		lerInteiroLoop:
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
			
			sub ebx, 0x30		; tiro a parte ascii
			mov eax, [valor]	;pego o que tiver em [valor]
			mov ecx, [casas]
			mul ecx
			add eax, ebx		;adiciono
			mov [valor], eax	;retorno para [valor]

			mov eax, 10
			mov [casas], eax

			jmp lerInteiroLoop	
		
		fimLerInteiro:

			ret
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
	_start:

;***** INPUT *****

	push	eax
	call	lerInteiro
	mov eax,	[valor]
	mov	[A],	eax
	pop	eax

;***** LOAD *****

	mov	dword	eax,	[A]

;***** MULT *****

	mov	edx,	0
	mov	dword	ebx,	B
	imul	dword	ebx

;***** STORE *****

	mov	dword	[RESPOSTA],	eax

;***** OUTPUT *****

	push	eax
	mov eax,	[RESPOSTA]
	call escreverInteiro
	pop	eax

;***** STOP *****

	mov	eax,	1
	mov	ebx,	0
	int	80h
