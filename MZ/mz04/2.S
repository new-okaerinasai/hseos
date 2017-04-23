    .global process
    .text

process:
    pushl   %ebp
    movl    %esp, %ebp    
    
    movl 8(%ebp), %eax
    
    imull $3, %eax
    jo end
    
    movl 12(%ebp), %ecx
    imull $2, %ecx
    jo end
    subl %ecx, %eax
    jo end
    jmp end_ok
end:
    movl $0, %eax
    movl %ebp, %esp
    popl %ebp
    ret
end_ok:
    movl 16(%ebp), %ecx
    movl %eax, (%ecx)
    movl $1, %eax
    movl %ebp, %esp
    popl %ebp
    ret