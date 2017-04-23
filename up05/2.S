    .text
    .global addbe

addbe:
    pushl %ebx
    pushl %edi
    pushl %esi
    pushl %ebp
    movl %esp, %ebp

    movl 20(%ebp), %ecx
    movl 24(%ebp), %ebx
    movl 28(%ebp), %esi
    movl 32(%ebp), %edi
    leal -1(%ebx, %ecx,), %ebx
    leal -1(%esi, %ecx,), %esi
    leal -1(%edi, %ecx,), %edi
    clc

addi:
    mov (%ebx), %al
    adc (%esi), %al
    mov %al, (%edi)
    dec %ebx
    dec %esi
    dec %edi
    loopnz addi

    movl $0, %eax
    adc $0, %eax

    movl %ebp, %esp
    popl %ebp
    popl %esi
    popl %edi
    popl %ebx
    ret