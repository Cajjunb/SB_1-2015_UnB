;Este programa pega o que o usuário digitou, A, e soma mais 10, B, imprimindo resultado na tela

section .data

section .bss
	valor			resb	4 	; NECESSÁRIO: 4 bytes para armazenar inteiro
	casas			resb	4	; NECESSÁRIO: casas decimais
	numero		resb	1 	; NECESSÁRIO: um byte para mostrar um número em ASCII. Precisa ser a última coisa adicionada no .bss

section .text
global _start
	_start:

		;******************** LER INTEIRO ********************
		call lerInteiro
		mov eax, [valor]
		mov [A], eax		;move para a label que o usuário quer que tenha o inteiro
		;******************** FIM DE LER INTEIRO ********************

		mov eax, [A]
		cmp eax, 123456
		je certo
		
		errado:
			push eax
			push ebx
			push ecx
			push edx
				
				mov eax, 4
				mov ebx, 1
				mov ecx, msg_debug7
				mov edx, DEBUG7SIZE
				int 80h	
			pop edx
			pop ecx
			pop ebx
			pop eax
		; Encerra programa
		mov eax, 1
		mov ebx, 0
		int 80h

		certo:
			push eax
			push ebx
			push ecx
			push edx
				
				mov eax, 4
				mov ebx, 1
				mov ecx, msg_debug6
				mov edx, DEBUG6SIZE
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