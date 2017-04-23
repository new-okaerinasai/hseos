head:
    .asciz "%d %d %d\n"
    .global print_fib
    .text
    .extern printf
print_fib:
    pushl   %ebp
    movl    %esp, %ebp

    movl A, %eax
    movl B, %ecx
    addl %ecx, %eax
    addl %eax, %ecx
    movl %ecx, %edx
    addl %eax, %edx

    pushl %edx
    pushl %ecx
    pushl %eax
    pushl $head
    call printf

    movl %ebp, %esp
    popl %ebp
    ret
