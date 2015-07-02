;       Inputs: As prompted
;       outputs As per input
%include "io.mac"

.DATA
welcome_msg        db      	'Este programa vai criar um arquivo chamado saida.txt', 0
debug1_msg		db		'Abri o arquivo e retornei seu ponteiro em eax, e logo depois salvei em fp', 0
debug2_msg		db		'Fechei o arquivo e o programa vai encerrar', 0
arq					db		'saida.txt',0
write_msg			db		'O rato roeu a roupa do rei de roma', 0
WRITESIZE			EQU 	$-write_msg


.UDATA
fp		resw	1			;ponteiro para memória

.CODE
        .STARTUP
        PutStr  welcome_msg
	nwln                

	mov eax, 8					;abrir arquivo
	mov ebx, arq					;nome do arquivo
	mov ecx, 0x0700				;permissão
	int 80h
	
	mov [fp], eax
	PutStr  debug1_msg 
	nwln    

	mov eax, 4						;escrever do arquivo
	mov ebx, [fp]					;ponteiro do arquivo
	mov ecx, write_msg			;buffer que vai ler do arquivo
	mov edx, WRITESIZE			;tamanho do buffer
	int 80h

	mov eax, 6						;fechar o arquivo
	mov ebx, [fp]					;ponteiro do arquivo
	int 80h
	
	PutStr  debug2_msg
	nwln   

        .EXIT