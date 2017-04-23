#include <asm/unistd_32.h>
    .global _start
    .text

_start:
	movl $__NR_write, %eax
    movl $0, %ebx
    movl $'1', %ecx
    movl $1, %edx
    int $0x80

    movl    $__NR_exit, %eax
    xorl    %ebx, %ebx
    int     $0x80