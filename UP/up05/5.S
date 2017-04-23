#include <asm/unistd_32.h>
    .global main
    .text

main:
        movl $__NR_read, %eax
        movl $0, %ebx
        movl $buf, %ecx
        movl $4096, %edx
        int $0x80
        