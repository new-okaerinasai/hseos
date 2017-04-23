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

tree_find:
    pushl %ebp
    movl %esp, %ebp

    subl $12, %esp

    movl 8(%ebp), %eax
    movl %eax, -4(%ebp)

    cmpl $0, -4(%ebp)
    je end_not_found

while_now_not_null:
    cmpl $0, -4(%ebp)
    je check_found

    movl -4(%ebp), %eax
    movsd (%eax), %xmm0
    movsd 12(%ebp), %xmm1
    subsd %xmm0, %xmm1
    subl $8, %esp
    movsd %xmm1, (%esp)
    call my_abs
    fstpl (%esp)
    movsd (%esp), %xmm0
    addl $8, %esp
    comisd kek, %xmm0
    jb check_found
    movl -4(%ebp), %eax
    movsd (%eax), %xmm0
    movsd 12(%ebp), %xmm1
    
    comisd %xmm0, %xmm1
    
    jb right
    ja left

right:
    movl -4(%ebp), %eax
    movl 8(%eax), %eax
    movl %eax, -4(%ebp)
    jmp while_now_not_null
left:
    movl -4(%ebp), %eax
    movl 12(%eax), %eax
    movl %eax, -4(%ebp)

    jmp while_now_not_null

check_found:
    cmpl $0, -4(%ebp)
    je end_not_found
    cmpl $0, 20(%ebp)
    je end_found
    movl -4(%ebp), %eax
    movl 16(%eax), %eax
    movl 20(%ebp), %edx
    movl %eax, (%edx)
    movl %edx, 20(%ebp)

end_found:
    movl $1, %eax
    movl %ebp, %esp
    popl %ebp
    ret
end_not_found:
    movl $0, %eax
    movl %ebp, %esp
    popl %ebp
    ret
