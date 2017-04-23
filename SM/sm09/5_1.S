	.global main
	.extern process
format:
	.asciz "%d %d\n"
main:

    pushl %ebp
    movl %esp, %ebp
	movl $12, %edi
	movl $55, %esi
	call process
	pushl %edi
	pushl %esi
	pushl $format
	call printf
	movl %ebp, %esp
    popl %ebp
	ret