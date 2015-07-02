%include "io.mac"
.DATA
	prompt_msg1 db "Please input the first number: ",0
	prompt_msg2 db "Please input the second number: ",0
	sum_msg db "The sum is ",0

.UDATA
	number1 resw 1
	number2 resw 1
	result resw 1

.CODE
	
	sum:
		push EBP ; save EBP value
		mov EBP,ESP ; copy TOS into EBP

		push AX
		mov AX,[EBP+10] ;sum = first number
		add AX,[EBP+8] ;sum = sum+second number

		mov [result],AX
		pop AX
		pop EBP
		
	ret 4
	
	.STARTUP
		PutStr prompt_msg1
		GetInt [number1]
		PutStr prompt_msg2
		GetInt [number2]
		push WORD [number1]
		push WORD [number2]
		
		call sum
		PutStr sum_msg
		PutInt [result]

		nwln

	 .EXIT