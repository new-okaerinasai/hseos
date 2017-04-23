    .global process
    .text
head:
    .asciz "%llu\n"
process:
    pushl %esi
    pushl %edi
    pushl   %ebp
    movl    %esp, %ebp
    
    movl A, %eax
    movl A + 4, %edx
    
    shldl $1, %eax, %edx
    shll %eax

    movl B, %esi
    movl B + 4, %edi

    shrdl $1, %edi, %esi
    shrl %edi

    subl %esi, %eax
    sbbl %edi, %edx
    pushl %edx
    pushl %eax
    pushl $head

    call printf

    movl %ebp, %esp

    popl %ebp
    popl %edi
    popl %esi
    ret