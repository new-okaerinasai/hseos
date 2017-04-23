    .global satsum
    .text
satsum:
    pushl %ebp
    movl %esp, %ebp
    
    
    movl 8(%ebp), %eax
    
    movl 12(%ebp), %ecx

    addl %ecx, %eax
    jnc end

ovf:
    movl $0, %eax
    notl %eax
    jmp end
    
end:    
    movl %ebp, %esp
    popl %ebp
    ret
