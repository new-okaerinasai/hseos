    .global myhypot
format: .asciz "%.10g"

myhypot:
    pushl %ebp
    movl %esp, %ebp

    movlpd 8(%esp), %xmm0
    movlpd 16(%esp), %xmm1
    movl 24(%esp), %eax
    mulsd %xmm0, %xmm0
    mulsd %xmm1, %xmm1
    addsd %xmm1, %xmm0
    sqrtsd %xmm0, %xmm0
    movsd %xmm0, (%eax)

    movl %ebp, %esp
    popl %ebp
    ret