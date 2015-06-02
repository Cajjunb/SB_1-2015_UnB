section .data
	msg_welcome 	db 'Bem vindo!'
	WELCOMESIZE	EQU $-msg_welcome

	msg_quociente 		db 'Quociente:'
	QUOCIENTESIZE			EQU $-msg_quociente

	msg_resto 		db 'Resto:'
	RESTOSIZE		EQU $-msg_resto

msg_debug1		db ' passou1:  '
	DEBUG1SIZE		EQU $-msg_debug1

msg_debug2		db ' passou2: '
	DEBUG2SIZE		EQU $-msg_debug2

	newline			db 0dh, 0ah
	NEWLINESIZE		EQU $-newline

section .bss
	quociente			resb	10
	resto				resb	1
	numero			resb	1 ; um byte para mostrar um número em ASCII
	auxValor			resb	4

section .text
global _start
	
	;--Argumentos
	; eax: número
	;ebx: endereço de memória
	arruma: 
			;add eax, 0x30
			;mov [ebx], eax
			
			cmp eax, 10
			jb preparaVolta
		
			mov ecx, 10
			mov edx, 0x0
			div ecx

			add edx, 0x30
			mov ecx, [ebx]
			shl ecx, 8
			or ecx, edx
			mov [ebx], ecx

			jmp arruma

			preparaVolta:

				add eax, 0x30
				mov ecx, [ebx]
				shl ecx, 8
				or ecx, eax
				mov [ebx], ecx

			jmp fim

	_start:

		mov eax, 3014
		mov ebx, 10
		
		mov edx, 0x0
		div ebx	; divide edx.eax/ebx----------> eax = quociente, edx = resto
		
		add edx, 0x30
		mov [resto], edx
		
		mov ebx, quociente
		jmp arruma

		fim:
			mov eax, 4
			mov ebx, 1
			mov ecx, newline
			mov edx, NEWLINESIZE
			int 80h

			mov eax, 4
			mov ebx, 1
			mov ecx, msg_quociente
			mov edx, QUOCIENTESIZE
			int 80h

			mov eax, 4
			mov ebx, 1
			mov ecx, quociente
			mov edx, 10
			int 80h

			mov eax, 4
			mov ebx, 1
			mov ecx, newline
			mov edx, NEWLINESIZE
			int 80h
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			mov eax, 4
			mov ebx, 1
			mov ecx, newline
			mov edx, NEWLINESIZE
			int 80h

			mov eax, 4
			mov ebx, 1
			mov ecx, msg_resto
			mov edx, RESTOSIZE
			int 80h

			mov eax, 4
			mov ebx, 1
			mov ecx, resto
			mov edx, 1
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