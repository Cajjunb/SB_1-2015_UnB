;       Inputs: As prompted
;       outputs As per input
%include "io.mac"

.DATA
welcome_msg        db      	'Este programa vai abrir um arquivo e escrever o que tem nele', 0
debug1_msg		db		'Abri o arquivo e retornei seu ponteiro em eax, e logo depois salvei em fp', 0
debug2_msg		db		'Fechei o arquivo e o programa vai encerrar', 0
arq					db		'arq.txt',0		;arquivo tem 32 bytes no total

.UDATA
buffer	resb    	33              	;buffer para pegar tudo o que tem no arquivo. +1 para EOF
fp		resb	32			;ponteiro para memória

.CODE
        .STARTUP
        PutStr  welcome_msg
	nwln                

	mov eax, 5						;abrir arquivo
	mov ebx, arq					;nome do arquivo
	mov ecx, 0						;modo de abertura do arquivo (slide 23 - aula 15)
	mov edx, 0x0700				;permissão
	int 80h
	
	mov [fp], eax
	PutStr  debug1_msg 
	nwln    

	mov eax, 3						;ler do arquivo
	mov ebx, [fp]					;ponteiro do arquivo
	mov ecx, buffer				;buffer que vai ler do arquivo
	mov edx, 33					;tamanho do buffer
	int 80h

	PutStr  buffer
	nwln 

	mov eax, 6						;fechar o arquivo
	mov ebx, [fp]					;ponteiro do arquivo
	int 80h
	
	PutStr  debug2_msg
	nwln   

        .EXIT