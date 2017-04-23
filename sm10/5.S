    .global mul64p
    .text
format: .asciz "%llx%016llx\n"
format_no: .asciz "%llx\n"
mul64p:
    pushl %ebx
    pushl %esi
    pushl %ebp
    movl %esp, %ebp
    subl $96, %esp

    movl $0, %eax
    movl $0, %ecx
    movl $0, %esi

    movl %eax, -56(%ebp)
    movl %eax, -60(%ebp)
    movl %eax, -64(%ebp)
    movl %eax, -68(%ebp)


    movl 16(%ebp), %eax
    mull 24(%ebp)
    movl %edx, %ecx
    movl %eax, -56(%ebp)

    movl 20(%ebp), %eax
    mull 24(%ebp)
    addl %ecx, %eax
    adcl $0, %edx
    movl %eax, %ebx
    movl %edx, %ecx

    movl 16(%ebp), %eax
    mull 28(%ebp)
    addl %ebx, %eax
    movl %eax, -60(%ebp)
    adcl %edx, %ecx
    adcl $0, %esi

    movl 20(%ebp), %eax
    mull 28(%ebp)
    addl %ecx, %eax
    adcl $0, %edx
    addl %esi, %edx
    adcl $0, %edx
    movl %eax, -64(%ebp)
    movl %edx, -68(%ebp)

    cmpl $0, %edx
    jne non_zero
    cmpl $0, %eax
    jne non_zero
    jmp zeros_0

non_zero:
    pushl -60(%ebp)
    pushl -56(%ebp)
    pushl -68(%ebp)
    pushl -64(%ebp)
    pushl $format
    call printf
    jmp end

zeros_0:
    pushl -60(%ebp)
    pushl -56(%ebp)
    pushl $format_no
    call printf
    jmp end

end:
    movl %ebp, %esp
    popl %ebp
    popl %esi
    popl %ebx
    ret