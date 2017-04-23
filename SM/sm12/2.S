        .text
        .global process

geteip:
        mov     (%esp), %ecx
        ret
process:
        call geteip
        addl $_GLOBAL_OFFSET_TABLE_, %ecx
        movl A@GOT(%ecx), %eax
        movsd (%eax), %xmm0
        movl B@GOT(%ecx), %eax
        movsd (%eax), %xmm1
        addsd %xmm0, %xmm1
        movl $2, %eax
        cvtsi2sd %eax, %xmm2
        divsd %xmm2, %xmm1
        movl C@GOT(%ecx), %eax
        movsd %xmm1, (%eax)
        ret