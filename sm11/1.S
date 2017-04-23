#include <asm/unistd_32.h>
    .global _start
    .text

_start:
read:
    subl $1, %esp
    movl $__NR_read, %eax
    movl $0, %ebx
    movl %esp, %ecx
    movl $1, %edx
    int $0x80

    cmpl $0, %eax
    je end

    movzbl (%esp), %eax
    cmpl $'0', %eax

    jae greater0
    jb not_a_digit
greater0:
    cmpl $'9', %eax
    jbe digit
    ja not_a_digit
digit:
    movl $__NR_write, %eax
    movl $1, %ebx
    subl $1, %esp
    movl $'0', (%esp)
    movl %esp, %ecx
    movl $1, %edx
    int $0x80
    addl $2, %esp
    jmp read
not_a_digit:
    movl $__NR_write, %eax
    movl $1, %ebx
    movl %esp, %ecx
    movl $1, %edx
    int $0x80
    addl $1, %esp
    jmp read
end:
    addl $1, %esp
    movl    $__NR_exit, %eax
    xorl    %ebx, %ebx
    int     $0x80