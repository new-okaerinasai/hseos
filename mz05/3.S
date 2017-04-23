    .global myexp

myexp:
    pushl %ebp
    movl %esp, %ebp
    movl $1, %eax
    cvtsi2sd %eax, %xmm0
    movsd 8(%ebp), %xmm1
    movsd 8(%ebp), %xmm4
    xorpd %xmm2, %xmm2
    xorpd %xmm3, %xmm3
    movsd %xmm1, %xmm2
    movsd %xmm1, %xmm3
    addsd %xmm0, %xmm3
    movl $2, %ecx
    /*
        old = xmm0, new = xmm1, old_sum = xmm2, new_sum = xmm3
        x = xmm4, ecx = xmm5
    */
iter:    
    comisd %xmm2, %xmm3
    je end

    movsd %xmm3, %xmm2
    movsd %xmm1, %xmm0
    mulsd %xmm4, %xmm1
    cvtsi2sd %ecx, %xmm5
    divsd %xmm5, %xmm1
    addsd %xmm1, %xmm3
    addl $1, %ecx
    jmp iter

end:
    movl 16(%ebp), %eax
    movsd %xmm3, (%eax)
    movl %ebp, %esp
    popl %ebp
    ret