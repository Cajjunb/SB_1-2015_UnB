section .data
	msg db 'Ola mundo de novo', 0dh, 0ah 	;<-------- 0dh + 0ab = CRLF (2 byte)

section .text
global _start

_start:
	mov eax, 4 ;<-------- Syscall de escrever
	mov ebx, 1 ;<-------- Onde escrever: tela
	mov ecx, msg 	;<-------- exc agora contém ponteiro da string
	mov edx, 19 ;<-------- Tamanho da string
	int 80h	;<-------- Syscall

	mov eax, 1
	mov ebx, 0
	int 80h