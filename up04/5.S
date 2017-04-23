    .global process, compare
    .text

compare:
    pushl %ebp
    movl %esp, %ebp
    subl $8, %esp
    movl 8(%ebp), %eax
    movl (%eax), %eax
    movl %eax, -4(%ebp)
    movl 12(%ebp), %edx
    movl (%edx), %edx
    movl %edx, -8(%ebp)

    movl -8(%ebp), %ecx
    popcnt -8(%ebp), %edx
    popcnt -4(%ebp), %eax

    cmpl %eax, %edx
    je equal
    subl %edx, %eax
    jmp end

equal:
    movl -4(%ebp), %eax
    movl -8(%ebp), %edx
    subl %eax, %edx
    movl %edx, %eax
end:
    movl %ebp, %esp
    popl %ebp
    ret

process:
    pushl %ebp
    movl %esp, %ebp

    movl $4, %eax
    
    pushl $compare
    pushl %eax
    pushl 12(%ebp)
    pushl 8(%ebp)
    call qsort

    movl %ebp, %esp
    popl %ebp
    ret