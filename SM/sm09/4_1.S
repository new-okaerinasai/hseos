	.global max, main, min
	.text

format_scan:
	.asciz "%d%d%d%d"

format_print:
	.asciz "%d\n"

max:
    pushl %ebp
    movl %esp, %ebp
    movl 8(%ebp), %eax
    cmpl 12(%ebp), %eax
    jge a_greater
    movl 12(%ebp), %eax
    jmp end_max
a_greater:
    movl 8(%ebp), %eax
end_max:
    movl %ebp, %esp
    popl %ebp
    ret

min:
    pushl %ebp
    movl %esp, %ebp
    movl 8(%ebp), %eax
    cmpl 12(%ebp), %eax
    jle b_greater
    movl 12(%ebp), %eax
    jmp end_min
b_greater:
    movl 8(%ebp), %eax
end_min:
    movl %ebp, %esp
    popl %ebp
    ret

main:
	pushl %ebp
    movl %esp, %ebp
    
    
	pushl $1
	pushl $2
	call min
	addl $8, %esp

	pushl %ebp
	pushl $format_print
	call printf
	addl $8, %esp
	
    movl %ebp, %esp
    popl %ebp
    ret
