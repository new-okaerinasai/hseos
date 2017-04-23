    .global process
    .data

format: .asciz "%d"
format_print: .asciz "%d\n"

    .text
process:
    pushl %ebx
    xorl %ebx, %ebx
    subl $4, %esp
    pushl %esp
    pushl $format

read:
    call scanf
    cmpl $-1, %eax
    je end
    movl 8(%esp), %eax
    andl $0xf, %eax
    subl $9, %eax
    cmpl $1, %eax
    ja pass
    cmpl $0, %eax
    jb pass
    jmp *jmptab(, %eax, 4)
pass:
    addl 8(%esp), %ebx
    jmp read
D1:
    movl 8(%esp), %eax
    movl $2, %ecx
    imull %ecx
    addl %eax, %ebx 
    jmp read
D0:
    movl 8(%esp), %eax
    addl $1, %eax
    addl %eax, %ebx
    jmp read
end:
    addl $12, %esp
    pushl %ebx
    pushl $format_print
    call printf
    addl $8, %esp
    popl %ebx
    ret
    
jmptab:
    .int D0, D1