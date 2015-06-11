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

	SIZE				EQU 6

section .bss
	quociente			resb	10
	resto				resb	1
	numero			resb	1 ; um byte para mostrar um número em ASCII
	auxValor			resb	SIZE*SIZE

section .text
global _start
	

	_start:
		mov ecx, SIZE

		mov ebx, quociente
		mov [quociente + eax + ebx], DWORD 0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Encerra programa
		mov eax, 1
		mov ebx, 0
		int 80h