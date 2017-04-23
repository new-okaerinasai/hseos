		.global main, writechar, flush
		.text
form:   .asciz "%d\n"
main:
		movl $4096, %ecx
lol:	
		movl %ecx, %esi
		movl $'a', %eax
		call writechar
		movl %esi, %ecx
		loop lol
		pushl cur
		pushl $form
		call printf
		addl $8, %esp
		ret