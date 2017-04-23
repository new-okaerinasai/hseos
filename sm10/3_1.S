	.global my_abs, sr
	.text
format:
    .asciz "%.10g\n"

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
    addl $4, %esp
    mulsd %xmm2, %xmm0
    movsd %xmm0, (%esp)   
    fldl (%esp)
    add $8, %esp
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

sr: 
    pushl %ebp
    movl %esp, %ebp
    movsd 8(%ebp), %xmm0
    movsd kek, %xmm1
    subsd %xmm1, %xmm0
    comisd ugar, %xmm0
    jb ti_pidr
    movl %ebp, %esp
    popl %ebp
    ret
ti_pidr:
    pushl $forma
    call printf
    movl %ebp, %esp
    popl %ebp
    ret

    .data
kek: .double 1.222
ugar: .double -1e-1
forma: .asciz "TI PIDR"