    .global mystrcmp
    .text
mystrcmp:
    pushl %ebp
    movl %esp, %ebp
move:
    movl 8(%ebp), %eax
    movzbl (%eax), %edx
    movl 12(%ebp), %eax
    movzbl (%eax), %eax
    cmpb %al, %dl
    je check_end
    jne not_equal
check_end:
    movl 8(%ebp), %eax
    movzbl (%eax), %eax
    testb %al, %al
    jne continue
    je equal
continue:
    addl $1, 8(%ebp)
    addl $1, 12(%ebp)
    jmp move
equal:
    movl $0, %eax
    jmp end
not_equal:
    movl    8(%ebp), %eax
    movzbl  (%eax), %eax
    movzbl  %al, %edx
    movl    12(%ebp), %eax
    movzbl  (%eax), %eax
    movzbl  %al, %eax
    subl    %eax, %edx
    movl    %edx, %eax
    jmp end
end:
    movl %ebp, %esp
    popl %ebp
    ret