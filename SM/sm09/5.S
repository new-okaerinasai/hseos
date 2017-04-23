    .global process
    .text
format:
    .asciz "%d"

format_nl: .asciz "%d\n"

process:
    pushl %esi
    pushl %edi
    pushl %ebp
    movl %esp, %ebp
    
    

    leal -8(%ebp), %eax
    pushl %eax
    pushl $format
    call scanf
    cmpl $0, -8(%ebp)
    je end
    movl -8(%ebp), %ecx
    movl -8(%ebp), %edi

scan:
    movl %ecx, %esi
    subl $4, %esp
    leal 4(%esp), %eax
    pushl %eax
    pushl $format
    call scanf
    addl $8, %esp
    movl %esi, %ecx
    loop scan

    addl $4, %esp
    movl %edi, %ecx

print:
    movl %ecx, %edi
    pushl $format_nl
    call printf
    addl $8, %esp
    movl %edi, %ecx
    loop print
end:
    movl %ebp, %esp
    popl %ebp

    popl %edi
    popl %esi
    ret
