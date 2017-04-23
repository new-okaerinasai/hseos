#include <asm/unistd_32.h>

        .global nextchar
        .global nc
        .data

buf:    .space 4096, 0
cur:    .int 0
nc:     .int 0
len:    .int 0
end:    .int 0

        .text

nextchar:
        pushl %ebx
        cmpl $1, end
        je fail
        movl cur, %eax
        cmpl %eax, len
        je read

        jmp continue
read:
        movl $__NR_read, %eax
        movl $0, %ebx
        movl $buf, %ecx
        movl $4096, %edx
        int $0x80
        
        cmpl $0, %eax
        jle fail
        
        movl %eax, len
        movl $0, cur

continue:
        movl $buf, %eax
        addl cur, %eax
        movzbl (%eax), %eax
        addl $1, cur
        jmp ok


fail:   
        movl $1, end
        movl $-1, %eax
        movl $-1, nc
        jmp fin

ok:     
        movl %eax, nc
fin:        
        popl %ebx
        ret