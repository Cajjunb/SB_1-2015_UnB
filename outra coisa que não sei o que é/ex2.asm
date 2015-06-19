section .data
	msg db 'CANGURU', 0dh, 0ah

section .text
global _start
	_start:
		mov eax, 4
		mov ebx, 1
		mov ecx, msg
		mov edx, 9
		int 80h

		mov ebx, msg
		mov eax, 7

		loop:
			add byte [ebx], 32
			inc ebx
			dec eax
			jnz loop

		mov eax, 4
		mov ebx, 1
		mov ecx, msg
		mov edx, 9
		int 80h

		mov eax, 1
		mov ebx, 0
		int 80h