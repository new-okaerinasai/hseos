	.global main

format:
	.asciz "%d"
main:
	pushl   %ebp
        movl    %esp, %ebp

        subl    $4, %esp
        leal    -4(%ebp), %eax
        pushl   %eax
        pushl   $format
        call    scanf
        
        movl    %eax, %ecx
        
        cmpl    $1, %ecx

        movl    %ebp, %esp
        popl    %ebp
        ret