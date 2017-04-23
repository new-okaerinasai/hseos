		.global readu32, main
format: .asciz "%d %d %c\n"
main:
		call nextchar
		call readu32

		pushl nc
		pushl %edx
		pushl %eax

		pushl $format
		call printf
		addl $16, %esp
		ret

