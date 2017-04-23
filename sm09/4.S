    .global max, process, min
    .text

format_scan:
    .asciz "%d%d%d%d"

format_print:
    .asciz "%0x%x\n"

max:
    pushl %ebp
    movl %esp, %ebp
    movl 8(%ebp), %eax
    cmpl 12(%ebp), %eax
    jge a_greater
    movl 12(%ebp), %eax
    jmp end_max
a_greater:
    movl 8(%ebp), %eax
end_max:
    movl %ebp, %esp
    popl %ebp
    ret

min:
    pushl %ebp
    movl %esp, %ebp
    movl 8(%ebp), %eax
    cmpl 12(%ebp), %eax
    jle b_greater
    movl 12(%ebp), %eax
    jmp end_min
b_greater:
    movl 8(%ebp), %eax
end_min:
    movl %ebp, %esp
    popl %ebp
    ret

process:
    andl $-16, %esp
    pushl %esi
    pushl %edi
    pushl %ebx
    pushl %ebp
    movl %esp, %ebp
    movl $0, %esi
scan:
    subl $16, %esp
    leal 8(%ebp), %eax
    pushl %eax
    leal 12(%ebp), %eax
    pushl %eax
    leal 16(%ebp), %eax
    pushl %eax
    leal 20(%ebp), %eax
    pushl %eax
    pushl $format_scan
    call scanf    
    addl $20, %esp
    cmpl $-1, %eax
    je end

    pushl 20(%ebp)
    pushl 12(%ebp)
    call max
    addl $8, %esp
    movl %eax, %edi

    pushl 16(%ebp)
    pushl 8(%ebp)
    call min
    addl $8, %esp
    movl %eax, %ebx

    cmpl %edi, %ebx
    jg ok
    jmp scan

ok: 
    subl %edi, %ebx
    addl %ebx, %esi
    jmp scan

end:
    movl %ebp, %esp
    popl %ebp
    popl %ebx
    popl %edi
    popl %esi
    andl $-16, %esp
    ret
