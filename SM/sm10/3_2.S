    .global tree_find, my_abs
    .data
kek: .double 1e-8
    .text
my_abs:
    push %ebp
    movl %esp, %ebp

    movsd 8(%ebp), %xmm0
    xorps %xmm1, %xmm1
    comisd %xmm1, %xmm0
    ja return_a
    
    sub $8, %esp
    subl $4, %esp
    movl $-1, (%esp)
    cvtsi2sd (%esp), %xmm2
    mulsd %xmm2, %xmm0
    movsd %xmm0, (%esp)   
    fldl (%esp)
    add $12, %esp
    jmp end

return_a:
    sub $8, %esp
    movsd %xmm0, (%esp)   
    fldl (%esp)
    add $8, %esp
end:
    movl %ebp, %esp
    pop %ebp
    ret

/* 
double my_abs(double a) {
    if (a > 0) return a; else return -a;
}*/
/*-----------------------------------------*/
format: .asciz "%.10g\n"
tree_find:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    movsd (%eax), %xmm0
    movsd 12(%ebp), %xmm1
    subsd %xmm0, %xmm1
    subl $8, %esp

    movsd %xmm1, (%esp)
    call my_abs
    fstl (%esp)
    pushl $format
    call printf
    addl $12, %esp

    movl %ebp, %esp
    popl %ebp
    ret