    .text
    .global extract

extract:
    pushl %ebp
    movl %esp, %ebp
    movl 8(%ebp), %eax
    subl $8, %esp

    movl $32, %ecx
    subl 12(%ebp), %ecx
    subl 16(%ebp), %ecx
    shll %cl, %eax
    movl 16(%ebp), %ecx
    movl $32, %edx
    subl %ecx, %edx
    movl %edx, %ecx
    shrl %cl, %eax
    movl %ebp, %esp
    popl %ebp
    ret