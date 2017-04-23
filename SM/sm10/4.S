    .global dot_product
    .text
dot_product:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%esp), %ecx
    cmpl $0, %ecx
    je end_not
    movl 12(%esp), %eax
    movl 16(%esp), %edx
    xorps %xmm2, %xmm2

mult:
    movlps (%eax), %xmm0
    movlps (%edx), %xmm1
    mulps %xmm1, %xmm0
    addss %xmm0, %xmm2
    addl $4, %eax
    addl $4, %edx
    loop mult

    subl $4, %esp
    movss %xmm2, (%esp)
    flds (%esp)
    addl $4, %esp

    movl %ebp, %esp
    popl %ebp
    ret
end_not:
    xorps %xmm2, %xmm2
    subl $4, %esp
    movss %xmm2, (%esp)
    flds (%esp)
    addl $4, %esp

    movl %ebp, %esp
    popl %ebp
    ret