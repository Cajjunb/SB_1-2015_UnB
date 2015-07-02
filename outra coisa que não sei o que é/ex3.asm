;       Inputs: As prompted
;       outputs As per input
%include "io.mac"

.DATA
name_msg        db      'please enter your name:', 0
query_msg       db      'How many times to repeat welcome message? ', 0
confirm_msg1    db      'Repeat welcome message ',0
confirm_msg2    db      ' times (y/n) ',0
welcome_msg     db      'Welcome to assembly Language Programming ',0

.UDATA
user_name       resb    16              ;buffer for user name
response        resb    1

.CODE
        .STARTUP
        PutStr  name_msg                ;prompt user for his/her name
        GetStr  user_name,16            ;read name (max. 15 characters)

	ask_count:
	        PutStr  query_msg               ;prompt for repeat count
        	GetInt  CX                      ;read repeat count
	        PutStr  confirm_msg2
        	GetCh   [response]              ;read user response
	        cmp     byte [response],'y'     ;if 'Y' display welcome message
        	jne     ask_count               ;otherwise request repeat count

	display_msg:
        	PutStr  welcome_msg             ;display welcome message
	        PutStr  user_name               ;display teh user name
        	nwln
	        loop    display_msg             ;repeat count times

        .EXIT