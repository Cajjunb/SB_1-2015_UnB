; Dado um número que o usuário digita, somar todos os dígitos

section .data
	msg_welcome 	db 'Bem vindo!'
	WELCOMESIZE	EQU $-msg_welcome

	msg_input 		db 'Digite um numero: '
	INPUTSIZE			EQU $-msg_input

	msg_output 		db 'O resulto da soma de cada digito e: '
	OUTPUTSIZE		EQU $-msg_output

msg_debug 		db 'OPA: '
	DEBUGSIZE		EQU $-msg_debug

	newline			db 0dh, 0ah
	NEWLINESIZE		EQU $-newline

section .bss
	soma			resb	10
	valor			resb	4
	numero		resb	1 ; um byte para mostrar um número em ASCII

section .text
global _start
	
	;--Argumentos
	; eax: número
	;ebx: endereço de memória
	;arruma vai colocar o número em ascii na forma little endian
	arruma: 

			cmp eax, 10	;Comparo o número com 10
			jb preparaVolta	;se número for menor que 10, vá para prepara volta
;se não
			mov ecx, 10	
			mov edx, 0x0	; limpo edx porque, na divisão, eax concatena com edx
			div ecx	;divido eax/ecx

			add edx, 0x30		;edx tem o resto, então coloque na forma ascii
			mov ecx, [ebx]	;pego o valor do endereço
			shl ecx, 8			;shifto 8 para esquerda os bits que estão em [valor]
			or ecx, edx		;adiciono edx à ecx na posição menos significativa, sem interferir no que tinha antes
			mov [ebx], ecx	;coloco o resultado em [ebx]

			jmp arruma		;volto pro arruma

			preparaVolta:

				add eax, 0x30	;eax é menor que 10, então coloque ele na posição menos significativa, sem interferir os outros bits
				mov ecx, [ebx]
				shl ecx, 8
				or ecx, eax
				mov [ebx], ecx

			jmp resultado

	_start:
		mov eax, 4
		mov ebx, 1
		mov ecx, newline
		mov edx, NEWLINESIZE
		int 80h

		mov eax, 4
		mov ebx, 1
		mov ecx, msg_welcome
		mov edx, WELCOMESIZE
		int 80h

		mov eax, 4
		mov ebx, 1
		mov ecx, newline
		mov edx, NEWLINESIZE
		int 80h

		mov eax, 4
		mov ebx, 1
		mov ecx, newline
		mov edx, NEWLINESIZE
		int 80h

		mov eax, 4
		mov ebx, 1
		mov ecx, msg_input
		mov edx, INPUTSIZE
		int 80h
		
		mov eax, [valor]
		mov eax, 0
		mov [valor], eax

		loop_leitura:

			mov eax, 3
			mov ebx, 0
			mov ecx, numero		;Leio um byte em ascii
			mov edx, 1
			int 80h
			
			mov ebx, [numero]		;transfere para variável ebx o que está em numero
			cmp ebx, 0x0A		;compara se é igual a enter
			jz fim

			sub ebx, 0x30		; tiro a parte ascii

			mov eax, [valor]	;pego o que tiver em [valor]
			add eax, ebx		;adiciono
			mov [valor], eax	;retorno para [valor]

			jmp loop_leitura
		
		fim:

			mov eax, 4
			mov ebx, 1
			mov ecx, newline
			mov edx, NEWLINESIZE
			int 80h

			mov eax, 4
			mov ebx, 1
			mov ecx, msg_output
			mov edx, OUTPUTSIZE
			int 80h
		
			mov eax, [valor]    ;aqui está o numero em int
			mov ebx, soma
			jmp arruma ; "função" que ajusta o endereço que irá mostrar o número

			resultado:
				
				mov eax, 4
				mov ebx, 1
				mov ecx, soma
				mov edx, 10
				int 80h	
		
				mov eax, 4
				mov ebx, 1
				mov ecx, newline
				mov edx, NEWLINESIZE
				int 80h

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Encerra programa
		mov eax, 1
		mov ebx, 0
		int 80h