    .global mystrspn
    .text
    
mystrspn:    
    pushl %ebp
    movl %esp, %ebp
    subl $24, %esp

    movl 8(%ebp), %eax
    movl %eax, -4(%ebp)

    movl 12(%ebp), %eax
    movl %eax, -8(%ebp)

    movl $0, -12(%ebp)

while_x_not_end:
    movl -4(%ebp), %eax
    movzbl (%eax), %eax
    testb %al, %al
    je end

while_accept_not_end:
    movl 12(%ebp), %eax
    movzbl (%eax), %eax
    testb %al, %al
    je accept_end

    movl 12(%ebp), %eax
    movzbl (%eax), %edx
    movl -4(%ebp), %eax
    movzbl (%eax), %eax
    cmpb %al, %dl
    jne check_accept_end_inside

    addl $1, -12(%ebp)
    movl -8(%ebp), %eax
    movl %eax, 12(%ebp)
    jmp accept_end

check_accept_end_inside:
    movl 12(%ebp), %eax
    movzbl (%eax), %eax
    testb %al, %al
    jne continue
    jmp end

continue:
    addl $1, 12(%ebp)
    jmp while_accept_not_end

accept_end:
    addl $1, -4(%ebp)
    jmp while_x_not_end

end:
    movl -12(%ebp), %eax
    movl %ebp, %esp
    popl %ebp
    ret
