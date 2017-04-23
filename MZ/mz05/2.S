    .text
    .global addbe

addbe:
    pushl %ebp
    movl %esp, %ebp
    movl 12(%ebp), %ecx
    movl 16(%ebp), %ebx
    addl 8(%ebp), %ebx
    addl 8(%ebp), %esi
    movl 8(%ebp), %ecx

adding:

    movzbl (%esi), %eax
    movzbl (%ebx), %edx

    addl %eax, %edx
    addl %edi, %edx
    movl $0, %edi
    adcl $0, %edi

    subl $1, %esi
    subl $1, %ebx

    
    loop adding

    movl %ebp, %esp
    popl %ebp
    ret