#include <asm/unistd_32.h>
        .global writechar, flush
        .data
buf:    .space 4096, 0
cur:    .int 0

        .text
writechar:
        movl $buf, %edx
        addl cur, %edx
        movb %al, (%edx)
        addl $1, cur
        cmpl $4096, cur
        je flush
        ret

flush:
        pushl %ebx
        movl $__NR_write, %eax
        movl $1, %ebx
        movl $buf, %ecx
        movl cur, %edx
        int $0x80
        movl $0, cur
        popl %ebx
        ret