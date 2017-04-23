		.global main
		.extern process
format: .asciz "%u\n"
main:	
		pushl %ebx
		pushl $format
		call printf
		call process
		pushl %ebx
		pushl $format
		call printf
		addl $16, %esp
		ret